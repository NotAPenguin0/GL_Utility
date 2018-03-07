#include "RegularPolygon.h"

namespace Core
{
	namespace Geometry
	{
		RegularPolygon::RegularPolygon(Vertex middle, unsigned int n, RegularPolygon::radius_type radius, GLenum usage)
			: m_radius(radius), Shape2D(calculateVertices(middle, radius, n), usage)
		{

		}

		std::vector<Vertex> RegularPolygon::calculateVertices(Vertex middle, RegularPolygon::radius_type radius, unsigned int n) const
		{
			const Vertex::value_type z = middle.z();

			
			//Get the radius
			float r = radius;
			//Get the middle coords
			float Mx = middle.x();
			float My = middle.y();
			//Get the angle we are using
			float a = Math::AngleOfRegularNPolygon(n);
			float b = Math::Supplement(a);
			float c = Math::Complement(a);

			std::vector<Vertex> vertices;


//			logpp::Console::debug(std::to_string(start.x()) + " " + std::to_string(start.y()) + " " + std::to_string(start.z()));

			unsigned int count = 1;

			do
			{
				Vertex current;
				current.x() = cos(glm::radians(c - (count - 1) * b)) * r + Mx; //2+2=4-1=3 QUICK MATHS
				current.y() = sin(glm::radians(c - (count - 1) * b)) * r + My;
				current.z() = z;

				vertices.push_back(current);

				++count;

			} while (count <= n);
		

			//Now we have the vertices in the right order, we have to make triangles of it:

			std::vector<Vertex> final_vertices;

			for (std::vector<Vertex>::size_type i = 0; i < vertices.size() - 1; ++i)
			{
//				logpp::Console::log(std::to_string(i));
				final_vertices.push_back(middle);
				final_vertices.push_back(vertices[i]);
				final_vertices.push_back(vertices[(i + 1)/* % vertices.size*/]);
			}

			final_vertices.push_back(middle);
			final_vertices.push_back(vertices[vertices.size() - 1]);
			final_vertices.push_back(vertices[0]);


			return final_vertices;
		}
	}
}