// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2016 Media Design School
//
// File Name   : main.cpp
// Description : Main implementation file 
// Author	   : Cameron Peet
// Mail		   : Cameron.Pee6737@mediadesignschool.com

//Includes
#include <ctime>
#include <iostream>

//Library Includes
#include <glew\glew.h>
#include <freeglut\freeglut.h>
//#include <soil\SOIL.h>

//
////GL Math Includes
//#include <glm\glm.hpp>
//#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>

////Local Includes
//#include "Utility\ShaderLoader.h"
//#include "Graphics\Camera.h"
//#include "Graphics\SkyBox.h"
//#include "Graphics\Light.h"
//#include "Graphics\ObjModel.h"
//#include "Graphics\Terrain.h"
//#include "Graphics\GeometryModel.h"

//Include Utility Files
#include "Utility\utils.h"
#include "Utility\CLogger.h"
#include "Utility\SceneManager.h"
#include "Utility\GlobalClock.h"
#include "Scenes\MainScene.h"

//Local Functions
bool Init();
void Render();
void Update();
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void Reshape(int width, int height);
void PassiveMotion(int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);

const float g_kWidth = 1200.0f;
const float g_kHeight = 800.0f;

//What are your start up options
int main(int argc, char ** argv)
{
	Utils::WIDTH = 1200.0f;
	Utils::HEIGHT = 800.0f;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(Utils::WIDTH, Utils::HEIGHT);
	glutInitWindowPosition(GLUT_WINDOW_WIDTH / 2, GLUT_WINDOW_HEIGHT / 2);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);

	glutCreateWindow("Advanced Graphics - Scenes");

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);               // Set background color to black and opaque
	glClearDepth(1.0f);                                 // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);                            // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);                             // Set the type of depth-test
	glShadeModel(GL_SMOOTH);                            // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	//glutSetCursor(GLUT_CURSOR_NONE);

	glewExperimental = GL_TRUE;

	glewInit();
	Init();

	glutDisplayFunc(Render);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutIdleFunc(Update);
	glutReshapeFunc(Reshape);
	glutPassiveMotionFunc(PassiveMotion);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	glutMainLoop();

	return EXIT_SUCCESS;
}

bool Init()
{
	CLogManager& _rMainLogger = CLogManager::GetInstance();
	_rMainLogger.WriteToAll("OpenGL Init() Called");

	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	VALIDATE(_rSceneManager.Initialise());

	_rSceneManager.AddScene(new MainScene(), "MainScene", true);

	_rMainLogger.WriteToAll("OpenGL Init() Completed");
	return true;
}

void Render()
{
	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->Render();
}
void Update()
{
	Time.Update();

	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->Update(Time.deltaTime);

}
void KeyDown(unsigned char key, int x, int y)
{
	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->KeyboardDown(key, x, y);
}
void KeyUp(unsigned char key, int x, int y)
{
	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->KeyboardUp(key, x, y);
}

void Reshape(int width, int height)
{
	Utils::WIDTH = width;
	Utils::HEIGHT = height;

	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->Reshape(width, height);
}


void PassiveMotion(int x, int y)
{
	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->PassiveMotion(x, y);
}

void Mouse(int button, int state, int x, int y)
{
	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->Mouse(button, state, x, y);
}

void Motion(int x, int y)
{
	CSceneManager& _rSceneManager = CSceneManager::GetInstance();
	_rSceneManager.GetScene()->Motion(x, y);
}

