#include "Math.h"

namespace Core
{

	namespace Math
	{

		Vertex::value_type Distance(Vertex const& v1, Vertex const& v2)
		{
			//Calculate distance using the formula d = sqrt( (x1 - x0)² + (y1 - y0)² + (z1 - z0)² )

			return std::sqrt(std::pow(v1.x() - v2.x(), 2) + std::pow(v1.y() - v2.y(), 2) + std::pow(v1.z() - v2.z(), 2));
		}

		Vertex Middle(Vertex const& v1, Vertex const& v2)
		{
			Vertex::value_type x = (v1.x() + v2.x()) / 2;
			Vertex::value_type y = (v1.y() + v2.y()) / 2;
			Vertex::value_type z = (v1.z() + v2.z()) / 2;
			return Vertex(x, y, z);
		}

		Angle AngleOfRegularNPolygon(unsigned int n)
		{
			return ((n - 2) * 180) / n;
		}

		Angle Complement(Angle const& a)
		{
			return Angle(90) - a;
		}

		Angle Supplement(Angle const& a)
		{
			return Angle(180) - a;
		}
	
	}

}