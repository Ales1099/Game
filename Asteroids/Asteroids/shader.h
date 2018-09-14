#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class shader
{
private:
	std::string filenameVS;
	std::string filenameFS;
	std::string filenameGS;
	const char * codeVS;
	const char * codeFS;
	const char * codeGS;
	GLuint shaderID;
public:
	shader();
	shader(std::string __filenameVS, std::string __filenameFS);
	shader(std::string __filanameVS, std::string __filenameFS, std::string __filenameGS);
	GLuint getShaderID();
	~shader();
private:
	inline std::string readFile(const std::string& filename);
	inline void loadShader(GLuint shaderProgram, const char * code, GLenum type);
	inline void createProgram(int t);
};