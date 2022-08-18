// See LICENSE_CELLO file for license and copyright information

/// @file     enzo_EnzoMethodStarNet.cpp
/// @author   William Hicks (whicks@ucsd.edu)
/// @date     Fri Apr  2 17:05:23 PDT 2010
/// @brief    Implements the EnzoMethodStarNet class

#include "cello.hpp"

#include "enzo.hpp"

//----------------------------------------------------------------------

EnzoMethodStarNet::EnzoMethodStarNet ()
  : Method()
{
#ifdef CONFIG_USE_TORCH
  // Initialize default Refresh object

  cello::simulation()->refresh_set_name(ir_post_,name());
  Refresh * refresh = cello::refresh(ir_post_);
  refresh->add_all_fields();
#endif
}

//----------------------------------------------------------------------

void EnzoMethodStarNet::pup (PUP::er &p)
{

  // NOTE: change this function whenever attributes change

  TRACEPUP;

  Method::pup(p);

#ifdef CONFIG_USE_TORCH

#endif
}

//----------------------------------------------------------------------

void EnzoMethodStarNet::compute ( Block * block) throw()
{

  if (block->is_leaf()) {
    compute_ (block);
  }

  block->compute_done();
}

//----------------------------------------------------------------------

double EnzoMethodStarNet::timestep ( Block * block ) throw()
{
  return std::numeric_limits<double>::max();
}

//======================================================================

void EnzoMethodStarNet::compute_ (Block * block) throw()
{
#ifdef CONFIG_USE_TORCH
  torch::jit::script::Module module;
  const std::string model = "/home1/07320/whick002/StarNetRuntime/model_checkpoints/smalldense.jtpt";
  // Deserialize the ScriptModule from a file using torch::jit::load().
  module = torch::jit::load(model); //, c10::nullopt);
  std::cout << "loaded module\n";
#endif
}
