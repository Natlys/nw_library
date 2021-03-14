#ifndef NW_MATH_BASE_H
#define NW_MATH_BASE_H
#include <nwl_core.hpp>
namespace NW
{
	template<typename ntype> ntype get_abs(ntype n) { return n < 0 ? -n : n; }
	template<typename ntype> ntype get_max(ntype n0, ntype n1)	{ return n0 > n1 ? n0 : n1; }
	template<typename ntype> ntype get_min(ntype n0, ntype n1)	{ return n0 < n1 ? n0 : n1; }
	template<typename ntype> ntype get_clamped(ntype nmin, ntype nmax, ntype naverage)	{ return get_max<ntype>(nmin, get_min<ntype>(nmax, naverage)); }
	template<typename ntype> ntype get_lerp(ntype nmin, ntype nmax, ntype npercent)		{ return (nmax - nmin) * npercent; }
}
#endif	// NW_MATH_BASE_H