#pragma once
#ifndef MAINSCENE_H


//Parent
#include "Scene.h"

#include "Camera.h"
#include "Model.h"
#include "SkyBox.h"
#include "..\Utility\utils.h"
#include "ShaderLoader.h"
#include "TessModel.h"
#include "ParticleEffect.h"

class MainScene : public CScene
{

public:
	MainScene();
	~MainScene();

	bool Init();
	void Update(float fDeltaTime);
	void Render();
	void PassiveMotion(int x, int y);
	void Mouse(int button, int state, int x, int y);
	void Motion(int x, int y);
	void KeyboardDown(unsigned char c, int x, int y);
	void KeyboardUp(unsigned char c, int x, int y);
	void Reshape(int width, int height);

	void BindUBO();
	void DefineUBO();

protected:

	Camera m_MainCamera;
	glm::vec3 m_Movement;
	
	SkyBox m_SkyBox;

	//Shader Variables
	ShaderLoader m_shaderLoader;

	//Shaders that contain the Camera UBO Matrix block
	GLuint m_uboMatrices;
	GLuint m_skyboxShader;

	GLuint* uboMatriceShaders[1]
	{
		&m_skyboxShader
	};

	//Tess Model
	TessModel* m_TessModel;
	ParticleEffect* m_ParticleEffect;
};

#endif // !MAINSCENE_H
