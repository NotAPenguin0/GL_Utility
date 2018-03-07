#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <vector> //For storing vertices
#include <algorithm> //For std::sort(), used in operator==()

#include "Shape2D.h"

namespace Core
{
	class Renderer;

	namespace Geometry
	{

		class Triangle : public Shape2D
		{
		public:

			//Triangle with 3 vertices all at origin
			Triangle();
			Triangle(Vertex const& v1, Vertex const& v2, Vertex const& v3, GLenum usage = GL_STATIC_DRAW);
			Triangle(std::vector<Vertex> const& vertices, GLenum usage = GL_STATIC_DRAW);
			Triangle(glm::vec3 const& v1, glm::vec3 const& v2, glm::vec3 const& v3, GLenum usage = GL_STATIC_DRAW);
			Triangle(Vertex::value_type const& x1, Vertex::value_type const& y1, Vertex::value_type const& z1,
				Vertex::value_type const& x2, Vertex::value_type const& y2, Vertex::value_type const& z2,
				Vertex::value_type const& x3, Vertex::value_type const& y3, Vertex::value_type const& z3, GLenum usage = GL_STATIC_DRAW);

			//See explanation in Shader.h

			Triangle(Triangle const& other) = delete;
			Triangle& operator=(Triangle const& other) = delete;

			~Triangle();

		private:
			static const int VERTEX_COUNT = 3;

		};
	}
}

#endif

