#ifndef NWL_RANDOM_H
#define NWL_RANDOM_H

#include <nwl_core.hpp>

#include <random>

#pragma warning(disable : 4067)
#undef max(a,b) (((a) > (b)) ? (a) : (b))
#undef min(a,b) (((a) < (b)) ? (a) : (b))

namespace NWL
{
	class NWL_API Random
	{
	public:
		// --getters
		static inline bool GetBool() {
			return  static_cast<bool>(GetInt(0, 1));
		}
		static inline bool GetByte() {
			return  static_cast<Byte>(GetInt(-128, 127));
		}
		static inline bool GetUByte() {
			return  static_cast<UByte>(GetInt(0, 255));
		}
		static inline Int32 GetInt(Int32 nMin = 0xFF'FF'00'00, Int32 nMax = 0x00'00'FF'FF) {
			constexpr Float64 nFraction = 1.0 / ( static_cast<Float64>(s_RandEngine.max()) );
			return  static_cast<Int32>(std::round(static_cast<Float64>(s_RandEngine()) * nFraction * (nMax - nMin))) + nMin;
		}
		static inline UInt32 GetUInt(UInt32 unMin = 0x00'00'00'00, UInt32 unMax = 0x00'00'FF'FF) {
			return static_cast<UInt32>(GetInt(unMin, unMax));
		}
		static inline Float32 GetFloat(float nMin = 0.0f, float nMax = 1.0f) {
			constexpr Float64 nFraction = 1.0 / ( static_cast<Float64>(s_RandEngine.max()) );
			return  static_cast<Float32>(static_cast<Float64>(s_RandEngine()) * nFraction * (nMax - nMin)) + nMin;
		}
		static inline Float64 GetDouble(float nMin = 0.0f, float nMax = 1.0f) {
			constexpr Float64 nFraction = 1.0 / (static_cast<Float64>(s_RandEngine.max()));
			return  static_cast<Float64>(static_cast<Float64>(s_RandEngine()) * nFraction * (nMax - nMin)) + nMin;
		}
		// --setters

		// --core_methods
	private:
		static std::mt19937 s_RandEngine;
	};
}

#endif	// NW_RANDOM_SYSTEM_H