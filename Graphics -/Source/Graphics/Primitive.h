#pragma once

//Dependencies
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <soil\SOIL.h>
#include <vector>
#include "Utils.h"

//Parent Class
#include "GameObject.h"

enum class PrimitiveShape
{
	QUAD,
	CIRCLE,
	TRIANGLE,
	CUBE,
	CUBEMAP,
	SPHERE,
	CYLINDER,
};

class Primitive : public GameObject
{
public:

	Primitive();
	Primitive(PrimitiveShape shape, char* _texturePath = nullptr);

	~Primitive();

	virtual bool Initialise();
	virtual void Update();
	virtual void Render(GLuint program = 0, Camera* camera = nullptr);

	GLuint vao;
	GLuint vbo;
	GLuint ebo;


	std::vector<VertexFormat> vertices;
	std::vector<GLuint> indices;

	PrimitiveShape shape;

	GLuint texture;
	char* texturePath;
};

