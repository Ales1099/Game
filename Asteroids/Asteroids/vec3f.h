#pragma once
#include "vec2f.h"
struct vec3f
{
	float x;
	float y;
	float z;

	vec3f() {};

	vec3f(float __x, float __y, float __z);

	vec3f(const vec3f& vec);

	vec3f(vec3f &&vec);

	float getX() { return x; }

	float getY() { return y; }

	float getZ() { return z; }

	vec3f(vec2f& vector, float __z);

	vec3f(vec2f& vector);

	~vec3f();

	vec3f& operator*=(const vec3f& right);

	vec3f& operator*=(float number);

	vec3f& operator+=(const vec3f& right);

	vec3f& operator+=(float number);

	vec3f& operator-=(const vec3f& right);

	vec3f& operator-=(float number);

	vec3f& operator/=(const vec3f& right);

	vec3f& operator/=(float number);

	vec3f& operator++();

	vec3f& operator++(int);

	vec3f& operator--();

	vec3f& operator--(int);

	void operator=(const vec3f& rigth);

	friend vec3f operator+(const vec3f& left, const vec3f& right);

	friend vec3f operator+(float number, const vec3f& right);

	friend vec3f operator+(const vec3f& left, float number);

	friend vec3f operator-(const vec3f& left, const vec3f& right);

	friend vec3f operator-(float number, const vec3f& right);

	friend vec3f operator-(const vec3f& left, float number);

	friend vec3f operator*(const vec3f& left, const vec3f& right);

	friend vec3f operator*(float number, const vec3f& right);

	friend vec3f operator*(const vec3f& left, float number);

	friend vec3f operator/(const vec3f& left, const vec3f& right);

	friend vec3f operator/(const vec3f& left, float number);

	friend vec3f operator/(float number, const vec3f& right);
};
