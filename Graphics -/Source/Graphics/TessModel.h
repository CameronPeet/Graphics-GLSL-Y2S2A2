#pragma once

#include "Camera.h"

class TessModel
{

public:
	~TessModel();

	TessModel(GLuint program, Camera* camera);

	void Render();

	//Scale, Position and Rotation Components
	glm::quat m_Rotation;
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_RotationPoint;

	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint texture;

	GLuint program;
	Camera* camera;
};