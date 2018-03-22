#ifndef _VERTEX_H_
#define _VERTEX_H_

#pragma warning(disable: 4005)

#include <GLM\glm.hpp>
#include <iostream>

namespace Core
{

	class Vertex
	{
	public:
		using value_type = float;

		Vertex();
		explicit Vertex(value_type const& x, value_type const& y, value_type const& z);
		explicit Vertex(glm::vec3 const& coords);
		//Constructor for 2D Vertices, will set z coordinate to zero
		explicit Vertex(value_type const& x, value_type const& y);
		Vertex(Vertex const& other) = default;
		~Vertex();

		//Accessor functions

		value_type& x();
		value_type& y();
		value_type& z();

		//Accessors for const Vertex objects

		value_type const& x() const;
		value_type const& y() const;
		value_type const& z() const;

		//Creates a glm::vec3 with this Vertex x, y and z values
		glm::vec3 to_vec3() const;
		//Creates a glm::vec4 with this Vertex x, y and z values. The w value is set to one
		glm::vec4 to_vec4() const;

		//Inverts coordinates
		friend Vertex operator-(Vertex const& v);

		Vertex operator+(Vertex const& v) const;
		Vertex operator-(Vertex const& v) const;

		//Multiplies x, y and z by scale
		Vertex operator*(value_type scale) const;

		bool operator==(Vertex const& other) const;
		bool operator!=(Vertex const& other) const;

		/*Vertex comparision sort order:
			1. x coordinate
			2. y coordinate
			3. z coordinate
			4. If all of these are equal, the vertices are considered equal
		*/
		bool operator<(Vertex const& other) const;
		bool operator<= (Vertex const& other) const;

		bool operator>(Vertex const& other) const;
		bool operator>=(Vertex const& other) const;

		friend std::ostream& operator<<(std::ostream& out, Vertex const& v);

	private:
		value_type m_x;
		value_type m_y;
		value_type m_z;
	};

}

#endif //_VERTEX_H_

