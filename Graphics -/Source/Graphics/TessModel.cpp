#include "TessModel.h"

TessModel::~TessModel()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

TessModel::TessModel(GLuint program, Camera* camera)
{
	this->program = program;
	this->camera = camera;

	GLfloat points[]
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};

	glPatchParameteri(GL_PATCH_VERTICES, 4); // Comment for tri patch

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	glBindVertexArray(0);
}


void TessModel::Render()
{
	glUseProgram(program);

	glm::mat4 model;
	//Translate the model according to its position and apply the rotation
	model = glm::translate(model, m_Position) * glm::mat4(m_Rotation);

	//Rotation points

	//Scale the model according to private member m_Scale
	glm::mat4 normalMatrix;
	normalMatrix = glm::transpose(glm::inverse(model * camera->GetViewMatrix()));

	glm::mat4 vp = camera->GetProjectionMatrix() * camera->GetViewMatrix() * model;

	GLuint vpLoc = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));

	glBindVertexArray(vao);
	glDrawArrays(GL_PATCHES, 0, 4);
	glBindVertexArray(0);
}