#ifndef NWL_ECS_COMPONENT_SYSTEM_H
#define NWL_ECS_COMPONENT_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_container.h>
#include <core/nwl_type.h>
#include <ecs/ecs_cmp.h>
namespace NWL
{
	/// component_system static class
	/// description:
	/// --core manager of components: creates, destroyes and gives components;
	/// --stores all components in tables of entities;
	/// --any cmp table contains abstract refs to components of particular type;
	/// --all cmp tables are inside of single registry;
	/// --registry: ent_id-table | tables: type_id-ref;
	class NWL_API cmp_sys
	{
		/// table of type_id and component references
		using cmps = dictionary<ui32, mem_ref<a_cmp>>;
		/// table of ent_id and component containers
		using registry = dictionary<ui32, cmps>;
	public:
		// --getters
		static inline registry& get_registry()			{ return s_reg; }
		static inline cmps& get_ent_cmps(ui32 ent_id)	{ return s_reg[ent_id]; }
		static inline mem_ref<a_cmp>& get_cmp(ui32 ent_id, ui32 type_id)	{ return s_reg[ent_id][type_id]; }
		template<class ctype> static mem_ref<a_cmp>& GetCmp(ui32 ent_id)	{ return get_cmp(ent_id, type_indexator::get_id<ctype>()); }
		// --predicates
		static inline bit has_cmp(ui32 ent_id, ui32 type_id) { return s_reg[ent_id][type_id].is_valid(); }
		template<class ctype> static bit has_cmp(ui32 ent_id) { return s_reg[type_indexator::get_id<>()][ent_id]; }
		// --core_methods
		static void on_init();
		static void on_quit();
		static void del_cmp(ui32 ent_id, ui32 type_id);
		template<class ctype, typename ... args>
		static mem_ref<a_cmp>& new_cmp(ui32 ent_id, args& ... arguments);
		template<class ctype>
		static void del_cmp(ui32 ent_id) { del_cmp(ent_id, type_indexator::get_id<ctype>()); }
	private:
		static registry s_reg;
	};
	// --setters
	template<class ctype, typename ... args>
	static mem_ref<a_cmp>& cmp_sys::new_cmp(ui32 ent_id, args& ... arguments) {
		mem_ref<a_cmp>& rcmp = s_reg[ent_id][type_indexator::get_id<ctype>()];
		rcmp.make_ref<ctype>(std::forward<args&>(arguments)...);
		rcmp->m_ent_id = ent_id;
		rcmp.set_ref(rcmp);
		return rcmp;
	}
}

#endif	// NWL_ECS_COMPONENT_SYSTEM_H