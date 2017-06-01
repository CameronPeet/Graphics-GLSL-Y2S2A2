#include "ShaderLoader.h"


class ShaderProgram
{
public:
	
	ShaderProgram(char*  vertexFile, char*  fragmentFile);
	ShaderProgram(char*  vertexFile, char*  fragmentFile, char*  geometryFile);
	ShaderProgram(char*  vertexFile, char*  fragmentFile, char*  geometryFile, char*  TesAFile, char*  TesBFile);
	~ShaderProgram();

	void Use();
	void BindAttribute(int attribute, char* variable);

	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint geometryShader;
	GLuint tesShaderA;
	GLuint tesShaderB;
	GLuint computeShader;

	bool OK = false;

private:
	static ShaderLoader shaderLoader;
};