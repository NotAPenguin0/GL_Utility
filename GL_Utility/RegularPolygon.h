#ifndef _REGULAR_POLYGON_H_
#define _REGULAR_POLYGON_H_

#pragma warning(disable: 4005)

#include "Math.h"
#include "Utility.h"
#include "Shape2D.h"

#include <ctime>

namespace Core
{
	namespace Geometry
	{		
		class RegularPolygon : public Shape2D
		{
		public:
			using radius_type = Vertex::value_type; 
		
			RegularPolygon(Vertex middle, unsigned int n, radius_type radius, GLenum usage = GL_STATIC_DRAW);

		private:
			std::vector<Vertex> calculateVertices(Vertex middle, radius_type radius, unsigned int n) const;

			radius_type m_radius;
		};
		

	}
}
#endif