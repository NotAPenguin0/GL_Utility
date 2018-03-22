#ifndef _MATH_H_
#define _MATH_H_

#pragma warning(disable: 4005)

#include <cmath>

#include "Vertex.h"
#include "Angle.h"

namespace Core
{

	namespace Math
	{

		Vertex::value_type Distance(Vertex const& v1, Vertex const& v2);

		template<typename T>
		T MapToRange(T val, T old_min, T old_max, T new_min, T new_max)
		{
			return (val - old_min) / (old_max - old_min) * (new_max - new_min) + new_min;
		}

		Angle AngleOfRegularNPolygon(unsigned int n);

		Angle Complement(Angle const& a);
		Angle Supplement(Angle const& a);

		Vertex Middle(Vertex const& v1, Vertex const& v2);
	};

}

#endif

