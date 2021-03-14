#ifndef NW_MATH_MATRIX_H
#define NW_MATH_MATRIX_H
#include <nwl_core.hpp>
namespace NW
{
	typedef glm::f32mat2 m2f32;
	typedef glm::f32mat3 m3f32;
	typedef glm::f32mat4 m4f32;
	
	typedef glm::f64mat2 m2f64;
	typedef glm::f64mat3 m3f64;
	typedef glm::f64mat4 m4f64;

	using m2f = m2f32;
	using m3f = m3f32;
	using m4f = m4f32;
}
#endif // NW_MATH_MATRIX_H