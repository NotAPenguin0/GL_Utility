#include "Angle.h"

namespace Core
{

	namespace Geometry
	{

		const Angle::degrees_type Angle::MAX_DEGREES = 360;

		Angle::Angle() : m_degrees(0)
		{
		}

		Angle::Angle(Angle::degrees_type degrees)
		{
			m_degrees = std::fmod(degrees, MAX_DEGREES);
		}


		Angle::~Angle()
		{
		}

		Angle::degrees_type Angle::degrees() const
		{
			return m_degrees;
		}

		Angle::radians_type Angle::radians() const
		{
			return glm::radians(degrees());
		}

		Angle::operator float() { return degrees(); }

		Angle& Angle::operator+(Angle const& other) const
		{
			return Angle(this->degrees() + other.degrees());
		}

		Angle& Angle::operator-(Angle const& other) const
		{
			return Angle(this->degrees() - other.degrees());
		}

		Angle& Angle::operator*(float scale) const
		{
			return Angle(this->degrees() * scale);
		}

	}
}