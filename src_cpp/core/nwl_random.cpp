#include <nwl_pch.hpp>
#include "nwl_random.h"
std::mt19937 s_rand_engine(static_cast<ui32>(time(nullptr)));
namespace NWL
{
	NWL_API bit get_rand_bit() {
		return  static_cast<bit>(get_rand_sint32(0, 1));
	}
	NWL_API si8 get_rand_sint8(si8 nmin, si8 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<si8>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	NWL_API ui8 get_rand_uint8(ui8 nmin, ui8 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<ui8>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	NWL_API si16 get_rand_sint16(si16 nmin, si16 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<si16>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	NWL_API ui16 get_rand_uint16(ui16 nmin, ui16 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<ui16>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	NWL_API si32 get_rand_sint32(si32 nmin, si32 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<si32>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	NWL_API ui32 get_rand_uint32(ui32 nmin, ui32 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<ui32>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	NWL_API f32 get_rand_f32(f32 nmin, f32 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<f32>(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin)) + nmin;
	}
	NWL_API f64 get_rand_f64(f64 nmin, f64 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<f64>(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin)) + nmin;
	}
}