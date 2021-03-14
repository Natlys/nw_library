#include <nwl_pch.hpp>
#include "ecs_cmp_sys.h"
#include <ecs/ecs_ent_sys.h>

NW::cmp_sys::registry NW::cmp_sys::s_reg;

namespace NW
{
	// --==<core_methods>==--
	void cmp_sys::on_init() {
		if (!s_reg.empty() && !s_reg.empty()) { return; }
	}
	void cmp_sys::on_quit() {
		if (s_reg.empty() && s_reg.empty()) { return; }
		s_reg.clear();
	}

	void cmp_sys::del_cmp(ui32 type_id, ui32 cmp_id) {
		if (!has_cmp(type_id, cmp_id)) { return; }
		s_reg[type_id].erase(cmp_id);
	}
	// --==</core_methods>==--
}