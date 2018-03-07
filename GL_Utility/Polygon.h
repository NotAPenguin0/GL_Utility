#ifndef _POlYGON_H_
#define _POLYGON_H_

#include <vector>

#include "Shape2D.h"

#include "common\shader\Shader.h"

namespace Core
{
	class Renderer;
	
	namespace Geometry
	{

		//TODO: Implement
		class Polygon : public Shape2D
		{
		public:
			Polygon(std::vector<Vertex> const& vertices, GLenum usage = GL_STATIC_DRAW);

			Polygon(Polygon const& other) = delete;
			Polygon& operator=(Polygon const& other) = delete;

			virtual ~Polygon();

			friend class Renderer;

		private:
			std::vector<Vertex> generateVertices(std::vector<Vertex> old_vertices);
		}; 

	}

}

#endif