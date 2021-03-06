#ifndef NWL_ECS_ENTITY_SYSTEM_H
#define NWL_ECS_ENTITY_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_container.h>
#include <core/nwl_type.h>
#include <ecs/ecs_ent.h>
#include <memory/mem_ref.h>
namespace NWL
{
	/// entity_system static class
	class NWL_API ent_sys
	{
		/// storable reference of an entity
		using ent_ref = mem_ref<a_ent>;
		/// table for entity id - entity ref association
		using ents = dictionary<ui32, ent_ref>;
		/// table for type id - entity refs association
		using registry = dictionary<ui32, ents>;
	public:
		// --getters
		static inline registry& get_registry()						{ return s_reg; }
		static inline ents& get_ents(ui32 type_id)					{ return s_reg[type_id]; }
		template<class etype> static ents& get_ents()				{ return get_ents(type_indexator::get_id<etype>()); }
		static inline ent_ref& get_ent(ui32 ent_id, ui32 type_id)	{ return s_reg[type_id][ent_id]; }
		template<class etype> static ent_ref& get_ent(ui32 ent_id)	{ return get_ent(type_indexator::get_id<etype>(), ent_id); }
		// --predicates
		static inline bit has_ent(ui32 ent_id, ui32 type_id)		{ return s_reg[type_id].find(ent_id) != s_reg[type_id].end(); }
		template<class etype> static bit has_ent(ui32 ent_id)		{ return has_ent(type_indexator::get_id<etype>(), ent_id); }
		// --core_methods
		static void on_init();
		static void on_quit();
		template<class etype, typename ... args>
		static void new_ent(ent_ref& ref, args&& ... arguments);
		static void del_ent(ui32 type_id, ui32 ent_id);
		template<class etype> static void del_ent(ui32 ent_id)		{ del_ent(type_indexator::get_id<etype>(), ent_id); }
	private:
		static registry s_reg;
	};
	// --setters
	template<class etype, typename ... args>
	void ent_sys::new_ent(ent_ref& ref, args&& ... arguments) {
		ref.make_ref<etype>(std::forward<args>(arguments)...);
		s_reg[ref->get_type_id()][ref->get_ent_id()].set_ref<a_ent>(ref);
	}
}
#endif // NWL_ECS_ENTITY_SYSTEM_H