#pragma once

#include <cstdint> //for std::uint32_t
#include <cmath>

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

		void* allocate(uint32_t bytes);

		//returns a marker to the top of the stack
		marker top();

		//rolls back stack to specified marker m
//		void free_to_marker(marker m);

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
		std::cout.setf(std::ios::hex);
		std::cout << (marker)m_top;
		std::cout.unsetf(std::ios::hex);
		std::cout << "\n";
#endif
	}

	stack_allocator::~stack_allocator()
	{
		clear();
	}

	void* stack_allocator::allocate(uint32_t bytes)
	{
		if (size + bytes > max_size)
		{
#ifdef ALLOCATOR_DEBUG
			std::cout << "stack_allocator::allocate(): trying to allocate " << bytes << " bytes. Stack is too small\n";
#endif
			return nullptr;
		}

		void* obj = (unsigned char*)m_top + 1;
		//move the top pointer
		m_top = (unsigned char*)m_top + bytes;
#ifdef ALLOCATOR_DEBUG
		std::cout << "stack_allocator::allocate(): allocated " << bytes << " bytes from memory location ";
		std::cout.setf(std::ios::hex);
		std::cout << (marker)obj;
		std::cout.unsetf(std::ios::hex);
		std::cout << "\n";
#endif
		//return pointer to newly allocated object
		return obj;
	}

	void stack_allocator::clear()
	{
		//Free all memory we allocated
		::operator delete(m_root, max_size);
#ifdef ALLOCATOR_DEBUG
		std::cout << "stack_allocator::clear(): deallocated " << max_size << " bytes from memory location ";
		std::cout.setf(std::ios::hex);
		std::cout << (marker)m_root;
		std::cout.unsetf(std::ios::hex);
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
};
