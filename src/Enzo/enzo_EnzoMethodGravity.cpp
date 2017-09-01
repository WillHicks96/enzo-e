// See LICENSE_CELLO file for license and copyright information

/// @file     enzo_EnzoMethodGravity.cpp
/// @author   James Bordner (jobordner@ucsd.edu)
/// @date     2016-11-07
/// @brief    Implements the EnzoMethodGravity class


#include "cello.hpp"
#include "enzo.hpp"

// #define DEBUG_METHOD

#ifdef DEBUG_METHOD
#   define TRACE_METHOD(METHOD,BLOCK)					\
  CkPrintf ("%d %s:%d %s TRACE %s %p\n",CkMyPe(),__FILE__,__LINE__, \
	    BLOCK->name().c_str(),METHOD,this);			    \
  fflush(stdout);
#else
#   define TRACE_METHOD(METHOD,BLOCK) /*  */ 
#endif
//----------------------------------------------------------------------

EnzoMethodGravity::EnzoMethodGravity
(const FieldDescr * field_descr,
 int index_solver,
 double grav_const,
 bool accumulate)
  : Method(),
    index_solver_(index_solver),
    grav_const_(grav_const)
{
  const int ir = add_refresh(4,0,neighbor_leaf,sync_barrier);
  const int id  = field_descr->field_id("density");
  const int idt = field_descr->field_id("density_total");
  const int ib  = field_descr->field_id("B");
  const int idensity = (idt != -1) ? idt : id;

  // Refresh adds density_total field faces and one layer of ghost
  // zones to "B" field

  if (accumulate) {
    // Accumulate is used when particles are deposited into density_total.
    refresh(ir)->add_field_src_dst(idensity,ib);
    refresh(ir)->set_accumulate(true);
  } else {
    // WARNING: accumulate cannot be used with AMR yet [170818]
    refresh(ir)->add_all_fields();
  }
}

//----------------------------------------------------------------------

void EnzoMethodGravity::compute(Block * block) throw()
{

  TRACE_METHOD("compute()",block);

  // Initialize the linear system

  Field field = block->data()->field();

  Matrix * A = new EnzoMatrixLaplace;
  const int ix = field.field_id ("potential");

  /// access problem-defining fields for eventual RHS and solution
  const int ib = field.field_id ("B");
  const int id  = field.field_id("density");
  const int idt = field.field_id("density_total");
  const int idensity = (idt != -1) ? idt : id;
  
  // Solve the linear system
  int gx,gy,gz;
  int mx,my,mz;
  field.dimensions (0,&mx,&my,&mz);
  field.ghost_depth(0,&gx,&gy,&gz);

  enzo_float * B = (enzo_float*) field.values (ib);
  enzo_float * D = (enzo_float*) field.values (idensity);

  TRACE_FIELD("B",B,1.0);

  for (int iz=0; iz<mz; iz++) {
    for (int iy=0; iy<my; iy++) {
      for (int ix=0; ix<mx; ix++) {
	int i = ix + mx*(iy + my*iz);
	D[i]  += B[i];
      }
    }
  }

  TRACE_FIELD("density-total",D,1.0);

  EnzoPhysicsCosmology * cosmology = (EnzoPhysicsCosmology * )
    block->simulation()->problem()->physics("cosmology");

  if (block->is_leaf()) {
    if (cosmology) {

      enzo_float a,dadt;
      double time = block->time();
      double dt   = block->dt();
      cosmology-> compute_expansion_factor (&a,&dadt,time+0.5*dt);
    
      for (int iz=0; iz<mz; iz++) {
	for (int iy=0; iy<my; iy++) {
	  for (int ix=0; ix<mx; ix++) {
	    int i = ix + mx*(iy + my*iz);
	    B[i]  = -(D[i] - 1.0)/a;
	  }
	}
      }

  } else {

    field.scale(ib, -4.0 * (cello::pi) * grav_const_, idensity);

  }
 } else {
  for (int i=0; i<mx*my*mz; i++) B[i] = 0.0;
 }
  
  //  TRACE_FIELD("density-shift",D,1.0);


  TRACE_FIELD("density-rhs",B,-1.0);

  Solver * solver = block->simulation()->problem()->solver(index_solver_);
  
  // May exit before solve is done...
  solver->set_callback (CkIndex_EnzoBlock::r_method_gravity_continue());

  
  solver->apply (A, ix, ib, block);

}

//----------------------------------------------------------------------

void EnzoBlock::r_method_gravity_continue()
{

  TRACE_METHOD("r_method_gravity_end()",this);

  // So do refresh with barrier synch (note barrier instead of
  // neighbor synchronization otherwise will conflict with Method
  // refresh ("Charm++ fatal error: mis-matched client callbacks in
  // reduction messages")

  Refresh refresh (4,0,neighbor_leaf, sync_barrier);
  refresh.set_active(is_leaf());
  refresh.add_all_fields();

  refresh_enter(CkIndex_EnzoBlock::r_method_gravity_end(NULL),&refresh);

}

//----------------------------------------------------------------------

void EnzoBlock::r_method_gravity_end(CkReductionMsg * msg)
{
  TRACE_METHOD("r_method_gravity_end()",this);
  
  delete msg;
  
  Field field = data()->field();
  int gx,gy,gz;
  int mx,my,mz;
  field.dimensions (0,&mx,&my,&mz);
  field.ghost_depth(0,&gx,&gy,&gz);
  enzo_float * potential = (enzo_float*) field.values ("potential");
  TRACE_FIELD("potential",potential,-1.0);
  
  /// compute acceleration fields from potential
  int order;
  EnzoComputeAcceleration compute_acceleration(data()->field().field_descr(),
					       rank(), order=2);

  compute_acceleration.compute(this);

  // Clear "B" field for next call since on entry adding density to B

  enzo_float * B = (enzo_float*) field.values("B");
  for (int i=0; i<mx*my*mz; i++) B[i] = 0.0;

  // wait for all Blocks before continuing
  compute_done();
}

//----------------------------------------------------------------------

double EnzoMethodGravity::timestep (Block * block) const throw()
{
  Field field = block->data()->field();
  
  int precision = field.precision(0);

  if      (precision == precision_single)
    return timestep_<float>      (block);
  else if (precision == precision_double)
    return timestep_<double>     (block);
  else if (precision == precision_quadruple)
    return timestep_<long double>(block);
  else 
    ERROR1("EnzoMethodGravity()", "precision %d not recognized", precision);
}

//----------------------------------------------------------------------

template <class T>
double EnzoMethodGravity::timestep_ (Block * block) const throw()
{
  Field field = block->data()->field();

  int nx,ny,nz;
  int mx,my,mz;
  int gx,gy,gz;
  field.size         (&nx,&ny,&nz);
  field.dimensions (0,&mx,&my,&mz);
  field.ghost_depth(0,&gx,&gy,&gz);

  T * ax = (T*) field.values ("acceleration_x");
  T * ay = (T*) field.values ("acceleration_y");
  T * az = (T*) field.values ("acceleration_z");

  T dt = std::numeric_limits<T>::max();

  double hx,hy,hz;
  block->cell_width(&hx,&hy,&hz);
  
  if (ax) {
    for (int ix=gx; ix<nx+gx; ix++) {
      for (int iy=gy; iy<ny+gy; iy++) {
	for (int iz=gz; iz<nz+gz; iz++) {
	  int i=ix + mx*(iy + iz*my);
	  dt = std::min(T(dt),T(sqrt(hx/(fabs(ax[i]+1e-20)))));
	}
      }
    }
  }
  if (ay) {
    for (int ix=gx; ix<nx+gx; ix++) {
      for (int iy=gy; iy<ny+gy; iy++) {
	for (int iz=gz; iz<nz+gz; iz++) {
	  int i=ix + mx*(iy + iz*my);
	  dt = std::min(T(dt),T(sqrt(hy/(fabs(ay[i]+1e-20)))));
	}
      }
    }
  }
  if (az) {
    for (int ix=gx; ix<nx+gx; ix++) {
      for (int iy=gy; iy<ny+gy; iy++) {
	for (int iz=gz; iz<nz+gz; iz++) {
	  int i=ix + mx*(iy + iz*my);
	  dt = std::min(T(dt),T(sqrt(hz/(fabs(az[i]+1e-20)))));
	}
      }
    }
  }

  return 0.5*dt;
}