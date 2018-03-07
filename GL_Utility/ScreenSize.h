#ifndef _SCREEN_SIZE_H_
#define _SCREEN_SIZE_H_

#include <utility> //For std::pair

#include "common\logpp\log++.h" //For log_assert

namespace Core
{
	namespace Misc
	{


		class ScreenSize
		{
		public:
			using type = unsigned int;
			using dimensionType = std::pair<type, type>;

			ScreenSize();
			ScreenSize(type w, type h);
			ScreenSize(dimensionType dimensions);

			~ScreenSize();

			type width() const;
			type height() const;


			//Returns a std::pair<ScreenSize::type, ScreenSize::type> with the width as first value and heigth as second value
			dimensionType dimensions() const;
		private:
			type m_width;
			type m_height;

			//Set to 1 so uninitialzed ScreenSize objects will still return valid results when scaling coordinates
			static const type DEFAULT_SIZE = 1;
		};

	}

}
#endif
