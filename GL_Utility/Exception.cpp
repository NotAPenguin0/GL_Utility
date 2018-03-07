#include "Exception.h"

namespace Core
{
	namespace Misc
	{

		Exception::Exception(std::string msg) : error(msg) {}
		std::string Exception::what() { return error; }

	}
}