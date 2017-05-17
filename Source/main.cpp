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
#include <soil\SOIL.h>


//GL Math Includes
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//Local Includes
#include "Utility\ShaderLoader.h"
#include "Graphics\Camera.h"
#include "Graphics\SkyBox.h"
#include "Graphics\Light.h"
#include "Graphics\ObjModel.h"
#include "Graphics\Terrain.h"
#include "Graphics\GeometryModel.h"

//Local Functions
bool Init();
void Render();
void Update();
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void Reshape(int width, int height);
void PassiveMotion(int x, int y);
void DefineUniformBufferObjects();
void BindUBO();
bool g_WindowRunning = false;

//Global Timer for calculating deltaTime
std::clock_t g_PreviousTicks;
std::clock_t g_CurrentTicks;


//Uniform buffer objects for uniform mat4's across all shaders (Camera Projectiona nd View matrix)
GLuint g_uboMatrices;

//Global Shader Programs
ShaderLoader shaderLoader;
GLuint standardShader;
GLuint skyboxShader;
GLuint objModelShader;
GLuint terrainShader;

//Global geometry shaders
GLuint geometry_explode_shader;
GLuint geometry_show_normals;
GLuint geometry_model_star;

GLuint* AllShaders[] =
{ 
	&standardShader, 
	&skyboxShader, 
	&objModelShader, 
	&terrainShader, 
	&geometry_explode_shader,
	&geometry_show_normals,
	&geometry_model_star

};


//Global Rendering Components and CObjects
Camera g_Camera;
SkyBox g_SkyBox;
Light g_GlobalLight;
ObjModel g_Castle3D;
ObjModel g_NanoSuit;
Terrain g_Terrain3D;
GeometryModel g_ModelGS;

glm::vec3 g_Movement;
glm::vec2 g_MousePos;

float lastX = 600.0f, lastY = 400.0f;
float yaw = 90.0f, pitch = 0.0f;
bool firstMouse = true;

//What are your start up options
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(GLUT_WINDOW_WIDTH / 2, GLUT_WINDOW_HEIGHT / 2);
	glutInitWindowSize(1200, 800);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);
	glutCreateWindow("Adcanced Graphics - Week 9 - Height Maps");


	glClearColor(1.0f, 1.0f, 0.0f, 0.5f);               // Set background color to black and opaque
	glClearDepth(1.0f);                                 // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);                            // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);                             // Set the type of depth-test
	glShadeModel(GL_SMOOTH);                            // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	glutSetCursor(GLUT_CURSOR_NONE);

	glewExperimental = GL_TRUE;

	glewInit();
	Init();

	glutDisplayFunc(Render);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutIdleFunc(Update);
	glutReshapeFunc(Reshape);
	glutPassiveMotionFunc(PassiveMotion);


	glutMainLoop();

	return EXIT_SUCCESS;
}

bool Init()
{
	//Load and create shader files
	standardShader	= shaderLoader.CreateProgram(
		"Assets/shaders/Shader.vert", 
		"Assets/shaders/Shader.frag");

	skyboxShader	= shaderLoader.CreateProgram(
		"Assets/shaders/Skybox.vs", 
		"Assets/shaders/Skybox.frag");

	objModelShader	= shaderLoader.CreateProgram(
		"Assets/shaders/3D_Model.vert",
		"Assets/shaders/3D_Model.frag");

	terrainShader = shaderLoader.CreateProgram(
		"Assets/shaders/heightmap.vs",
		"Assets/shaders/heightmap.fs");

	geometry_explode_shader = shaderLoader.CreateProgram(
		"Assets/shaders/geometry_explode.vs",
		"Assets/shaders/geometry_explode.frag",
		"Assets/shaders/geometry_explode.gs");

	geometry_show_normals = shaderLoader.CreateProgram(
		"Assets/shaders/geometry_show_normals.vs",
		"Assets/shaders/geometry_show_normals.frag",
		"Assets/shaders/geometry_show_normals.gs");

	geometry_model_star = shaderLoader.CreateProgram(
		"Assets/shaders/geometry_model_star.vert",
		"Assets/shaders/geometry_model_star.frag",
		"Assets/shaders/geometry_model_star.gs");

	//Camera creation
	g_Camera.SetPosition(glm::vec3(0.0f, 2.0f, 10.0f));
	g_Camera.SetViewPort(0, 0, 1200.0f, 800.0f);
	g_Camera.SetProjection(45.0f, (float)(1200.0f / 800.0f), 0.1f, 1000.0f);

	g_GlobalLight.Position.y += 10.0f;

	//Skybox creation
	g_SkyBox = SkyBox(CUBE, 
		"Assets/skybox/right.jpg",  //Each tile is labeled according to its mapped position on a box
		"Assets/skybox/left.jpg", 
		"Assets/skybox/top.jpg", 
		"Assets/skybox/bottom.jpg",
		"Assets/skybox/back.jpg", 
		"Assets/skybox/front.jpg");
	g_SkyBox.Initialise();

	//3D Model Loading
	g_Castle3D = ObjModel("Assets/Models/castle/Castle Obj.obj", &g_Camera, objModelShader);
	g_Castle3D.m_Position = glm::vec3(0.0f, 25.0f, -100.0f);
	g_NanoSuit = ObjModel("Assets/Models/Nanosuit/nanosuit.obj", &g_Camera, geometry_show_normals);
	g_NanoSuit.m_Position = glm::vec3(0.0f, 10, -20.0f);

	//3D Terrain Generating from a HeighMap
	g_Terrain3D = Terrain(L"assets/heightmap/terrain.raw",
		"assets/heightmap/sand.jpg",
		"assets/heightmap/stones.jpg",
		"assets/heightmap/rock.png",
		terrainShader,
		&g_Camera,
		&g_GlobalLight);
	g_Terrain3D.m_Position = glm::vec3(0.0f, -10.0f, 0.0f);
	g_Terrain3D.ObjectColor = glm::vec3(0.5f, 0.5f, 0.5f);

	g_ModelGS = GeometryModel(geometry_model_star, &g_Camera);
	g_ModelGS.m_Position = g_Camera.GetPosition() + glm::vec3(0, 0, -2.0f);

	DefineUniformBufferObjects();
	BindUBO();
	return true;
}



void Render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	//Update the uniform buffer objects in the shaders with the latest proj and view matrix
	BindUBO();

	//Render Skybox
	g_SkyBox.Render(skyboxShader, g_Camera);

	////Render 3D Models
	g_Castle3D.Render();

	g_NanoSuit.program = objModelShader;
	g_NanoSuit.Render();

	g_NanoSuit.program = geometry_show_normals;
	g_NanoSuit.Render();

	glm::vec3 pos = g_NanoSuit.m_Position;
	g_NanoSuit.m_Position += glm::vec3(10.0f, 0.0f, 0.0);
	g_NanoSuit.program = geometry_explode_shader;
	g_NanoSuit.Render();
	g_NanoSuit.m_Position = pos;

	////Render Terrain
	g_Terrain3D.Render();

	g_ModelGS.Render();

	//Render Shape Models

	//Render Reflections

	glBindVertexArray(0);
	glutSwapBuffers();
}
void Update()
{

	g_CurrentTicks = std::clock();
	float deltaTicks = (float)(g_CurrentTicks - g_PreviousTicks);
	g_PreviousTicks = g_CurrentTicks;
	float fDeltaTime = deltaTicks / (float)CLOCKS_PER_SEC;


	GLfloat currentTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME); //get current time
	currentTime = currentTime / 1000; // convert millisecond to seconds 

	glUseProgram(geometry_explode_shader);

	GLint currentTimeLocation = glGetUniformLocation(geometry_explode_shader, "time"); // get uniform lcoation from program 
	glUniform1f(currentTimeLocation, static_cast<float>(currentTime)); // set value

	glUseProgram(0);


	g_Camera.Translate(g_Movement * 10.0f * fDeltaTime);


	g_WindowRunning = true;
	Sleep(10);
	glutPostRedisplay();
}
void KeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		g_Movement.z = -1.0f;
		break;
	case 'a':
	case 'A':
		g_Movement.x = -1.0f;
		break;
	case 's':
	case 'S':
		g_Movement.z = 1.0f;
		break;
	case 'd':
	case 'D':
		g_Movement.x = 1.0f;
		break;
	case 'q':
	case 'Q':
		g_Movement.y = -1.0f;
		break;
	case 'e':
	case 'E':
		g_Movement.y = 1.0f;
		break;

	case VK_ESCAPE:
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
}
void KeyUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		g_Movement.z = 0.f;
		break;
	case 'a':
	case 'A':
		g_Movement.x = 0.f;
		break;
	case 's':
	case 'S':
		g_Movement.z = 0.f;
		break;
	case 'd':
	case 'D':
		g_Movement.x = 0.f;
		break;
	case 'q':
	case 'Q':
		g_Movement.y = 0.f;
		break;
	case 'e':
	case 'E':
		g_Movement.y = 0.f;
		break;
	default:
		break;
	}
}

void Reshape(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}

	g_Camera.SetViewPort(0, 0, width, height);
	g_Camera.SetProjection(45.0f, (float)(width / height), 0.1f, 1000.0f);
}


void ResetPointer()
{
	glutWarpPointer(600, 400);
	glutSetCursor(GLUT_CURSOR_NONE);
	lastX = 600.0f;
	lastY = 400.0f;
}

void PassiveMotion(int x, int y)
{
	static bool sJustWarped = false;

	if (sJustWarped) {
		sJustWarped = false;
		return;
	}

	GLfloat xoffset = x - lastX;
	GLfloat yoffset = lastY - y;

	lastX = static_cast<float>(x);
	lastY = static_cast<float>(y);

	GLfloat sensitivity = 0.005f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;



	g_Camera.SetRotation(glm::quat());
	g_Camera.Rotate(glm::angleAxis(-yaw, glm::vec3(0, 1, 0)));
	g_Camera.Rotate(glm::angleAxis(pitch, glm::vec3(1, 0, 0)));


	ResetPointer();
	sJustWarped = true;
}



void DefineUniformBufferObjects()
{

	int size = sizeof(AllShaders) / sizeof(AllShaders[0]);
	for (int i = 0; i < size; i++)
	{
		GLuint uniformBlockIndex = glGetUniformBlockIndex(*AllShaders[i], "Matrices");
		glUniformBlockBinding(*AllShaders[i], uniformBlockIndex, 0);
	}

	glGenBuffers(1, &g_uboMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, g_uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, g_uboMatrices, 0, 2 * sizeof(glm::mat4));
}

void BindUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, g_uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(g_Camera.GetProjectionMatrix()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, g_uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(g_Camera.GetViewMatrix()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}