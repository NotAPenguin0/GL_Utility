#ifndef _REGULAR_POLYGON_H_
#define _REGULAR_POLYGON_H_

#include "Polygon.h"
#include "Math.h"
#include "Utility.h"

namespace Core
{
	namespace Geometry
	{		
		class RegularPolygon : public Shape2D
		{
		public:
			using radius_type = Vertex::value_type; //boo!
		
			RegularPolygon(Vertex middle, unsigned int n, radius_type radius, GLenum usage = GL_STATIC_DRAW);

		private:

			std::vector<Vertex> calculateVertices(Vertex middle, radius_type radius, unsigned int n) const;

			radius_type m_radius;
		};
		

	}
}
#endif