#include <nwl_pch.hpp>
#include "ecs_component.h"
#include "ecs_ent_sys.h"
#include "ecs_cmp_sys.h"

namespace NWL
{
	ACmp::ACmp(UInt32 tId) : m_tId(tId), m_eId(0) { }
	ACmp::~ACmp() {}
	// --setters
}