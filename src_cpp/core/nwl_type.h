#ifndef NW_TYPE_H
#define NW_TYPE_H
#include <nwl_core.hpp>
#include <memory/mem_sys.h>
namespace NW
{
	class NW_API type_indexator
	{
	public:
		template <typename type>
		static const ui32 get_id() { static const ui32 s_type_id{ s_curr_id++ }; return s_type_id; }
		static const ui32 get_id() { return s_curr_id; }
	private:
		static ui32 s_curr_id;
	};
}
namespace NW
{
	/// abstract type_owner class
	class NW_API a_type_owner : public a_mem_user
	{
	protected:
		a_type_owner();
	public:
		virtual ~a_type_owner();
		// --getters
		virtual inline ui32 get_type_id() const = 0;
		// --predicates
		template<typename ctype>
		bit check_type_id() const	{ return get_type_id() == type_indexator::get_id<ctype>(); }
	};
	/// templated type_owner class
	template<typename type>
	class NW_API t_type_owner : public a_mem_user
	{
	protected:
		t_type_owner() { }
	public:
		virtual ~t_type_owner() { }
		// --getters
		static inline ui32 get_type_id_static()				{ return type_indexator::get_id<type>(); }
		virtual inline ui32 get_type_id() const override	{ return type_indexator::get_id<type>(); }
	};
}
#endif	// NW_TYPE_H