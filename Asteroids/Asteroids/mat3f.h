#pragma once

#define M_MAT3F 3
#include "vec3f.h"

#define _USE_MATH_DEFINES
#include <cmath>
#define ToRadian(x)(x*M_PI/180.0f)
#define ToDegree(x)(x*180.0f/M_PI)


class mat3f
{
private:
	float mass[M_MAT3F][M_MAT3F];
public:
	mat3f();
	~mat3f();
	void Identety();
	void Value(float value);
	void InitTransformScale(float ScaleX, float ScaleY);
	void InitTransformRotation(float Rotate);
	void InitTransformWorldPosition(float PositionX, float PositionY);
	void operator=(const mat3f& matrix);

	mat3f& operator+=(const mat3f& matrix);
	mat3f& operator+=(float number);
	mat3f& operator*=(const mat3f& matrix);
	mat3f& operator*=(float number);
	mat3f& operator-=(const mat3f& matrix);
	mat3f& operator-=(float number);

	friend mat3f operator+(const mat3f& left, const mat3f& right);
	friend mat3f operator*(const mat3f& left, const mat3f& right);
	friend mat3f operator-(const mat3f& left, const mat3f& right);

	friend vec3f operator*(const mat3f& matrix, const vec3f& vector);
	friend vec3f operator*(const vec3f& vector, const mat3f& matrix);
};

