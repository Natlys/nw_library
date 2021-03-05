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
		/// entity id - entity ref
		using ents = dictionary<ui32, mem_ref<a_ent>>;
		/// type id - entity refs
		using registry = dictionary<ui32, ents>;
	public:
		// --getters
		static inline registry& get_registry() { return s_reg; }
		static inline ents& get_ents(ui32 type_id) { return s_reg[type_id]; }
		static inline mem_ref<a_ent>& get_ent(ui32 ent_id, ui32 type_id) { return s_reg[type_id][ent_id]; }
		template<class etype>
		static ents& get_ents() { return s_reg[type_indexator::get_id<etype>()]; }
		template<class etype>
		static mem_ref<a_ent>& get_ent(ui32 ent_id) { return s_reg[type_indexator::get_id<etype>()][ent_id]; }
		// --predicates
		static inline bit has_ent(ui32 ent_id, ui32 type_id)	{ return s_reg[type_id][ent_id].is_valid(); }
		template<class etype> static bit has_ent(ui32 ent_id)	{ return s_reg[type_indexator::get_id<etype>()][ent_id].is_valid(); }
		// --core_methods
		static void on_init();
		static void on_quit();
		static void del_ent(ui32 ent_id, ui32 type_id);
		template<class etype, typename ... args>
		static mem_ref<a_ent>& new_ent(args&& ... arguments);
		template<class etype>
		static void del_ent(ui32 ent_id) { del_ent(ent_id, type_indexator::get_id<etype>()); }
	private:
		static registry s_reg;
	};
	// --setters
	template<class etype, typename ... args>
	mem_ref<a_ent>& ent_sys::new_ent(args&& ... arguments) {
		auto& ents = get_ents<etype>();
		mem_ref<a_ent> rent_temp;
		rent_temp.make_ref<etype>(std::forward<args>(arguments)...);
		rent[rent->get_ent_id()].set_ref<a_ent>(rent);
		return ents[rent->get_ent_id()];
	}
}
#endif // NWL_ECS_ENTITY_SYSTEM_H