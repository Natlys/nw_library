#ifndef NWL_MEMORY_SYSTEM_H
#define NWL_MEMORY_SYSTEM_H
#include <nwl_core.hpp>
#include <memory/mem_allocator.h>
namespace NWL
{
	/// memory_system static class
	class NWL_API mem_sys
	{
	public:
		// --getters
		static inline a_mem_allocator& get_memory() { return s_memory; }
		// --core_methods
		static void on_init(size memory_size = 1 << 20);
		static void on_quit();
		static inline void* alloc(size alloc_size, size align_size = sizeof(mem_link)) { return s_memory.alloc(alloc_size, align_size); }
		static inline void dealloc(ptr block_ptr, size dealloc_size) { s_memory.dealloc(block_ptr, dealloc_size); }
		static inline void* realloc(ptr block_ptr, size new_size, size old_size) { return s_memory.realloc(block_ptr, old_size, new_size); }
		// --templated_methods
		template<typename mtype, typename ... args> static inline mtype* new_one(args&& ... arguments);
		template<typename mtype> static inline mtype* new_arr(ui64 unAlloc);
		template<typename mtype> static inline void del_one(mtype* block_ptr);
		template <typename mtype> static inline void del_arr(mtype* block_ptr, ui64 unDealloc);
	private:
		static mem_arena s_memory;
	};
	// --templated_methods
	template<typename mtype, typename ... args>
	inline mtype* mem_sys::new_one(args&& ... arguments) { return s_memory.new_one<mtype>(std::forward<args>(arguments)...); }
	template <typename mtype>
	inline mtype* mem_sys::new_arr(ui64 unAlloc) { return s_memory.new_arr<mtype>(unAlloc); }
	template<typename mtype>
	inline void mem_sys::del_one(mtype* block_ptr) { s_memory.del_one<mtype>(block_ptr); }
	template <typename mtype>
	inline void mem_sys::del_arr(mtype* block_ptr, ui64 unDealloc) { s_memory.del_arr<mtype>(block_ptr, unDealloc); }
}
namespace NWL
{
	/// abstract memory_user
	/// description:
	/// -- overrides default new/delete operators
	/// that the the memory is allocated by memory system
	class NWL_API a_mem_user
	{
	public:
		// --operators
		inline void* operator new(size alloc_size, ptr block_ptr) { return ::operator new(alloc_size, block_ptr); }
		inline void* operator new(size alloc_size) { return mem_sys::alloc(alloc_size); }
		inline void* operator new[](size alloc_size) { return mem_sys::alloc(alloc_size); }
		inline void operator delete(ptr block_ptr, size dealloc_size) { mem_sys::dealloc(block_ptr, dealloc_size); }
		inline void operator delete[](ptr block_ptr, size dealloc_size) { mem_sys::dealloc(block_ptr, dealloc_size); }
	};
}

#endif	// NWL_MEMORY_SYSTEM_H