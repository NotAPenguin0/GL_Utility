#pragma once

#include <cstdint> //for std::uint32_t

namespace mem
{

	class stack_allocator
	{
	public:
		using marker = uint32_t;

		explicit stack_allocator(uint32_t stack_size_bytes);
		~stack_allocator();

		void* allocate(uint32_t bytes);

	private:
		void* m_root;
		void* m_top;
	};

	stack_allocator::stack_allocator(uint32_t stack_size_bytes)
	{
		m_root = ::operator new(stack_size_bytes); //allocate bytes
		m_top = (unsigned char*)m_root + stack_size_bytes; //set top pointer
	}

	stack_allocator::~stack_allocator()
	{

	}

	void* stack_allocator::allocate(uint32_t bytes)
	{

	}
};
