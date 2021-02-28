#ifndef NWL_ECS_ENTITY_SYSTEM_H
#define NWL_ECS_ENTITY_SYSTEM_H

#include <nwl_core.hpp>
#include <core/nwl_container.h>
#include <core/nwl_type.h>
#include <ecs/ecs_entity.h>

namespace NWL
{
	/// EntitySystem static class
	class NWL_API EntSys
	{
		/// entity id - entity ref
		using Ents = HashMap<UInt32, RefKeeper<AEnt>>;
		/// type id - entity refs
		using EntsRegistry = HashMap<UInt32, Ents>;
	public:
		// --getters
		static inline EntsRegistry& GetRegistry() { return s_eReg; }
		static inline Ents& GetEnts(UInt32 tId) { return s_eReg[tId]; }
		static inline RefKeeper<AEnt>& GetEnt(UInt32 eId, UInt32 tId) { return s_eReg[tId][eId]; }
		template<class EType> static Ents& GetEnts() { return s_eReg[TypeIndexator::GetId<EType>()]; }
		template<class EType> static RefKeeper<AEnt>& GetEnt(UInt32 eId) { return s_eReg[TypeIndexator::GetId<EType>()][eId]; }
		// --predicates
		static inline bool HasEnt(UInt32 eId, UInt32 tId) { return s_eReg[tId][eId].IsValid(); }
		template<class EType> static bool HasEnt(UInt32 eId) { return s_eReg[TypeIndexator::GetId<EType>()][eId].IsValid(); }
		// --core_methods
		static void OnInit();
		static void OnQuit();
		template<class EType, typename ... Args>
		static RefKeeper<AEnt>& AddEnt(Args&& ... Arguments);
		static void RmvEnt(UInt32 eId, UInt32 tId);
		template<class EType> static void RmvEnt(UInt32 eId) { RmvEnt(eId, TypeIndexator::GetId<EType>()); }
	private:
		static EntsRegistry s_eReg;
	};
	// --setters
	template<class EType, typename ... Args>
	RefKeeper<AEnt>& EntSys::AddEnt(Args&& ... Arguments) {
		auto& rEnts = GetEnts<EType>();
		RefKeeper<AEnt> Ent;
		Ent.MakeRef<EType>(std::forward<Args>(Arguments)...);
		rEnts[pEnt->GetEntId()].SetRef(pEnt);
		return rEnts[Ent->GetEntId()];
	}
}

#endif // NWL_ECS_ENTITY_SYSTEM_H