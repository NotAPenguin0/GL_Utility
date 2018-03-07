#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <vector> //To store vertices
#include <cmath> //For sin()

#include "Vertex.h"
#include "Math.h"

#include "common\shader\Shader.h"
#include "common\logpp\log++.h"

namespace Core
{

	namespace Geometry
	{

		class Circle
		{
		public:
			class Precision;

			using radius_type = Vertex::value_type;

			Circle();
			Circle(Vertex const& middle, radius_type radius);
			Circle(Vertex const& middle, radius_type radius, Precision p);
			~Circle();

			void setShader(Shader* s);
			Shader* getShader();

			void setPrecision(Precision p);
			Precision getPrecision() const;

			//Must be friend to be able to call draw()
			friend class Renderer;


			//Class used for circle precision, holds a value that describes the precision
			//Examples of how precision will be used:
			//If precision is 4, the circle will be drawn as a square
			//Precision = n, the circle will be drawn as a regular polygon with n sides
			class Precision
			{
			public:
				using precision_type = unsigned long;

				Precision(precision_type p);

				precision_type& precision();
				precision_type const& precision() const;

			private:
				precision_type m_p; //precision
			};

			static const Precision DEFAULT_PRECISION;
			static const GLuint ATTRIBUTE_VERTICES = 0;

		private:
			//When the precision changes, the buffer and Vertex Array have to be regenerated

			void generateBuffer(); //Creates the buffer
			void generateVertexArray(); //Fills the m_vertices vector according to the set precision

			//This function has to be called everytime the Circle changes, or the changes won't be applied otherwise
			void setupData();

			//This has to be called everytime the Circle changes, but not in the constructor
			void clearBuffer();

			radius_type m_radius;
			Vertex m_middle;
			Shader* m_shader;
			Precision m_drawPrecision;

			GLuint m_buffer;
			std::vector<Vertex> m_vertices;
			std::vector<Vertex::value_type> m_vertex_array;

			//Called by the renderer
			void draw() const;
		};

	}
}

#endif

