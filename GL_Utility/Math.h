#ifndef _MATH_H_
#define _MATH_H_

#include <cmath>

#include "Vertex.h"
#include "Line.h"

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

		float AngleOfRegularNPolygon(unsigned int n);

		float Complement(float a);
		float Supplement(float a);

		Vertex Middle(Vertex const& v1, Vertex const& v2);
	};

}

#endif

