#pragma once
struct vec2f
{
	float x;
	float y;

	vec2f() {};

	vec2f(float __x, float __y);

	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
	}

	~vec2f();

	vec2f& operator*=(const vec2f& right);

	vec2f& operator*=(float number);

	vec2f& operator+=(const vec2f& right);

	vec2f& operator+=(float number);

	vec2f& operator-=(const vec2f& right);

	vec2f& operator-=(float number);

	vec2f& operator/=(const vec2f& right);

	vec2f& operator/=(float number);

	vec2f& operator++();

	vec2f& operator++(int);

	vec2f& operator--();

	vec2f& operator--(int);

	void operator=(const vec2f& rigth);

	friend vec2f operator+(const vec2f& left, const vec2f& right);

	friend vec2f operator+(float number, const vec2f& right);

	friend vec2f operator+(const vec2f& left, float number);

	friend vec2f operator-(const vec2f& left, const vec2f& right);

	friend vec2f operator-(float number, const vec2f& right);

	friend vec2f operator-(const vec2f& left, float number);

	friend vec2f operator*(const vec2f& left, const vec2f& right);

	friend vec2f operator*(float number, const vec2f& right);

	friend vec2f operator*(const vec2f& left, float number);

	friend vec2f operator/(const vec2f& left, const vec2f& right);

	friend vec2f operator/(const vec2f& left, float number);

	friend vec2f operator/(float number, const vec2f& right);
};

