#ifndef NWL_ECS_COMPONENT_SYSTEM_H
#define NWL_ECS_COMPONENT_SYSTEM_H

#include <nwl_core.hpp>
#include <core/nwl_container.h>
#include <core/nwl_type.h>
#include <ecs/ecs_component.h>

namespace NWL
{
	/// ComponentSystem static class
	/// Description:
	/// --core manager of components: creates, destroyes and gives components;
	/// --stores all components in tables of entities;
	/// --any cmp table contains abstract refs to components of particular type;
	/// --all cmp tables are inside of single registry;
	/// --registry: ent_id-table | tables: type_id-ref;
	class NWL_API CmpSys
	{
		/// table of ent_id and component references
		using EntCmps = HashMap<UInt32, RefKeeper<ACmp>>;
		/// table of type id's and component references
		using EntCmpRegistry = HashMap<UInt32, EntCmps>;
		/// table of ent_id and component references
		using TypeCmps = HashMap<UInt32, RefKeeper<ACmp>>;
		/// table of type_id and component containers
		using TypeCmpRegistry = HashMap<UInt32, TypeCmps>;
	public:
		// --getters
		static inline EntCmpRegistry& GetEntCmpRegistry() { return s_ecReg; }
		static inline TypeCmpRegistry& GetTypeCmpRegistry() { return s_tcReg; }
		static inline EntCmps& GetEntCmps(UInt32 eId) { return s_ecReg[eId]; }
		static inline TypeCmps& GetTypeCmps(UInt32 tId) { return s_tcReg[tId]; }
		template<class CType> static TypeCmps& GetTypeCmps() { return s_tcReg[TypeIndexator::GetId<CType>()]; }
		static inline RefKeeper<ACmp>& GetCmp(UInt32 eId, UInt32 tId) { return s_ecReg[eId][tId]; }
		template<class CType> static RefKeeper<ACmp>& GetCmp(UInt32 eId) { return GetCmp(eId, TypeIndexator::GetId<CType>()); }
		// --predicates
		static inline bool HasCmp(UInt32 eId, UInt32 tId) { return s_ecReg[eId][tId].IsValid(); }
		template<class CType> static bool HasCmp(UInt32 eId) { return s_tcReg[TypeIndexator::GetId<>()][eId]; }
		// --core_methods
		static void OnInit();
		static void OnQuit();
		static void AddCmp(RefKeeper<ACmp>& rCmp);
		template<class CType, typename ... Args>
		static RefKeeper<ACmp>& AddCmp(UInt32 eId, Args& ... Arguments);
		static void RmvCmp(UInt32 eId, UInt32 tId);
		template<class CType> static void RmvCmp(UInt32 eId) { RmvCmp(eId, TypeIndexator::GetId<CType>()); }
	private:
		static EntCmpRegistry s_ecReg;
		static TypeCmpRegistry s_tcReg;
	};
	// --setters
	template<class CType, typename ... Args>
	static RefKeeper<ACmp>& CmpSys::AddCmp(UInt32 eId, Args& ... Arguments) {
		RefKeeper<ACmp> rCmp;
		rCmp.MakeRef<CType>(std::forward<Args&>(Arguments)...);
		rCmp->m_eId = eId;
		s_ecReg[rCmp->GetEntId()][rCmp->GetTypeId()].SetRef(rCmp);
		s_tcReg[rCmp->GetTypeId()][rCmp->GetEntId()].SetRef(rCmp);
		return GetCmp(rCmp->GetEntId(), rCmp->GetTypeId());
	}
}

#endif	// NWL_ECS_COMPONENT_SYSTEM_H