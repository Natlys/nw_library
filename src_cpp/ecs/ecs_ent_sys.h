#ifndef NWL_ECS_ENTITY_SYSTEM_H
#define NWL_ECS_ENTITY_SYSTEM_H

#include <nwl_core.hpp>

#include <ecs/ecs_entity.h>

namespace NWL
{
	/// EntitySystem static class
	class NWL_API EntSys
	{
		using Ents = HashMap<UInt32, RefKeeper<AEntity>>;
	public:
		// --getters
		static inline Ents& GetEnts() { static Ents s_Ents; return s_Ents; }
		static inline AEntity* GetEnt(UInt32 eId);
		// --setters
		template<class EType, typename ... Args> static inline UInt32 AddEnt(Args ... Arguments);
		static inline void RmvEnt(UInt32 eId);
		// --core_methods
		static void OnInit();
		static void OnQuit();
	};
	inline AEntity* EntSys::GetEnt(UInt32 eId) {
		Ents& rEnts = GetEnts();
		if (rEnts.empty()) { return nullptr; }
		auto& itEnt = rEnts.find(eId);
		return itEnt == rEnts.end() ? nullptr : itEnt->second.GetRef();
	}
	template<class EType, typename ... Args> inline UInt32 EntSys::AddEnt(Args ... Arguments) {
		Ents& rEnts = GetEnts();
		RefKeeper<AEntity> pEnt;
		pEnt.MakeRef<EType>(Arguments...);
		rEnts[pEnt->GetId()] = pEnt;
		return pEnt->GetId();
	}
	inline void EntSys::RmvEnt(UInt32 eId) {
		Ents& rEnts = GetEnts();
		if (rEnts.empty()) { return; }
		auto& itEnt = rEnts.find(eId);
		rEnts.erase(itEnt);
	}
}

#endif // NWL_ECS_ENTITY_SYSTEM_H