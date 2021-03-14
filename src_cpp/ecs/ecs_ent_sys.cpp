#include <nwl_pch.hpp>
#include "ecs_ent_sys.h"

NW::ent_sys::registry NW::ent_sys::s_reg;

namespace NW
{
	// --==<core_methods>==--
	void ent_sys::on_init() {
		if (!s_reg.empty()) { return; }
	}
	void ent_sys::on_quit()
	{
		if (s_reg.empty()) { return; }
		s_reg.clear();
	}

	void ent_sys::del_ent(ui32 type_id, ui32 ent_id) {
		if (!has_ent(type_id, ent_id)) { return; }
		s_reg[type_id].erase(ent_id);
	}
	// --==</core_methods>==--
}