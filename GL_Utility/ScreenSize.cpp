#include "ScreenSize.h"

namespace Core
{

	namespace Misc
	{

		ScreenSize::ScreenSize() : m_width(DEFAULT_SIZE), m_height(DEFAULT_SIZE)
		{
		}

		ScreenSize::ScreenSize(ScreenSize::type w, ScreenSize::type h) : m_width(w), m_height(h)
		{
			logpp::Console::log_assert(w != 0 && h != 0, "ScreenSize::ScreenSize(ScreenSize::type w, ScreenSize::type h): cannot initialize ScreenSize with zero value as size");
		}

		ScreenSize::ScreenSize(ScreenSize::dimensionType dimensions) : m_width(dimensions.first), m_height(dimensions.second)
		{
			logpp::Console::log_assert(dimensions.first != 0 && dimensions.second != 0,
				"ScreenSize::ScreenSize(ScreenSize::dimensionType dimensions): cannot initialize ScreenSize with zero value as size");
		}

		ScreenSize::type ScreenSize::height() const { return m_height; }
		ScreenSize::type ScreenSize::width()  const { return m_width; }

		ScreenSize::dimensionType ScreenSize::dimensions() const { return std::make_pair(m_width, m_height); }

		ScreenSize::~ScreenSize()
		{
		}
	}
}
