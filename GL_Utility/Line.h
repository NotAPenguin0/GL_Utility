#ifndef _LINE_H_
#define _LINE_H_

#include "Vertex.h"

namespace Core
{
	
	namespace Math
	{

		class Line2D
		{
		public:
			Line2D();
			Line2D(Vertex const& start, Vertex const& end);

			~Line2D();

			Vertex& start();
			Vertex& end();

			Vertex const& start() const;
			Vertex const& end() const;

			float slope() const;

			Vertex intersection(Line2D const& other);

			bool parallel(Line2D const& other);
			bool contains(Vertex const& point);

		private:
			Vertex m_start;
			Vertex m_end;

			float m_slope;
			float a, b, c; //l <-> ax + by + c = 0

			bool m_ParallelWithXAxis;

			float calculateSlope();
		};

	}

}
#endif