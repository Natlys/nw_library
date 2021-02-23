#include <nwl_pch.hpp>
#include "ecs_entity.h"

#include "ecs_cmp_sys.h"

namespace NWL
{
	Entity::Entity(unsigned int tId) :
		m_eId(GetIdStack().GetFreeId()), m_tId(tId),
		m_bIsEnabled(true) { }
	Entity::Entity(const Entity& rCpy) :
		m_eId(rCpy.m_eId), m_tId(rCpy.m_tId),
		m_bIsEnabled(rCpy.m_bIsEnabled) { }
	Entity::~Entity()
	{
		GetIdStack().SetFreeId(m_eId);
		if (CmpSys::HasEnt(m_eId)) { CmpSys::GetRegistry().erase(m_eId); }
	}
	// --setters
	void Entity::SetEnabled(bool bIsEnabled) { m_bIsEnabled = bIsEnabled; }
	// --core_methods
}