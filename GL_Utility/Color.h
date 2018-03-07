#ifndef _COLOR_H_
#define _COLOR_H_

#include <GLM\glm.hpp>
#include "Math.h"

namespace Core
{

	namespace Misc
	{

		class RGBBase256
		{
		public:
			using type = unsigned char;

			RGBBase256(type r, type g, type b, type a = 255);
			RGBBase256(glm::vec4 rgba);
			RGBBase256(glm::vec3 rgb);

			type& r();
			type& g();
			type& b();
			type& a();

			type const& r() const;
			type const& g() const;
			type const& b() const;
			type const& a() const;

			glm::vec4 MapToRange(int min = 0, int max = 1);
		private:
			type m_r, m_g, m_b, m_a;
		};

		class Color
		{
		public:
			Color();
			Color(float r, float g, float b, float a = 1.0f); //All values have to be in valid range [0, 1]
			Color(glm::vec4 rgba); //Assumes all rgba values are in valid range [0, 1]
			Color(glm::vec3 rgb); //Sets alpha to default value of 1
			Color(RGBBase256 rgba);

			float& r();
			float& g();
			float& b();
			float& a();

			float const& r() const;
			float const& g() const;
			float const& b() const;
			float const& a() const;
		private:
			//Values ranging from 0 to 1
			float m_r;
			float m_g;
			float m_b;
			float m_a;
		};

	}

}
#endif
