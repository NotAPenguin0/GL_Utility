#pragma once

#include "mem_util.hpp"
#include "assert.h"

#include <utility>
#include <type_traits>

namespace mem
{

	template<typename T, size_t block_size = 4096>
	class pool_allocator
	{
	public:
		//Member types
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using const_pointer = const T*;
		using const_reference = const T&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;

		//#TODO: Constructors, copy assignment, etc

		pointer allocate();
		void deallocate(pointer p);

		template<typename U, typename... Args>
		pointer construct(U* p, Args&&... args);

		template<typename U>
		void destroy(U* p);

		template<typename U, typename... Args>
		pointer newElement(U* p, Args&&... args);

		template<typename U>
		void deleteElement(U* p);

		size_type max_size() const;

	private:
		union slot
		{
			value_type element;
			slot* next;
		};

		slot* m_current_block;
		slot* m_current_slot;
		slot* m_last_slot;
		slot* m_free_slot;

		using data_ptr = char*;

		void allocate_block();
		size_type pad_pointer(data_ptr p, size_type align) const;

		STATIC_ASSERT(block_size >= 2 * sizeof(slot), "pool_allocator(): block size is too small");
	};

	template<typename T, size_t block_size>
	typename pool_allocator<T, block_size>::size_type pool_allocator<T, block_size>::pad_pointer(data_ptr p, size_type align) const
	{
		auto result = reinterpret_cast<uintptr_t>(p);
		return ((align - result) % align);
	}

	template<typename T, size_t block_size>
	void pool_allocator<T, block_size>::allocate_block()
	{
		//Allocate a new block
		auto new_block = reinterpret_cast<data_ptr>(::operator new(block_size));

		//set next
		reinterpret_cast<slot*>(new_block)->next = m_current_block;

		//set current block to newly allocated block
		m_current_block = reinterpret_cast<slot*>(new_block);

		//do pointer alignment
		auto body = new_block + sizeof(slot*);
		auto body_padding = pad_pointer(body, alignof(slot));

		m_current_slot = reinterpret_cast<slot*>(body + body_padding);
		m_last_slot = reinterpret_cast<slot*>(new_block + block_size - sizeof(slot) + 1);
		
	}

	/*Pseudo:
	 *If we have a free slot, move to next and return
	 *
	 *Else: 
	 *if current slot is last slot -> new mem
	 *return next current slot*/
	template<typename T, size_t block_size>
	typename pool_allocator<T, block_size>::pointer pool_allocator<T, block_size>::allocate()
	{
		/*Check if there are still free slots available*/
		if (m_free_slot != nullptr)
		{
			/*Create the T* pointer and move on to next free slot*/
			auto result = reinterpret_cast<pointer>(m_free_slot);
			m_free_slot = m_free_slot->next;
			return result;
		}
		else
		{
			if (m_current_slot >= m_last_slot)
				allocate_block();
			return reinterpret_cast<pointer>(m_current_slot++);
		}
	}

	template<typename T, size_t block_size>
	void pool_allocator<T, block_size>::deallocate(pointer p)
	{
		if (p != nullptr)
		{
			reinterpret_cast<slot*>(p)->next = m_free_slot;
			m_free_slot = reinterpret_cast<slot*>(p);
		}
	}

	template<typename T, size_t block_size>
	typename pool_allocator<T, block_size>::size_type pool_allocator<T, block_size>::max_size() const
	{
		size_type max_blocks = -1 / block_size;
		return (block_size - sizeof(data_ptr)) / sizeof(slot) * max_blocks;
	}

	template<typename T, size_t block_size>
	template<typename U, typename... Args>
	void pool_allocator<T, block_size>::construct(U* p, Args&&... args)
	{
		new (p) U(std::forward<Args>(args)...);
	}

	template<typename T, size_t block_size>
	template<typename U>
	void pool_allocator<T, block_size>::destroy(U* p)
	{
		p->U::~U();
	}


};