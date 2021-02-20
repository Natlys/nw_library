#ifndef NWL_ECS_ENTITY_SYSTEM_H
#define NWL_ECS_ENTITY_SYSTEM_H

#include <nwl_core.hpp>

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
		static inline EntsRegistry& GetRegistry() { static EntsRegistry s_Ents; return s_Ents; }
		template<class EType>
		static inline Ents& GetEnts() { return GetRegistry()[TypeIndexator::Get<EType>()]; }
		static inline Entity* GetEnt(UInt32 tId, UInt32 eId);
		template<typename EType>
		static inline EType* GetEnt(UInt32 eId);
		template<typename EType>
		static inline EType* GetEntByName(const char* strName);
		// --setters
		template<class EType, typename ... Args>
		static inline RefKeeper<Entity>& AddEnt(Args&& ... Arguments);
		static inline void RmvEnt(UInt32 tId, UInt32 eId);
		template<class EType>
		static inline void RmvEnt(UInt32 eId);
		// --core_methods
		static void OnInit();
		static void OnQuit();
	};
	inline Entity* EntSys::GetEnt(UInt32 tId, UInt32 eId) {
		auto& rReg = GetRegistry();
		if (rReg.empty()) { return nullptr; }
		auto& itEnts = rReg.find(tId);
		if (itEnts == rReg.end()) { return nullptr; }
		if (itEnts->second.empty()) { return nullptr; }
		auto& itEnt = itEnts->second.find(eId);
		if (itEnt == itEnts->second.end()) { return nullptr; }
		return itEnt->second.GetRef();
	}
	template<typename EType>
	inline EType* EntSys::GetEnt(UInt32 eId) { return static_cast<EType*>(GetEnt(TypeIndexator::Get<EType>(), eId)); }
	template<typename EType>
	inline EType* EntSys::GetEntByName(const char* strName) {
		auto& rEnts = GetEnts<EType>();
		if (rEnts.empty()) { return; }
		auto& itEnt = std::find_if(rEnts.begin(), rEnts.end(),
			[&](std::pair<const UInt32, RefKeeper<Entity>>& rEnt)->bool {
				return strcmp(static_cast<EType*>(rEnt.second.GetRef())->GetName(), strName) == 0;
			});
		if (itEnt == rEnts.end()) { return nullptr; }
		return static_cast<EType*>(itEnt->second.GetRef());
	}
	// --setters
	template<class EType, typename ... Args>
	inline RefKeeper<Entity>& EntSys::AddEnt(Args&& ... Arguments) {
		auto& rEnts = GetEnts<EType>();
		RefKeeper<Entity> pEnt;
		pEnt.MakeRef<EType>(std::forward<Args>(Arguments)...);
		rEnts[pEnt->GetId()] = pEnt;
		return rEnts[pEnt->GetId()];
	}
	inline void EntSys::RmvEnt(UInt32 tId, UInt32 eId) {
		auto& rReg = GetRegistry();
		if (rReg.empty()) { return; }
		auto& itEnts = rReg.find(tId);
		if (itEnts == rReg.end()) { return; }
		if (itEnts->second.empty()) { return; }
		auto& itEnt = itEnts->second.find(eId);
		if (itEnt == itEnts->second.end()) { return; }
		itEnts->second.erase(itEnt);
	}
	template<class EType>
	inline void EntSys::RmvEnt(UInt32 eId) { return RmvEnt(TypeIndexator::Get<EType>(), eId); }
}

#endif // NWL_ECS_ENTITY_SYSTEM_H