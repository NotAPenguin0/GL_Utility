#ifndef _SSE_UTILITY_H_
#define _SSE_UTILITY_H_

#include <xmmintrin.h>
#include "assert.h"

namespace sse
{
	/*Element-wise addition*/
	inline __m128 add_m128(__m128 v1, __m128 v2)
	{
		return _mm_add_ps(v1, v2);
	}

	/*Element-wise subtraction*/
	inline __m128 sub_m128(__m128 v1, __m128 v2)
	{
		return _mm_sub_ps(v1, v2);
	}

	/*Element-wise multiplication, and stores the resulting 4 values in a new __m128 vector*/
	inline __m128 mul_m128(__m128 v1, __m128 v2)
	{
		return _mm_mul_ps(v1, v2);
	}

	/*Element-wise division, and stores the resulting 4 values in a new __m128 vector*/
	inline __m128 div_m128(__m128 v1, __m128 v2)
	{
		return _mm_div_ps(v1, v2);
	}

	inline float _m128_element(__m128 v, unsigned int idx)
	{
		static const int V_ELEMENT_COUNT = 4;

		ASSERT(idx < V_ELEMENT_COUNT && idx >= 0, "vector index out of range")

		typedef union
		{
			__m128 vector;
			float array[V_ELEMENT_COUNT];
		} converter;

		converter c;
		
		c.vector = v;
		return c.array[idx];
	}
}

#endif // ifndef _SSE_UTILITY_H_
