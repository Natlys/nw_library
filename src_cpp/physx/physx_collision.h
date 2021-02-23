#ifndef NWL_PHYSX_COLLISION_H
#define NWL_PHYSX_COLLISION_H

#include <nwl_core.hpp>
#include <math/math_vector.h>

namespace NWL
{
	bool IsCollidPointRect(V2f xyPoint, V2f LeftTop, V2f RightBot);
	bool IsCollidRectRect(V2f LeftTop0, V2f RightBot0, V2f LeftTop1, V2f RightBot1);
}

#endif	// NWL_PHYSICS_COLLISION_H