#include <nwl_pch.hpp>
#include "ecs_ent.h"
#include <ecs/ecs_cmp_sys.h>
namespace NWL
{
	a_ent::a_ent() : m_is_enabled(true)
	{
		//cmp_sys::get_registry()[get_ent_id()];
	}
	a_ent::~a_ent() {
		//cmp_sys::get_registry().erase(get_ent_id());
	}
	// --setters
	void a_ent::set_enabled(bit enable) { m_is_enabled = enable; }
}