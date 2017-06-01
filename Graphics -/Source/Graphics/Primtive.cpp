#include "Primitive.h"
#include "Utils.h"

Primitive::Primitive()
{

}


Primitive::~Primitive()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}



Primitive::Primitive(PrimitiveShape shape, char* texturePath)
{
	switch (shape)
	{
	case PrimitiveShape::QUAD:
		Utils::SetQuad(vertices, indices);
		break;

	case PrimitiveShape::CIRCLE:
		Utils::SetCircle(vertices, indices);
		break;
	case PrimitiveShape::TRIANGLE:
		Utils::SetTriangle(vertices, indices);
		break;
	case PrimitiveShape::CUBE:
		Utils::SetCube(vertices, indices);
		break;
	case PrimitiveShape::CUBEMAP:
		Utils::SetCube(vertices, indices);
		break;
	case PrimitiveShape::SPHERE:
		Utils::SetSphere(vertices, indices);
		break;
	case PrimitiveShape::CYLINDER:
		break;
	}

	this->shape = shape;
	this->texturePath = texturePath;

	localScale = glm::vec3(1, 1, 1);
}


bool Primitive::Initialise()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	//Attribute Setting
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Texture Position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Vertex Normals
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	if (texturePath != nullptr)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// Set texutre wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height;
		unsigned char* image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	return true;
}

void Primitive::Update()
{

}


void Primitive::Render(GLuint program, Camera* camera)
{
	glUseProgram(program);

	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::scale(model, localScale);

	glm::mat4 normalMatrix;
	normalMatrix = glm::transpose(glm::inverse(model * camera->GetViewMatrix()));

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(program, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "Texture"), 0);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}