#include <nwl_pch.hpp>
#include "mem_allocator.h"
#include <io/io_error.h>
namespace NW
{
	mem_link* mem_link::get_block(size memory_size) {
		if (block_size >= memory_size) { block_size -= memory_size; return this; }
		mem_link* block_ptr = this;
		mem_link* block_next_ptr = nullptr;
		while (block_ptr != nullptr && block_next_ptr != nullptr) {
			if (block_ptr = block_ptr->block_ptr) {
				if (block_next_ptr = block_ptr->block_ptr) {
					if (block_next_ptr->block_size >= memory_size) {
						block_next_ptr->block_size -= memory_size;
						if (block_ptr->block_size == 0) { block_ptr->block_ptr = block_next_ptr->block_ptr; }
						return block_next_ptr;
					}
				}
				else { break; }
			}
			else { break; }
		}
		return nullptr;
	}
}
namespace NW
{
	a_mem_allocator::a_mem_allocator(ptr memory_ptr, size memory_size) :
		m_data_ptr(static_cast<sbyte*>(memory_ptr)),
		m_data_size(memory_size),
		m_alloc_size(0) { }
	a_mem_allocator::~a_mem_allocator() { }
}
namespace NW
{
	mem_arena::mem_arena(ptr memory_ptr, size memory_size) :
		a_mem_allocator(memory_ptr, memory_size),
		m_free_list(nullptr) { }
	mem_arena::~mem_arena() {}
	// --==<core_methods>==--
	void* mem_arena::alloc(size alloc_size, size align_size) {
		ptr block_ptr = nullptr;
		if (alloc_size == 0) { throw error("attempt to allocate zero memory"); return nullptr; }
		alloc_size = NW_ALIGN_FORWARD(alloc_size, align_size);
		if (alloc_size < sizeof(mem_link)) { alloc_size = sizeof(mem_link); }
		if (m_free_list != nullptr) {
			if (mem_link* free_link = m_free_list->get_block(alloc_size)) {
				block_ptr = free_link;
				if (free_link == m_free_list && m_free_list->block_ptr == nullptr) { m_free_list = m_free_list->block_ptr; }
			}
			else {
				if (has_enough_size(alloc_size)) { block_ptr = &m_data_ptr[m_alloc_size]; }
				else { throw error("the memory has been exhausted!"); }
			}
		}
		else {
			if (has_enough_size(alloc_size)) { block_ptr = &m_data_ptr[m_alloc_size]; }
			else { throw error("the memory has been exhausted!"); }
		}
		m_alloc_size += alloc_size;
		return block_ptr;
	}
	void mem_arena::dealloc(ptr block_ptr, size dealloc_size) {
		if (has_block(block_ptr)) {
			dealloc_size = NW_ALIGN_FORWARD(dealloc_size, sizeof(mem_link));
			if (dealloc_size < sizeof(mem_link)) { dealloc_size = sizeof(mem_link); }
			if ((static_cast<si64>(m_alloc_size) - static_cast<si64>(dealloc_size)) < 0) {
				throw error("memory deallocation violation"); return;
			}
			mem_link* next_free_list = new(block_ptr)mem_link();
			next_free_list->block_ptr = m_free_list;
			next_free_list->block_size = dealloc_size;
			m_free_list = next_free_list;
		}
		else { throw error("the pointer is out of bounds!"); }
		m_alloc_size -= dealloc_size;
	}
	void* mem_arena::realloc(ptr block_ptr, size old_size, size new_size) {
		size copy_size = old_size < new_size ? old_size : new_size;
		ptr realloc_block_ptr = alloc(new_size);
		memcpy(realloc_block_ptr, block_ptr, copy_size);
		dealloc(block_ptr, old_size);
		return realloc_block_ptr;
	}
	// --==</core_methods>==--
}
namespace NW
{
	linear_allocator::linear_allocator(ptr memory_ptr, size memory_size) :
		a_mem_allocator(memory_ptr, memory_size) { }
	linear_allocator::~linear_allocator() { }
	// --==<core_methods>==--
	void* linear_allocator::alloc(size alloc_size, size align_size) {
		ptr block_ptr = nullptr;
		if (alloc_size == 0) { return nullptr; }
		alloc_size = NW_ALIGN_FORWARD(alloc_size, align_size);
		if (!has_enough_size(alloc_size)) {
			throw error("the memory has been exhausted");
			return nullptr;
		}
		block_ptr = &m_data_ptr[m_alloc_size];
		m_alloc_size += alloc_size;
		return block_ptr;
	}
	void linear_allocator::dealloc(ptr block_ptr, size dealloc_size) {
		if (block_ptr != &m_data_ptr[m_alloc_size]) { throw error("deallocation violation"); return; }
		memset(block_ptr, 0, dealloc_size);
		m_alloc_size -= dealloc_size;
	}
	ptr linear_allocator::realloc(ptr block_ptr, size old_size, size new_size) {
		if (block_ptr != &m_data_ptr[m_alloc_size]) { return block_ptr; }
		size copy_size = old_size < new_size ? old_size : new_size;
		ptr realloc_block_ptr = alloc(new_size);
		memcpy(realloc_block_ptr, block_ptr, copy_size);
		dealloc(block_ptr, old_size);
		return realloc_block_ptr;
	}
	void linear_allocator::clear() {
		memset(m_data_ptr, 0, m_data_size);
		m_data_size = 0;
	}
	// --==</core_methods>==--
}