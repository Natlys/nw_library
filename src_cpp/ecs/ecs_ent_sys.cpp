#include <nwl_pch.hpp>
#include "ecs_ent_sys.h"

NWL::EntSys::EntsRegistry NWL::EntSys::s_eReg = EntsRegistry();

namespace NWL
{
	// --setters
	void EntSys::RmvEnt(UInt32 eId, UInt32 tId) {
		auto& rReg = GetRegistry();
		if (rReg.empty()) { return; }
		auto& itEnts = rReg.find(tId);
		if (itEnts == rReg.end()) { return; }
		if (itEnts->second.empty()) { return; }
		auto& itEnt = itEnts->second.find(eId);
		if (itEnt == itEnts->second.end()) { return; }
		itEnts->second.erase(itEnt);
	}
	// --==<core_methods>==--
	void EntSys::OnInit() {
		if (!GetRegistry().empty()) { return; }
	}
	void EntSys::OnQuit()
	{
		if (GetRegistry().empty()) { return; }
		GetRegistry().clear();
	}
	// --==</core_methods>==--
}