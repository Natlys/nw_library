#ifndef NWL_ECS_COMPONENT_SYSTEM_H
#define NWL_ECS_COMPONENT_SYSTEM_H

#include <nwl_core.hpp>

#include <ecs/ecs_component.h>
#include <core/nwl_container.h>

namespace NWL
{
	/// ComponentSystem static class
	class NWL_API CmpSys
	{
		/// Table of component type id's and component references
		using Cmps = HashMap<UInt32, RefKeeper<ACmp>>;
		/// Table of entity id's and component containers
		using CmpsRegistry = HashMap<UInt32, Cmps>;
	public:
		// --getters
		static inline CmpsRegistry& GetRegistry() { return s_cReg; }
		static inline Cmps& GetCmps(UInt32 eId) { return GetRegistry()[eId]; }
		static inline ACmp* GetCmp(UInt32 eId, UInt32 tId) { return HasCmp(eId, tId) ? GetCmps(eId)[tId].GetRef() : nullptr; }
		template<class CType> static ACmp* GetCmp(UInt32 eId) { return HasCmp<CType>(eId) ? GetCmps(eId)[TypeIndexator::GetId<CType>()].GetRef<CType>() : nullptr; }
		template<class CType> static Cmps& GetCmps() { return GetRegistry()[TypeIndexator::GetId<CType>()]; }
		template<class CType> static CType* GetCmp(UInt32 eId) { return static_cast<CType*>(GetCmp(eId, TypeIndexator::GetId<CType>())); }
		// --setters
		static void RmvCmp(UInt32 eId, UInt32 tId);
		template<class CType, typename ... Args> static CType* AddCmp(UInt32 eId, Args& ... Arguments);
		template<class CType> static void RmvCmp(UInt32 eId) { RmvCmp(eId, TypeIndexator::GetId<CType>(eId)); }
		// --predicates
		static inline bool HasEnt(UInt32 eId) { if (GetRegistry().empty()) { return false; } return GetRegistry().find(eId) != GetRegistry().end(); }
		static inline bool HasCmp(UInt32 eId, UInt32 tId) { if (!HasEnt(eId)) { return false; } return GetRegistry()[eId][tId].IsValid(); }
		template<class CType> static bool HasCmp(UInt32 eId) { return HasCmp(eId, TypeIndexator::GetId<>()); }
		// --core_methods
		static void OnInit();
		static void OnQuit();
	private:
		static CmpsRegistry s_cReg;
	};
	// --setters
	template<class CType, typename ... Args>
	static inline CType* CmpSys::AddCmp(UInt32 eId, Args& ... Arguments) {
		Entity* pEnt = EntSys::GetEnt(eId);
		if (pEnt == nullptr) { return 0; }
		if (pEnt->HasCmp<CType>()) { return nullptr; }
		RefKeeper<ACmp> pCmp;
		pCmp.MakeRef<CType>(std::forward<Args&>(Arguments)...);
		pEnt->AddCmp(pCmp);
		return pCmp.GetRef<CType>();
	}
}
namespace NWL
{
	/// Templated Component class
	template <class CType>
	class NWL_API TCmp : public ACmp
	{
	protected:
		TCmp() : ACmp(TypeIndexator::GetId<CType>()GetStaticTypeId()) { }
	public:
		virtual ~TCmp() { }
	};
	// --template_component_methods
}

#endif	// NWL_ECS_COMPONENT_SYSTEM_H