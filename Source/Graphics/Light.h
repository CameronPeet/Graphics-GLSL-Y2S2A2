#pragma once
#include "glm\glm.hpp"
class Light 
{
public:
	Light() {
		Position = glm::vec3(0.f, 0.f, 0.f);
		Color = glm::vec3(1.0f, 1.0f, 1.0f);
		float Intensity = 0.1f;
	}
	Light(glm::vec3 Position, glm::vec3 Color, float Intensity) {
		this->Position = Position;
		this->Color = Color;
		this->Intensity = Intensity;
	}

	glm::vec3 Position;
	glm::vec3 Color;
	float Intensity;

};

#pragma once

class DirLight
{
public:
	DirLight(glm::vec3 dir = glm::vec3(0), glm::vec3 amb = glm::vec3(0.2f), glm::vec3 dif = glm::vec3(0), glm::vec3 spec = glm::vec3(0))
		: direction(dir),
		  ambient(amb),
		  diffuse(dif),
		  specular(spec)
	{};

	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;


	void PassUniforms(GLuint program)
	{
		glUniform3fv(glGetUniformLocation(program, "dirLight.position"), 1, glm::value_ptr(direction));
		glUniform3fv(glGetUniformLocation(program, "dirLight.ambient"), 1, glm::value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(program, "dirLight.diffuse"), 1, glm::value_ptr(diffuse));
		glUniform3fv(glGetUniformLocation(program, "dirLight.specular"), 1, glm::value_ptr(specular));
	}
};

#pragma once

class PointLight : public DirLight
{
public:
	PointLight(glm::vec3 position = glm::vec3(0), glm::vec3 dir = glm::vec3(0), glm::vec3 amb = glm::vec3(0.2f), glm::vec3 dif = glm::vec3(0), glm::vec3 spec = glm::vec3(0), float constant = 0.f, float linear = 0.f, float quadratic = 0.f)
		: DirLight(dir, amb, dif, spec), position(position), constant(constant), linear(linear), quadratic(quadratic)
	{ };

	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	void PassUniforms(GLuint program)
	{
		glUniform3fv(glGetUniformLocation(program, "pointLight.position"), 1, glm::value_ptr(position));
		glUniform3fv(glGetUniformLocation(program, "pointLight.direction"), 1, glm::value_ptr(direction));
		glUniform3fv(glGetUniformLocation(program, "pointLight.ambient"), 1, glm::value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(program, "pointLight.diffuse"), 1, glm::value_ptr(diffuse));
		glUniform3fv(glGetUniformLocation(program, "pointLight.specular"), 1, glm::value_ptr(specular));


		glUniform1f(glGetUniformLocation(program, "pointLight.constant"), constant);
		glUniform1f(glGetUniformLocation(program, "pointLight.linear"), linear);
		glUniform1f(glGetUniformLocation(program, "pointLight.quadratic"), quadratic);
	}

};


class SpotLight : public PointLight
{
public:
		SpotLight(
			glm::vec3 position = glm::vec3(0),
			glm::vec3 dir = glm::vec3(0), 
			glm::vec3 amb = glm::vec3(0.2f),
			glm::vec3 dif = glm::vec3(1), 
			glm::vec3 spec = glm::vec3(1),
			float constant = 1.f, 
			float linear = 0.09f, 
			float quadratic = 0.032f, 
			float cutOff = 12.5f,
			float outerCutOff = 15.f)
			: PointLight(
				position,
				dir, 
				amb,
				dif, 
				spec, 
				constant, 
				linear,
				quadratic), cutOff(cutOff), outerCutOff(outerCutOff)
		{ };

		float cutOff;
		float outerCutOff;

		void PassUniforms(GLuint program)
		{
			glUniform3fv(glGetUniformLocation(program, "spotLight.position"), 1, glm::value_ptr(position));
			glUniform3fv(glGetUniformLocation(program, "spotLight.direction"), 1, glm::value_ptr(direction));
			glUniform3fv(glGetUniformLocation(program, "spotLight.ambient"), 1, glm::value_ptr(ambient));
			glUniform3fv(glGetUniformLocation(program, "spotLight.diffuse"), 1, glm::value_ptr(diffuse));
			glUniform3fv(glGetUniformLocation(program, "spotLight.specular"), 1, glm::value_ptr(specular));
		

			glUniform1f(glGetUniformLocation(program, "spotLight.constant"), constant);
			glUniform1f(glGetUniformLocation(program, "spotLight.linear"), linear);
			glUniform1f(glGetUniformLocation(program, "spotLight.quadratic"), quadratic);
			glUniform1f(glGetUniformLocation(program, "spotLight.cutOff"), glm::cos(glm::radians(cutOff)));
			glUniform1f(glGetUniformLocation(program, "spotLight.outerCutOff"), glm::cos(glm::radians(cutOff)));
		}

};

class Camera;

struct RenderStruct
{
	RenderStruct(GLuint& program, Camera& camera, DirLight& dirLight, PointLight& pointLight, SpotLight& spotLight)
		: program(program), camera(camera), dirLight(dirLight), pointLight(pointLight), spotLight(spotLight)
	{	};

	GLuint program;
	Camera& camera;
	DirLight& dirLight;
	PointLight& pointLight;
	SpotLight& spotLight;
};