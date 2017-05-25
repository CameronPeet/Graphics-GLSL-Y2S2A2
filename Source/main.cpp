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
GLuint g_uboLights;
//Global Shader Programs
ShaderLoader shaderLoader;
GLuint standardShader;
GLuint skyboxShader;
GLuint objModelShader;
GLuint terrainShader;
GLuint multiple_light_shader;

//Global geometry shaders
GLuint geometry_explode_shader;
GLuint geometry_show_normals;
GLuint geometry_model_star;
GLuint geometry_shader_star_world;

//Multiple Lights in UBO for 3D Model with Multiple Lights shader
GLuint objModelWithLights;

//Adding shader to alist that is generating the uniform buffer objects for these shaders
GLuint* AllShaders[] =
{ 
	&standardShader, 
	&skyboxShader, 
	&objModelShader, 
	&terrainShader, 
	&geometry_explode_shader,
	&geometry_show_normals,
	&geometry_model_star,
	&geometry_shader_star_world,
	&multiple_light_shader
};


//Global Rendering Components and CObjects
Camera g_Camera;
SkyBox g_SkyBox;


Light g_GlobalLight;
Model g_lightModel;
ObjModel g_Castle3D;
ObjModel g_NanoSuit;
Terrain g_Terrain3D;
GeometryModel g_ModelGS;


//NEW STUFF
DirLight g_DirLight;
PointLight g_PointLight;
SpotLight g_SpotLight;
Model modelType2;

void InitLights(DirLight& dirLight, PointLight& pointLight, SpotLight& spotLight);

//Movement variables
glm::vec3 g_Movement;
glm::vec2 g_MousePos;

float lastX = 600.0f, lastY = 400.0f;
float yaw = 90.0f, pitch = 0.0f;
bool firstMouse = true;


bool MovingCamera = true;
bool MovingLight = false;
bool SpaceDown = false;
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

	objModelWithLights = shaderLoader.CreateProgram(
			"Assets/shaders/3D_Model_WithLighting.vert",
			"Assets/shaders/3D_Model_WithLighting.frag");
	//Load and create shader files
	multiple_light_shader = shaderLoader.CreateProgram(
		"Assets/shaders/MultipleLights.vert",
		"Assets/shaders/MultipleLights.frag");

	standardShader	= shaderLoader.CreateProgram(
		"Assets/shaders/Shader.vert", 
		"Assets/shaders/Shader.frag");

	skyboxShader	= shaderLoader.CreateProgram(
		"Assets/shaders/Skybox.vs", 
		"Assets/shaders/Skybox.frag");

	objModelShader	= shaderLoader.CreateProgram(
		"Assets/shaders/3D_Model_WithLighting.vert",
		"Assets/shaders/3D_Model_WithLighting.frag");

	terrainShader = shaderLoader.CreateProgram(
		"Assets/shaders/heightmap_mult.vert",
		"Assets/shaders/heightmap_mult.frag");

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

	geometry_shader_star_world = shaderLoader.CreateProgram(
		"Assets/shaders/geometry_shader_star_world.vert",
		"Assets/shaders/geometry_model_star.frag",
		"Assets/shaders/geometry_model_star.gs");

	//Camera creation
	g_Camera.SetPosition(glm::vec3(0.0f, 2.0f, 10.0f));
	g_Camera.SetViewPort(0, 0, 1200.0f, 800.0f);
	g_Camera.SetProjection(45.0f, (float)(1200.0f / 800.0f), 0.1f, 1000.0f);


	InitLights(g_DirLight, g_PointLight, g_SpotLight);

	modelType2 = Model(CUBE, "Assets/Textures/container2.jpg", "Assets/Textures/container2.png", 32.0f);
	modelType2.Initialise2();

	g_GlobalLight.Position.y += 10.0f;
	g_lightModel = Model(SPHERE, "Assets/textures/Ball.jpg");
	g_lightModel.Initialise();
	g_lightModel.m_Scale = glm::vec3(0.4f, 0.4f, 0.4f);

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

	g_SpotLight.direction = glm::normalize(g_Camera.GetRayTo(600, 400));
	g_SpotLight.position = g_Camera.GetPosition();

	//Render Skybox
	g_SkyBox.Render(skyboxShader, g_Camera);

	RenderStruct renderStruct = RenderStruct(multiple_light_shader, g_Camera, g_DirLight, g_PointLight, g_SpotLight);

	renderStruct.program = multiple_light_shader;
	modelType2.Render(renderStruct);

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
	renderStruct.program = terrainShader;
	g_Terrain3D.Render(renderStruct);

	//Rendering onto NDC screen space
	g_ModelGS.program = geometry_model_star;
	g_ModelGS.Render();

	//Rendering into 3D Space
	g_ModelGS.program = geometry_shader_star_world;
	g_ModelGS.Render();

	//Render Shape Models

	//Render Reflections

	glBindVertexArray(0);
	glutSwapBuffers();
}
void Update()
{
	MovingCamera = MovingLight ? false : true;

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

	if (MovingCamera)
		g_Camera.Translate(g_Movement * 10.0f * fDeltaTime);
	else if (MovingLight)
		g_PointLight.position += (g_Movement * 10.0f * fDeltaTime);

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
	case VK_SPACE:
		
		MovingLight = SpaceDown ? false : MovingLight ? false : true;

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

	float maxPitch = glm::radians(89.0f);
	if (pitch > maxPitch)
		pitch = maxPitch;
	if (pitch < -maxPitch)
		pitch = -maxPitch;



	g_Camera.SetRotation(glm::quat());
	g_Camera.Rotate(glm::angleAxis(-yaw, glm::vec3(0, 1, 0)));
	g_Camera.Rotate(glm::angleAxis(pitch, glm::vec3(1, 0, 0)));

	glm::vec3 euler = g_Camera.GetEulerAngles();



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



	GLuint uniformBlockIndex = glGetUniformBlockIndex(objModelWithLights, "Lights");
	glUniformBlockBinding(objModelWithLights, uniformBlockIndex, 1);

	glGenBuffers(1, &g_uboLights);

	glBindBuffer(GL_UNIFORM_BUFFER, g_uboLights);
	glBufferData(GL_UNIFORM_BUFFER, (15 * sizeof(glm::vec4)), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 2, g_uboLights, 0, 15 * sizeof(glm::vec4));
}

void BindUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, g_uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(g_Camera.GetProjectionMatrix()));
	glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(g_Camera.GetViewMatrix()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, g_uboLights);
						//					OFFSET									//SIZE OF DATA		// DATA
	glBufferSubData(GL_UNIFORM_BUFFER, 0 * sizeof(glm::vec4)					 , sizeof(glm::vec4) , glm::value_ptr(g_DirLight.direction));
	glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::vec4)					 , sizeof(glm::vec4) , glm::value_ptr(g_DirLight.ambient));
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4)					 , sizeof(glm::vec4) , glm::value_ptr(g_DirLight.diffuse));
	glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4)					 , sizeof(glm::vec4) , glm::value_ptr(g_DirLight.specular));
	glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(glm::vec4)					 , sizeof(glm::vec4) , glm::value_ptr(g_PointLight.position));
	glBufferSubData(GL_UNIFORM_BUFFER, 5 * sizeof(glm::vec4)					 , sizeof(glm::vec4) , glm::value_ptr(g_PointLight.ambient));
	glBufferSubData(GL_UNIFORM_BUFFER, 6 * sizeof(glm::vec4)					 , sizeof(glm::vec4) , glm::value_ptr(g_PointLight.diffuse));
	glBufferSubData(GL_UNIFORM_BUFFER, 7 * sizeof(glm::vec4)					 , sizeof(glm::vec4) , glm::value_ptr(g_PointLight.specular));
	glBufferSubData(GL_UNIFORM_BUFFER, 8 * sizeof(glm::vec4)					 , sizeof(float)	 , &g_PointLight.constant);
	glBufferSubData(GL_UNIFORM_BUFFER, 8 * sizeof(glm::vec4) + sizeof(float)	 , sizeof(float)	 , &g_PointLight.linear);
	glBufferSubData(GL_UNIFORM_BUFFER, 8 * sizeof(glm::vec4) + (sizeof(float) * 2) , sizeof(float)	 , &g_PointLight.quadratic);
	glBufferSubData(GL_UNIFORM_BUFFER, 9 * sizeof(glm::vec4) - sizeof(float)     , sizeof(glm::vec4) , glm::value_ptr(g_SpotLight.position));
	glBufferSubData(GL_UNIFORM_BUFFER, 10 * sizeof(glm::vec4) - sizeof(float)    , sizeof(glm::vec4) , glm::value_ptr(g_SpotLight.direction));
	glBufferSubData(GL_UNIFORM_BUFFER, 11 * sizeof(glm::vec4) - sizeof(float)	 , sizeof(glm::vec4) , glm::value_ptr(g_SpotLight.ambient));
	glBufferSubData(GL_UNIFORM_BUFFER, 12 * sizeof(glm::vec4) - sizeof(float)	 , sizeof(glm::vec4) , glm::value_ptr(g_SpotLight.diffuse));
	glBufferSubData(GL_UNIFORM_BUFFER, 13 * sizeof(glm::vec4) - sizeof(float)	 , sizeof(glm::vec4) , glm::value_ptr(g_SpotLight.specular));
	glBufferSubData(GL_UNIFORM_BUFFER, 13 * sizeof(glm::vec4)					 , sizeof(float)	 , &g_SpotLight.constant);
	glBufferSubData(GL_UNIFORM_BUFFER, 13 * sizeof(glm::vec4) + sizeof(float)	 , sizeof(float)	 , &g_SpotLight.linear);
	glBufferSubData(GL_UNIFORM_BUFFER, 13 * sizeof(glm::vec4) + sizeof(float) * 2, sizeof(float)	 , &g_SpotLight.quadratic);
	glBufferSubData(GL_UNIFORM_BUFFER, 13 * sizeof(glm::vec4) + sizeof(float) * 3, sizeof(float)	 , &g_SpotLight.cutOff);
	glBufferSubData(GL_UNIFORM_BUFFER, 13 * sizeof(glm::vec4) + sizeof(float) * 4, sizeof(float)	 , &g_SpotLight.outerCutOff);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void InitLights(DirLight& dirLight, PointLight& pointLight, SpotLight& spotLight)
{
	dirLight = DirLight(
		glm::vec3(-0.2f, -1.0f, -0.3f),
		glm::vec3(0.2f),
		glm::vec3(0.4f),
		glm::vec3(0.5f));

	pointLight = PointLight(
		glm::vec3(0),
		glm::vec3(0),
		glm::vec3(0.2f),
		glm::vec3(0.8f),
		glm::vec3(1.0f),
		1.0f,
		0.09f,
		0.032f
	);

	spotLight = SpotLight(
		glm::vec3(0),
		glm::vec3(0),
		glm::vec3(0.2f),
		glm::vec3(1),
		glm::vec3(1),
		1.f,
		0.09f,
		0.032f,
		12.5f,
		15.f
	);
}