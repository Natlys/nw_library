#ifndef NW_MEMORY_REF_H
#define NW_MEMORY_REF_H
#include <nwl_core.hpp>
#include <memory/mem_allocator.h>
#include <memory/mem_sys.h>
namespace NW
{
	/// mem_ref class
	/// Description:
	/// -- Smart "shared" pointer in nw implementation
	/// -- Allocates object due to given allocator
	/// -- The reference gets deleted if there is no any other mem_refs for it
	/// Interface:
	/// -> Create mem_ref -> MakeRef with particular allocator -> set_ref for other keepers -> use as a pointer
	template <typename mtype>
	class NW_API mem_ref : public a_mem_user
	{
	public:
		mem_ref();
		mem_ref(mtype& ref);
		mem_ref(const mem_ref<mtype>& copy);
		template<typename vtype> mem_ref(const mem_ref<vtype>& copy);
		~mem_ref() { reset(); }
		// --getters
		inline mtype* get_ref()		{ return static_cast<mtype*>(m_ref); }
		inline ui64* get_counter()	{ return m_counter; }
		template<typename vtype>
		inline vtype* get_ref()		{ return static_cast<vtype*>(m_ref); }
		// --setters
		void set_ref(mtype& rRef);
		void set_ref(const mem_ref<mtype>& rmem_ref);
		template<typename vtype>
		void set_ref(const mem_ref<vtype>& rmem_ref);
		void reset();
		// --predicates
		inline bit is_valid() { return m_ref != nullptr && m_counter != nullptr; }
		// --operators
		inline operator bit()					{ return m_ref != nullptr; }
		inline mtype* operator->()				{ return (m_ref); }
		inline mtype& operator*()				{ return *(m_ref); }
		inline operator mtype* ()				{ return static_cast<mtype*>(m_ref); }
		inline operator mtype& ()				{ return static_cast<mtype&>(*m_ref); }
		inline const mtype* operator->()const	{ return (m_ref); }
		inline const mtype& operator*() const	{ return *(m_ref); }
		inline operator const mtype* () const	{ return static_cast<const mtype*>(m_ref); }
		inline operator const mtype& () const	{ return static_cast<const mtype&>(*m_ref); }
		inline mem_ref<mtype>& operator=(const mem_ref<mtype>& copy){ set_ref(copy); return *this; }
		template<typename vtype> operator vtype*()					{ return static_cast<vtype*>(m_ref); }
		template<typename vtype> operator const vtype*() const		{ return static_cast<const vtype*>(m_ref); }
		template<typename vtype>
		operator mem_ref<vtype>() { mem_ref<vtype> memmem_ref(*this); return memmem_ref; }
		// --core_methods
		template <typename vtype, typename ... args>
		void make_ref(args&& ... arguments);
	private:
		mutable mtype* m_ref;
		mutable ui64* m_counter;
	};
	// --constructors_destructors
	template <typename mtype>
	mem_ref<mtype>::mem_ref() : m_ref(nullptr), m_counter(nullptr) { reset(); }
	template <typename mtype>
	mem_ref<mtype>::mem_ref(mtype& rRef) : mem_ref() { set_ref(rRef); }
	template <typename mtype>
	mem_ref<mtype>::mem_ref(const mem_ref<mtype>& copy) : mem_ref() { set_ref(copy); }
	template <typename mtype> template <typename vtype>
	mem_ref<mtype>::mem_ref(const mem_ref<vtype>& copy) : mem_ref() { set_ref<vtype>(copy); }
	// --setters
	template <typename mtype>
	void mem_ref<mtype>::set_ref(mtype& rRef) {
		reset();
		m_ref = &rRef;
		m_counter = mem_sys::new_one<ui64>();
		*m_counter = 1;
	}
	template <typename mtype>
	void mem_ref<mtype>::set_ref(const mem_ref<mtype>& rmem_ref) {
		reset();
		mem_ref<mtype>& ref_keeper = const_cast<mem_ref<mtype>&>(rmem_ref);
		m_ref = ref_keeper.get_ref<mtype>();
		m_counter = ref_keeper.get_counter();
		if (m_counter != nullptr) { *m_counter += 1; }
	}
	template <typename mtype> template <typename vtype>
	void mem_ref<mtype>::set_ref(const mem_ref<vtype>& rmem_ref) {
		reset();
		mem_ref<vtype>& ref_keeper = const_cast<mem_ref<vtype>&>(rmem_ref);
		m_ref = ref_keeper.get_ref<mtype>();
		m_counter = ref_keeper.get_counter();
		if (m_counter != nullptr) { *m_counter += 1; }
	}
	template <typename mtype>
	void mem_ref<mtype>::reset() {
		if (m_counter != nullptr) {
			*m_counter -= 1;
			if (*m_counter == 0) {
				delete m_ref;
				m_ref = nullptr;
				mem_sys::dealloc(m_counter, sizeof(*m_counter));
				m_counter = nullptr;
			}
		}
		m_ref = nullptr;
		m_counter = nullptr;
	}
	// --core_methods
	template <typename mtype> template <typename vtype, typename ... args> 
	void mem_ref<mtype>::make_ref(args&& ... arguments) {
		reset();
		m_ref = new vtype(std::forward<args>(arguments)...);
		m_counter = mem_sys::new_one<ui64>();
		*m_counter = 1;
	}
}

#endif	// NW_MEMORY_REF_H