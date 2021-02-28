#include <nwl_pch.hpp>
#include "ecs_ent_sys.h"

NWL::EntSys::EntsRegistry NWL::EntSys::s_eReg = EntsRegistry();

namespace NWL
{
	// --==<core_methods>==--
	void EntSys::OnInit() {
		if (!s_eReg.empty()) { return; }
	}
	void EntSys::OnQuit()
	{
		if (s_eReg.empty()) { return; }
		s_eReg.clear();
	}

	void EntSys::RmvEnt(UInt32 eId, UInt32 tId) {
		auto& rReg = s_eReg;
		if (rReg.empty()) { return; }
		auto& itEnts = rReg.find(tId);
		if (itEnts == rReg.end()) { return; }
		if (itEnts->second.empty()) { return; }
		auto& itEnt = itEnts->second.find(eId);
		if (itEnt == itEnts->second.end()) { return; }
		itEnts->second.erase(itEnt);
	}
	// --==</core_methods>==--
}