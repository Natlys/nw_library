#ifndef NWL_MEMORY_ALLOCATOR_H
#define NWL_MEMORY_ALLOCATOR_H
#include <nwl_core.hpp>
#include <core/nwl_info.h>
namespace NWL
{
	/// memory_link struct
	struct NWL_API mem_link
	{
	public:
		mem_link* block_ptr = nullptr;
		size block_size = 0;
	public:
		// --getters
		mem_link* get_block(size nof_bytes);
		// --operators
		template <typename mtype> inline operator mtype*() { return reinterpret_cast<mtype*>(this); }
	};
}
namespace NWL
{
	/// abstract mem_allocator class
	class NWL_API a_mem_allocator
	{
	public:
		a_mem_allocator(ptr memory_ptr = nullptr, size memory_size = 0ul);
		virtual ~a_mem_allocator();
		// --getters
		inline ptr get_data() { return &m_data_ptr[0]; }
		inline size get_data_size() const	{ return m_data_size; }
		inline size get_alloc_size() const	{ return m_alloc_size; }
		inline size get_free_size() const	{ return m_data_size - m_alloc_size; }
		// --predicates
		inline bit has_block(ptr block_ptr) const	{ return (block_ptr >= &m_data_ptr[0]) && (block_ptr <= &m_data_ptr[m_data_size]); }
		inline bit has_enough_size(size szof_memory) const	{ return get_free_size() > szof_memory; }
		// --core_methods
		virtual void* alloc(size memory_size, size align_size = sizeof(mem_link)) = 0;
		virtual void dealloc(ptr block_ptr, size dealloc_size) = 0;
		virtual void* realloc(ptr block_ptr, size old_size, size new_size) = 0;
		template<typename mtype, typename ... Args>
		mtype* new_one(Args&& ... Arguments);
		template<typename mtype>
		mtype* new_arr(ui64 nof_alloc);
		template<typename mtype>
		void del_one(mtype* block_ptr);
		template<typename mtype>
		void del_arr(mtype* block_ptr, ui64 nof_dealloc);
	protected:
		sbyte* m_data_ptr;
		size m_data_size;
		size m_alloc_size;
	};
	template<typename mtype, typename ... args>
	mtype* a_mem_allocator::new_one(args&& ... arguments) {
		mtype* block_ptr = reinterpret_cast<mtype*>(alloc(1ul * sizeof(mtype), __alignof(mtype)));
		new(block_ptr) mtype(std::forward<args>(arguments)...);
		return block_ptr;
	}
	template <typename mtype>
	mtype* a_mem_allocator::new_arr(ui64 nof_alloc) {
		return reinterpret_cast<mtype*>(alloc(nof_alloc* sizeof(mtype), __alignof(mtype)));
	}
	template<typename mtype>
	void a_mem_allocator::del_one(mtype* block_ptr) {
		block_ptr->~mtype();
		dealloc(block_ptr, 1 * sizeof(mtype));
	}
	template <typename mtype>
	void a_mem_allocator::del_arr(mtype* block_ptr, ui64 nof_dealloc) {
		for (size bi = 0; bi < nof_dealloc; bi++) { block_ptr[bi].~mtype(); }
		dealloc(block_ptr, nof_dealloc * sizeof(mtype));
	}
}
namespace NWL
{
	/// memory_arena class
	/// Description:
	/// --Just a chunk of bytes works with Ptr and char* pointers
	class NWL_API mem_arena : public a_mem_allocator
	{
	public:
		mem_arena(ptr memory_ptr = nullptr, size memory_size = 0ul);
		virtual ~mem_arena();
		// --core_methods
		virtual void* alloc(size alloc_size, size align_size = sizeof(mem_link)) override;
		virtual void dealloc(ptr block_ptr, size dealloc_size) override;
		virtual void* realloc(ptr block_ptr, size old_size, size new_size) override;
	private:
		mem_link* m_free_list;
	};
}
namespace NWL
{
	/// linear_memory_allocator class
	class linear_allocator: public a_mem_allocator
	{
	public:
		linear_allocator(ptr memory_ptr = nullptr, size memory_size = 0ul);
		virtual ~linear_allocator();
		// --core_methods
		virtual void* alloc(size alloc_size, size align_size = sizeof(int)) override;
		virtual void dealloc(ptr block_ptr, size dealloc_size) override;
		virtual void* realloc(ptr block_ptr, size old_size, size new_size) override;
		void clear();
	};
}
#endif	// NWL_MEMORY_ALLOCATOR_H