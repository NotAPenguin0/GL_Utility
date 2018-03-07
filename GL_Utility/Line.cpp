#include "Line.h"

namespace Core
{
	namespace Math
	{

		Line2D::Line2D()
		{
		}

		Line2D::Line2D(Vertex const& start, Vertex const& end) : m_start(start), m_end(end), m_slope(calculateSlope())
		{
			if (this->start().x() == this->end().x())
			{
				//line is parallel with x axis
				m_ParallelWithXAxis = true;

				a = b = c = 0;
			}
			else
			{
				m_ParallelWithXAxis = false;
				a = slope();
				b = -1;
				c = -slope() * this->start().x() + this->start().y();
			}
		}

		Line2D::~Line2D()
		{
		}

		Vertex& Line2D::start() { return m_start; }
		Vertex& Line2D::end() { return m_end; }

		Vertex const& Line2D::start() const { return m_start; }
		Vertex const& Line2D::end() const { return m_end; }

		float Line2D::slope() const { return m_slope; }

		bool Line2D::parallel(Line2D const& other)
		{
			return m_slope == other.m_slope;
		}

		float Line2D::calculateSlope()
		{
			return (m_end.y() - m_start.y()) / (m_start.x() - m_end.x());
		}

		Vertex Line2D::intersection(Line2D const& other)
		{
			float x, y;
			if (this->m_ParallelWithXAxis == false && other.m_ParallelWithXAxis == false)
			{
				y = (other.c * this->a - this->c * other.a) / (this->b * other.a - other.b * this->a);
				x = (-this->b * y - this->c) / this->a;
			}
			else
			{
				if (this->m_ParallelWithXAxis)
				{
					x = this->start().x();
					y = (-other.a / other.b) * x - (other.c / other.b);
				}
				else
				{
					x = other.start().x();
					y = (-a / b) * x - (c / b);
				}
			}
			
			return Vertex(x, y);
		}
	}

}
