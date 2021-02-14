#ifndef NWL_ECS_ENTITY_H
#define NWL_ECS_ENTITY_H

#include <nwl_core.hpp>
#include <nwl_memory.hpp>

#include <core/nwl_container.h>
#include <core/nwl_id_stack.h>
#include <core/nwl_string.h>
#include <core/nwl_type.h>
#include <ecs/ecs_component.h>

namespace NWL
{
	/// AEntity class
	class NWL_API AEntity
	{
		friend class EntSys;
		using ACmps = DArray<RefKeeper<ACmp>>;
	public:
		AEntity(UInt32 eId);
		AEntity(const AEntity& rCpy) = delete;
		virtual ~AEntity();

		// --getters
		inline const UInt32 GetEntId() const { return m_eId; }
		inline ACmp* GetCmp(UInt32 tId);
		template<class CType>
		inline CType* GetCmp() { return static_cast<CType*>(GetCmp(CType::GetStaticTypeId())); }
		// --setters
		inline void AddCmp(RefKeeper<ACmp>& rCmp);
		inline void RmvCmp(UInt32 tId);
		void SetEnabled(bool bIsEnabled);
		// --predicates
		inline bool IsEnabled() { return m_bIsEnabled; }
		inline bool HasCmp(UInt32 tId) { return GetCmp(tId) != nullptr; }
		template<class CType>
		inline bool HasCmp() { return GetCmp<CType>() != nullptr; }
		// --operators
		inline void operator=(const AEntity& rCpy) = delete;
		inline void operator delete(Ptr pBlock) = delete;
		inline void operator delete[](Ptr pBlock) = delete;
	private:
		UInt32 m_eId;
		ACmps m_ACmps;
		bool m_bIsEnabled;
	};
	// --getters
	inline ACmp* AEntity::GetCmp(UInt32 tId) {
		if (m_ACmps.size() < tId) { return nullptr; }
		return m_ACmps[tId].IsValid() ? m_ACmps[tId].GetRef() : nullptr;
	}
	// --setters
	inline void AEntity::AddCmp(RefKeeper<ACmp>& rCmp) {
		if (!rCmp.IsValid()) { return; }
		if (m_ACmps.size() <= rCmp->GetTypeId()) { m_ACmps.resize((rCmp->GetTypeId() + 1ul) * 2ul); }
		else if (m_ACmps[rCmp->GetTypeId()].IsValid()) { return; }
		m_ACmps[rCmp->GetTypeId()].SetRef(rCmp);
		rCmp->m_eId = GetEntId();
	}
	inline void AEntity::RmvCmp(UInt32 tId) {
		if (m_ACmps.size() <= tId) { return; }
		m_ACmps[tId].Reset();
	}
}

#endif	// NWL_ECS_ENTITY_H