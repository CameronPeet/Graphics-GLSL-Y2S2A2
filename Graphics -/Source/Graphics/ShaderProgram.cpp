#include "ShaderProgram.h"

ShaderLoader ShaderProgram::shaderLoader = ShaderLoader();


ShaderProgram::ShaderProgram(char* vertexFile, char* fragmentFile)
{
	ShaderVariables shaderVariables = shaderLoader.CreateShaderProgram(vertexFile, fragmentFile);
	if (shaderVariables.OK)
	{
		program = shaderVariables.program;
		vertexShader = shaderVariables.vertexShader;
		fragmentShader = shaderVariables.fragmentShader;
		geometryShader = shaderVariables.geometryShader;
	}
}
ShaderProgram::ShaderProgram(char*  vertexFile, char*  fragmentFile, char*  geometryFile)
{
	ShaderVariables shaderVariables = shaderLoader.CreateShaderProgram(vertexFile, fragmentFile, geometryFile);
	if (shaderVariables.OK)
	{
		program = shaderVariables.program;
		vertexShader = shaderVariables.vertexShader;
		fragmentShader = shaderVariables.fragmentShader;
		geometryShader = shaderVariables.geometryShader;
	}
}
ShaderProgram::ShaderProgram(char*  vertexFile, char*  fragmentFile, char*  geometryFile, char*  TesAFile, char*  TesBFile)
{
	//ShaderVariables shaderVariables = shaderLoader.CreateShaderProgram(vertexFile, fragmentFile, geometryFile, TesAFile, TesBFile);
	/*if (shaderVariables.OK)
	{
		program = shaderVariables.program;
		vertexShader = shaderVariables.vertexShader;
		fragmentShader = shaderVariables.fragmentShader;
		geometryShader = shaderVariables.geometryShader;
		
	}*/
}
ShaderProgram::~ShaderProgram()
{
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	glDetachShader(program, geometryShader);
	glDetachShader(program, tesShaderA);
	glDetachShader(program, tesShaderB);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
	glDeleteShader(tesShaderA);
	glDeleteShader(tesShaderB);
	glDeleteProgram(program);
}


void ShaderProgram::Use()
{
	glUseProgram(program);
}


void ShaderProgram::BindAttribute(int attribute, char* variable)
{
	glBindAttribLocation(program, attribute, variable);
}

