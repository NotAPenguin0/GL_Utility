#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>

namespace Core
{
	namespace Misc
	{

		class Exception
		{
		public:
			explicit Exception(std::string msg);
			std::string what();
		private:
			std::string error;
		};

	}

}

#endif