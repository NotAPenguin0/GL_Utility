#include "Triangle.h"

namespace Core
{
	namespace Geometry
	{

		using ::Core::Misc::Exception;

		Triangle::Triangle() : Shape2D(std::vector<Vertex>(3, Vertex()))
		{
		}

		Triangle::Triangle(Vertex const & v1, Vertex const & v2, Vertex const & v3, GLenum usage) 
			: Shape2D(std::vector<Vertex> {v1, v2, v3}, usage)
		{

		}

		Triangle::Triangle(std::vector<Vertex> const & vertices, GLenum usage)
			: Shape2D(vertices, usage)
		{
			if (vertices.size() < VERTEX_COUNT)
			{
				throw ::Core::Misc::Exception("Triangle::Triangle(std::vector<Vertex> const&): Vector supplied does not contain enough vertices (minimum is 3).");
			}
		}

		Triangle::Triangle(glm::vec3 const & v1, glm::vec3 const & v2, glm::vec3 const & v3, GLenum usage)
			: Shape2D(std::vector<Vertex> 
									{Vertex(v1.x, v1.y, v1.z), 
									 Vertex(v2.x, v2.y, v2.z),
									 Vertex(v3.x, v3.y, v3.z)
									}, 
					  usage)
		{
	
		}
		Triangle::Triangle(Vertex::value_type const & x1, Vertex::value_type const & y1, Vertex::value_type const & z1,
			Vertex::value_type const & x2, Vertex::value_type const & y2, Vertex::value_type const & z2,
			Vertex::value_type const & x3, Vertex::value_type const & y3, Vertex::value_type const & z3, GLenum usage) 
			:
			Shape2D(std::vector<Vertex::value_type> 
							{
							 x1, y1, z1,
							 x2, y2, z2,
							 x3, y3, z3
							}
					, usage)
		{
		}


		Triangle::~Triangle()
		{
			release();
		}

	}
}
