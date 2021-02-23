#ifndef NWL_ECS_ENTITY_SYSTEM_H
#define NWL_ECS_ENTITY_SYSTEM_H

#include <nwl_core.hpp>

#include <core/nwl_container.h>
#include <ecs/ecs_entity.h>

namespace NWL
{
	/// EntitySystem static class
	class NWL_API EntSys
	{
		using Ents = HashMap<UInt32, RefKeeper<Entity>>;
		using EntsRegistry = HashMap<UInt32, Ents>;
	public:
		// --getters
		static inline EntsRegistry& GetRegistry() { return s_eReg; }
		static inline Ents& GetEnts(UInt32 tId) { return GetRegistry()[tId]; }
		static Entity* GetEnt(UInt32 eId, UInt32 tId) { return HasEnt(eId, tId) ? GetRegistry()[tId][eId].GetRef() : nullptr; }
		template<class EType> static Ents& GetEnts() { return GetRegistry()[TypeIndexator::Get<EType>()]; }
		template<class EType> static EType* GetEnt(UInt32 eId) { return static_cast<EType*>(GetEnt(TypeIndexator::Get<EType>(), eId)); }
		// --setters
		static void RmvEnt(UInt32 eId, UInt32 tId);
		template<class EType, typename ... Args> static RefKeeper<Entity>& AddEnt(Args&& ... Arguments);
		template<class EType> static void RmvEnt(UInt32 eId) { RmvEnt(eId, TypeIndexator::Get<EType>(eId)); }
		// --predicates
		static bool HasEnt(UInt32 eId, UInt32 tId) { if (GetRegistry()[tId].empty()) { return false; } return GetRegistry()[tId].find(eId) != GetRegistry()[tId].end(); }
		template<class EType> static bool HasEnt(UInt32 eId) { return HasEnt(eId, TypeIndexator::Get<EType>()); }
		// --core_methods
		static void OnInit();
		static void OnQuit();
	private:
		static EntsRegistry s_eReg;
	};
	// --setters
	template<class EType, typename ... Args>
	RefKeeper<Entity>& EntSys::AddEnt(Args&& ... Arguments) {
		auto& rEnts = GetEnts<EType>();
		RefKeeper<Entity> pEnt;
		pEnt.MakeRef<EType>(std::forward<Args>(Arguments)...);
		rEnts[pEnt->GetEntId()] = pEnt;
		return rEnts[pEnt->GetEntId()];
	}
}

#endif // NWL_ECS_ENTITY_SYSTEM_H