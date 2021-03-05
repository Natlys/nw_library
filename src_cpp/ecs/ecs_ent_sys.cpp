#include <nwl_pch.hpp>
#include "ecs_ent_sys.h"

NWL::ent_sys::registry NWL::ent_sys::s_reg;

namespace NWL
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

	void ent_sys::del_ent(ui32 ent_id, ui32 type_id) {
		if (s_reg.empty()) { return; }
		auto& ents = s_reg.find(type_id);
		if (ents == s_reg.end()) { return; }
		if (ents->second.empty()) { return; }
		auto& ent = ents->second.find(ent_id);
		if (ent == ents->second.end()) { return; }
		ents->second.erase(ent_id);
	}
	// --==</core_methods>==--
}