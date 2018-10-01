#include "Enemy.h"

Enemy::Enemy()
{
	points[0] = vec2f(0.7f, 0.0f);
	points[1] = vec2f(0.745f, 0.0f);
	points[2] = vec2f(0.75f, 0.05f);
	points[3] = vec2f(0.75f, -0.05f);

	rocket[0] = vec2f(-10.0f, -10.0f);
	rocket[1] = vec2f(-10.0f, -10.0f);
	rocket[2] = vec2f(-10.0f, -10.0f);

	bufferRocket[0] = vec3f(rocket[0]);
	bufferRocket[1] = vec3f(rocket[1]);
	bufferRocket[2] = vec3f(rocket[2]);

	buffer[0] = points[0];
	buffer[1] = points[1];
	buffer[2] = points[2];
	buffer[3] = points[3];

	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 0;
	index[4] = 1;
	index[5] = 3;
}

Enemy::Enemy(const vec2f(&_points)[4])
{

	points[0] = _points[0];
	points[1] = _points[1];
	points[2] = _points[2];
	points[3] = _points[3];

	buffer[0] = points[0];
	buffer[1] = points[1];
	buffer[2] = points[2];
	buffer[3] = points[3];

	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 0;
	index[4] = 1;
	index[5] = 3;
}

Enemy::~Enemy()
{
	delete[] points;
	delete[] buffer;
	delete[] rocket;
	delete ptr;
	delete[] index;
	delete[] bufferRocket;
	delete m_position;
	delete m_scale;
	delete m_rotation;
	delete m_result;
	delete m_position_rocket;
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VAORocket);
	glDeleteBuffers(1, &VBORocket);
}

void Enemy::initScale(float ScaleX, float ScaleY)
{
	m_scale->InitTransformScale(ScaleX, ScaleY);
}

void Enemy::initPosition(float PositionX, float PositionY)
{
	m_position->InitTransformWorldPosition(PositionX, PositionY);
}

void Enemy::initRotate(float rot)
{
	m_rotation->InitTransformRotation(rot);
}

void Enemy::updatePosition()
{
	(*ptr) = buffer[0] * (*m_position);
	points[0] = vec2f(ptr->x, ptr->y);

	(*ptr) = buffer[1] * (*m_position);
	points[1] = vec2f(ptr->x, ptr->y);

	(*ptr) = buffer[2] * (*m_position);
	points[2] = vec2f(ptr->x, ptr->y);

	(*ptr) = buffer[3] * (*m_position);
	points[3] = vec2f(ptr->x, ptr->y);
}

void Enemy::genVABIO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glGenVertexArrays(1, &VAORocket);
	glGenBuffers(1, &VBORocket);
}

void Enemy::create()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*points) * 4, points, GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*index) * 6, index, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Enemy::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

bool Enemy::getStatus()
{
	return is_ok;
}

float Enemy::getX(unsigned int index)
{
	try
	{
		if (index >= 4)
		{
			throw 101;
		}
	}

	catch (int i)
	{
		std::cout << "filed::" << i << std::endl;
		return(0.0f);
	}

	return points[index].x;
}

float Enemy::getY(unsigned int index)
{
	try
	{
		if (index >= 4)
		{
			throw 101;
		}
	}

	catch (int i)
	{
		std::cout << "filed::" << i << std::endl;
		return(0.0f);
	}


	return points[index].y;
}

float Enemy::getRocketX(unsigned int index)
{
	try
	{
		if (index >= 3)
			throw 143;
	}
	catch (int i)
	{
		std::cout << "failed::" << i << std::endl;
		return(0.0f);
	}

	return rocket[index].x;
}

float Enemy::getRocketY(unsigned int index)
{
	try
	{
		if (index >= 3)
			throw 143;
	}
	catch (int i)
	{
		std::cout << "failed::" << i << std::endl;
		return(0.0f);
	}

	return rocket[index].y;
}

void Enemy::pos()
{
	rocket[0] = points[0];
	rocket[1] = vec2f(points[1].x - 0.02f, points[2].y - 0.065f);
	rocket[2] = vec2f(points[1].x - 0.02f, points[3].y + 0.065f);

	bufferRocket[0] = vec3f(rocket[0]);
	bufferRocket[1] = vec3f(rocket[1]);
	bufferRocket[2] = vec3f(rocket[2]);
}

void Enemy::emptyRocket()
{
	rocket[0] = vec2f(-10.0f, -10.0f);
	rocket[1] = vec2f(-10.0f, -10.0f);
	rocket[2] = vec2f(-10.0f, -10.0f);

	bufferRocket[0] = vec3f(rocket[0]);
	bufferRocket[1] = vec3f(rocket[1]);
	bufferRocket[2] = vec3f(rocket[2]);
}

void Enemy::createRocket()
{
	glBindVertexArray(VAORocket);
	glBindBuffer(GL_ARRAY_BUFFER, VBORocket);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*rocket) * 3, rocket, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Enemy::initPositionRocket(float PositionX, float PositionY)
{
	m_position_rocket->InitTransformWorldPosition(PositionX, PositionY);
}

void Enemy::updetPositionRocket()
{
	(*ptr) = bufferRocket[0] * (*m_position_rocket);
	rocket[0] = vec2f(ptr->x, ptr->y);

	(*ptr) = bufferRocket[1] * (*m_position_rocket);
	rocket[1] = vec2f(ptr->x, ptr->y);

	(*ptr) = bufferRocket[2] * (*m_position_rocket);
	rocket[2] = vec2f(ptr->x, ptr->y);
}

void Enemy::drawRocket()
{
	glBindVertexArray(VAORocket);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}