#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "common/logpp/log++.h"

#undef ASSERT
#ifndef DISABLE_ASSERT
#define ASSERT(condition, str) if (condition) \
{ \
} \
else \
{ \
logpp::Console::error(std::string("Assertion failed at location: ") + std::string(__FILE__) + "::" + std::to_string(__LINE__) + "\nCondition: " + #condition + "\nMessage: " + #str); \
}

#else
#define ASSERT(condition, str)

#endif

#undef STATIC_ASSERT
#ifndef DISABLE_ASSERT
#define STATIC_ASSERT(condition, str) static_assert(condition, #str);
#else
#define STATIC_ASSERT(condition, str)

#endif


#endif 
