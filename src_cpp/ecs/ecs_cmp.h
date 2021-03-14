#ifndef NW_ECS_COMPONENT_H
#define NW_ECS_COMPONENT_H
#include <nwl_core.hpp>
#include <core/nwl_id.h>
#include <core/nwl_type.h>
#include <memory/mem_ref.h>
namespace NW
{
	/// abstract component class
	class NW_API a_cmp : public a_type_owner
	{
	protected:
		a_cmp();
		a_cmp(const a_cmp& copy) = delete;
	public:
		virtual ~a_cmp();
		// --getters
		virtual inline ui32 get_type_id() const = 0;
		virtual inline ui32 get_cmp_id() const = 0;
		// --operators
		inline void operator=(const a_cmp& copy) = delete;
	};
}
namespace NW
{
	/// templated component class
	template <class ctype>
	class NW_API t_cmp : public a_cmp
	{
	protected:
		t_cmp() : a_cmp(), m_cmp_id(get_id_stack().get_free_id()) { }
	public:
		virtual ~t_cmp() { get_id_stack().set_free_id(m_cmp_id); };
		// --getters
		static inline ui32 get_type_id_static()				{ return type_indexator::get_id<ctype>(); }
		virtual inline ui32 get_type_id() const override	{ return type_indexator::get_id<ctype>(); }
		virtual inline ui32 get_cmp_id() const override		{ return m_cmp_id; }
	protected:
		const ui32 m_cmp_id;
	private:
		static id_stack& get_id_stack() { static id_stack s_id_stack(1); return s_id_stack; }
	};
}
#endif	// NW_ECS_COMPONENT_H