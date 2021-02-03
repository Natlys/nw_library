#ifndef NWL_ECS_ENTITY_SYSTEM_H
#define NWL_ECS_ENTITY_SYSTEM_H

#include <nwl_core.hpp>

#include <ecs/ecs_entity.h>

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

#endif // NWL_ECS_ENTITY_SYSTEM_H