#include "mat3f.h"

mat3f::mat3f()
{
	mass[0][0] = 0.0f; mass[0][1] = 0.0f; mass[0][2] = 0.0f;
	mass[1][0] = 0.0f; mass[1][1] = 0.0f; mass[1][2] = 0.0f;
	mass[2][0] = 0.0f; mass[2][1] = 0.0f; mass[2][2] = 0.0f;
}

mat3f::~mat3f()
{
}

void mat3f::Identety()
{
	mass[0][0] = 1.0f; mass[0][1] = 0.0f; mass[0][2] = 0.0f;
	mass[1][0] = 0.0f; mass[1][1] = 1.0f; mass[1][2] = 0.0f;
	mass[2][0] = 0.0f; mass[2][1] = 0.0f; mass[2][2] = 1.0f;
}

void mat3f::Value(float value)
{
	mass[0][0] = value; mass[0][1] = 0.0f;  mass[0][2] = 0.0f;
	mass[1][0] = 0.0f;  mass[1][1] = value; mass[1][2] = 0.0f;
	mass[2][0] = 0.0f;  mass[2][1] = 0.0f;  mass[2][2] = value;
}

void mat3f::InitTransformScale(float ScaleX, float ScaleY)
{
	mass[0][0] = ScaleX; mass[0][1] = 0.0f;   mass[0][2] = 0.0f;
	mass[1][0] = 0.0f;   mass[1][1] = ScaleY; mass[1][2] = 0.0f;
	mass[2][0] = 0.0f;   mass[2][1] = 0.0f;   mass[2][2] = 1.0f;
}

void mat3f::InitTransformRotation(float Rotate)
{
	float dxy = ToRadian(Rotate);

	mass[0][0] = cosf(dxy); mass[0][1] = 0.0f;       mass[0][2] = 0.0f;
	mass[1][0] = 0.0f;	    mass[1][1] = 1.0f;       mass[1][2] = 0.0f;
	mass[2][0] = 0.0f;      mass[2][1] = 0.0f;       mass[2][2] = 1.0f;
}

void mat3f::InitTransformWorldPosition(float PositionX, float PositionY)
{
	mass[0][0] = 1.0f; mass[0][1] = 0.0f; mass[0][2] = PositionX;
	mass[1][0] = 0.0f; mass[1][1] = 1.0f; mass[1][2] = PositionY;
	mass[2][0] = 0.0f; mass[2][1] = 0.0f; mass[2][2] = 1.0f;
}

void mat3f::operator=(const mat3f& matrix)
{
	if (&matrix == this) return;
	for (int i = 0; i < M_MAT3F; ++i)
		for (int j = 0; j < M_MAT3F; ++j)
			mass[i][j] = matrix.mass[i][j];
}

mat3f& mat3f::operator+=(const mat3f& matrix)
{
	for (int i = 0; i < M_MAT3F; ++i)
		for (int j = 0; j < M_MAT3F; ++j)
			mass[i][j] += matrix.mass[i][j];

	return *this;
}

mat3f& mat3f::operator+=(float number)
{
	mass[0][0] += number;
	mass[1][1] += number;
	mass[2][2] += number;

	return *this;
}

mat3f& mat3f::operator*=(const mat3f& matrix)
{
	for (int i = 0; i < M_MAT3F; ++i)
		for (int j = 0; j < M_MAT3F; ++j)
			mass[i][j] = mass[i][0] * matrix.mass[0][j] +
			mass[i][1] * matrix.mass[1][j] +
			mass[i][2] * matrix.mass[2][j];

	return *this;
}

mat3f& mat3f::operator*=(float number)
{
	for (int i = 0; i < M_MAT3F; ++i)
		for (int j = 0; j < M_MAT3F; ++j)
			mass[i][j] *= number;

	return *this;
}

mat3f& mat3f::operator-=(const mat3f& matrix)
{
	for (int i = 0; i < M_MAT3F; ++i)
		for (int j = 0; j < M_MAT3F; ++j)
			mass[i][j] -= matrix.mass[i][j];

	return *this;
}

mat3f& mat3f::operator-=(float number)
{
	mass[0][0] -= number;
	mass[1][1] -= number;
	mass[2][2] -= number;

	return *this;
}

mat3f operator+(const mat3f& left, const mat3f& right)
{
	mat3f result;
	result = left;
	result += right;
	return result;
}

mat3f operator-(const mat3f& left, const mat3f& right)
{
	mat3f result;
	result = left;
	result -= right;
	return result;
}

mat3f operator*(const mat3f& left, const mat3f& right)
{
	mat3f result;
	result = left;
	result *= right;
	return result;
}

vec3f operator*(const mat3f& matrix, const vec3f& vector)
{
	return vec3f(
		matrix.mass[0][0] * vector.x + matrix.mass[0][1] * vector.y + matrix.mass[0][2] * vector.z,
		matrix.mass[1][0] * vector.x + matrix.mass[1][1] * vector.y + matrix.mass[1][2] * vector.z,
		matrix.mass[2][0] * vector.x + matrix.mass[2][1] * vector.y + matrix.mass[2][2] * vector.z
	);
}

vec3f operator*(const vec3f& vector, const mat3f& matrix)
{
	return vec3f(
		vector.x * matrix.mass[0][0] + vector.y * matrix.mass[0][1] + vector.z * matrix.mass[0][2],
		vector.x * matrix.mass[1][0] + vector.y * matrix.mass[1][1] + vector.z * matrix.mass[1][2],
		vector.x * matrix.mass[2][0] + vector.y * matrix.mass[2][1] + vector.z * matrix.mass[2][2]
	);
}