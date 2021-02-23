#include <nwl_pch.hpp>
#include "physx_collision.h"

namespace NWL
{
	bool IsCollidPointRect(V2f xyPoint, V2f LeftTop, V2f RightBot) {
		return ((xyPoint.x > LeftTop.x && xyPoint.x < RightBot.x) &&
			(xyPoint.y > LeftTop.y && xyPoint.y < RightBot.y));
	}
	bool IsCollidRectRect(V2f LeftTop0, V2f RightBot0, V2f LeftTop1, V2f RightBot1) {
		return ((LeftTop0.x > LeftTop1.x && LeftTop0.x < RightBot1.x) &&
			(LeftTop0.y > LeftTop1.y && LeftTop0.y < RightBot1.y)) ||
			((RightBot0.x > LeftTop1.x && RightBot0.x < RightBot1.x) &&
				(RightBot0.y > LeftTop1.y && RightBot0.y < RightBot1.y));
	}
}