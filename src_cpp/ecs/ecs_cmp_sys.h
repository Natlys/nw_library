#ifndef NWL_ECS_COMPONENT_SYSTEM_H
#define NWL_ECS_COMPONENT_SYSTEM_H

#include <nwl_core.hpp>

#include <ecs/ecs_component.h>
#include <ecs/ecs_ent_sys.h>

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
}
namespace NWL
{
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
	// --template_component_methods
	template<class CType>
	TCmp<CType>::TCmp() : ACmp(GetStaticTypeId()) { CmpSys::GetCmps<CType>().push_back(static_cast<CType*>(this)); }
	template<class CType>
	TCmp<CType>::~TCmp() { auto& rCmps = CmpSys::GetCmps<CType>(); rCmps.erase(std::find(rCmps.begin(), rCmps.end(), this)); }
}

#endif	// NWL_ECS_COMPONENT_SYSTEM_H