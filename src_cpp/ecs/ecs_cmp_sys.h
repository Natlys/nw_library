#ifndef NW_ECS_COMPONENT_SYSTEM_H
#define NW_ECS_COMPONENT_SYSTEM_H
#include <nwl_core.hpp>
#include <core/nwl_container.h>
#include <core/nwl_type.h>
#include <ecs/ecs_cmp.h>
namespace NW
{
	/// component_system static class
	/// description:
	/// --core manager of components: creates, destroyes and gives components;
	/// --stores all components in tables of entities;
	/// --any cmp table contains abstract refs to components of particular type;
	/// --all cmp tables are inside of single registry;
	/// --registry: ent_id-table | tables: type_id-ref;
	class NW_API cmp_sys
	{
		using cmp_ref = mem_ref<a_cmp>;
		/// table of type_id and component references
		using cmps = dictionary<ui32, cmp_ref>;
		/// table of cmp_id and component containers
		using registry = dictionary<ui32, cmps>;
	public:
		// --getters
		static inline registry& get_registry()						{ return s_reg; }
		static inline cmps& get_cmps(ui32 type_id)					{ return s_reg[type_id]; }
		static inline cmp_ref& get_cmp(ui32 type_id, ui32 cmp_id)	{ return s_reg[type_id][cmp_id]; }
		template<class ctype> static inline cmps& get_cmps()		{ return s_reg[type_indexator::get_id<ctype>()]; }
		template<class ctype> static cmp_ref& get_cmp(ui32 cmp_id)	{ return s_reg[type_indexator::get_id<ctype>()][cmp_id]; }
		// --predicates
		static inline bit has_cmp(ui32 type_id, ui32 cmp_id)		{ return s_reg[type_id].find(cmp_id) != s_reg[type_id].end(); }
		template<class ctype> static bit has_cmp(ui32 cmp_id)		{ return has_ent(type_indexator::get_id<ctype>(), cmp_id); }
		// --core_methods
		static void on_init();
		static void on_quit();
		template<class ctype, typename ... args>
		static void new_cmp(cmp_ref& ref, args& ... arguments);
		static void del_cmp(ui32 type_id, ui32 cmp_id);
		template<class ctype> static void del_cmp(ui32 cmp_id)	{ del_cmp(type_indexator::get_id<ctype>(), cmp_id); }
	private:
		static registry s_reg;
	};
	// --setters
	template<class ctype, typename ... args>
	static void cmp_sys::new_cmp(cmp_ref& ref, args& ... arguments) {
		ref.make_ref<ctype>(std::forward<args&>(arguments)...);
		s_reg[ref->get_type_id()][ref->get_cmp_id()].set_ref<a_cmp>(ref);
	}
}

#endif	// NW_ECS_COMPONENT_SYSTEM_H