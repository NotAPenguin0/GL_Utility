#include "Color.h"

namespace Core
{
	namespace Misc
	{

		RGBBase256::RGBBase256(RGBBase256::type r, RGBBase256::type g, RGBBase256::type b, RGBBase256::type a) : m_r(r), m_g(g), m_b(b), m_a(a)
		{

		}

		RGBBase256::RGBBase256(glm::vec4 rgba) : m_r(rgba.x),
			m_g(rgba.y),
			m_b(rgba.z),
			m_a(rgba.w)
		{

		}

		RGBBase256::RGBBase256(glm::vec3 rgb) : m_r(rgb.x),
			m_g(rgb.y),
			m_b(rgb.z),
			m_a(255)
		{

		}

		RGBBase256::type& RGBBase256::r()
		{
			return m_r;
		}

		RGBBase256::type& RGBBase256::g()
		{
			return m_g;
		}

		RGBBase256::type& RGBBase256::b()
		{
			return m_b;
		}

		RGBBase256::type& RGBBase256::a()
		{
			return m_a;
		}

		RGBBase256::type const& RGBBase256::r() const
		{
			return m_r;
		}

		RGBBase256::type const& RGBBase256::g() const
		{
			return m_g;
		}

		RGBBase256::type const& RGBBase256::b() const
		{
			return m_b;
		}

		RGBBase256::type const& RGBBase256::a() const
		{
			return m_a;
		}

		glm::vec4 RGBBase256::MapToRange(int min, int max)
		{
			static const int OLD_MIN = 0, OLD_MAX = 255;
			return glm::vec4(
				Math::MapToRange<float>(m_r, OLD_MIN, OLD_MAX, 0, 1),
				Math::MapToRange<float>(m_g, OLD_MIN, OLD_MAX, 0, 1),
				Math::MapToRange<float>(m_b, OLD_MIN, OLD_MAX, 0, 1),
				Math::MapToRange<float>(m_a, OLD_MIN, OLD_MAX, 0, 1)
			);
		}


		Color::Color() : m_r(0), m_g(0), m_b(0), m_a(1) {}
		Color::Color(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a)
		{

		}

		Color::Color(glm::vec4 rgba) : m_r(rgba.x), m_g(rgba.y), m_b(rgba.z), m_a(rgba.w) {}

		Color::Color(glm::vec3 rgb) : m_r(rgb.x), m_g(rgb.y), m_b(rgb.z), m_a(1.0f) {}

		Color::Color(RGBBase256 rgba) : Color(rgba.MapToRange(0, 1))
		{

		}

		float& Color::r() { return m_r; }
		float& Color::g() { return m_g; }
		float& Color::b() { return m_b; }
		float& Color::a() { return m_a; }

		float const& Color::r() const { return m_r; }
		float const& Color::g() const { return m_g; }
		float const& Color::b() const { return m_b; }
		float const& Color::a() const { return m_a; }

	}
}