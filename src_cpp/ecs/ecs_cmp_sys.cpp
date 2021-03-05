#include <nwl_pch.hpp>
#include "ecs_cmp_sys.h"
#include <ecs/ecs_ent_sys.h>

NWL::cmp_sys::registry NWL::cmp_sys::s_reg;

namespace NWL
{
	// --==<core_methods>==--
	void cmp_sys::on_init() {
		if (!s_reg.empty() && !s_reg.empty()) { return; }
	}
	void cmp_sys::on_quit() {
		if (s_reg.empty() && s_reg.empty()) { return; }
		s_reg.clear();
	}

	void cmp_sys::del_cmp(ui32 ent_id, ui32 type_id) {
		if (!has_cmp(ent_id, type_id)) { return; }
		s_reg[ent_id].erase(type_id);
	}
	// --==</core_methods>==--
}