#include "Window.h"

Window::Window()
{
}

Window::~Window()
{
	glDeleteBuffers(1, &VAOStars);
	glDeleteBuffers(1, &VBOStars);
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "fatal erro :: GLFW is not init!!!" << std::endl;
		return(false);
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "Asteroids", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "fatal error :: GLEW is not OK!!!" << std::endl;
		return(false);
	}

	return(true);
}

void Window::createGame()
{
	spaceship.genVABIO();
	spaceship.genVABORockets();

	nlo.genVABIO();
	
	glGenVertexArrays(1, &VAOStars);
	glGenBuffers(1, &VBOStars);

	srand(time(NULL));
	for (uint8_t i = 0; i < STARS; ++i)
		stars[i] = vec2f(RandomizeX(), RandomizeY());
	
	program = shader("vertex.vert", "fragment.frag");
}

void Window::mainLoop()
{
	render();
	update();
	
	glfwSwapBuffers(window);
}

bool Window::exit()
{
	return(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}

float Window::RandomizeX()
{
	return(0.0011f * float(-(HEIGHT) + rand() % WIDTH));
}

float Window::RandomizeY()
{
	return(0.0011f * float(-(HEIGHT) + rand() % WIDTH));
}

void Window::key_callback()
{
	glfwGetWindowUserPointer(window);

	if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
		tem.y_hero_position += tem.speed_hero;

	if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
		tem.y_hero_position += tem.speed_hero;

	if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
		tem.y_hero_position -= tem.speed_hero;

	if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
		tem.y_hero_position -= tem.speed_hero;

	if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
		tem.x_hero_position += tem.speed_hero;

	if (glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
		tem.x_hero_position += tem.speed_hero;

	if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
		tem.x_hero_position -= tem.speed_hero;

	if (glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
		tem.x_hero_position -= tem.speed_hero;

	if (spaceship.getX(0) <= -1.0f)
		tem.x_hero_position += tem.speed_hero;

	if (spaceship.getX(3) >= 1.0f)
		tem.x_hero_position -= tem.speed_hero;

	if (spaceship.getY(6) >= 1.0f)
		tem.y_hero_position -= tem.speed_hero;

	if (spaceship.getY(0) <= -1.0f)
		tem.y_hero_position += tem.speed_hero;
}

void Window::render()
{
	key_callback();
	if (c == 5)
		c = 0;

	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program.getShaderID());

	createVABOStars();
	spaceship.create();
	nlo.create();
	createVABOStars();
	nlo.createRocket();
	spaceship.createRocket();

	nlo.draw();
	spaceship.drawHero();
	spaceship.drawRocket();
	nlo.drawRocket();

	glBindVertexArray(VAOStars);
	glDrawArrays(GL_POINTS, 0, STARS);

	glBindVertexArray(0);
}

void Window::update()
{
	nlo.initPosition(tem.x_nlo_position, sinf(tem.y_nlo_position));

	if (!(tem.x_nlo_position <= 0.0f))
	{
		tem.x_nlo_position -= tem.speed_nlo;
		tem.y_nlo_position = 0.0f;
	}
	else
	{
		tem.speed_nlo = 0.015f;
		tem.x_nlo_position = 0.0f;
		tem.y_nlo_position += tem.speed_nlo;
	}

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && spaceship.getPer() != true)
	{
		spaceship.genRocket(c);
		c++;
	}
	
	float pos = sinf(tem.y_nlo_position);

	if (pos < 0.8f && pos > 0.7f)
	{
		nlo.pos();
		tem.nlo_attacks = true;
	}

	if (pos > -0.8f && pos < -0.7f)
	{
		nlo.pos();
		tem.nlo_attacks = true;
	}

	if (nlo.getRocketX(0) <= -1.0f)
	{
		tem.x_rocekt_nlo_position = 0.0f;
		tem.nlo_attacks = false;
	}

	if (tem.nlo_attacks)
	{

		tem.x_rocekt_nlo_position -= tem.speed_nlo_rocket;
		nlo.initPositionRocket(tem.x_rocekt_nlo_position, 0.0f);
	}
	else
	{
		nlo.emptyRocket();
		tem.x_rocekt_nlo_position = 0.0f;
	}
	
	//EGObool nloRocketToHero = PointQuadsVec2f(nlo.getRocketX(0), nlo.getRocketY(0), spaceship.getX(2), spaceship.getY(2), spaceship.getX(4), spaceship.getY(4));
//	if (nloRocketToHero == 1)
	//	update_is_ok = false;
	//EGObool heroRocketToNlo = PointTriangleVec2f(spaceship.getRocketX(0, 1), spaceship.getRocketY(0, 6), nlo.getX(0), nlo.getY(0), nlo.getX(2), nlo.getY(2), nlo.getX(3), nlo.getY(3));
	//if (heroRocketToNlo == 1)
		//update_is_ok = false;
	if (update_is_ok)
	{
		spaceship.initPositionHero(tem.x_hero_position, tem.y_hero_position);
		spaceship.updatePosition();
		spaceship.proverca();
		spaceship.updateRocket();
		spaceship.updatePeregrev();

		nlo.updetPositionRocket();

		updateVABOStars();
		nlo.updatePosition();
	}
}

void Window::createVABOStars()
{
	glBindVertexArray(VAOStars);
	glBindBuffer(GL_ARRAY_BUFFER, VBOStars);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stars), stars, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Window::updateVABOStars()
{
	for (uint8_t i = 0; i < STARS; ++i)
	{
		if (stars[i].x <= -1.0f)
		{
			stars[i] = vec2f(1.0f, RandomizeY());
		}

		if (i % 6 != 0)
		{
			stars[i].x -= tem.speed_star_standart;
		}
		else
		{
			stars[i].x -= tem.speed_star_none;
		}

		if (i % 10 != 0)
		{
			stars[i].x -= tem.speed_star_standart;
		}
		else
		{
			stars[i].x -= tem.speed_star;
		}
	}
}