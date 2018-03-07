#include "Circle.h"

namespace Core
{
	namespace Geometry
	{

		Circle::Precision::Precision(Circle::Precision::precision_type p) : m_p(p) {}

		Circle::Precision::precision_type&  Circle::Precision::precision() { return m_p; }
		Circle::Precision::precision_type const&  Circle::Precision::precision() const { return m_p; }

		const Circle::Precision Circle::DEFAULT_PRECISION = Circle::Precision(4);

		Circle::Circle() : m_middle(/*Creates Vertex at origin*/), m_radius(0), m_drawPrecision(DEFAULT_PRECISION)
		{
			setupData();
		}

		Circle::Circle(Vertex const& middle, Circle::radius_type radius) : m_middle(middle), m_radius(radius), m_drawPrecision(DEFAULT_PRECISION)
		{
			setupData();
		}

		Circle::Circle(Vertex const& middle, Circle::radius_type radius, Circle::Precision p)
			: m_middle(middle), m_radius(radius), m_drawPrecision(p)
		{
			setupData();
		}


		Circle::~Circle()
		{
		}

		void Circle::setShader(Shader* s) { m_shader = s; }
		Shader* Circle::getShader() { return m_shader; }

		void Circle::setPrecision(Precision p)
		{
			m_drawPrecision = p;
			clearBuffer();
			setupData();
		}

		Circle::Precision Circle::getPrecision() const { return m_drawPrecision; }

		inline void error()
		{
			auto errID = glGetError();

			auto error = glewGetErrorString(errID);
			std::cout << errID << ": ";
			std::cout << error << "\n";
		}

		void Circle::draw() const
		{
			if (m_shader != nullptr)
				m_shader->use();

			static const GLuint VERTICES_PER_LINE = 2;

			error();

			glEnableVertexAttribArray(ATTRIBUTE_VERTICES);
			error();
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
			error();
			glVertexAttribPointer(ATTRIBUTE_VERTICES, VERTICES_PER_LINE, GL_FLOAT, GL_FALSE, 0, nullptr);
			error();

			//CRASHES ON NEXT OPENGL FUNCTION CALL

		//	glDrawArrays(GL_LINES, 0, VERTICES_PER_LINE);
			glDrawArrays(GL_LINES, 0, m_vertices.size());
			glDisableVertexAttribArray(ATTRIBUTE_VERTICES);
		}

		void Circle::setupData()
		{
			//First create the vertex array, so we can write it to the buffer in the generateBuffer() function
			generateVertexArray();
			generateBuffer();
		}

		void Circle::clearBuffer()
		{
			m_vertices.clear();
			m_vertex_array.clear();
			glDeleteBuffers(1, &m_buffer);
		}

		void Circle::generateBuffer()
		{
			glGenBuffers(1, &m_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

			//Before writing the data, we have to convert the array of vertices to an array of floats

			static const unsigned int VERTEX_SIZE = 3;
			m_vertex_array.clear();
			m_vertex_array.resize(m_vertices.size() * VERTEX_SIZE);
			for (std::vector<Vertex::value_type>::size_type i = 0; i < m_vertices.size(); ++i)
			{
				m_vertex_array[i * VERTEX_SIZE] = m_vertices[i].x();
				m_vertex_array[i * VERTEX_SIZE + 1] = m_vertices[i].y();
				m_vertex_array[i * VERTEX_SIZE + 2] = m_vertices[i].z();
			}

			for (std::vector<Vertex::value_type>::size_type i = 0; i < m_vertex_array.size(); ++i)
			{
				logpp::Console::debug(std::to_string(m_vertex_array[i]));
			}

			glBufferData(m_buffer, m_vertex_array.size() * sizeof(Vertex::value_type), m_vertex_array.data(), GL_STATIC_DRAW); //TODO: allow setting GL_STATIC_DRAW or GL_DYNAMIC_DRAW
		}

		//TODO: Add formulas to Math.h
		void Circle::generateVertexArray()
		{
			//There is alot of math in this function, so I will explain,
			//See also the attached image file for a drawing of the situation
			/*
			As said, as Circle will be drawn as a regular polygon with n sides, where n is the precision that is currently set
			Let r be the radius of the circle we want to draw, and n be the precision set (the number of sides of the polygon)
			Then the length of one side Sn = 2 * r * sin(180° / n)
			The angle of one corner of the polygon is a = ( (n - 2) * 180° ) / n
			We come to this formula by saying that the sum of all angles of the polygon is (n - 2) * 180°
			Divide this by the number of corners we have, and we have the angle of one corner.
			Let the coordinates of the middle of the circle be (xM, yM)

			Now we know what's given, lets move on to the algorithm itself
			The way the algorithm will work is as follows:
			We will generate the Vertices clockwise, starting with the one straight above the middle of the circle.
			We calculate the coord of the Vertex that we're currently at, add this to the vertex list, and move on to the next vertex

			Calculating the Vertex coordinates is what makes this algorithm complicated. The first vertex is easy:
			co(A) = (Xm, yM + r)
			To calculate the coordinate of the next vertex we use two mathematical formulas:
				1. The sine rule
				2. Pythagoras
			Let's simplify the situation: We have the middle M, and a point A(Xm, Ym + r) and a point B(x, y) that we don't know
			To simplify this situation, we can put M at the origin, and transform the coordinates later by adding Xm and Ym to the result
			This leaves us with a middle M(0, 0), a point A(0, r) and B(x, y)
			Since we know that B is part of the circle, we know that |MB| = |MA| = r, this length is important to calculate the y coordinate
			Let's call the angle AOB b. To calculate this angle, we use the fact that the sum of the angles of a triangle is 180°.
			Now we know that AÔB = 180° - OÂB - OBA
			Since A and B are both corners of the polygon, we know that they both are equal to a, which we defined as ( (n - 2) * 180° ) / n
			This means that OAB and OBA are both equal to a / 2, which leads us to the fact that AÔB = 180° - a.
			Now we can state that b = 180° - a. We can use this information together with the sine rule to calculate the x coordinate.
			The sine rules states that in triangle, the following is always true:
			sin(A) / a = sin(B) / b = sin(C) / c
			We will use this rule in triangle OBD to calculate |BD|, which is the x coordinate of B:
			sin(D) / |OB| = sin(O) / |BD|
			since we know D = 90°, O = 180° - a, and |OB| = r, we can fill in and work out to |BD|
			<=> sin(90°) / |OB| = sin(180° - a) / |BD|
			<=> 1 / r = sin(a) / |BD|			(the sines of supplementary angles are equal)
			<=> |BD| = sin(a) / (1 / r)
			<=> |BD| = sin(a) * r
			<=> x = sin(a) * r

			Now we know the x coordinate of B. The y coordinate is relatively simple now, since we know x.
			By using Pythagoras in triange OBD we can state that
			|OB|² = |OD|² + |BD|²
			We calculated |BD| in the previous step, and |OB| is the radius, so
			r² = y² + x²
			y² = r² - x²
			y = sqrt(r² - x²)

			Now we know the coordinates of B: ( sin(a) * r, sqrt(r² - ( sin(a) * r)² ),
			where a = ( (n - 2) * 180° ) / n

			Finally, we need to transform our coordinates back to global space, as we worked with the circle middle as origin for now, so:
			co(B) = ( sin(a) * r + Mx, sqrt(r² - ( sin(a) * r)² + My)

			Unfortunately this whole approach only works for the first coordinate we need to find. Afterwards, this is no longer true.
			Luckily there is a way to solve this. First, let's temporarily set our radius to 1, and scale the coordinates later.
			This way, we get
			co(B) = ( sin(a), sqrt(1 - sin²(a) ) )
			<=> co(B) = ( sin(a), sqrt( cos²(a) ) )
			<=> co(B) = ( sin(a), cos(a) )

			This is already a lot simpler than before.
			Now we need a general case, because the angle a changes for every new coordinate
			We have already stated that AÔB, aka b is equal to 180° - a.
			We need to know the angle the x-axis makes with our point that we want the coordinate of. To do so, we need to introduce a new
			angle c. This angle is the complement of b, so 90° - b
			For a specific point Xn on the polygon, we can say that
			co(Xn) = ( cos(c + (n - 1) * b), sin(c + (n - 1) * b) )
			Now we apply the transformations by first scaling by r and then adding Mx and My:

			co(Xn) = ( cos(c + (n - 1) * b) * r + Mx, sin(c + (n - 1) * b) * r + My )
			*/


			//z value will be constant, as we're only drawing 2D circles
			const Vertex::value_type z = m_middle.z();

			//Get our number of polygon sides
			unsigned int n = m_drawPrecision.precision();
			//Get the radius
			float r = m_radius;
			//Get the middle coords
			float Mx = m_middle.x();
			float My = m_middle.y();
			//Get the angle we are using
			float a = Math::AngleOfRegularNPolygon(n);
			float b = Math::Supplement(a);
			float c = Math::Complement(a);

			//The rest will be given without comments, all is explained in detail above

			Vertex start(Mx, My + r, z);
			m_vertices.push_back(start);

			logpp::Console::debug(std::to_string(start.x()) + " " + std::to_string(start.y()) + " " + std::to_string(start.z()));

			unsigned int count = 1;

			do
			{
				Vertex current;
				current.x() = cos(glm::radians(c + (count - 1) * b)) * r + Mx;
				current.y() = sin(glm::radians(c + (count - 1) * b)) * r + My;
				current.z() = z;



				logpp::Console::debug(std::to_string(current.x()) + " " + std::to_string(current.y()) + " " + std::to_string(current.z()));

				if (count > n - 1)
					break;

				m_vertices.push_back(current);

				++count;
			} while (true);


		}

	}

}