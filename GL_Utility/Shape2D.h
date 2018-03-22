#ifndef _SHAPE_2D_H_
#define _SHAPE_2D_H_

#pragma warning(disable: 4005)

#include "Vertex.h"
#include "Exception.h"
#include "Utility.h"

#include "common\shader\Shader.h"
#include "common\logpp\log++.h"

#include <vector>
#include <algorithm>

namespace Core
{

	class Renderer;

	namespace Geometry
	{

		class Shape2D
		{
		public:
			Shape2D(std::vector<Vertex> const& vertices, GLenum usage = GL_STATIC_DRAW);
			Shape2D(std::vector<Vertex::value_type> const& vertices, GLenum usage = GL_STATIC_DRAW);

			Shape2D(Shape2D const& other) = delete;
			Shape2D& operator=(Shape2D const& other) = delete;

			Shape2D(Shape2D&& other);
			virtual Shape2D& operator=(Shape2D&& other);

			virtual ~Shape2D();

			std::vector<Vertex> getVertices() const;

			void setShader(Shader* s);
			Shader* getShader() const;

			virtual bool operator==(Shape2D const& other);
			virtual bool operator!=(Shape2D const& other);

			friend class Renderer;

			static const unsigned int VTX_SIZE = 3;
			static const unsigned int VTX_PER_TRIANGLE = 3;
		protected:
			/*Override if you don't want to use default mode
			  Default mode:
				-mode = GL_TRIANGLES
				-first = 0
				-count = vtx_count
			*/
			virtual void draw() const;

			virtual void release();

			void generateBuffer(GLenum usage, std::vector<Vertex::value_type> vertices);
			
			std::vector<Vertex::value_type> generateFloatVector(std::vector<Vertex> const& v) const;
			std::vector<Vertex> generateVertexVector(std::vector<Vertex::value_type> const& v) const;

			static const unsigned int ATTRIBUTE_VERTICES = 0;

			Shader* m_shader;
			std::vector<Vertex> m_vertices;
			GLuint m_buffer;

		};

	}

}

#endif
