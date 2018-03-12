#include "Utility.h"

namespace Core
{

	std::ostream& operator<<(std::ostream& out, glm::mat4 const& mat)
	{
		static const unsigned int MAX_INDEX = 4;

		for (unsigned int i = 0; i < MAX_INDEX; ++i)
		{
			out << "[ ";
			for (unsigned int j = 0; j < MAX_INDEX; j++)
			{
				out << mat[i][j] << ", ";
			}
			out << "]\n";
		}

		return out;
	}

}
