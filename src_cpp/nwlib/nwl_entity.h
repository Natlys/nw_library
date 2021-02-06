#ifndef NWL_ENTITY_H
#define NWL_ENTITY_H

#include <nwl_core.hpp>
#include <nwlib/nwl_container.h>
#include <nwlib/nwl_memory.h>
#include <nwlib/nwl_types.h>
#include <nwlib/nwl_id_stack.h>

namespace NWL
{
	/// Abstract Component class
	/// Description:
	/// --provides basic interface, getters and setters for components
	/// --the only one derrived class can be used is templated component
	/// --templated component provides this static type index
	/// --because of that index we can get any component by simple array number
	/// --components cannot use only TCmp because only abstract one can be used
	/// via pointer/ref without explicit type declaration
	/// --only component system can set entity id
	/// because entity id is needed for component only for external access and
	/// explicit argument for constructor is pretty uncomfortable
	class NWL_API ACmp
	{
		friend class AEntity;
		friend class CmpSys;
	protected:
		ACmp(UInt32 tId);
	public:
		virtual ~ACmp();
		// --getters
		inline UInt32 GetEntId() const { return m_eId; }
		inline UInt32 GetTypeId() const { return m_tId; }
		// --operators
		inline void operator delete(Ptr pBlock) = delete;
		inline void operator delete[](Ptr pBlock) = delete;
	protected:
		UInt32 m_eId;
		UInt32 m_tId;
	protected:
		static inline IdStack& GetIdStack() { static IdStack s_idStack; return s_idStack; }
	};
	/// Templated Component class
	template <class CType>
	class NWL_API TCmp : public ACmp
	{
	protected:
		TCmp();
	public:
		virtual ~TCmp();
		// --getters
		static inline UInt32 GetStaticTypeId() { static UInt32 s_nextId = GetIdStack().GetFreeId(); return s_nextId; }
	};
}
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
		void SetEnabled(bool bIsEnabled);
		inline void AddCmp(AMemAllocator& rAllocator, ACmp& rCmp, Size szData);
		inline void RmvCmp(UInt32 tId);
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
		bool m_bIsEnabled;
		ACmps m_ACmps;
	};
	inline ACmp* AEntity::GetCmp(UInt32 tId) {
		if (m_ACmps.size() < tId) { return nullptr; }
		return m_ACmps[tId].IsValid() ? m_ACmps[tId].GetRef() : nullptr;
	}
	inline void AEntity::AddCmp(AMemAllocator& rAllocator, ACmp& rCmp, Size szData) {
		if (m_ACmps.size() <= rCmp.GetTypeId()) { m_ACmps.resize((rCmp.GetTypeId() + 1) * 2); }
		else if (m_ACmps[rCmp.GetTypeId()].IsValid()) { return; }
		m_ACmps[rCmp.GetTypeId()].SetRef(rAllocator, rCmp, szData);
		rCmp.m_eId = GetEntId();
	}
	inline void AEntity::RmvCmp(UInt32 tId) {
		if (m_ACmps.size() <= tId) { return; }
		m_ACmps[tId].Reset();
	}
}
namespace NWL
{
	/// EntitySystem static class
	class NWL_API EntSys
	{
		using Ents = DArray<RefKeeper<AEntity>>;
	public:
		// --getters
		static inline AMemAllocator& GetMemory() { static MemArena s_Memory; return s_Memory; }
		static inline Ents& GetEnts() { static Ents s_Ents; return s_Ents; }
		static inline AEntity* GetEnt(UInt32 eId);
		// --setters
		static inline UInt32 AddEnt();
		static inline void RmvEnt(UInt32 eId);
		// --core_methods
		static void OnInit();
		static void OnQuit();
	private:
		static inline IdStack& GetIdStack() { static IdStack s_idStack; return s_idStack; }
	};
	inline AEntity* EntSys::GetEnt(UInt32 eId) {
		Ents& rEnts = GetEnts();
		if (rEnts.size() <= eId) { return nullptr; }
		return rEnts[eId].GetRef();
	}
	inline UInt32 EntSys::AddEnt() {
		Ents& rEnts = GetEnts();
		UInt32 eId = GetIdStack().GetFreeId();
		if (rEnts.size() <= eId) { rEnts.resize((rEnts.size() + 1) * 2); }
		rEnts[eId].MakeRef<AEntity>(GetMemory(), eId);
		return eId;
	}
	inline void EntSys::RmvEnt(UInt32 eId) {
		Ents& rEnts = GetEnts();
		if (rEnts.size() <= eId) { return; }
		rEnts[eId].Reset();
		GetIdStack().SetFreeId(eId);
	}
}
namespace NWL
{
	/// ComponentSystem static class
	class NWL_API CmpSys
	{
		template<class CType>
		using Cmps = DArray<CType*>;
	public:
		// --getters
		static inline AMemAllocator& GetMemory() { static MemArena s_Memory; return s_Memory; }
		template <class CType>
		static inline Cmps<CType>& GetCmps() { static Cmps<CType> s_Cmps; return s_Cmps; }
		template<class CType>
		static inline CType* GetCmp(UInt32 eId);
		// --setters
		template<class CType, typename ... Args>
		static inline CType* AddCmp(UInt32 eId, Args& ... Arguments);
		template<class EType>
		static inline void RmvCmp(UInt32 eId);
		// --core_methods
		static void OnInit();
		static void OnQuit();
	};
	// --getters
	template<class CType>
	inline CType* CmpSys::GetCmp(UInt32 eId) {
		AEntity* pEnt = EntSys::GetEnt(eId);
		if (pEnt == nullptr) { return nullptr; }
		return pEnt->GetCmp<CType>();
	}
	// --setters
	template<class CType, typename ... Args>
	static inline CType* CmpSys::AddCmp(UInt32 eId, Args& ... Arguments) {
		AEntity* pEnt = EntSys::GetEnt(eId);
		if (pEnt == nullptr) { return 0; }
		if (pEnt->HasCmp<CType>()) { return nullptr; }
		CType* pCmp = NewT<CType>(GetMemory(), std::forward<Args>(Arguments)...);
		pEnt->AddCmp(GetMemory(), *pCmp, sizeof(*pCmp));
		return pCmp;
	}
	template<class CType>
	static inline void CmpSys::RmvCmp(UInt32 eId) {
		AEntity* pEnt = EntSys::GetEnt(eId);
		if (pEnt == nullptr) { return; }
		pEnt->RmvCmp(CType::GetStaticTypeId());
	}
	// --template_component_methods
	template<class CType>
	TCmp<CType>::TCmp() : ACmp(GetStaticTypeId()) { CmpSys::GetCmps<CType>().push_back(static_cast<CType*>(this)); }
	template<class CType>
	TCmp<CType>::~TCmp() { auto& rCmps = CmpSys::GetCmps<CType>(); rCmps.erase(std::find(rCmps.begin(), rCmps.end(), this)); }
}

#endif	// NWL_ENTITY_H