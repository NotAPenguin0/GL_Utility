#include "Vertex.h"

namespace Core
{

	Vertex::Vertex() : m_x(0.0f), m_y(0.0f), m_z(0.0f)
	{

	}

	Vertex::Vertex(Vertex::value_type const& x, Vertex::value_type const& y, Vertex::value_type const& z) : m_x(x), m_y(y), m_z(z)
	{
	}

	Vertex::Vertex(glm::vec3 const& coords) : m_x(coords.x), m_y(coords.y), m_z(coords.z)
	{

	}

	Vertex::Vertex(Vertex::value_type const& x, Vertex::value_type const& y) : m_x(x), m_y(y), m_z(0.0f)
	{

	}

	Vertex::~Vertex()
	{
	}

	Vertex::value_type& Vertex::x() { return m_x; }
	Vertex::value_type& Vertex::y() { return m_y; }
	Vertex::value_type& Vertex::z() { return m_z; }

	Vertex::value_type const& Vertex::x() const { return m_x; }
	Vertex::value_type const& Vertex::y() const { return m_y; }
	Vertex::value_type const& Vertex::z() const { return m_z; }

	glm::vec3 Vertex::to_vec3() const { return glm::vec3(x(), y(), z()); }
	glm::vec4 Vertex::to_vec4() const { return glm::vec4(to_vec3(), 1.0f); }

	Vertex operator-(Vertex const & v)
	{
		return Vertex(-v.m_x, -v.m_y, -v.m_z);
	}

	Vertex Vertex::operator+(Vertex const& v) const
	{
		return Vertex(this->m_x + v.x(), this->m_y + v.y(), this->m_z + v.z());
	}

	Vertex Vertex::operator-(Vertex const& v) const
	{
		return Vertex(*this + (-v));
	}

	Vertex Vertex::operator*(Vertex::value_type scale) const
	{
		return Vertex(this->m_x * scale, this->m_y * scale, this->m_z * scale);
	}

	bool Vertex::operator==(Vertex const& other) const
	{
		return (this->m_x == other.x() && this->m_y == other.y() && this->m_z == other.z());
	}

	bool Vertex::operator!=(Vertex const& other) const
	{

		return !(*this == other);
	}

	bool Vertex::operator<(Vertex const& other) const
	{
		//Only use selected coordinate as return criterion if it is not equal
		//if it is equal, move on to the next one
		//See also Vertex.h for the order in which Vertex coordinates are evaluated
		//First check if the vertices are equal, and return false if this is the case, as this is the
		//< operator, not the <= operator

		if (*this == other)
			return false;

		if (this->x() != other.x())
			return this->x() < other.x();
		if (this->y() != other.y())
			return this->y() < other.y();
		if (this->z() != other.z())
			return this->z() < other.z();

		return false; //This never happens, but the compiler gives me a warning here that I wanted to fix
	}

	bool Vertex::operator<=(Vertex const& other) const
	{
		//Return true if any of the conditions are met, see above for operator< and operator== implementations
		//See also Vertex.h for the order in which Vertex coordinates are evaluated

		return (*this < other) || *this == other;
	}

	bool Vertex::operator>(Vertex const& other) const
	{
		//A > B evaluates to true if !(A <= B) is true, so...
		//See also Vertex.h for the order in which Vertex coordinates are evaluated

		return !(*this <= other);
	}

	bool Vertex::operator>=(Vertex const& other) const
	{
		//A >= B evaluates to true if !(A < B), so...
		//See also Vertex.h for the order in which Vertex coordinates are evaluated

		return !(*this < other);
	}

	std::ostream& operator<<(std::ostream& out, Vertex const& v)
	{
		out << "(" << v.m_x << ", " << v.m_y << ", " << v.m_z << ")";
		return out;
	}

}
