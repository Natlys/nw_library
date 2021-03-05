#include <nwl_pch.hpp>
#include "physx_collision.h"

namespace NWL
{
	bool is_collision_pt_rt(v2f32 xyPoint, v2f32 rect_left_top, v2f32 rect_right_bot) {
		return (
			(xyPoint.x > rect_left_top.x && xyPoint.x < rect_right_bot.x) &&
			(xyPoint.y > rect_left_top.y && xyPoint.y < rect_right_bot.y)
			);
	}
	bool is_collision_rt_rt(v2f32 rect0_left_top, v2f32 rect0_right_bot, v2f32 rect1_left_top, v2f32 rect1_right_bot) {
		return (
			(rect0_left_top.x > rect1_left_top.x && rect0_left_top.x < rect1_right_bot.x) &&
			(rect0_left_top.y > rect1_left_top.y && rect0_left_top.y < rect1_right_bot.y)) ||
			((rect0_right_bot.x > rect1_left_top.x && rect0_right_bot.x < rect1_right_bot.x) &&
			(rect0_right_bot.y > rect1_left_top.y && rect0_right_bot.y < rect1_right_bot.y)
				);
	}
}