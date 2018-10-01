#pragma once

#include "Hero.h"

Hero::Hero()
{
	points[0] = vec2f(0.01f, 0.01f);
	points[1] = vec2f(0.03f, 0.01f);
	points[2] = vec2f(0.05f, 0.04f);
	points[3] = vec2f(0.11f, 0.05f);
	points[4] = vec2f(0.11f, 0.08f);
	points[5] = vec2f(0.05f, 0.09f);
	points[6] = vec2f(0.03f, 0.12f);
	points[7] = vec2f(0.01f, 0.12f);
	points[8] = vec2f(0.03f, 0.09f);
	points[9] = vec2f(0.03f, 0.04f);
	points[10] = vec2f(0.03f, 0.1f);
	points[11] = vec2f(0.03f, 0.11f);
	points[12] = vec2f(0.06f, 0.11f);
	points[13] = vec2f(0.06f, 0.1f);
	points[14] = vec2f(0.03f, 0.02f);
	points[15] = vec2f(0.03f, 0.03f);
	points[16] = vec2f(0.06f, 0.03f);
	points[17] = vec2f(0.06f, 0.02f);

	buffer[0] = vec3f(points[0]);
	buffer[1] = vec3f(points[1]);
	buffer[2] = vec3f(points[2]);
	buffer[3] = vec3f(points[3]);
	buffer[4] = vec3f(points[4]);
	buffer[5] = vec3f(points[5]);
	buffer[6] = vec3f(points[6]);
	buffer[7] = vec3f(points[7]);
	buffer[8] = vec3f(points[8]);
	buffer[9] = vec3f(points[9]);
	buffer[10] = vec3f(points[10]);
	buffer[11] = vec3f(points[11]);
	buffer[12] = vec3f(points[12]);
	buffer[13] = vec3f(points[13]);
	buffer[14] = vec3f(points[14]);
	buffer[15] = vec3f(points[15]);
	buffer[16] = vec3f(points[16]);
	buffer[17] = vec3f(points[17]);
}

Hero::Hero(const vec2f(&_points)[18])
{
	for (int8_t i = 0; i < 18; ++i)
	{
		points[i] = _points[i];
		buffer[i] = vec3f(points[i]);
	}
}

Hero::~Hero()
{
	delete m_position;
	delete m_scale;
	delete m_result;
	delete m_position_rocket;
	delete tempret;
	delete buffer_rocket;
	delete[] points;
	delete[] buffer;

	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(5, VBORockets);
	glDeleteBuffers(5, VAORockets);
}

void Hero::genVABIO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
}

void Hero::genVABORockets()
{
	glGenVertexArrays(5, VAORockets);
	glGenBuffers(5, VBORockets);
}

void Hero::create()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*points) * 18, points, GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_index), m_index, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

float Hero::getX(unsigned int index)
{
	try
	{
		if (index >= 18)
			throw 145;
	}
	catch (int i)
	{
		std::cout << "failed::" << i << std::endl;
		return(0.0f);
	}

	return(points[index].x);
}

float Hero::getY(unsigned int index)
{
	try
	{
		if (index >= 18)
			throw 145;
	}
	catch (int i)
	{
		std::cout << "failed::" << i << std::endl;
		return(0.0f);
	}

	return(points[index].y);
}

float Hero::getRocketX(unsigned int index_one, unsigned int index_two)
{
	try
	{
		if (index_one >= 5 || index_two >= 8)
			throw 156;
	}
	catch (int i)
	{
		std::cout << "failed :: " << i << std::endl;
		return(0.0f);
	}

	return(rocket[index_one][index_two].x);
}

float Hero::getRocketY(unsigned int index_one, unsigned int index_two)
{
	try
	{
		if (index_one >= 5 || index_two >= 8)
			throw 156;
	}
	catch (int i)
	{
		std::cout << "failed :: " << i << std::endl;
		return(0.0f);
	}

	return(rocket[index_one][index_two].y);
}

void Hero::initScaleHero(float ScaleX, float ScaleY)
{
	m_scale->InitTransformScale(ScaleX, ScaleY);
}

void Hero::initPositionHero(float PositionX, float PositionY)
{
	m_position->InitTransformWorldPosition(PositionX, PositionY);
}

void Hero::initScaleAndPositionHero(float ScaleX, float ScaleY, float PositionX, float PositionY)
{
	m_scale->InitTransformScale(ScaleX, ScaleY);
	m_position->InitTransformWorldPosition(PositionX, PositionY);

	(*m_result) = (*m_position) * (*m_scale);
}

void Hero::updateScale()
{
	(*tempret) = buffer[0] * (*m_scale);
	points[0] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[1] * (*m_scale);
	points[1] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[2] * (*m_scale);
	points[2] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[3] * (*m_scale);
	points[3] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[4] * (*m_scale);
	points[4] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[5] * (*m_scale);
	points[5] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[6] * (*m_scale);
	points[6] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[7] * (*m_scale);
	points[7] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[8] * (*m_scale);
	points[8] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[9] * (*m_scale);
	points[9] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[10] * (*m_scale);
	points[10] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[11] * (*m_scale);
	points[11] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[12] * (*m_scale);
	points[12] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[13] * (*m_scale);
	points[13] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[14] * (*m_scale);
	points[14] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[15] * (*m_scale);
	points[15] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[16] * (*m_scale);
	points[16] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[17] * (*m_scale);
	points[17] = vec2f(tempret->x, tempret->y);
}

void Hero::updatePosition()
{
	(*tempret) = buffer[0] * (*m_position);
	points[0] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[1] * (*m_position);
	points[1] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[2] * (*m_position);
	points[2] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[3] * (*m_position);
	points[3] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[4] * (*m_position);
	points[4] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[5] * (*m_position);
	points[5] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[6] * (*m_position);
	points[6] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[7] * (*m_position);
	points[7] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[8] * (*m_position);
	points[8] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[9] * (*m_position);
	points[9] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[10] * (*m_position);
	points[10] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[11] * (*m_position);
	points[11] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[12] * (*m_position);
	points[12] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[13] * (*m_position);
	points[13] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[14] * (*m_position);
	points[14] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[15] * (*m_position);
	points[15] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[16] * (*m_position);
	points[16] = vec2f(tempret->x, tempret->y);

	(*tempret) = buffer[17] * (*m_position);
	points[17] = vec2f(tempret->x, tempret->y);
}

void Hero::updateRocket()
{
	for (int8_t i = 0; i < 5; ++i)
	{
		if (hero_attac[i] == true)
		{
			position_rocket[i] += speed_rocket;
			m_position_rocket->InitTransformWorldPosition(position_rocket[i], 0.0f);

			buffer_rocket = new vec3f(rocket[i][0]);
			(*tempret) = (*buffer_rocket) * (*m_position_rocket);
			rocket[i][0] = vec2f(tempret->x, tempret->y);

			buffer_rocket = new vec3f(rocket[i][1]);
			(*tempret) = (*buffer_rocket) * (*m_position_rocket);
			rocket[i][1] = vec2f(tempret->x, tempret->y);

			buffer_rocket = new vec3f(rocket[i][2]);
			(*tempret) = (*buffer_rocket) * (*m_position_rocket);
			rocket[i][2] = vec2f(tempret->x, tempret->y);

			buffer_rocket = new vec3f(rocket[i][3]);
			(*tempret) = (*buffer_rocket) * (*m_position_rocket);
			rocket[i][3] = vec2f(tempret->x, tempret->y);

			buffer_rocket = new vec3f(rocket[i][4]);
			(*tempret) = (*buffer_rocket) * (*m_position_rocket);
			rocket[i][4] = vec2f(tempret->x, tempret->y);

			buffer_rocket = new vec3f(rocket[i][5]);
			(*tempret) = (*buffer_rocket) * (*m_position_rocket);
			rocket[i][5] = vec2f(tempret->x, tempret->y);

			buffer_rocket = new vec3f(rocket[i][6]);
			(*tempret) = (*buffer_rocket) * (*m_position_rocket);
			rocket[i][6] = vec2f(tempret->x, tempret->y);

			buffer_rocket = new vec3f(rocket[i][7]);
			(*tempret) = (*buffer_rocket) * (*m_position_rocket);
			rocket[i][7] = vec2f(tempret->x, tempret->y);
		}
	}
}

void Hero::drawHero()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, (void*)0);
}

void Hero::drawRocket()
{
		glBindVertexArray(VAORockets[0]);
		glDrawArrays(GL_QUADS, 0, 8);

		glBindVertexArray(VAORockets[1]);
		glDrawArrays(GL_QUADS, 0, 8);

		glBindVertexArray(VAORockets[2]);
		glDrawArrays(GL_QUADS, 0, 8);

		glBindVertexArray(VAORockets[3]);
		glDrawArrays(GL_QUADS, 0, 8);

		glBindVertexArray(VAORockets[4]);
		glDrawArrays(GL_QUADS, 0, 8);
}

void Hero::createRocket()
{
	glBindVertexArray(VAORockets[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBORockets[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rocket[0]), rocket[0], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAORockets[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBORockets[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rocket[1]), rocket[1], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAORockets[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBORockets[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rocket[2]), rocket[2], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAORockets[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBORockets[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rocket[3]), rocket[3], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAORockets[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBORockets[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rocket[4]), rocket[4], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Hero::genRocket(int8_t index)
{
	if (index >= 5)
		return;

	hero_attac[index] = true;
	rocket[index][0] = points[10];
	rocket[index][1] = points[11];
	rocket[index][2] = points[12];
	rocket[index][3] = points[13];

	rocket[index][4] = points[14];
	rocket[index][5] = points[15];
	rocket[index][6] = points[16];
	rocket[index][7] = points[17];
	
}

void Hero::proverca()
{
	for (int8_t i = 0; i < 5; ++i)
	{
		if (rocket[i][1].x >= 1.0f)
		{
			hero_attac[i] = false;
			position_rocket[i] = 0.0f;

			rocket[i][0] = vec2f(0.0f, 0.0f);
			rocket[i][1] = vec2f(0.0f, 0.0f);
			rocket[i][2] = vec2f(0.0f, 0.0f);
			rocket[i][3] = vec2f(0.0f, 0.0f);

			rocket[i][4] = vec2f(0.0f, 0.0f);
			rocket[i][5] = vec2f(0.0f, 0.0f);
			rocket[i][6] = vec2f(0.0f, 0.0f);
			rocket[i][7] = vec2f(0.0f, 0.0f);
		}
	}
}

void Hero::updatePeregrev()
{
	for (int8_t i = 0; i < 5; ++i)
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

bool Hero::getPer()
{
	return peregrev;
}