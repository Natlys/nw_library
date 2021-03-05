#ifndef NWL_PHYSX_COLLISION_H
#define NWL_PHYSX_COLLISION_H
#include <nwl_core.hpp>
#include <math/math_vector.h>
namespace NWL
{
	bool is_collision_pt_rt(v2f32 xyPoint, v2f32 rect_left_top, v2f32 rect_right_bot);
	bool is_collision_rt_rt(v2f32 rect0_left_top, v2f32 rect0_right_bot, v2f32 rect1_left_top, v2f32 rect1_right_bot);
}

#endif	// NWL_PHYSICS_COLLISION_H