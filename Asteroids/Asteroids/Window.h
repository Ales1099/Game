#ifndef WINDOW
#define WINDOW
#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdint>
#include <ctime>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "Hero.h"
#include "Enemy.h"
///#include "collusion.h"
#include "commands.h"

#define WIDTH   1800 
#define HEIGHT	900
#define STARS   200

struct Variables
{
	float x_hero_position = 0.0f;
    float y_hero_position = 0.0f;

	float x_nlo_position = 0.25f;
	float y_nlo_position = 0.0f;

	float x_asteroid_position = 0.0f;
	float y_asteroid_position = 0.0f;
	float x_asteroid_rotation = 0.0f;
	float y_asteroid_rotation = 0.0f;

	float x_rocekt_nlo_position = 0.0f;

	float speed_nlo = 0.001f;
	float speed_hero = 0.035f;
	float speed_nlo_rocket = 0.02f;
	float speed_hero_rocket = 0.0015f;
	float speed_asteroids = 0.01f;
	float speed_star_standart = 0.0001f;
	float speed_star_none = 0.001f;
	float speed_star = 0.01f;
	bool nlo_attacks = false;
};

class Window
{
private:
	Hero spaceship = Hero();
	Enemy nlo = Enemy();
	shader program;
	EGObool heroToRocket, nloToRocket;
	bool update_is_ok = true, update_nlo_is_ok = true;
	GLFWwindow * window;
	int8_t c = 0;
	vec2f stars[STARS];
	GLuint VAOStars, VBOStars;

	Variables tem;
public:
	Window();
	~Window();
	bool init();
	void createGame();
	void mainLoop();
	bool exit();
	///void(*funcDraw[4])() = {Hero::drawHero, Hero::drawRocket, Enemy::drawNlo, Enemy::drawRocket};
private:
	inline void render();
	inline void update();
	inline void key_callback();

	inline void createVABOStars();
	inline void updateVABOStars();
	
	inline float RandomizeX();
	inline float RandomizeY();
};

#endif