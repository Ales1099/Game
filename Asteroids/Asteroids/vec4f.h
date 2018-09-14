#pragma once
#include "vec3f.h"
struct vec4f
{

	float x;
	float y;
	float z;
	float w;

	vec4f() {};

	vec4f(float __x, float __y, float __z, float __w);

	vec4f(vec3f& vector, float __w);

	vec4f(vec3f& vector);

	vec4f(vec2f& vector, float __z, float __w);

	vec4f(vec2f& vector_one, vec2f& vector_two);

	vec4f(vec2f& vector);

	~vec4f();

	vec4f& operator*=(const vec4f& right);

	vec4f& operator*=(float number);

	vec4f& operator+=(const vec4f& right);

	vec4f& operator+=(float number);

	vec4f& operator-=(const vec4f& right);

	vec4f& operator-=(float number);

	vec4f& operator/=(const vec4f& right);

	vec4f& operator/=(float number);

	vec4f& operator++();

	vec4f& operator++(int);

	vec4f& operator--();

	vec4f& operator--(int);

	void operator=(const vec4f& rigth);

	friend vec4f operator+(const vec4f& left, const vec4f& right);

	friend vec4f operator+(float number, const vec4f& right);

	friend vec4f operator+(const vec4f& left, float number);

	friend vec4f operator-(const vec4f& left, const vec4f& right);

	friend vec4f operator-(float number, const vec4f& right);

	friend vec4f operator-(const vec4f& left, float number);

	friend vec4f operator*(const vec4f& left, const vec4f& right);

	friend vec4f operator*(float number, const vec4f& right);

	friend vec4f operator*(const vec4f& left, float number);

	friend vec4f operator/(const vec4f& left, const vec4f& right);

	friend vec4f operator/(const vec4f& left, float number);

	friend vec4f operator/(float number, const vec4f& right);
};

