#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#pragma warning(disable: 4005)

#include <vector> //To store vertices
#include <cmath> //For sin()

#include "Vertex.h"
#include "Math.h"
#include "RegularPolygon.h"

#include "common\shader\Shader.h"
#include "common\logpp\log++.h"

namespace Core
{

	namespace Geometry
	{

		class Circle : public RegularPolygon
		{
		public:
			class Precision;

			using radius_type = Vertex::value_type;

			Circle();
			Circle(Vertex const& middle, radius_type radius, GLenum usage = GL_STATIC_DRAW);
			Circle(Vertex const& middle, radius_type radius, Precision p, GLenum usage = GL_STATIC_DRAW);
			~Circle();


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

		private:
			Precision m_drawPrecision;
		};

	}
}

#endif

