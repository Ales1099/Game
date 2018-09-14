#include "vec4f.h"


vec4f::vec4f(float __x, float __y, float __z, float __w)
{
	this->x = __x;
	this->y = __y;
	this->z = __z;
	this->w = __w;
}

vec4f::vec4f(vec3f& vector, float __w)
{
	this->x = vector.getX();
	this->y = vector.getY();
	this->z = vector.getZ();
	this->w = __w;
}

vec4f::vec4f(vec3f& vector)
{
	this->x = vector.getX();
	this->y = vector.getY();
	this->z = vector.getZ();
	this->w = 1.0f;
}

vec4f::vec4f(vec2f& vector, float __z, float __w)
{
	this->x = vector.getX();
	this->y = vector.getY();
	this->z = __z;
	this->w = __w;
}

vec4f::vec4f(vec2f& vector_one, vec2f& vector_two)
{
	this->x = vector_one.getX();
	this->y = vector_one.getY();
	this->z = vector_two.getX();
	this->w = vector_two.getY();
}

vec4f::vec4f(vec2f& vector)
{
	this->x = vector.getX();
	this->y = vector.getY();
	this->z = 1.0f;
	this->w = 1.0f;
}

vec4f::~vec4f()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

vec4f& vec4f::operator*=(const vec4f& right)
{
	this->x *= right.x;
	this->y *= right.y;
	this->z *= right.z;
	this->w *= right.w;

	return *this;
}

vec4f& vec4f::operator*=(float number)
{
	this->x *= number;
	this->y *= number;
	this->z *= number;
	this->w *= number;

	return *this;
}

vec4f& vec4f::operator+=(const vec4f& right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	this->w += right.w;

	return *this;
}

vec4f& vec4f::operator+=(float number)
{
	this->x += number;
	this->y += number;
	this->z += number;
	this->w += number;

	return *this;
}

vec4f& vec4f::operator-=(const vec4f& right)
{
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
	this->w -= right.w;

	return *this;
}

vec4f& vec4f::operator-=(float number)
{
	this->x -= number;
	this->y -= number;
	this->z -= number;
	this->w -= number;

	return *this;
}

vec4f& vec4f::operator/=(const vec4f& right)
{
	this->x /= right.x;
	this->y /= right.y;
	this->z /= right.z;
	this->w /= right.w;

	return *this;
}

vec4f& vec4f::operator/=(float number)
{
	this->x /= number;
	this->y /= number;
	this->z /= number;
	this->w /= number;

	return *this;
}

vec4f& vec4f::operator++()
{
	this->x++;
	this->y++;
	this->z++;
	this->w++;

	return *this;
}

vec4f& vec4f::operator++(int)
{
	++this->x;
	++this->y;
	++this->z;
	++this->w;

	return *this;
}

vec4f& vec4f::operator--()
{
	this->x--;
	this->y--;
	this->z--;
	this->w--;

	return *this;
}

vec4f& vec4f::operator--(int)
{
	--this->x;
	--this->y;
	--this->z;
	--this->w;

	return *this;
}

void vec4f::operator=(const vec4f& right)
{
	this->x = right.x;
	this->y = right.y;
	this->z = right.z;
	this->w = right.w;
}

vec4f operator+(const vec4f& left, const vec4f& right)
{
	return vec4f(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

vec4f operator+(float number, const vec4f& right)
{
	return vec4f(number + right.x, number + right.y, number + right.z, number + right.w);
}

vec4f operator+(const vec4f& left, float number)
{
	return vec4f(left.x + number, left.y + number, left.z + number, left.w + number);
}

vec4f operator-(const vec4f& left, const vec4f& right)
{
	return vec4f(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

vec4f operator-(float number, const vec4f& right)
{
	return vec4f(number - right.x, number - right.y, number - right.z, number - right.w);
}

vec4f operator-(const vec4f& left, float number)
{
	return vec4f(left.x - number, left.y - number, left.z - number, left.w - number);
}

vec4f operator*(const vec4f& left, const vec4f& right)
{
	return vec4f(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
}

vec4f operator*(float number, const vec4f& right)
{
	return vec4f(number * right.x, number * right.y, number * right.z, number * right.w);
}

vec4f operator*(const vec4f& left, float number)
{
	return vec4f(left.x * number, left.y * number, left.z * number, left.w * number);
}

vec4f operator/(const vec4f& left, const vec4f& right)
{
	return vec4f(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
}

vec4f operator/(float number, const vec4f& right)
{
	return vec4f(number / right.x, number / right.y, number / right.z, number / right.w);
}

vec4f operator/(const vec4f& left, float number)
{
	return vec4f(left.x / number, left.y / number, left.z / number, left.w / number);
}
