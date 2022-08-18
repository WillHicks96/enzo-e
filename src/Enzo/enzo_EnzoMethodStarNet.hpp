// See LICENSE_CELLO file for license and copyright information

/// @file     enzo_EnzoMethodStarNet.hpp
/// @author   William Hicks (whicks@ucsd.edu) 
/// @date     Thu Apr  1 16:14:38 PDT 2010
/// @brief    [\ref Enzo] Declaration of EnzoMethodStarNet
///           Inference model for Pop III star formation and feedback.
//            Uses neural networks designed and trained by Azton Wells

#ifndef ENZO_ENZO_METHOD_STARNET_HPP
#define ENZO_ENZO_METHOD_STARNET_HPP

class EnzoMethodStarNet : public Method {

  /// @class    EnzoMethodHeat
  /// @ingroup  Enzo
  ///
  /// @brief [\ref Enzo] Demonstration method to solve heat equation
  /// using forward Euler method

public: // interface

  /// Create a new EnzoMethodHeat object
  EnzoMethodStarNet();

  /// Charm++ PUP::able declarations
  PUPable_decl(EnzoMethodStarNet);
  
  /// Charm++ PUP::able migration constructor
  EnzoMethodStarNet (CkMigrateMessage *m)
    : Method (m)
  { }

  /// CHARM++ Pack / Unpack function
  void pup (PUP::er &p) ;
  
  /// Apply the method to advance a block one timestep 
  virtual void compute( Block * block ) throw();

  virtual std::string name () throw () 
  { return "starnet"; }

  /// Compute maximum timestep for this method
  virtual double timestep ( Block * block ) throw();

protected: // methods

  void compute_ (Block * block ) throw();

protected: // attributes

};

#endif /* ENZO_ENZO_METHOD_STARNET_HPP */
