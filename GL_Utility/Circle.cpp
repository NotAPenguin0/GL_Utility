#include "Circle.h"

namespace Core
{
	namespace Geometry
	{

		Circle::Precision::Precision(Circle::Precision::precision_type p) : m_p(p) {}

		Circle::Precision::precision_type&  Circle::Precision::precision() { return m_p; }
		Circle::Precision::precision_type const&  Circle::Precision::precision() const { return m_p; }

		const Circle::Precision Circle::DEFAULT_PRECISION = Circle::Precision(20);

		Circle::Circle() : RegularPolygon(Vertex(), 0, 0, GL_STATIC_DRAW), m_drawPrecision(0)
		{
		}

		Circle::Circle(Vertex const& middle, Circle::radius_type radius, GLenum usage) 
			: RegularPolygon(middle, DEFAULT_PRECISION.precision(), radius, usage), m_drawPrecision(DEFAULT_PRECISION)
		{
		}

		Circle::Circle(Vertex const& middle, Circle::radius_type radius, Circle::Precision p, GLenum usage)
			: RegularPolygon(middle, p.precision(), radius, usage), m_drawPrecision(p)
		{
		}


		Circle::~Circle()
		{
		}

	}

}