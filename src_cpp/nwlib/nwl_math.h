#ifndef NWL_MATH_H
#define NWL_MATH_H

#include <glm/trigonometric.hpp>

namespace NWL
{
	template<typename ValType> inline ValType GetPi();
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

#endif	// NWL_MATH_H