#pragma once

#include <iostream>

#include <glew\glew.h>
#include <freeglut\freeglut.h>

struct ShaderVariables
{
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint geometryShader;
	GLuint tesShaderA;
	GLuint tesShaderB;
	GLuint computeShader;

	bool OK = false;
};

class ShaderLoader
{
private:

	std::string ReadShader(char *filename);
	GLuint CreateShader(GLenum shaderType,
		std::string source,
		char* shaderName);

public:

	ShaderLoader(void);
	~ShaderLoader(void);

	//Create vs, fs and gs shader program
	GLuint CreateProgram(char* VertexShaderFilename,
		char* FragmentShaderFilename,
		char* geometryShaderFilename = nullptr);

	GLuint CreateProgram(char* vertexShaderFilename,
		char* fragmentShaderFilename,
		char* tessControlShaderFilename,
		char* tessEvalShaderFilename);


	GLuint CreateComputeShaderProgram(char* computeShaderFilename);

	ShaderVariables CreateShaderProgram(char* VertexShaderFileName, char* FragmentShaderFileName, char* GeometryShaderFileName = nullptr);
};
