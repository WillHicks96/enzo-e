// See LICENSE_CELLO file for license and copyright information

/// @file     Enzo/hydro-mhd/hydro-mhd.hpp
/// @author   Matthew Abruzzo (matthewabruzzo@gmail.com)
/// @date     2023-05-30
/// @brief    Include file for hydro-mhd subcomponent within the \ref Enzo layer

#ifndef ENZO_HYDROMHD_HYDROMHD_HPP
#define ENZO_HYDROMHD_HYDROMHD_HPP

//----------------------------------------------------------------------
// System includes
//----------------------------------------------------------------------

#include <array>
#include <string>
#include <vector>

//----------------------------------------------------------------------
// Component dependencies
//----------------------------------------------------------------------

#include "Cello/cello.hpp"

#include "Cello/mesh.hpp"    // Block
#include "Cello/problem.hpp" // Method
#include "Cello/view.hpp" // CelloView

#include "Enzo/enzo.hpp" // enzo_float, EnzoConfig, EFltArrayMap

// in the future, the following should be removed from this header file
// (there's no NEED for it to be a transitive dependency for anything that
//  depends on the hydro-mhd dependency)
// - currently, it needs to be included after the headers defining
//   EnzoEFltArrayMap, EnzoCenteredFieldRegistry, & EnzoEOSVariant
// - TODO: make the Riemann Header Self-contained
#include "Enzo/hydro-mhd/riemann/EnzoRiemann.hpp"

//----------------------------------------------------------------------
// Component Headers
//----------------------------------------------------------------------

#include "Enzo/hydro-mhd/toolkit/EnzoIntegrationQuanUpdate.hpp"
#include "Enzo/hydro-mhd/toolkit/EnzoLazyPassiveScalarFieldList.hpp"
#include "Enzo/hydro-mhd/toolkit/EnzoSourceGravity.hpp"
#include "Enzo/hydro-mhd/toolkit/EnzoSourceInternalEnergy.hpp"

// [order dependencies:]
#include "Enzo/hydro-mhd/toolkit/EnzoReconstructor.hpp"
#include "Enzo/hydro-mhd/toolkit/EnzoReconstructorNN.hpp"
#include "Enzo/hydro-mhd/toolkit/EnzoReconstructorPLM.hpp"

// [order dependencies:]
#include "Enzo/hydro-mhd/toolkit/EnzoBfieldMethod.hpp"
#include "Enzo/hydro-mhd/toolkit/EnzoBfieldMethodCT.hpp"

#include "Enzo/hydro-mhd/EnzoMethodMHDVlct.hpp"
#include "Enzo/hydro-mhd/EnzoMethodPpm.hpp"
#include "Enzo/hydro-mhd/EnzoMethodPpml.hpp"

#endif /* ENZO_HYDROMHD_HYDROMHD_HPP */
