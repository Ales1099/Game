#include <iostream>
#include <ctime>
#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "EGOMachine.h"
#include <cstdint>

#define GAME_WINDOW_WIDTH	1800
#define GAME_WINDOW_HEIGHT	900

#define HERO_ROCKETS	 5
#define HERO_ROCKET_XY   8
#define NLO_XY			 4
#define HERO_XY          18
#define NLO_ROCKET_XY    3
#define ASTEROID_XY		 7
#define ASTEROIDS        5
#define STARS          200

static float x_hero_position = 0.0f;
static float y_hero_position = 0.0f;

static float x_nlo_position = 0.25f;
static float y_nlo_position = 0.0f;

static float x_asteroid_position = 0.0f;
static float y_asteroid_position = 0.0f;
static float x_asteroid_rotation = 0.0f;
static float y_asteroid_rotation = 0.0f;

static float x_rocekt_nlo_position = 0.0f;
static float x_rocket_hero_position[5] = { 0.0f,0.0f,0.0f,0.0f,0.0f };

static float speed_nlo = 0.001f;
static float speed_hero = 0.055f;
static float speed_nlo_rocket = 0.0014f;
static float speed_hero_rocket = 0.0015f;
static float speed_asteroids = 0.01f;
static float speed_star_standart = 0.0001f;
static float speed_star_none = 0.001f;
static float speed_star = 0.01f;

bool nlo_attack = false;
bool hero_attac[HERO_ROCKETS] = { false,false,false,false,false };
bool update_is_ok = true;
bool peregrev = false;
bool nlo_update_is_ok = true;

GLFWwindow * gameWindow;
GLuint gVBO[14], gVAO[14], gEBO[2];
GLuint index[24] = { 0,1,2,9,2,3,4,5,5,6,7,8,8,5,2,9,10,11,12,13,14,15,16,17 };
GLuint indexNlo[6] = { 0,1,2,0,1,3 };
vec2f hero[HERO_XY];
vec2f nlo[NLO_XY];
vec2f nlo_rocket[NLO_ROCKET_XY];
vec2f hero_rocket[HERO_ROCKETS][HERO_ROCKET_XY];
vec2f stars[STARS];
vec2f asteroids[ASTEROIDS][ASTEROID_XY];

vec3f bufferHero[HERO_XY], bufferNlo[NLO_XY];

inline EGObool GameInit();
inline float RandomizeX();
inline float RandomizeY();
inline void keyCallback(GLFWwindow * window, int key, int action, int scancode, int mode);
inline void createVABOHero();
inline void updateVABOHero();
inline void createVABONlo();
inline void updateVABONlo();
inline void createVABORocketNlo();
inline void updateVABORocketNlo();
inline void createVABOStars();
inline void updateVABOStars();
inline void createVABORocketHero();
inline void updateVABORocketHero();
inline void updateHeroRockets();
inline void updatePer();
inline void createAsteroids();
inline void updateAsteroids();

int main()
{
	srand(time(NULL));
	if (GameInit() != 1)
		std::cout << "fatal error :: GAME is not init!!!" << std::endl;

	glGenVertexArrays(13, gVAO);
	glGenBuffers(13, gVBO);
	glGenBuffers(2, gEBO);

	hero[0] = vec2f(0.01f, 0.01f);
	hero[1] = vec2f(0.03f, 0.01f);
	hero[2] = vec2f(0.05f, 0.04f);
	hero[3] = vec2f(0.11f, 0.05f);
	hero[4] = vec2f(0.11f, 0.08f);
	hero[5] = vec2f(0.05f, 0.09f);
	hero[6] = vec2f(0.03f, 0.12f);
	hero[7] = vec2f(0.01f, 0.12f);
	hero[8] = vec2f(0.03f, 0.09f);
	hero[9] = vec2f(0.03f, 0.04f);
	hero[10] = vec2f(0.03f, 0.1f);
	hero[11] = vec2f(0.03f, 0.11f);
	hero[12] = vec2f(0.06f, 0.11f);
	hero[13] = vec2f(0.06f, 0.1f);
	hero[14] = vec2f(0.03f, 0.02f);
	hero[15] = vec2f(0.03f, 0.03f);
	hero[16] = vec2f(0.06f, 0.03f);
	hero[17] = vec2f(0.06f, 0.02f);

	nlo[0] = vec2f(0.7f, 0.0f);
	nlo[1] = vec2f(0.745f, 0.0f);
	nlo[2] = vec2f(0.75f, 0.05f);
	nlo[3] = vec2f(0.75f, -0.05f);

	nlo_rocket[0] = vec2f();
	nlo_rocket[1] = vec2f();
	nlo_rocket[2] = vec2f();

	for (uint8_t i = 0; i < STARS; ++i)
		stars[i] = vec2f(RandomizeX(), RandomizeY());

	bufferHero[0] = hero[0];
	bufferHero[1] = hero[1];
	bufferHero[2] = hero[2];
	bufferHero[3] = hero[3];
	bufferHero[4] = hero[4];
	bufferHero[5] = hero[5];
	bufferHero[6] = hero[6];
	bufferHero[7] = hero[7];
	bufferHero[8] = hero[8];
	bufferHero[9] = hero[9];
	bufferHero[10] = hero[10];
	bufferHero[11] = hero[11];
	bufferHero[12] = hero[12];
	bufferHero[13] = hero[13];
	bufferHero[14] = hero[14];
	bufferHero[15] = hero[15];
	bufferHero[16] = hero[16];
	bufferHero[17] = hero[17];
	
	bufferNlo[0] = nlo[0];
	bufferNlo[1] = nlo[1];
	bufferNlo[2] = nlo[2];
	bufferNlo[3] = nlo[3];

	shader app = shader("vertex.vert", "fragment.frag");
	int8_t c = 0;
	
	while (glfwGetKey(gameWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(gameWindow) == 0)
	{
		if (c == HERO_ROCKETS)
			c = 0;

		glfwPollEvents();

		createVABOHero();
		createVABONlo();
		createVABOStars();
		createVABORocketHero();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(app.getShaderID());

		glBindVertexArray(gVAO[0]);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, (void*)0);

		glBindVertexArray(gVAO[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		glBindVertexArray(gVAO[3]);
		glDrawArrays(GL_POINTS, 0, STARS);

		glBindVertexArray(gVAO[4]);
		glDrawArrays(GL_QUADS, 0, 8);
		
		glBindVertexArray(gVAO[5]);
		glDrawArrays(GL_QUADS, 0, 8);

		glBindVertexArray(gVAO[6]);
		glDrawArrays(GL_QUADS, 0, 8);

		glBindVertexArray(gVAO[7]);
		glDrawArrays(GL_QUADS, 0, 8);
		
		glBindVertexArray(gVAO[8]);
		glDrawArrays(GL_POINTS, 0, STARS);

		glBindVertexArray(gVAO[9]);
		glDrawArrays(GL_QUADS, 0, 8);

		glBindVertexArray(gVAO[10]);
		glDrawArrays(GL_QUADS, 0, 8);

		glBindVertexArray(gVAO[11]);
		glDrawArrays(GL_QUADS, 0, 8);

		glBindVertexArray(gVAO[12]);
		glDrawArrays(GL_QUADS, 0, 8);

		if (glfwGetKey(gameWindow,GLFW_KEY_J) == GLFW_PRESS && peregrev != true)
		{
			hero_attac[c] = true;

			hero_rocket[c][0] = hero[10];
			hero_rocket[c][1] = hero[11];
			hero_rocket[c][2] = hero[12];
			hero_rocket[c][3] = hero[13];

			hero_rocket[c][4] = hero[14];
			hero_rocket[c][5] = hero[15];
			hero_rocket[c][6] = hero[16];
			hero_rocket[c][7] = hero[17];

			c++;
		}
		
		float pos = sinf(y_nlo_position);

		if (pos > 0.0f && pos < 0.8f && pos > 0.6f)
		{
			nlo_rocket[0] = nlo[0];
			nlo_rocket[1] = vec2f(nlo[1].x - 0.02f, nlo[2].y - 0.07f);
			nlo_rocket[2] = vec2f(nlo[1].x - 0.02f, nlo[3].y + 0.07f);

			nlo_attack = true;
		}

		if (nlo_attack == true)
		{
			createVABORocketNlo();
			
			glBindVertexArray(gVAO[2]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		if (nlo_rocket[1].x <= -1.0f)
		{
			x_rocekt_nlo_position = 0.0f;
			nlo_attack = 0;
		}

		if (pos <0.0f && pos > -0.8f && pos < -0.6f)
		{
			nlo_rocket[0] = nlo[0];
			nlo_rocket[1] = vec2f(nlo[1].x - 0.02f, nlo[2].y - 0.07f);
			nlo_rocket[2] = vec2f(nlo[1].x - 0.02f, nlo[3].y + 0.07f);

			nlo_attack = true;
		}

		EGObool hero_to_nlo_rocket = PointQuadsVec2f(&nlo_rocket[0].x, &nlo_rocket[0].y, &hero[2].x, &hero[2].y, &hero[4].x, &hero[4].y);

		if (hero_to_nlo_rocket == 0)
		{
			x_rocekt_nlo_position -= speed_nlo_rocket;
		}
		else
		{
			nlo_update_is_ok = false;
			update_is_ok = false;
		}

		glBindVertexArray(0);

		if (update_is_ok)
		{
			updateVABOHero();
			
			updateVABOStars();
			updateVABORocketNlo();

			updateVABORocketHero();
			updateHeroRockets();
			updatePer();
		}
		
		if(nlo_update_is_ok)
			updateVABONlo();
		else
		{
			nlo[0] = vec2f(bufferNlo[0].x,bufferNlo[0].y);
			nlo[1] = vec2f(bufferNlo[1].x,bufferNlo[1].y);
			nlo[2] = vec2f(bufferNlo[2].x,bufferNlo[2].y);
			nlo[3] = vec2f(bufferNlo[3].x,bufferNlo[3].y);

			bufferNlo[0] = vec3f(nlo[0]);
			bufferNlo[1] = vec3f(nlo[1]);
			bufferNlo[2] = vec3f(nlo[2]);
			bufferNlo[3] = vec3f(nlo[3]);

			x_nlo_position = 0.25f;
			y_nlo_position = 0.0f;

			nlo_update_is_ok = true;
		}

		glfwSwapBuffers(gameWindow);

		//Sleep(100);
	}

	glDeleteBuffers(13, gVAO);
	glDeleteBuffers(13, gVBO);
	glDeleteBuffers(2, gEBO);
	glDeleteProgram(app.getShaderID());
	glfwDestroyWindow(gameWindow);
	return(0);
}

inline EGObool GameInit()
{
	if (!glfwInit())
	{
		std::cout << "fatal erro :: GLFW is not OK!!!" << std::endl;
		return(-1);
	}

	gameWindow = glfwCreateWindow(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, "Asteroids", NULL, NULL);
	glfwMakeContextCurrent(gameWindow);
	glfwSetKeyCallback(gameWindow, keyCallback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "fatal error :: GLEW is not OK!!!" << std::endl;
		return(-1);
	}

	return(1);
}

inline float RandomizeX()
{
	float ran = 0.0011f * float(-GAME_WINDOW_HEIGHT + rand() % GAME_WINDOW_WIDTH);
	return ran;
}

inline float RandomizeY()
{
	float ran = 0.0011f * float(-GAME_WINDOW_HEIGHT + rand() % GAME_WINDOW_WIDTH);
	return ran;
}

inline void keyCallback(GLFWwindow * window, int key, int action, int scancode, int mode)
{
	glfwGetWindowUserPointer(window);

	if (key == GLFW_KEY_UP && action != GLFW_RELEASE)
		y_hero_position += speed_hero;

	if (key == GLFW_KEY_W && action != GLFW_RELEASE)
		y_hero_position += speed_hero;

	if (key == GLFW_KEY_DOWN && action != GLFW_RELEASE)
		y_hero_position -= speed_hero;

	if (key == GLFW_KEY_S && action != GLFW_RELEASE)
		y_hero_position -= speed_hero;

	if (key == GLFW_KEY_RIGHT && action != GLFW_RELEASE)
		x_hero_position += speed_hero;

	if (key == GLFW_KEY_D && action != GLFW_RELEASE)
		x_hero_position += speed_hero;

	if (key == GLFW_KEY_LEFT && action != GLFW_RELEASE)
		x_hero_position -= speed_hero;

	if (key == GLFW_KEY_A && action != GLFW_RELEASE)
		x_hero_position -= speed_hero;

	if (hero[7].x <= -0.98f)
		x_hero_position += speed_hero;

	if (hero[7].y >= 1.0f)
		y_hero_position -= speed_hero;

	if (hero[0].y <= -1.0f)
		y_hero_position += speed_hero;

	if (hero[3].x >= 0.99f)
		x_hero_position -= speed_hero;
}

inline void createVABOHero()
{
	glBindVertexArray(gVAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(hero), hero, GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

inline void updateVABOHero()
{
	mat3f * position = new mat3f;
	vec3f * result = new vec3f;

	position->InitTransformWorldPosition(x_hero_position, y_hero_position);

	(*result) = bufferHero[0] * (*position);
	hero[0] = vec2f(result->x, result->y);

	(*result) = bufferHero[1] * (*position);
	hero[1] = vec2f(result->x, result->y);

	(*result) = bufferHero[2] * (*position);
	hero[2] = vec2f(result->x, result->y);

	(*result) = bufferHero[3] * (*position);
	hero[3] = vec2f(result->x, result->y);

	(*result) = bufferHero[4] * (*position);
	hero[4] = vec2f(result->x, result->y);

	(*result) = bufferHero[5] * (*position);
	hero[5] = vec2f(result->x, result->y);

	(*result) = bufferHero[6] * (*position);
	hero[6] = vec2f(result->x, result->y);

	(*result) = bufferHero[7] * (*position);
	hero[7] = vec2f(result->x, result->y);

	(*result) = bufferHero[8] * (*position);
	hero[8] = vec2f(result->x, result->y);

	(*result) = bufferHero[9] * (*position);
	hero[9] = vec2f(result->x, result->y);

	(*result) = bufferHero[10] * (*position);
	hero[10] = vec2f(result->x, result->y);

	(*result) = bufferHero[11] * (*position);
	hero[11] = vec2f(result->x, result->y);

	(*result) = bufferHero[12] * (*position);
	hero[12] = vec2f(result->x, result->y);

	(*result) = bufferHero[13] * (*position);
	hero[13] = vec2f(result->x, result->y);

	(*result) = bufferHero[14] * (*position);
	hero[14] = vec2f(result->x, result->y);

	(*result) = bufferHero[15] * (*position);
	hero[15] = vec2f(result->x, result->y);

	(*result) = bufferHero[16] * (*position);
	hero[16] = vec2f(result->x, result->y);

	(*result) = bufferHero[17] * (*position);
	hero[17] = vec2f(result->x, result->y);

	delete position;
	delete result;
}

inline void createVABONlo()
{
	glBindVertexArray(gVAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nlo), nlo, GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexNlo), indexNlo, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

inline void updateVABONlo()
{
	mat3f * position = new mat3f;
	vec3f * result = new vec3f;

	if (x_nlo_position <= 0.0f)
	{
		speed_nlo = 0.03f;
		y_nlo_position += speed_nlo;
		position->InitTransformWorldPosition(0.0f, sinf(y_nlo_position));
	}
	else
	{
		x_nlo_position -= speed_nlo;
		position->InitTransformWorldPosition(x_nlo_position, 0.0f);
	}

	(*result) = bufferNlo[0] * (*position);
	nlo[0] = vec2f(result->x, result->y);

	(*result) = bufferNlo[1] * (*position);
	nlo[1] = vec2f(result->x, result->y);

	(*result) = bufferNlo[2] * (*position);
	nlo[2] = vec2f(result->x, result->y);

	(*result) = bufferNlo[3] * (*position);
	nlo[3] = vec2f(result->x, result->y);

	delete position;
	delete result;
}

inline void createVABORocketNlo()
{
	glBindVertexArray(gVAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nlo_rocket), nlo_rocket, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

inline void updateVABORocketNlo()
{
	mat3f * position = new mat3f;

	position->InitTransformWorldPosition(x_rocekt_nlo_position, 0.0f);

	vec3f * buffer0 = new vec3f(nlo_rocket[0]);
	vec3f * buffer1 = new vec3f(nlo_rocket[1]);
	vec3f * buffer2 = new vec3f(nlo_rocket[2]);
	vec3f * result = new vec3f;

	(*result) = (*buffer0) * (*position);
	nlo_rocket[0] = vec2f(result->x, result->y);

	(*result) = (*buffer1) * (*position);
	nlo_rocket[1] = vec2f(result->x, result->y);

	(*result) = (*buffer2) * (*position);
	nlo_rocket[2] = vec2f(result->x, result->y);

	delete result;
	delete buffer2;
	delete buffer1;
	delete buffer0;
	delete position;
}

inline void createVABOStars()
{
	glBindVertexArray(gVAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stars), stars, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

inline void updateVABOStars()
{
	for (uint8_t i = 0; i < STARS; ++i)
	{
		if (stars[i].x <= -1.0f)
		{
			stars[i] = vec2f(1.0f, RandomizeY());
		}

		if (i % 6 != 0)
		{
			stars[i].x -= speed_star_standart;
		}
		else
		{
			stars[i].x -= speed_star_none;
		}

		if (i % 10 != 0)
		{
			stars[i].x -= speed_star_standart;
		}
		else
		{
			stars[i].x -= speed_star;
		}
	}
}

inline void createVABORocketHero()
{
		glBindVertexArray(gVAO[4]);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(hero_rocket[0]), hero_rocket[0], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		glBindVertexArray(gVAO[5]);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO[5]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(hero_rocket[1]), hero_rocket[1], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		glBindVertexArray(gVAO[6]);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO[6]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(hero_rocket[2]), hero_rocket[2], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		glBindVertexArray(gVAO[7]);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO[7]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(hero_rocket[3]), hero_rocket[3], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		glBindVertexArray(gVAO[8]);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO[8]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(hero_rocket[4]), hero_rocket[4], GL_STREAM_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
}


inline void updateVABORocketHero()
{
	mat3f * position = new mat3f;
	vec3f * buffer = new vec3f;
	vec3f * result = new vec3f;

	for (int8_t i = 0; i < HERO_ROCKETS; ++i)
	{

		EGObool col = PointTriangleVec2f(&hero_rocket[i][3].x, &hero_rocket[i][3].y,&nlo[0].x,&nlo[0].y,&nlo[2].x,&nlo[2].y,&nlo[3].x,&nlo[3].y);

		if (col == 1 && x_nlo_position < 0.0f)
			nlo_update_is_ok = false;

		col = PointTriangleVec2f(&hero_rocket[i][6].x, &hero_rocket[i][6].y, &nlo[0].x, &nlo[0].y, &nlo[2].x, &nlo[2].y, &nlo[3].x, &nlo[3].y);

		if (col == 1 && x_nlo_position < 0.0f)
			nlo_update_is_ok = false;

		if (hero_attac[i] == true)
		{
			x_rocket_hero_position[i] += speed_hero_rocket;
			position->InitTransformWorldPosition(x_rocket_hero_position[i], 0.0f);

			buffer = new vec3f(hero_rocket[i][0]);

			(*result) = (*buffer) * (*position);
			hero_rocket[i][0] = vec2f(result->x, result->y);

			buffer = new vec3f(hero_rocket[i][1]);

			(*result) = (*buffer) * (*position);
			hero_rocket[i][1] = vec2f(result->x, result->y);

			buffer = new vec3f(hero_rocket[i][2]);

			(*result) = (*buffer) * (*position);
			hero_rocket[i][2] = vec2f(result->x, result->y);

			buffer = new vec3f(hero_rocket[i][3]);

			(*result) = (*buffer) * (*position);
			hero_rocket[i][3] = vec2f(result->x, result->y);

			buffer = new vec3f(hero_rocket[i][4]);

			(*result) = (*buffer) * (*position);
			hero_rocket[i][4] = vec2f(result->x, result->y);

			buffer = new vec3f(hero_rocket[i][5]);

			(*result) = (*buffer) * (*position);
			hero_rocket[i][5] = vec2f(result->x, result->y);

			buffer = new vec3f(hero_rocket[i][6]);

			(*result) = (*buffer) * (*position);
			hero_rocket[i][6] = vec2f(result->x, result->y);

			buffer = new vec3f(hero_rocket[i][7]);

			(*result) = (*buffer) * (*position);
			hero_rocket[i][7] = vec2f(result->x, result->y);
		}
	}

	delete result;
	delete buffer;
	delete position;
}

inline void updateHeroRockets()
{
	for (int8_t i = 0; i < HERO_ROCKETS; ++i)
	{
		if (hero_rocket[i][0].x >= 1.0f)
		{
			x_rocket_hero_position[i] = 0.0f;
			hero_attac[i] = false;

			hero_rocket[i][0] = vec2f(0.0f, 0.0f);
			hero_rocket[i][2] = vec2f(0.0f, 0.0f);
			hero_rocket[i][2] = vec2f(0.0f, 0.0f);
			hero_rocket[i][3] = vec2f(0.0f, 0.0f);

			hero_rocket[i][4] = vec2f(0.0f, 0.0f);
			hero_rocket[i][5] = vec2f(0.0f, 0.0f);
			hero_rocket[i][6] = vec2f(0.0f, 0.0f);
			hero_rocket[i][7] = vec2f(0.0f, 0.0f);
		}
	}
}

inline void updatePer()
{
	for (short int i = 0; i < HERO_ROCKETS; ++i)
	{
		if (hero_attac[i] == true)
		{
			peregrev = true;
		}
		else
		{
			peregrev = false;
			return;
		}
	}
}

inline void createAsteroids()
{
	glBindVertexArray(gVAO[9]);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO[9]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(asteroids[0]), asteroids[0], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(gVAO[10]);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO[10]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(asteroids[1]), asteroids[1], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(gVAO[11]);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO[11]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(asteroids[2]), asteroids[2], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(gVAO[12]);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO[12]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(asteroids[3]), asteroids[3], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(gVAO[13]);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO[13]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(asteroids[4]), asteroids[4], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

inline void updateAsteroids()
{
	mat3f * position = new mat3f;
	mat3f * rotation = new mat3f;
	vec3f * buffer = new vec3f;
	vec3f * rep = new vec3f;

	position->InitTransformWorldPosition(x_asteroid_position, y_asteroid_position);
	rotation->InitTransformRotation(x_asteroid_rotation);

	for (int8_t i = 0; i < ASTEROIDS; ++i)
	{
		buffer = new vec3f(asteroids[i][0]);
		(*rep) = (*buffer) * (*rotation);
		asteroids[i][0] = vec2f(rep->x, rep->y);
		buffer = new vec3f(asteroids[i][0]);
		(*rep) = (*buffer) * (*position);
		asteroids[i][0] += vec2f(rep->x, rep->y);

		buffer = new vec3f(asteroids[i][1]);
		(*rep) = (*buffer) * (*rotation);
		asteroids[i][1] = vec2f(rep->x, rep->y);
		buffer = new vec3f(asteroids[i][1]);
		(*rep) = (*buffer) * (*position);
		asteroids[i][1] += vec2f(rep->x, rep->y);

		buffer = new vec3f(asteroids[i][2]);
		(*rep) = (*buffer) * (*rotation);
		asteroids[i][2] = vec2f(rep->x, rep->y);
		buffer = new vec3f(asteroids[i][2]);
		(*rep) = (*buffer) * (*position);
		asteroids[i][2] += vec2f(rep->x, rep->y);

		buffer = new vec3f(asteroids[i][3]);
		(*rep) = (*buffer) * (*rotation);
		asteroids[i][3] = vec2f(rep->x, rep->y);
		buffer = new vec3f(asteroids[i][3]);
		(*rep) = (*buffer) * (*position);
		asteroids[i][3] += vec2f(rep->x, rep->y);

		buffer = new vec3f(asteroids[i][4]);
		(*rep) = (*buffer) * (*rotation);
		asteroids[i][4] = vec2f(rep->x, rep->y);
		buffer = new vec3f(asteroids[i][4]);
		(*rep) = (*buffer) * (*position);
		asteroids[i][4] += vec2f(rep->x, rep->y);

		buffer = new vec3f(asteroids[i][5]);
		(*rep) = (*buffer) * (*rotation);
		asteroids[i][5] = vec2f(rep->x, rep->y);
		buffer = new vec3f(asteroids[i][5]);
		(*rep) = (*buffer) * (*position);
		asteroids[i][5] += vec2f(rep->x, rep->y);

		buffer = new vec3f(asteroids[i][6]);
		(*rep) = (*buffer) * (*rotation);
		asteroids[i][6] = vec2f(rep->x, rep->y);
		buffer = new vec3f(asteroids[i][6]);
		(*rep) = (*buffer) * (*position);
		asteroids[i][6] += vec2f(rep->x, rep->y);
	}

	delete rep;
	delete buffer;
	delete position;
}