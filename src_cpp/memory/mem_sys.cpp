#include <nwl_pch.hpp>
#include "mem_sys.h"

namespace NWL
{
	// --==<core_methods>==--
	void MemSys::OnInit(Size szMemory) {
		if (GetMemory().GetDataBeg() != nullptr) { return; }
		GetMemory() = MemArena(new Byte[szMemory], szMemory);
	}
	void MemSys::OnQuit() {
		if (GetMemory().GetDataBeg() == nullptr) { return; }
		delete[] GetMemory().GetDataBeg();
		GetMemory() = MemArena(nullptr, 0);
	}
	// --==</core_methods>==--
}