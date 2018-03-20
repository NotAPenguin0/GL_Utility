#pragma once

#include <cstdint>
#include <memory>

namespace mem
{
	template<typename T>
	class stack_allocator
	{
	public:
		template<typename U> void dont_delete( U* ) { /*do nothing*/} 

		using size_type = uint32_t;
		using marker = uint32_t;

		/*Creates a stack_allocator
		 *@param count		Memory will be allocated for count instances of T
		 */
		stack_allocator(size_type count) : m_amount(count)
		{
			m_data = new T(count);
		}

		~stack_allocator()
		{
			clear();
		}

		/*Returns an std::shared_ptr to the first allocated object*/
		std::shared_ptr<T> get()
		{
			//This will make sure the user can't delete the pointer, and that he must do it via the allocator
			return std::shared_ptr<T>(m_data, &dont_delete);
		}

		//deallocates all data
		void clear()
		{
			delete[] m_data;
		}

	private:
		T* m_data;
		size_type m_amount;
	};

};

/*#Idea
 *to implement stack_allocator:
 *alloc(): have a pointer move on from the root up to root + bytes position?
 *
 **/
