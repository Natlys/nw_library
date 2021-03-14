#ifndef NW_ECS_ENTITY_H
#define NW_ECS_ENTITY_H
#include <nwl_core.hpp>
#include <core/nwl_type.h>
#include <core/nwl_id.h>
#include <core/nwl_container.h>
#include <memory/mem_sys.h>
#include <ecs/ecs_cmp.h>
namespace NW
{
	/// abstract entity class
	/// --main object base class for complex objects;
	/// --allows to construct an object of different components;
	/// --takes responsibility for creation and destruction of all components
	class NW_API a_ent : public a_type_owner
	{
		using cmps = darray<mem_ref<a_cmp>>;
	protected:
		a_ent();
		a_ent(const a_ent& copy) = delete;
	public:
		virtual ~a_ent();
		// --getters
		virtual inline ui32 get_type_id() const = 0;
		virtual inline ui32 get_ent_id() const = 0;
		// --setters
		void set_enabled(bit enable);
		// --predicates
		inline bit is_enabled() { return m_is_enabled; }
		// --predicates
		template<typename etype>
		bit check_type() const { return get_type_id() == type_indexator::get_id<etype>(); }
		// --operators
		inline void operator=(const a_ent& copy) = delete;
	protected:
		bit m_is_enabled;
	};
}
namespace NW
{
	/// templated entity class
	template<class etype>
	class NW_API t_ent: public a_ent
	{
	protected:
		t_ent() : a_ent(), m_ent_id(get_id_stack().get_free_id()) { }
	public:
		virtual ~t_ent() { get_id_stack().set_free_id(m_ent_id); }
		// --getters
		static inline ui32 get_type_id_static() { return type_indexator::get_id<etype>(); }
		virtual inline ui32 get_type_id() const override { return type_indexator::get_id<etype>(); }
		virtual inline ui32 get_ent_id() const override { return m_ent_id; }
	protected:
		const ui32 m_ent_id;
	private:
		static inline id_stack& get_id_stack() { id_stack s_id_stack(1); return s_id_stack; }
	};
}
#endif	// NW_ECS_ENTITY_H