#pragma once

namespace mem
{
	/*Custom deleter that does nothing*/
	template<typename U> void dont_delete(U*) { /*do nothing*/ }
};
