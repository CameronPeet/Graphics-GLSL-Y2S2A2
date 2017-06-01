#pragma once

#include "Camera.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class GameObject 
{
public:

	virtual bool Initialise() = 0;
	virtual void Update() = 0;
	virtual void Render(GLuint program = 0, Camera* camera = nullptr) = 0;

	
protected:

	bool enabled;

	glm::mat4 transform;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 localScale;
};









