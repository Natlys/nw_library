#ifndef NWL_PHYSICS_2D_H
#define NWL_PHYSICS_2D_H

#include <nwlib/nwl_math_vector.h>
#include <nwlib/nwl_container.h>
#include <nwlib/nwl_memory.h>

namespace NWL
{
	inline bool IsCollidPointRect(V2f xyPoint, V2f LeftTop, V2f RightBot) {
		return ((xyPoint.x > LeftTop.x && xyPoint.x < RightBot.x) &&
			(xyPoint.y > LeftTop.y && xyPoint.y < RightBot.y));
	}
	inline bool IsCollidRectRect(V2f LeftTop0, V2f RightBot0, V2f LeftTop1, V2f RightBot1) {
		return ((LeftTop0.x > LeftTop1.x && LeftTop0.x < RightBot1.x) &&
			(LeftTop0.y > LeftTop1.y && LeftTop0.y < RightBot1.y)) ||
			((RightBot0.x > LeftTop1.x && RightBot0.x < RightBot1.x) &&
			(RightBot0.y > LeftTop1.y && RightBot0.y < RightBot1.y));
	}
}

#endif	// NWL_PHYSICS_2D_H