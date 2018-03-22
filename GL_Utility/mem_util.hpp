#pragma once

#include <iostream>
#include <memory>

namespace mem
{
	/*Custom deleter that does nothing*/
	template<typename U> void dont_delete(U*) {  }

	template<typename U> void default_deleter(U* obj) { delete obj; }

	template<typename U> void identify_delete(U* obj) { std::cout << "deleting " << obj << "\n"; }

	/*Convert a shared_ptr<void> to shared_ptr<T>
	 *Template parameter U represents the type the resulting smart pointer will hold*/
	template<typename TO, typename Deleter = decltype(default_deleter<TO>)>
	std::shared_ptr<TO> cast_from_void(std::shared_ptr<void> original, Deleter deleter = default_deleter<TO>)
	{
		auto raw_ptr = original.get();
		auto converted_ptr = (TO*)raw_ptr;
		return std::shared_ptr<TO>(converted_ptr, deleter);
	}
};
