#pragma once

#include <cstdint> //for std::uint32_t
#include <cmath>

#include "mem_util.h"

#ifdef ALLOCATOR_DEBUG
#include <iostream>
#endif

namespace mem
{

	class stack_allocator
	{
	public:
		using marker = uintptr_t;

		explicit stack_allocator(uint32_t stack_size_bytes);
		~stack_allocator();

		std::shared_ptr<void> allocate(uint32_t bytes);

		//overload for allocate() returns a shared pointer to T, memory will be allocated by the other version of allocate()
		template<typename T> std::shared_ptr<T> allocate();

		//returns a marker to the top of the stack
		marker top();

		//rolls back stack to specified marker m
//		void free_to_marker(marker m);

		//deallocates memory if it is at the top of the stack, and sets the pointer passed to nullptr
		template<typename T>
		void deallocate(T* data);

		//deallocates all memory allocated by the stack
		void clear();

	private:
		uint32_t max_size;
		uint32_t size;

		void* m_root;
		void* m_top;
	};


	stack_allocator::stack_allocator(uint32_t stack_size_bytes) : max_size(stack_size_bytes), size(0)
	{
		m_root = ::operator new(stack_size_bytes); //allocate bytes
		m_top = m_root; //set top to root, as currently, nothing is in use
#ifdef ALLOCATOR_DEBUG
		std::cout << "stack_allocator::stack_allocator(): allocated " << stack_size_bytes << " bytes from memory location ";
//		std::cout.setf(std::ios::hex);
		std::cout << m_top;
//		std::cout.unsetf(std::ios::hex);
		std::cout << "\n";
#endif
	}

	stack_allocator::~stack_allocator()
	{
		clear();
	}

	std::shared_ptr<void> stack_allocator::allocate(uint32_t bytes)
	{
		if (size + bytes > max_size)
		{
#ifdef ALLOCATOR_DEBUG
			std::cout << "stack_allocator::allocate(): trying to allocate " << bytes << " bytes. Stack is too small\n";
#endif
			return nullptr;
		}

		void* obj = m_top;
		//move the top pointer
		m_top = (unsigned char*)m_top + bytes;
#ifdef ALLOCATOR_DEBUG
		std::cout << "stack_allocator::allocate(): allocated " << bytes << " bytes from memory location ";
//		std::cout.setf(std::ios::hex);
		std::cout << obj;
//		std::cout.unsetf(std::ios::hex);
		std::cout << "\n";
#endif
		//return pointer to newly allocated object
		return std::shared_ptr<void>(obj, &dont_delete<void>);
	}

	void stack_allocator::clear()
	{
		//Free all memory we allocated
		::operator delete(m_root, max_size);
#ifdef ALLOCATOR_DEBUG
		std::cout << "stack_allocator::clear(): deallocated " << max_size << " bytes from memory location ";
//		std::cout.setf(std::ios::hex);
		std::cout << m_root;
//		std::cout.unsetf(std::ios::hex);
		std::cout << "\n";
#endif
	}

	stack_allocator::marker stack_allocator::top()
	{
		return (uintptr_t)m_top;
	}

/*	void stack_allocator::free_to_marker(marker m)
	{
		auto bytes = abs((unsigned char*)m_top - (unsigned char*)m);

		//Move top
		m_top = (unsigned char*)m_top - bytes;

#ifdef ALLOCATOR_DEBUG
		std::cout << "stack_allocator::free_to_marker(): moved top " << bytes << " bytes from memory location ";
		std::cout.setf(std::ios::hex);
		std::cout << (marker)m_top + bytes;
		std::cout.unsetf(std::ios::hex);
		std::cout << "\n";
#endif
	}
*/

	template<typename T>
	inline std::shared_ptr<T> stack_allocator::allocate()
	{
		return std::shared_ptr<T>(cast_from_void<T>(allocate(sizeof(T), &dont_delete<T>)));
	}

	template<typename T>
	void stack_allocator::deallocate(T* data)
	{
		//#TODO: Ownership checking ("is this data mine?")
		data->T::~T();

		auto bytes = sizeof(T);

		//Move top
		m_top = (unsigned char*)m_top - bytes;

#ifdef ALLOCATOR_DEBUG
		std::cout << "stack_allocator::deallocate(): deallocated " << bytes << " bytes from memory location ";
//		std::cout.setf(std::ios::hex);
		std::cout << m_top;
//		std::cout.unsetf(std::ios::hex);
		std::cout << "\n";
#endif

		data = nullptr;
	}

};
