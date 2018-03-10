#include "Shape2D.h"

namespace Core
{
	namespace Geometry
	{

		Shape2D::Shape2D(std::vector<Vertex> const& vertices, GLenum usage) : m_vertices(vertices)
		{
			try
			{
				generateBuffer(usage, generateFloatVector(vertices));
			}
			catch (Core::Misc::Exception e)
			{
				logpp::Console::error(e.what());
			}
		}

		Shape2D::Shape2D(std::vector<Vertex::value_type> const& vertices, GLenum usage)
		{
			m_vertices = generateVertexVector(vertices);
			try
			{
				generateBuffer(usage, vertices);
			}
			catch (Core::Misc::Exception e)
			{
				logpp::Console::error(e.what());
			}
		}

		Shape2D::Shape2D(Shape2D && other) : m_buffer(other.m_buffer), m_shader(other.m_shader), m_vertices(other.m_vertices)
		{
			other.m_buffer = 0;
		}

		Shape2D & Shape2D::operator=(Shape2D && other)
		{
			if (this != &other)
			{
				m_buffer = other.m_buffer;
				m_shader = other.m_shader;

				other.m_buffer = 0;

				m_vertices = other.getVertices();
			}
			return *this; 
		}

		Shape2D::~Shape2D()
		{
			release();
		}

		void Shape2D::setShader(Shader* s)
		{
			m_shader = s;
		}

		Shader* Shape2D::getShader() const
		{
			return m_shader;
		}

		std::vector<Vertex> Shape2D::getVertices() const
		{
			return m_vertices;
		}

		bool Shape2D::operator==(Shape2D const& other)
		{
			std::sort(m_vertices.begin(), m_vertices.end());

			auto other_vertices = other.m_vertices;
			std::sort(other_vertices.begin(), other_vertices.end());

			return ::Core::Misc::VectorsAreEqual(m_vertices, other_vertices);
		}

		bool Shape2D::operator!=(Shape2D const& other)
		{
			return !(*this == other);
		}


		void Shape2D::draw() const
		{
			if (m_shader != nullptr)
//				logpp::Console::warning("void Shape2D::draw(): Shader is NULL");
/*			else*/ m_shader->use();

//			logpp::Console::debug("Drawing a Shape2D");

			glEnableVertexAttribArray(ATTRIBUTE_VERTICES);
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
			glVertexAttribPointer(ATTRIBUTE_VERTICES, VTX_PER_TRIANGLE, GL_FLOAT, GL_FALSE, 0, nullptr);
			glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
			glDisableVertexAttribArray(ATTRIBUTE_VERTICES);
		}

		void Shape2D::release()
		{
			m_vertices.clear();
			glDeleteBuffers(1, &m_buffer);
			m_buffer = 0;
		}

		void Shape2D::generateBuffer(GLenum usage, std::vector<Vertex::value_type> vertices)
		{
			if (usage != GL_STATIC_DRAW && usage != GL_DYNAMIC_DRAW)
			{
				throw ::Core::Misc::Exception("Shape2D::generateBuffer(Glenum usage, std::vector<Vertex::value_type> vertices): \
												Invalid usage enum specified (must be either GL_STATIC_DRAW or GL_DYNAMIC_DRAW).");
			}

			glGenBuffers(1, &m_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex::value_type), vertices.data(), usage);
		}

		std::vector<Vertex::value_type> Shape2D::generateFloatVector(std::vector<Vertex> const& v) const
		{
			std::vector<Vertex::value_type> vertex_array(m_vertices.size() * VTX_SIZE); //vertices.size() * VERTEX_SIZE (VTX_SIZE = 3)
			for (std::vector<Vertex::value_type>::size_type i = 0; i < m_vertices.size(); ++i)
			{
				vertex_array[i * VTX_SIZE] = m_vertices[i].x();
				vertex_array[i * VTX_SIZE + 1] = m_vertices[i].y();
				vertex_array[i * VTX_SIZE + 2] = m_vertices[i].z();
			}

			return vertex_array;
		}

		std::vector<Vertex> Shape2D::generateVertexVector(std::vector<Vertex::value_type> const& v) const
		{
			std::vector<Vertex> vertex_array(v.size() / VTX_SIZE);
			for (std::vector<Vertex::value_type>::size_type i = 0; i < v.size(); i++)
			{
				vertex_array[i].x() = v[i * VTX_SIZE];
				vertex_array[i].y() = v[i * VTX_SIZE + 1];
				vertex_array[i].z() = v[i * VTX_SIZE + 2];
			}

			return vertex_array;
		}

	}
}
