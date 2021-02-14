#include <nwl_pch.hpp>
#include "ecs_entity.h"

namespace NWL
{
	AEntity::AEntity(UInt32 eId) : m_eId(eId) {}
	AEntity::~AEntity() {}
	// --setters
	void AEntity::SetEnabled(bool bIsEnabled) { m_bIsEnabled = bIsEnabled; }
}