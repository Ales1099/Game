#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "mat3f.h"
#include "vec2f.h"
#include "vec3f.h"
#include "commands.h"

class Hero {
private:
	vec2f * points = new vec2f[18];
	vec3f * buffer = new vec3f[18];
	vec3f * tempret = new vec3f;
	GLuint m_index[24] = { 0,1,2,9,2,3,4,5,5,6,7,8,8,5,2,9,10,11,12,13,14,15,16,17 };

	mat3f * m_position = new mat3f;
	mat3f * m_scale = new mat3f;
	mat3f * m_result = new mat3f;

	mat3f * m_position_rocket = new mat3f;

	const float speed_rocket = 0.0015f;
	float x_rocket = 0.0f;

	vec2f rocket[5][8];
	bool hero_attac[5] = { false,false,false,false,false };
	bool peregrev = false;
	float position_rocket[5] = { 0.0f,0.0f,0.0f,0.0f,0.0f };
	vec3f * buffer_rocket = new vec3f;

	GLuint VAO;
	GLuint VBO;
	GLuint IBO;

	GLuint VAORockets[5];
	GLuint VBORockets[5];
public:
	Hero();

	Hero(const vec2f(&_points)[18]);

	~Hero();

	void genVABIO();

	void genVABORockets();

	void create();

	float getX(unsigned int index);

	float getY(unsigned int index);

	float getRocketX(unsigned int index_one, unsigned int index_two);

	float getRocketY(unsigned int index_one, unsigned int index_two);

	void initScaleHero(float ScaleX, float ScaleY);

	void initPositionHero(float PositionX, float PositionY);

	void initScaleAndPositionHero(float ScaleX, float ScaleY, float PositionX, float PositionY);

	void updateScale();

	void updatePosition();

	void updateRocket();
	
	void drawHero();

	void drawRocket();

	void createRocket();

	void genRocket(int8_t index);

	void proverca();

	void updatePeregrev();

	bool getPer();
};