#pragma once

#include "setup.hpp"
#include <limits>

namespace glm{
namespace detail
{
	template<typename genFitype, bool /*signed*/>
	struct compute_abs
	{};

	template<typename genFitype>
	struct compute_abs<genFitype, true>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static genFitype call(genFitype x)
		{
			GLM_STATIC_ASSERT(
				std::numeric_limits<genFitype>::is_iec559 || std::numeric_limits<genFitype>::is_signed,
				"'abs' only accept floating-point and integer scalar or vector inputs");

			return x >= genFitype(0) ? x : -x;
			// TODO, perf comp with: *(((int *) &x) + 1) &= 0x7fffffff;
		}
	};

#if GLM_COMPILER & GLM_COMPILER_CUDA
	template<>
	struct compute_abs<float, true>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static float call(float x)
		{
			return fabsf(x);
		}
	};
#endif

	template<typename genFitype>
	struct compute_abs<genFitype, false>
	{
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR static genFitype call(genFitype x)
		{
			GLM_STATIC_ASSERT(
				(!std::numeric_limits<genFitype>::is_signed && std::numeric_limits<genFitype>::is_integer),
				"'abs' only accept floating-point and integer scalar or vector inputs");
			return x;
		}
	};
}//namespace detail
}//namespace glm
