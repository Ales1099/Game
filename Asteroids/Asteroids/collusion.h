#pragma once

#include "commands.h"
#define _USE_MATH_DEFINES
#include <cmath>

#define Length(x0,y0,x1,y1) (sqrtf((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1)))

EGObool PointCircleVec2f(float * point_x, float * point_y, float * x_center_circle, float * y_center_circle, float * circle_radius)
{
	float length = sqrtf((*x_center_circle - *point_x) * (*x_center_circle - *point_x) + (*y_center_circle - *point_y)*(*y_center_circle - *point_y));
	if (length <= *circle_radius)
		return(TRUE);
	else
		return(FALSE);
}

//EGObool PointCircleVec3f(float point_x, float point_y, float x_center_circle, float y_center_circle, float circle_radius);

EGObool PointQuadsVec2f(float * point_x, float * point_y, float * x0, float * y0, float * x1, float * y1)
{
	if (*point_x == 0.0f && *point_y == 0.0f && *x0 == 0.0f && *y0 == 0.0f && *x1 == 0.0f && *y1 == 0.0f)
		return(FALSE);
	if (*x1 > *x0)
		if (*point_x >= *x0 && *point_x <= *x1 && *point_y >= *y0 && *point_y <= *y1)
			return(TRUE);
		else
			return(FALSE);
	else
		if (*point_x >= *x1 && *point_x <= *x0 && *point_y >= *y1 && *point_y <= *y0)
			return(TRUE);
		else
			return(FALSE);
}

//EGObool PointQuadsVec3f(float point_x, float point_y, float x0, float y0, float x1, float y1);

EGObool PointTriangleVec2f(float * point_x, float * point_y, float * t_x0, float * t_y0, float * t_x1, float * t_y1, float * t_x2, float * t_y2)
{
	float a = Length((*t_x0), (*t_y0), (*t_x1), (*t_y1));
	float b = Length((*t_x1), (*t_y1), (*t_x2), (*t_y2));
	float c = Length((*t_x0), (*t_y0), (*t_x2), (*t_y2));

	float ptri = (a + b + c) / 2;
	float stri = sqrt(ptri*(ptri - a)*(ptri - b)*(ptri - c));

	float aPoint = Length((*point_x), (*point_y), (*t_x0), (*t_y0));
	float bPoint = Length((*point_x), (*point_y), (*t_x1), (*t_y1));
	float cPoint = Length((*point_x), (*point_y), (*t_x2), (*t_y2));

	float pOneTri = (aPoint + bPoint + a) / 2;
	float pTwoTri = (bPoint + cPoint + b) / 2;

	float sOneTri = sqrt(pOneTri*(pOneTri - aPoint)*(pOneTri - bPoint)*(pOneTri - a));
	float sTwoTri = sqrt(pTwoTri*(pTwoTri - bPoint)*(pTwoTri - cPoint)*(pTwoTri - b));

	if ((sOneTri + sTwoTri) < stri)
		return(1);
	else
		return(0);
}

//EGObool PointTriangleVec3f(float point_x, float point_y, float point_z, float t_x0, float t_y0, float t_x1, float t_y1, float x_2, float t_y2);

//EGObool TrianglesQuadsVec2f(float t_x0, float t_y0, float t_x1, float t_y1, float t_x2, float t_y2, float q_x0, float q_y0, float q_x1, float q_y1, float q_x2, float q_y2, float q_x3, float q_y3);
