#ifndef _ANGLE_H_
#define _ANGLE_H_

#include <GLM\glm.hpp>
#include <cmath>

namespace Core
{

	namespace Math
	{

		class Angle
		{
		public:
			using radians_type = float;
			using degrees_type = float;

			Angle(degrees_type degrees);
			Angle();
			~Angle();

			operator float();

			degrees_type degrees() const;
			radians_type radians() const;

			Angle& operator+(Angle const& other) const;
			Angle& operator-(Angle const& other) const;
			Angle& operator*(float scale) const;

			static const degrees_type MAX_DEGREES;
		private:
			degrees_type m_degrees;
		};

	}
}

#endif

