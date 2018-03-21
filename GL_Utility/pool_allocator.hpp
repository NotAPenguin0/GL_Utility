#pragma once

#include "mem_util.hpp"
#include "common/logpp/log++.h"

#include <list>
#include <cstdint>


namespace mem
{

	template<typename T>
	class pool_allocator
	{
	public:
		using value_type = T;
		using pointer = T*;

		using size_type = uint32_t;

		pool_allocator(int pool_size_elems);
	private:
		void* m_data;
		std::list<void*> m_free_data;
	};

	template<typename T>
	pool_allocator<T>::pool_allocator(int pool_size_elems)
	{
		auto bytes = sizeof(T) * pool_size_elems;

		m_data = ::operator new(bytes);
#ifdef ALLOCATOR_DEBUG
		std::cout << "pool_allocator::pool_allocator(): allocated " << bytes << " bytes\n";
#endif
		/*Fill free list*/
		while ((--pool_size_elems) >= 0)
		{
			m_free_data.emplace_front((void*)((T*)m_data + pool_size_elems));
		}
#ifdef ALLOCATOR_DEBUG
		std::cout << "pool_allocator::pool_allocator(): Created free_data list containing following addresses:\n";
		for (auto it = m_free_data.begin(); it != m_free_data.end(); ++it)
		{
			std::cout << (void*)(*it) << "\n";
		}
#endif

	}

};