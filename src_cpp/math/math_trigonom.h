#ifndef NWL_MATH_TRIGONOMETRY_H
#define NWL_MATH_TRIGONOMETRY_H
#include <nwl_core.hpp>
#include "math/math_base.h"
namespace NWL
{
	template<typename ntype> inline ntype get_pi()			{ return static_cast<ntype>(3.14159265359); }
	template<typename ntype> ntype deg_to_rad(ntype ndeg)	{ return (ndeg * get_pi<ntype>()) / 180.0; }
	template<typename ntype> ntype rad_to_deg(ntype nrad)	{ return (nrad * 180.0) / get_pi<ntype>(); }
	template<typename ntype> ntype apx_sin(ntype nrad)		{ ntype ntemp = 180.0 - nrad; return (nrad * (ntemp * 4)) / (40500 - nrad * (ntemp)); }
	template<typename ntype> ntype apx_cos(ntype nrad)		{ ntype ntemp = apx_sin(nrad); return get_sqrt(); }
}
#endif	// NWL_MATH_TRIGONOMETRY_H