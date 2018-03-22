#include "mem_util.hpp"
#include "assert.h"

namespace mem
{

	template<typename T>
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
	};

};