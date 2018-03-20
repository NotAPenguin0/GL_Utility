#ifndef _VECTOR_4_H_
#define _VECTOR_4_H_

#include "sse_util.h"


class vector4
{
public:
	vector4(float x, float y, float z, float w)
	{
		sse::set_m128(data, x, y, z, w);
	}

	sse::vec4f const& get() const { return data; }

	float x() const { return sse::element_m128(data, 0); }
	float y() const { return sse::element_m128(data, 1); }
	float z() const { return sse::element_m128(data, 2); }
	float w() const { return sse::element_m128(data, 3); }

	vector4& operator+(vector4 const& other)
	{
		//#FIXME: error here
		return sse::add_m128(data, other.get());
	}
	vector4& operator-(vector4 const& other)
	{
		return sse::sub_m128(data, other.get());
	}
	
	float dotp(vector4 const& other);
	float crossp(vector4 const& other);

private:
	sse::vec4f data;
};

#endif