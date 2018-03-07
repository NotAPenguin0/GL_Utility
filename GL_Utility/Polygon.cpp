#include "Polygon.h"

namespace Core
{

	namespace Geometry
	{
		
		Polygon::Polygon(std::vector<Vertex> const& vertices, GLenum usage)
			: Shape2D(generateVertices(vertices), usage)
		{
			
		}


		Polygon::~Polygon()
		{
			Shape2D::~Shape2D();
		}
		
		std::vector<Vertex> Polygon::generateVertices(std::vector<Vertex> old_vertices)
		{
			/*
				Steps:
					1. Create two temporary lines between 2 non adjacent vertices of the Polygon
					2. Find their intersection, this is our middle
					3. Create the final vector, which will containt vertices in this order:
						Middle - old[0] - old[1] - Middle - old[1] - old[2] - ... - old[n] - old[0]
					4. This will give us the correct triangles to draw
			*/

			return std::vector<Vertex>();

		}

	}

}