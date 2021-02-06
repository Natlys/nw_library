#ifndef NWL_MATH_H
#define NWL_MATH_H

#include <glm/trigonometric.hpp>

namespace NWL
{
	template<typename ValType> inline ValType GetPi();
	template<typename ValType> inline ValType GetZero();
	template<> inline Int8 GetZero<Int8>() { return 0; }
	template<> inline Int16 GetZero<Int16>() { return 0; }
	template<> inline Int32 GetZero<Int32>() { return 0; }
	template<> inline Int64 GetZero<Int64>() { return 0; }
	template<> inline UInt8 GetZero<UInt8>() { return 0; }
	template<> inline UInt16 GetZero<UInt16>() { return 0; }
	template<> inline UInt32 GetZero<UInt32>() { return 0; }
	template<> inline UInt64 GetZero<UInt64>() { return 0; }
	template<> inline Float32 GetZero<Float32>() { return 0.0f; }
	template<> inline Float64 GetZero<Float64>() { return 0.0; }
	template<> inline Float128 GetZero<Float128>() { return 0.0; }
	template<> inline Float32 GetPi<Float32>() { return 3.14159265359f; }
	template<> inline Float64 GetPi<Float64>() { return 3.14159265359; }
	template<> inline Float128 GetPi<Float128>() { return 3.14159265359; }
}

namespace NWL
{
	template<typename ValType>
	inline ValType Abs(ValType n0) { return n0 < 0 ? -n0 : n0; }
	template<typename ValType>
	inline ValType Max(ValType n0, ValType n1) { return n0 > n1 ? n0 : n1; }
	template<typename ValType>
	inline ValType Min(ValType n0, ValType n1) { return n0 < n1 ? n0 : n1; }
	template<typename ValType>
	inline ValType Clamp(ValType nMin, ValType nMax, ValType nAverage) { return Max(nMin, Min(nMax, nAverage)); }
	template<typename ValType>
	inline ValType Lerp(ValType nMin, ValType nMax, ValType nPercentage) { return ((nMax - nMin) * nPercentage); }
}
namespace NWL
{
	template<typename ValType>
	inline ValType DegToRad(ValType nDegrees) { return (nDegrees * GetPi<ValType>()) / 180.0; }
	template<typename ValType>
	inline ValType RadToDeg(ValType nRadians) { return (nRadians * 180.0) / GetPi<ValType>(); }
	template<typename ValType>
	inline ValType ApxSin(ValType nRadians) { ValType nTemp = 180.0 - nRadians; return (nRadians * (nTemp * 4)) / (40500 - nRadians * (nTemp)); }
	template<typename ValType>
	inline ValType ApxCos(ValType nRadians) { ValType nTemp = ApxSin(nRadians); return std::sqrt(1 - (nTemp * nTemp)); }
}
namespace NWL
{
	/// RectInfo struct
	template<typename ValType>
	struct NWL_API RectInfo
	{
	public:
		ValType nX0 = GetZero<ValType>(), nY0 = GetZero<ValType>(), nX1 = GetZero<ValType>(), nY1 = GetZero<ValType>();
	public:
		// --getters
		inline ValType GetWidth() { return Abs(nX1 - nX0); }
		inline ValType GetHeight() { return Abs(nY1 - nY0); }
		// --setters
	};
}

#endif	// NWL_MATH_H