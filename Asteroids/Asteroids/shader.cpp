#include "shader.h"



shader::shader()
{
	
}

shader::shader(std::string __filenameVS, std::string __filenameFS)
{
	this->filenameVS = __filenameVS;
	this->filenameFS = __filenameFS;

	std::string bufferOne = readFile(filenameVS);
	std::string bufferTwo = readFile(filenameFS);

	codeVS = bufferOne.c_str();
	codeFS = bufferTwo.c_str();

	createProgram(2);
}

shader::shader(std::string __filenameVS, std::string __filanemeFS, std::string __filanemeGS)
{
	this->filenameVS = __filenameVS;
	this->filenameFS = __filanemeFS;
	this->filenameGS = __filanemeGS;

	std::string bufferOne = readFile(filenameVS);
	std::string bufferTwo = readFile(filenameFS);
	std::string bufferThree = readFile(filenameGS);

	codeVS = bufferOne.c_str();
	codeFS = bufferTwo.c_str();
	codeGS = bufferThree.c_str();

	createProgram(3);
}

shader::~shader()
{
	glDeleteProgram(shaderID);
}

GLuint shader::getShaderID()
{
	return shaderID;
}

inline std::string shader::readFile(const std::string& filename)
{
	std::fstream file(filename.c_str());
	std::string result(std::istreambuf_iterator<char>(file.rdbuf()), std::istreambuf_iterator<char>());
	return result;
}

inline void shader::loadShader(GLuint shaderProgram, const char * code, GLenum type)
{
	if (shaderProgram == 0)
	{
		std::cout << "fatal error :: shader program is not OK!!!" << std::endl;
		return;
	}

	GLuint shaderProg = glCreateShader(type);
	GLint error, infoLogLenght;

	glShaderSource(shaderProg, 1, &code, NULL);
	glCompileShader(shaderProg);

	glGetShaderiv(shaderProg, GL_COMPILE_STATUS, &error);
	glGetShaderiv(shaderProg, GL_INFO_LOG_LENGTH, &infoLogLenght);
	if (!error)
	{
		GLchar * info = new GLchar[infoLogLenght];
		glGetShaderInfoLog(shaderProg, infoLogLenght, NULL, info);
		std::cout << "fatal error :: " << info << std::endl;
		delete[] info;
		return;
	}

	glAttachShader(shaderProgram, shaderProg);
}

inline void shader::createProgram(int t)
{
	GLint error, infoLogLenght;
	shaderID = glCreateProgram();

	if (t == 2)
	{
		loadShader(shaderID, codeVS, GL_VERTEX_SHADER);
		loadShader(shaderID, codeFS, GL_FRAGMENT_SHADER);
	}

	if (t == 3)
	{
		loadShader(shaderID, codeVS, GL_VERTEX_SHADER);
		loadShader(shaderID, codeFS, GL_FRAGMENT_SHADER);
		loadShader(shaderID, codeGS, GL_GEOMETRY_SHADER);
	}

	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &error);
	glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLenght);

	if (error == 0)
	{
		GLchar * info = new GLchar[infoLogLenght];
		glGetProgramInfoLog(shaderID, infoLogLenght, NULL, info);
		std::cout << "fatal error :: " << info << std::endl;
		delete[] info;
		return;
	}

	glValidateProgram(shaderID);

	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &error);
	glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLenght);

	if (error == 0)
	{
		GLchar * info = new GLchar[infoLogLenght];
		glGetProgramInfoLog(shaderID, infoLogLenght, NULL, info);
		std::cout << "fatal error :: " << info << std::endl;
		delete[] info;
		return;
	}
}
