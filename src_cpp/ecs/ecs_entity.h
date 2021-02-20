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
	/// Anstract Entity class
	class NWL_API Entity
	{
		friend class EntSys;
	protected:
		Entity() : m_unId(0), m_bIsEnabled(false) { }
	public:
		Entity(const Entity& rCpy) : m_unId(rCpy.m_unId), m_bIsEnabled(rCpy.m_bIsEnabled) {}
		virtual ~Entity() {}
		// --getters
		inline unsigned int GetId() const { return m_unId; }
		virtual inline unsigned int GetTypeId() const = 0;
		virtual inline const char* GetTypeStr() const = 0;
		// --setters
		void SetEnabled(bool bIsEnabled) { m_bIsEnabled = bIsEnabled; }
		// --predicates
		inline bool IsEnabled() { return m_bIsEnabled; }
		// --predicates
		template<class EType> inline bool IsOfType() { return TypeIndexator<EType>() == GetTypeId(); }
		// --operators
		inline void operator=(const Entity& rCpy) = delete;
		inline void* operator new(Size szData, Ptr pData) { return ::operator new(szData, pData); }
		inline void* operator new(Size szData) { return MemSys::Alloc(szData); }
		inline void* operator new[](Size szData) { return MemSys::Alloc(szData); }
		inline void operator delete(Ptr pData, Size szData) { MemSys::Dealloc(pData, szData); }
		inline void operator delete[](Ptr pData, Size szData) {MemSys::Dealloc(pData, szData); }
	protected:
		unsigned int m_unId;
		bool m_bIsEnabled;
	};
}
namespace NWL
{
	/// Templated Entity class
	template<class EType>
	class NWL_API TEntity : public Entity
	{
	public:
		TEntity() : Entity() { m_unId = GetIdStack().GetFreeId(); }
		virtual ~TEntity() { GetIdStack().SetFreeId(m_unId); }
		// --getters
		virtual inline unsigned int GetTypeId() const override { return TypeIndexator::Get<EType>(); }
		virtual inline const char* GetTypeStr() const override { return typeid(EType).name(); }
	protected:
		static inline IdStack& GetIdStack() { static IdStack s_idStack(0); return s_idStack; }
	};
}
namespace NWL
{
	/// CmpEntity class
	class NWL_API CmpEntity : TEntity<CmpEntity>
	{
		using ACmps = DArray<RefKeeper<ACmp>>;
	public:
		CmpEntity() : TEntity() {}
		virtual ~CmpEntity() {}
		// --getters
		inline ACmp* GetCmp(UInt32 tId);
		template<class CType> inline CType* GetCmp();
		// --setters
		inline void AddCmp(RefKeeper<ACmp>& rCmp);
		inline void RmvCmp(UInt32 tId);
		// --predicates
		inline bool HasCmp(UInt32 tId) { return GetCmp(tId) != nullptr; }
		template<class CType>
		inline bool HasCmp() { return GetCmp<CType>() != nullptr; }
	private:
		ACmps m_ACmps;
	};
	// --getters
	inline ACmp* CmpEntity::GetCmp(UInt32 tId) {
		if (m_ACmps.size() < tId) { return nullptr; }
		return m_ACmps[tId].IsValid() ? m_ACmps[tId].GetRef() : nullptr;
	}
	template<class CType> inline CType* CmpEntity::GetCmp() { return static_cast<CType*>(GetCmp(CType::GetStaticTypeId())); }
	// --setters
	inline void CmpEntity::AddCmp(RefKeeper<ACmp>& rCmp) {
		if (!rCmp.IsValid()) { return; }
		if (m_ACmps.size() <= rCmp->GetTypeId()) { m_ACmps.resize((rCmp->GetTypeId() + 1ul) * 2ul); }
		else if (m_ACmps[rCmp->GetTypeId()].IsValid()) { return; }
		m_ACmps[rCmp->GetTypeId()].SetRef(rCmp);
		rCmp->m_tId = GetId();
	}
	inline void CmpEntity::RmvCmp(UInt32 tId) {
		if (m_ACmps.size() <= tId) { return; }
		m_ACmps[tId].Reset();
	}
}

#endif	// NWL_ECS_ENTITY_H