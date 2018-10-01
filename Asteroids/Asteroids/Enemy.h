#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "mat3f.h"
#include "vec2f.h"
#include "vec3f.h"

class Enemy
{
private:
	vec2f * points = new vec2f[4];
	vec3f * buffer = new vec3f[4];
	vec3f * ptr = new vec3f;
	vec2f * rocket = new vec2f[3];
	vec3f * bufferRocket = new vec3f[3];
	unsigned int * index = new unsigned int[6];

	mat3f * m_position = new mat3f();
	mat3f * m_scale = new mat3f();
	mat3f * m_rotation = new mat3f();
	mat3f * m_result = new mat3f();
	mat3f * m_position_rocket = new mat3f();

	GLuint VAO;
	GLuint VBO;
	GLuint IBO;

	GLuint VAORocket;
	GLuint VBORocket;

	bool is_ok = true;
public:
	Enemy();

	Enemy(const vec2f(&_points)[4]);

	~Enemy();

	void initScale(float ScaleX, float ScaleY);

	void initPosition(float PositionX, float PositionY);

	void initRotate(float rot);

	void updatePosition();

	void genVABIO();

	void create();

	void draw();

	bool getStatus();
	
	float getX(unsigned int index);

	float getY(unsigned int index);

	float getRocketX(unsigned int index);

	float getRocketY(unsigned int index);

	void pos();

	void emptyRocket();

	void createRocket();

	void initPositionRocket(float PositionX, float PositionY);

	void updetPositionRocket();

	void drawRocket();

	void learning(unsigned int pos);
};