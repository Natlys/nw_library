#include <nwl_pch.hpp>
#include "ecs_ent.h"
#include <ecs/ecs_cmp_sys.h>
namespace NWL
{
	a_ent::a_ent() :
		a_type_owner(),
		m_is_enabled(true)
	{
	}
	a_ent::~a_ent() { }
	// --setters
	void a_ent::set_enabled(bit enable) { m_is_enabled = enable; }
}