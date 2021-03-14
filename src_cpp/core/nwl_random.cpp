#include <nwl_pch.hpp>
#include "nwl_random.h"
std::mt19937 s_rand_engine(clock());
namespace NW
{
	bit get_rand_bit() {
		return  static_cast<bit>(get_rand_sint32(0, 1));
	}
	si8 get_rand_sint8(si8 nmin, si8 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<si8>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	ui8 get_rand_uint8(ui8 nmin, ui8 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<ui8>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	si16 get_rand_sint16(si16 nmin, si16 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<si16>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	ui16 get_rand_uint16(ui16 nmin, ui16 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<ui16>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	si32 get_rand_sint32(si32 nmin, si32 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<si32>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	ui32 get_rand_uint32(ui32 nmin, ui32 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<ui32>(std::round(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin))) + nmin;
	}
	f32 get_rand_f32(f32 nmin, f32 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<f32>(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin)) + nmin;
	}
	f64 get_rand_f64(f64 nmin, f64 nmax) {
		constexpr f64 nfraction = 1.0 / (static_cast<f64>(s_rand_engine.max()));
		return  static_cast<f64>(static_cast<f64>(s_rand_engine()) * nfraction * (nmax - nmin)) + nmin;
	}
}