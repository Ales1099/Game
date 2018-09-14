#include "vec3f.h"

vec3f::vec3f(float __x, float __y, float __z)
{
	this->x = __x;
	this->y = __y;
	this->z = __z;
}

vec3f::vec3f(const vec3f& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.x;
}

vec3f::vec3f(vec3f&& vec) : x(vec.x), y(vec.y), z(vec.z)
{
	vec.x = 0.0f;
	vec.y = 0.0f;
	vec.z = 0.0f;
}

vec3f::vec3f(vec2f& vector, float __z)
{
	this->x = vector.getX();
	this->y = vector.getY();
	this->z = __z;
}

vec3f::vec3f(vec2f& vector)
{
	this->x = vector.getX();
	this->y = vector.getY();
	this->z = 1.0f;
}

vec3f::~vec3f()
{
}

vec3f& vec3f::operator*=(const vec3f& right)
{
	this->x *= right.x;
	this->y *= right.y;
	this->z *= right.z;

	return *this;
}

vec3f& vec3f::operator*=(float number)
{
	this->x *= number;
	this->y *= number;
	this->z *= number;

	return *this;
}

vec3f& vec3f::operator+=(const vec3f& right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;

	return *this;
}

vec3f& vec3f::operator+=(float number)
{
	this->x += number;
	this->y += number;
	this->z += number;

	return *this;
}

vec3f& vec3f::operator-=(const vec3f& right)
{
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;

	return *this;
}

vec3f& vec3f::operator-=(float number)
{
	this->x -= number;
	this->y -= number;
	this->z -= number;

	return *this;
}

vec3f& vec3f::operator/=(const vec3f& right)
{
	this->x /= right.x;
	this->y /= right.y;
	this->z /= right.z;

	return *this;
}

vec3f& vec3f::operator/=(float number)
{
	this->x /= number;
	this->y /= number;
	this->z /= number;

	return *this;
}

vec3f& vec3f::operator++()
{
	this->x++;
	this->y++;
	this->z++;

	return *this;
}

vec3f& vec3f::operator++(int)
{
	++this->x;
	++this->y;
	++this->z;

	return *this;
}

vec3f& vec3f::operator--()
{
	this->x--;
	this->y--;
	this->z--;

	return *this;
}

vec3f& vec3f::operator--(int)
{
	--this->x;
	--this->y;
	--this->z;

	return *this;
}

void vec3f::operator=(const vec3f& right)
{
	this->x = right.x;
	this->y = right.y;
	this->z = right.z;
}

vec3f operator+(const vec3f& left, const vec3f& right)
{
	return vec3f(left.x + right.x, left.y + right.y, left.z + right.z);
}

vec3f operator+(float number, const vec3f& right)
{
	return vec3f(number + right.x, number + right.y, number + right.z);
}

vec3f operator+(const vec3f& left, float number)
{
	return vec3f(left.x + number, left.y + number, left.z + number);
}

vec3f operator-(const vec3f& left, const vec3f& right)
{
	return vec3f(left.x - right.x, left.y - right.y, left.z - right.z);
}

vec3f operator-(float number, const vec3f& right)
{
	return vec3f(number - right.x, number - right.y, number - right.z);
}

vec3f operator-(const vec3f& left, float number)
{
	return vec3f(left.x - number, left.y - number, left.z - number);
}

vec3f operator*(const vec3f& left, const vec3f& right)
{
	return vec3f(left.x*right.x, left.y*right.y, left.z*right.z);
}

vec3f operator*(float number, const vec3f& right)
{
	return vec3f(number*right.x, number*right.y, number*right.z);
}

vec3f operator*(const vec3f& left, float number)
{
	return vec3f(left.x*number, left.y*number, left.z*number);
}

vec3f operator/(const vec3f& left, const vec3f& right)
{
	return vec3f(left.x / right.x, left.y / right.y, left.z / right.z);
}

vec3f operator/(const vec3f& left, float number)
{
	return vec3f(left.x / number, left.y / number, left.z / number);
}

vec3f operator/(float number, const vec3f& right)
{
	return vec3f(number / right.x, number / right.y, number / right.z);
}
