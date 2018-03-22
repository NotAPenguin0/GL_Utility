#ifndef _UTILITY_H_
#define _UTILITY_H_

#pragma warning(disable: 4005)

#include <vector>
#include <iostream>

#include <GLM\glm.hpp>

namespace Core
{
	namespace Misc
	{
		template<typename T>
		bool VectorsAreEqual(std::vector<T> const& v1, std::vector<T> const& v2)
		{
			if (v1.size() != v2.size()) return false;
			
			for (std::vector<T>::size_type t = 0; t < v1.size(); ++t)
			{
				if (v1[t] != v2[t]) return false;
			} 

			return true;
		}

		template<typename T>
		void print(std::vector<T> const& v)
		{
			std::cout << "{";
			for (auto const& a : v)
				std::cout << a << ", ";
			std::cout << "}";
		}
	}

	std::ostream& operator<<(std::ostream& out, glm::mat4 const& mat);
}

#endif
