#include "nwl_entity.h"

namespace NWL
{
	ACmp::ACmp(UInt32 tId) : m_eId(0), m_tId(tId) {}
	ACmp::~ACmp() {}
}

namespace NWL
{
	AEntity::AEntity(UInt32 eId) :
		m_eId(eId), m_bIsEnabled(true),
		m_ACmps(ACmps(1 << 3)) { }
	AEntity::~AEntity() { }
	// --setters
	void AEntity::SetEnabled(bool bIsEnabled) {
		m_bIsEnabled = bIsEnabled;
	}
}

namespace NWL
{
	// --core_methods
	void EntSys::OnInit()
	{
		GetMemory() = MemArena(new Byte[1 << 19], 1 << 19);
	}
	void EntSys::OnQuit()
	{
		while (!GetEnts().empty()) { GetEnts().erase(GetEnts().begin()); }
		delete[] GetMemory().GetDataBeg();
		GetMemory() = MemArena(nullptr, 0);
	}
}

namespace NWL
{
	void CmpSys::OnInit()
	{
		GetMemory() = MemArena(new Byte[1 << 19], 1 << 19);
	}
	void CmpSys::OnQuit()
	{
		delete[] GetMemory().GetDataBeg();
		GetMemory() = MemArena(nullptr, 0);
	}
}