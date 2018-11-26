// This class is composed of several component classses
// These classes include the following:
//
//    EnzoEquationOfState:       Equation of State for Gas
//    EnzoReconstructor:         Reconstructs primitive variables
//    EnzoRiemann:               Solves the Riemann Problem
//    EnzoConstrainedTransport:  Performs constrained transport
//
// Some notes on implementation
//    - this Method tracks energy density, (referred to as energy density)
//
//    Grouping Objects
//    ----------------
//    Implementation relies upon passing around instances of the Grouping
//    object between different object methods. Originally attempted to pass
//    around vectors of field ids, but that doesn't offer nearly as much
//    flexibility. In particular:
//        - It would make it more difficult to add new fields without altering
//          the interface (e.g. optionally using a dual energy formalism,
//          species, colors, Cosmic Ray energy density and flux density)
//        - Relatedly, by sharing common group names between different grouping
//          objects it is easier to load in relevant fields representing
//          different physical quantities (e.g. Groupings of fluxes and
//          conserved variables each have a "momentum" group)
//
//    Presently we track 9 different groupings:
//        - conserved quantities, primitive quantities, reconstructed left/right
//          primitive fields, fluxes in the x/y/z direction, (edge centered
//          electric fields, and temp conserved quantities (to store values at
//          the half timestep)
//        - several groups only contain 1 field (e.g. the "density" and
//          "total_energy" groups). In effect, they serve as alias names for
//          the fields
//        - This implementation relies on the fact that the fields in a
//          Grouping are sorted alphabetically (in this way the fields in the
//          "momentum" group are always ordered "momentum_x","momentum_y",
//          "momentum_z"
//        - The conserved quantities grouping and temp conserved quantities
//          grouping each always contain groups called "density", "momentum",
//          "total_energy", "bfield" (cell-centered B-fields), "bfieldi"
//          (longitudinal B-fields centered at interface between cells). The
//          x/y/z flux groupings contain the same groups except it does not
//          have a "bfieldi" group.
//
//    The number of tracked Groupings could be reduced drastically if we could
//    track histories of fields temporarily, and if we could easily search for
//    fields by specifying multiple group tags.

#ifndef ENZO_ENZO_METHOD_VLCT_HPP
#define ENZO_ENZO_METHOD_VLCT_HPP

class EnzoEquationOfState;
class EnzoReconstructor;
class EnzoRiemann;
class EnzoConstrainedTransport;

// Define the lists of groups in Grouping - these lists need to be updated as
// more physics are added (e.g. dual energy formalism, CR Energy & Flux,
// Species, colors)

// The following list only contains cell-centered conserved quantities
// conserved_group_, temp_conserved_group, xflux_group, yflux_group, and
// zflux_group all will include a single subset of groups in the following list
std::string cons_group_names[4] = {"density", "momentum", "total_energy",
				   "bfield"};
int num_cons_names = 4;
// Note: conserved_group_, temp_conserved_group will always have an additional
// group: "bfieldi" (stores the longitudinal Bfields at the interface of cells)

// The following list contains the names of groups of primitive quantities
// primitive_group_, priml_group, and primr_group all will have the same subset
// of 
std::string prim_group_names[4] = {"density", "velocity", "pressure",
				   "bfield"};
int num_prim_names = 4;



// define 2 helper functions for reading in Grouping fields
enzo_float* load_grouping_field_(Field *field, Grouping *grouping,
				 std::string group_name, int index)
{
  int size = grouping->size(group_name);
  if ((size == 0) || (size>=index)){
    return NULL;
  }
  return (enzo_float *) field->values(grouping->item(group_name,i));
}

// Load fields with 3 dimensions. If there are not 3 dimensions, does not
// load anything. field_i, field_j, and field_k are a cyclic permutation of
// dimensions x, y, and z. The value of ith_dim sets the dimension of field_i
// (0 <-> x, 1 <-> y, 2 <-> z)
void load_dimensional_group_fields_(Field *field, Grouping *grouping,
				    std::string group_name, int ith_dim,
				    enzo_float **field_i, enzo_float **field_j,
				    enzo_float **field_k)
{
  int size = grouping->size(group_name);
  if ((size == 0) || (size>3)){
    return;
  } else if ((ith_dim < 0) || (ith_dim>2)) {
    return;
  }

  int i = ith_dim;
  int j = (i+1)%3;
  int k = (i+2)%3;

  *field_i = (enzo_float *) field->values(grouping->item(group_name,i));
  *field_j = (enzo_float *) field->values(grouping->item(group_name,j));
  *field_k = (enzo_float *) field->values(grouping->item(group_name,k));
}



class EnzoMethodVlct : public Method {

  /// @class    EnzoMethodVlct
  /// @ingroup  Enzo
  /// @brief    [\ref Enzo] Encapsulate VL + CT MHD method

public: // interface

  /// Create a new EnzoMethodVlct object
  EnzoMethodVlct();

  /// Charm++ PUP::able declarations
  PUPable_decl(EnzoMethodVlct);
  
  /// Charm++ PUP::able migration constructor
  EnzoMethodVlct (CkMigrateMessage *m)
    : Method (m),
      eos_(NULL),
      half_dt_recon_(NULL),
      full_dt_recon_(NULL),
      riemann_solver_(NULL)
  {
    // We want to pack/unpack Groupings in the future.
    conserved_group_ = new Grouping;
    primitive_group_ = new Grouping;
    setup_groups_();
  }

  /// CHARM++ Pack / Unpack function
  void pup (PUP::er &p);

  /// Delete EnzoMethodVlct object
  ~EnzoMethodVlct();

  /// Apply the method to advance a block one timestep 
  virtual void compute( Block * block) throw();

  virtual std::string name () throw () 
  { return "vlct"; }

  /// Compute maximum timestep for this method
  virtual double timestep ( Block * block) const throw();

protected: // methods

  // Prepare the group
  void setup_groups_();

  // not sure if I will pass field_ids and blocks or arrays
  // not sure if this should be static
  void compute_flux_(Block *block, int dim, Grouping &cur_cons_group,
		     Grouping &priml_group, Grouping &primr_group,
		     Grouping &flux_group, EnzoReconstructor &reconstructor);

  // compute the Electric fields using the fluxes and cell-centered
  // primitives
  void compute_efields_(Block *block, Grouping &xflux_group,
			Grouping &yflux_group, Grouping &zflux_group,
			int center_efield_id, Grouping &efield_group,
			EnzoConstrainedTransport &ct);

  // adds flux divergence to the fields listed in conserved_group_ and stores
  // the results in out_cons_group (this can be the same as conserved_group_)
  void update_quantities_(Block *block, Grouping &xflux_group,
			  Grouping &yflux_group, Grouping &zflux_group,
			  Grouping &out_cons_group, double dt);

  // allocate the temporary fields needed for scratch space and store their ids
  // efield_ids refer to efields centered on the edges of cells
  void allocate_temp_fields_(Block *block, Grouping &priml_group,
			     Grouping &primr_group, Grouping &xflux_group,
			     Grouping &yflux_group, Grouping &zflux_group,
			     Grouping &efield_group, int &center_efield_id,
			     Grouping &temp_conserved_group);

  // deallocate the temporary fields used for scratch space
  void deallocate_temp_fields_(Block *block, Grouping &priml_group,
			       Grouping &primr_group, Grouping &xflux_group,
			       Grouping &yflux_group, Grouping &zflux_group,
			       Grouping &efield_group, int center_efield_id,
			       Grouping &temp_conserved_group);

protected: // attributes

  // tracked_quan_ and temp_quan_ are the same, except that tracked_quan_
  // includes conserved fields tracked over time steps while temp_quan_
  // includes temporary fields temporarily allocated for a single timestep
  // In a lot of senses, these will serve as aliases
  Grouping *conserved_group_;
  Grouping *primitive_group_;
  
  EnzoEquationOfState *eos_;
  EnzoReconstructor *half_dt_recon_;
  EnzoReconstructor *full_dt_recon_;
  EnzoRiemann *riemann_solver_;

};

#endif /* ENZO_ENZO_METHOD_VLCT_HPP */
