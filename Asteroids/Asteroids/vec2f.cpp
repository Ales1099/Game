#include "vec2f.h"

vec2f::vec2f(float __x, float __y)
{
	this->x = __x;
	this->y = __y;
}

vec2f::~vec2f()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

vec2f& vec2f::operator+=(const vec2f& right)
{
	this->x += right.x;
	this->y += right.y;

	return *this;
}

vec2f& vec2f::operator+=(float number)
{
	this->x += number;
	this->y += number;

	return *this;
}

vec2f& vec2f::operator-=(const vec2f& right)
{
	this->x -= right.x;
	this->y -= right.y;

	return *this;
}

vec2f& vec2f::operator-=(float number)
{
	this->x -= number;
	this->y -= number;

	return *this;
}

vec2f& vec2f::operator*=(const vec2f& right)
{
	this->x *= right.x;
	this->y *= right.y;

	return *this;
}

vec2f& vec2f::operator*=(float number)
{
	this->x *= number;
	this->y *= number;

	return *this;
}


vec2f& vec2f::operator/=(const vec2f& right)
{
	this->x /= right.x;
	this->y /= right.y;

	return *this;
}

vec2f& vec2f::operator/=(float number)
{
	this->x /= number;
	this->y /= number;

	return *this;
}

vec2f& vec2f::operator++()
{
	this->x++;
	this->y++;

	return *this;
}

vec2f& vec2f::operator++(int)
{
	++this->x;
	++this->y;

	return *this;
}

vec2f& vec2f::operator--()
{
	this->x--;
	this->y--;

	return *this;
}

vec2f& vec2f::operator--(int)
{
	--this->x;
	--this->y;

	return *this;
}

void vec2f::operator=(const vec2f& rigth)
{
	this->x = rigth.x;
	this->y = rigth.y;
}

vec2f operator+(const vec2f& left, const vec2f& right)
{
	return vec2f(left.x + right.x, left.y + right.y);
}

vec2f operator+(float number, const vec2f& right)
{
	return vec2f(number + right.x, number + right.y);
}

vec2f operator+(const vec2f& left, float number)
{
	return vec2f(left.x + number, left.y + number);
}

vec2f operator-(const vec2f& left, const vec2f& right)
{
	return vec2f(left.x - right.x, left.y - right.y);
}

vec2f operator-(float number, const vec2f& right)
{
	return vec2f(number - right.x, number - right.y);
}

vec2f operator-(const vec2f& left, float number)
{
	return vec2f(left.x - number, left.y - number);
}

vec2f operator*(const vec2f& left, const vec2f& right)
{
	return vec2f(left.x*right.x, left.y*right.y);
}

vec2f operator*(float number, const vec2f& right)
{
	return vec2f(number*right.x, number*right.y);
}

vec2f operator*(const vec2f& left, float number)
{
	return vec2f(left.x*number, left.y*number);
}

vec2f operator/(const vec2f& left, const vec2f& right)
{
	return vec2f(left.x / right.x, left.y / right.y);
}

vec2f operator/(const vec2f& left, float number)
{
	return vec2f(left.x / number, left.y / number);
}

vec2f operator/(float number, const vec2f& right)
{
	return vec2f(number / right.x, number / right.y);
}
