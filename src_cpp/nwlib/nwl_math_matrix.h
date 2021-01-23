#ifndef NWL_MATH_MATRIX_H
#define NWL_MATH_MATRIX_H

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace NWL
{
	typedef glm::mat2 Mat2f;
	typedef glm::mat3 Mat3f;
	typedef glm::mat4 Mat4f;
	typedef glm::dmat2x2 Mat2d;
	typedef glm::dmat3x3 Mat3d;
	typedef glm::dmat4x4 Mat4d;
}

#endif // NWL_MATH_MATRIX_H