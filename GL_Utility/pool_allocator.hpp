#pragma once

#include "mem_util.hpp"
#include "common/logpp/log++.h"

#include <list>
#include <cstdint>
#include <utility>


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
		~pool_allocator();

		std::shared_ptr<T> allocate();

		/*calls destructor and frees memory*/
		void deallocate(T* data);

		size_type size();
	private:
		size_type m_pool_size_elems;

		void* m_data;
		std::list<std::shared_ptr<void>> m_free_data;

//		std::list<void*>::iterator m_next_free;
	};

	template<typename T>
	pool_allocator<T>::pool_allocator(int pool_size_elems) : m_pool_size_elems(pool_size_elems)
	{
		auto bytes = sizeof(T) * pool_size_elems;
		
		m_data = ::operator new(bytes);

#ifdef ALLOCATOR_DEBUG
		std::cout << "pool_allocator::pool_allocator(): allocated " << bytes << " bytes\n";
#endif
		/*Fill free list*/
		while ((--pool_size_elems) >= 0)
		{
			m_free_data.emplace_front(std::shared_ptr<void>((void*)((T*)m_data + pool_size_elems), &identify_delete<void>));
		}
#ifdef ALLOCATOR_DEBUG
		std::cout << "pool_allocator::pool_allocator(): Created free_data list containing following addresses:\n";
		for (auto it = m_free_data.begin(); it != m_free_data.end(); ++it)
		{
			std::cout << it->get() << "\n";
		}
#endif
		

//		m_next_free = m_free_data.begin();
	}

	template<typename T>
	pool_allocator<T>::~pool_allocator()
	{
		for (size_type idx = 0; idx < size(); ++idx)
		{
			auto obj = (T*)m_data + idx;

			//if the object is not in the free list, we can safely destruct it
			if (std::find(m_free_data.begin(), m_free_data.end(), std::shared_ptr<void>((void*)obj, &identify_delete<void>)) == m_free_data.end())
			{
				obj->T::~T();
			}

		}

//		m_free_data.erase(std::remove_if(m_free_data.begin(), m_free_data.end(), [](void*) {return true; }));
		m_free_data.clear();
		//delete allocated memory block
		::operator delete(m_data, size() * sizeof(T));

#ifdef ALLOCATOR_DEBUG
		std::cout << "pool_allocator::~pool_allocator(): deallocated " << sizeof(T) * size() << " bytes\n";
#endif
	}

	template<typename T>
	typename pool_allocator<T>::size_type pool_allocator<T>::size()
	{
		return m_pool_size_elems;
	}

	template<typename T>
	std::shared_ptr<T> pool_allocator<T>::allocate()
	{
		/*Pick first element of the free list, remove it from the free list and return it*/
		if (m_free_data.empty())
		{
#ifdef ALLOCATOR_DEBUG
			logpp::Console::error("pool_allocator::allocate(): pool is not large enough");
#endif
		}
		auto data = m_free_data.begin()->get();

		m_free_data.erase(std::remove(m_free_data.begin(), m_free_data.end(), std::shared_ptr<void>(data, &identify_delete<void>)));

//		std::remove(m_free_data.begin(), m_free_data.end(), (void*)data);

//		m_free_data.erase(m_free_data.begin());

#ifdef ALLOCATOR_DEBUG
		std::cout << "pool_allocator::allocate(): allocated " << sizeof(T) << " bytes at memory location " << data << "\n";
#endif

		return cast_from_void<T>(std::shared_ptr<void>(data), &dont_delete<T>);
	}

	template<typename T>
	void pool_allocator<T>::deallocate(T* data)
	{
		/*check if this is actually allocated data, if it is not a nullptr, and if the data belongs to this allocator
		 *
		 *If all these conditions are met, call the destructor and move it to the free list*/
	}

};

/*
 *list of addresses of starting points for free elements
 *void**
 *->ptr to void*
 *
 **/
