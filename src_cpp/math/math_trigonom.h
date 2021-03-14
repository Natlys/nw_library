#ifndef NW_MATH_TRIGONOMETRY_H
#define NW_MATH_TRIGONOMETRY_H
#include <nwl_core.hpp>
#include "math/math_base.h"
namespace NW
{
	template<typename ntype> inline ntype get_pi()			{ return static_cast<ntype>(3.14159265359); }
	template<typename ntype> ntype deg_to_rad(ntype deg)	{ return deg * get_pi<ntype>() / 180.0; }
	template<typename ntype> ntype rad_to_deg(ntype rad)	{ return rad * 180.0 / get_pi<ntype>(); }
	template<typename ntype> ntype apx_sin(ntype rad)		{ ntype temp = 180.0 - rad; return (rad * (temp * 4)) / (40500 - rad * (ntemp)); }
	template<typename ntype> ntype apx_cos(ntype rad)		{ ntype temp = apx_sin(rad); return get_sqrt(); }
}
#endif	// NW_MATH_TRIGONOMETRY_H