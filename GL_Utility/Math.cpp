#include "Math.h"

namespace Core
{

	Vertex::value_type Math::Distance(Vertex const& v1, Vertex const& v2)
	{
		//Calculate distance using the formula d = sqrt( (x1 - x0)² + (y1 - y0)² + (z1 - z0)² )

		return std::sqrt(std::pow(v1.x() - v2.x(), 2) + std::pow(v1.y() - v2.y(), 2) + std::pow(v1.z() - v2.z(), 2));
	}

	Vertex Math::Middle(Vertex const& v1, Vertex const& v2)
	{
		Vertex::value_type x = (v1.x() + v2.x()) / 2;
		Vertex::value_type y = (v1.y() + v2.y()) / 2;
		Vertex::value_type z = (v1.z() + v2.z()) / 2;
		return Vertex(x, y, z);
	}

	float Math::AngleOfRegularNPolygon(unsigned int n)
	{
		return ((n - 2) * 180) / n;
	}

	float Math::Complement(float a)
	{
		return 90 - a;
	}

	float Math::Supplement(float a)
	{
		return 180 - a;
	}

}