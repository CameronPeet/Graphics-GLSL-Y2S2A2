#include "MainScene.h"

MainScene::MainScene()
{

}


MainScene::~MainScene()
{

}


bool MainScene::Init()
{
	//Camera creation
	m_MainCamera.SetPosition(glm::vec3(0.0f, 2.0f, 10.0f));
	m_MainCamera.SetViewPort(0, 0, Utils::WIDTH, Utils::HEIGHT);
	m_MainCamera.SetProjection(45.0f, (float)(Utils::WIDTH / Utils::HEIGHT), 0.1f, 1000.0f);

	DefineUBO();

	//Each tile is labeled according to its mapped position on a box
	m_SkyBox = SkyBox(CUBE,
		"Assets/skybox/right.jpg", 
		"Assets/skybox/left.jpg",
		"Assets/skybox/top.jpg",
		"Assets/skybox/bottom.jpg",
		"Assets/skybox/back.jpg",
		"Assets/skybox/front.jpg");
	m_SkyBox.Initialise();

	m_skyboxShader = m_shaderLoader.CreateProgram(
		"Assets/shaders/Skybox.vs",
		"Assets/shaders/Skybox.frag");

	GLuint tessProgram = m_shaderLoader.CreateProgram(
		"Assets/shaders/tess.vert",
		"Assets/shaders/tess.frag",
		"Assets/shaders/tessTriModel.tcs",
		"Assets/shaders/tessTriModel.tes");

	m_TessModel = new TessModel(tessProgram, &m_MainCamera);
	m_TessModel->m_Position = (glm::vec3(6.0f, -2.0f, 0.0f));
	
	GLuint computeProgram = m_shaderLoader.CreateComputeShaderProgram(
		"Assets/shaders/compParticle.comp");

	GLuint particleProgram = m_shaderLoader.CreateProgram(
		"Assets/shaders/compParticle.vert",
		"Assets/shaders/compParticle.frag");

	m_ParticleEffect = new ParticleEffect(computeProgram, particleProgram, &m_MainCamera, 1024);
	m_ParticleEffect->Init();
	
	return true;
}

void MainScene::Update(float fDeltaTime)
{
	m_MainCamera.Translate(m_Movement * 10.0f * fDeltaTime);
	m_ParticleEffect->Update(fDeltaTime);
	Sleep(10);
	glutPostRedisplay();
}

void MainScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	BindUBO();

	m_SkyBox.Render(m_skyboxShader, m_MainCamera);

	m_TessModel->Render();
	//m_ParticleEffect->Render();

	glBindVertexArray(0);
	glutSwapBuffers();
}

void MainScene::PassiveMotion(int x, int y)
{
	static bool sJustWarped = false;
	static float lastX = 600.0f;
	static float lastY = 400.0f;
	static float yaw = 90.0f;
	static float pitch = 0.0f;
	static bool firstMouse = true;

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



	m_MainCamera.SetRotation(glm::quat());
	m_MainCamera.Rotate(glm::angleAxis(-yaw, glm::vec3(0, 1, 0)));
	m_MainCamera.Rotate(glm::angleAxis(pitch, glm::vec3(1, 0, 0)));

	glm::vec3 euler = m_MainCamera.GetEulerAngles();



	glutWarpPointer(Utils::WIDTH / 2, Utils::HEIGHT / 2);
	glutSetCursor(GLUT_CURSOR_NONE);
	lastX = Utils::WIDTH / 2;
	lastY = Utils::HEIGHT / 2;

	sJustWarped = true;
}

void MainScene::Mouse(int button, int state, int x, int y)
{

}

void MainScene::Motion(int x, int y)
{

}

bool WIREFRAMEMODE = false;
void MainScene::KeyboardDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		m_Movement.z = -1.0f;
		break;
	case 'a':
	case 'A':
		m_Movement.x = -1.0f;
		break;
	case 's':
	case 'S':
		m_Movement.z = 1.0f;
		break;
	case 'd':
	case 'D':
		m_Movement.x = 1.0f;
		break;
	case 'q':
	case 'Q':
		m_Movement.y = -1.0f;
		break;
	case 'e':
	case 'E':
		m_Movement.y = 1.0f;
		break;

	case VK_SPACE:
		if (WIREFRAMEMODE)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			WIREFRAMEMODE = false;
		}
		break;

	case VK_ESCAPE:
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
}

void MainScene::KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		m_Movement.z = 0.f;
		break;
	case 'a':
	case 'A':
		m_Movement.x = 0.f;
		break;
	case 's':
	case 'S':
		m_Movement.z = 0.f;
		break;
	case 'd':
	case 'D':
		m_Movement.x = 0.f;
		break;
	case 'q':
	case 'Q':
		m_Movement.y = 0.f;
		break;
	case 'e':
	case 'E':
		m_Movement.y = 0.f;
		break;

	case VK_SPACE:
		if (!WIREFRAMEMODE)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			WIREFRAMEMODE = true;
		}
		break;

	
	default:
		break;
	}
}

void MainScene::Reshape(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}

	m_MainCamera.SetViewPort(0, 0, width, height);
	m_MainCamera.SetProjection(60.0f, (float)(width / height), 0.1f, 1000.0f);
}

void MainScene::DefineUBO()
{
	int size = sizeof(uboMatriceShaders) / sizeof(uboMatriceShaders[0]);
	for (int i = 0; i < size; i++)
	{
		GLuint uniformBlockIndex = glGetUniformBlockIndex(*uboMatriceShaders[i], "Matrices");
		glUniformBlockBinding(*uboMatriceShaders[i], uniformBlockIndex, 0);
	}

	glGenBuffers(1, &m_uboMatrices);

	glBindBuffer(GL_UNIFORM_BUFFER, m_uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_uboMatrices, 0, 2 * sizeof(glm::mat4));
}


void MainScene::BindUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(m_MainCamera.GetProjectionMatrix()));
	glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(m_MainCamera.GetViewMatrix()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}