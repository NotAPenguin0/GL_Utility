#pragma once

#include <cstdint>
#include <memory>

#ifdef ALLOCATOR_DEBUG
#include <iostream>
#endif

#include "custom_deleters.h"

namespace mem
{

	template<typename T>
	class test_allocator
	{
	public:


		using size_type = uint32_t;
		using marker = uint32_t;

		/*Creates a stack_allocator
		 *@param count		Memory will be allocated for count instances of T
		 */
		test_allocator(size_type count) : m_amount(count)
		{
			m_data = (T*)(::operator new(sizeof(T) * count));
#ifdef ALLOCATOR_DEBUG
			std::cout << "Allocating " << sizeof(T) * count << " bytes\n";
#endif
		}

		~test_allocator()
		{
			clear();
		}

		/*Returns an std::shared_ptr to the first allocated object.
		 *Note that deleting this pointer does not do anything
		 *Objects allocated by the allocator will be deallocated by the allocator*/
		std::shared_ptr<T> get()
		{
			//This will make sure the user can't delete the pointer, and that he must do it via the allocator
			return std::shared_ptr<T>(m_data, &dont_delete<T>);
		}

		std::shared_ptr<T> get(size_type idx)
		{
			if (idx < 0 || idx >= m_amount) return std::shared_ptr<T>(nullptr, &dont_delete<T>);
			else return std::shared_ptr<T>(&(m_data[idx]), &dont_delete<T>);
		}

		//deallocates all data
		void clear()
		{
			delete[] m_data;
#ifdef ALLOCATOR_DEBUG
			std::cout << "Deleted " << sizeof(T) * m_amount << " bytes\n";
#endif
		}

	private:
		T* m_data;
		size_type m_amount;
	};

};

