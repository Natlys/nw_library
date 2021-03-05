#ifndef NWL_RANDOM_H
#define NWL_RANDOM_H
#include <nwl_core.hpp>
#include <random>
#pragma warning(disable : 4067)
namespace NWL
{
	// --getters
	NWL_API bit get_rand_bit();
	NWL_API si8 get_rand_sint8(si8 nmin = 0xf0, si8 nmax = 0x0f);
	NWL_API ui8 get_rand_uint8(ui8 nmin = 0x00u, ui8 nmax = 0xffu);
	NWL_API si16 get_rand_sint16(si16 nmin = 0x00'00, si16 nmax = 0x00'ff);
	NWL_API ui16 get_rand_uint16(ui16 nmin = 0x00'00u, ui16 nmax = 0xff'ffu);
	NWL_API si32 get_rand_sint32(si32 nmin = 0xff'ff'00'00, si32 nmax = 0x00'00'ff'ff);
	NWL_API ui32 get_rand_uint32(ui32 nmin = 0x00'00'00'00, ui32 nmax = 0xff'ff'ff'ff);
	NWL_API f32 get_rand_f32(f32 nmin = 0.0f, f32 nmax = 1.0f);
	NWL_API f64 get_rand_f64(f64 nmin = 0.0, f64 nmax = 1.0);
}

#endif	// NW_RANDOM_SYSTEM_H