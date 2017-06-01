// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Utils.cpp
// Description	: Seperates the initialisation from the bulk code required to set the vertices and indices for each model type.
// Author		: Cameron Peet
// Mail			: Cameron.Peet@mediadesign.school.nz
#include "Utils.h"
#include "Model.h"

float Utils::WIDTH = 1200.0f;
float Utils::HEIGHT = 800.0f;
/*
Author : Cameron Peet
File Description : 

Each function creates a local definition of the shape described in the function name.
1) Define the vertex format
2) Store by copy each vertex format in the models vertex format vector
3) Set directly the indices array. 

*/
void Utils::SetQuad(Model& _rModel)
{
	VertexFormat v1(-1, 0, 1, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	VertexFormat v2(-1, 0, -1, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	VertexFormat v3(1, 0, 1, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	VertexFormat v4(1, 0, -1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	_rModel.vertices.push_back(v1);
	_rModel.vertices.push_back(v2);
	_rModel.vertices.push_back(v3);
	_rModel.vertices.push_back(v4);
	
	//Set Indices directly
	_rModel.indices = { 0, 1, 2, 1, 3, 2 };


	//Struct method. Clunky code.
	//_rModel.indices.push_back(IndexFormat(0, 1, 3));
	//_rModel.indices.push_back(IndexFormat(1, 2, 3));
}


/*Author : Cameron Peet  
Purpose	:  Define the 3 points required to make a unit triangle */
void Utils::SetTriangle(Model& _rModel)
{
	// Pos1, 2, 3, Tex1, 2, Color1, 2, 3
	VertexFormat v1(0.0f, 0.5f, 0.0f,	 0.0f, 0.0f,	0.0f, 0.0f, 1.0f);  
	VertexFormat v2(0.5f, 0.0f, 0.0f,	 1.0f, 1.0f,	0.0f, 0.0f, 1.0f); 
	VertexFormat v3(-0.5f, 0.0f, 0.0f,	 0.0f, 1.0F,	0.0f, 0.0f, 1.0f);

	_rModel.vertices.push_back(v1);
	_rModel.vertices.push_back(v2);
	_rModel.vertices.push_back(v3);

	//Setting indices
	_rModel.indices = { 0, 1, 2 };

	//_rModel.indices.push_back(IndexFormat(0, 1, 2));
}
void Utils::SetPyramid(Model& _rModel)
{

	VertexFormat v1(0.0f, 0.5f, 0.0f,	0, 1, 1, 0.0f, 0.0f);
	VertexFormat v2(-0.5f, -0.5f, 0.5f, 0, 0, 0.0f, 1, 0.0f);
	VertexFormat v3(0.5f, -0.5f, 0.5f,  1, 0, 0.0f, 0.0f, 1);
	//Bottom
	VertexFormat v4(0.0f, 0.5f, 0.0f, 0, 1, 1, 0.0f, 0.0f);
	VertexFormat v5(-0.5f, -0.5f, 0.5f, 0, 0, 0.0f, 1, 0.0f);
	VertexFormat v6(0.0f, -0.5f, -0.5f, 1, 0, 0.0f, 0.0f, 1);
	//right
	VertexFormat v7(0.0f, 0.5f, 0.0f, 0, 1,		1, 0.0f, 0.0f);
	VertexFormat v8(0.0f, -0.5f, -0.5, 0, 0,	0.0f, 1, 0.0f);
	VertexFormat v9(0.5f, -0.5f, 0.5f, 1, 0,	0.0f, 0.0f, 1);
	//left
	VertexFormat v10(-0.5f, -0.5f, 0.5f, 0, 1, 1, 0.0f, 0.0f);
	VertexFormat v11(0.0f, -0.5f, -0.5f, 0, 0 ,0.0f, 1, 0.0f);
	VertexFormat v12(0.5f, -0.5f, 0.5f,  1, 0, 0.0f, 0.0f, 0.0);

	//top
	_rModel.vertices.push_back(v1);
	_rModel.vertices.push_back(v2);
	_rModel.vertices.push_back(v3);
	//bottom
	_rModel.vertices.push_back(v4);
	_rModel.vertices.push_back(v5);
	_rModel.vertices.push_back(v6);
	//right
	_rModel.vertices.push_back(v7);
	_rModel.vertices.push_back(v8);
	_rModel.vertices.push_back(v9);
	//left
	_rModel.vertices.push_back(v10);
	_rModel.vertices.push_back(v11);
	_rModel.vertices.push_back(v12);


	//Setting indices
	_rModel.indices = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11
	};

	//_rModel.indices.push_back(IndexFormat(0, 1, 2));
	//_rModel.indices.push_back(IndexFormat(3, 4, 5));
	//_rModel.indices.push_back(IndexFormat(6, 7, 8));
	//_rModel.indices.push_back(IndexFormat(9, 10, 11));
}



void Utils::SetCube(Model& _rModel)
{

	VertexFormat frontA(-1, 1, 1,	0.0f, 1.0f,		0.0f, 0.0f, 1.0f);  //Top Left
	VertexFormat frontB(1, 1, 1,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f); // Top right
	VertexFormat frontC(-1, -1, 1,	0.0f, 0.0f,		0.0f, 0.0f, 1.0f); //Bottom Left
	VertexFormat frontD(1, -1, 1,	1.0f, 0.0f,		0.0f, 0.0f, 1.0f); //Bottom Right

	VertexFormat sideA(1, 1, 1,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f);
	VertexFormat sideB(1, 1, -1,	0.0f, 1.0f,		1.0f, 0.0f, 0.0f);
	VertexFormat sideC(1, -1, 1,	1.0f, 0.0f,		1.0f, 0.0f, 0.0f);
	VertexFormat sideD(1, -1, -1,	0.0f, 0.0f,		1.0f, 0.0f, 0.0f);

	VertexFormat topA(-1, 1, 1,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f);
	VertexFormat topB(-1, 1, -1,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f);
	VertexFormat topC(1, 1, 1,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f);
	VertexFormat topD(1, 1, -1,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f);

	VertexFormat backA(frontA);
	backA.VertexPosition._fZ = -1;
	backA.Normal._fZ = -1;
	VertexFormat backB(frontB);
	backB.VertexPosition._fZ = -1;
	backB.Normal._fZ = -1;
	VertexFormat backC(frontC);
	backC.VertexPosition._fZ = -1;
	backC.Normal._fZ = -1;
	VertexFormat backD(frontD);
	backD.Normal._fZ = -1;
	backD.VertexPosition._fZ = -1;

	VertexFormat oSideA(sideA);
	oSideA.VertexPosition._fX = -1;
	oSideA.Normal._fX = -1;
	VertexFormat oSideB(sideB);
	oSideB.VertexPosition._fX = -1;
	oSideB.Normal._fX = -1;
	VertexFormat oSideC(sideC);
	oSideC.VertexPosition._fX = -1;
	oSideC.Normal._fX = -1;
	VertexFormat oSideD(sideD);
	oSideD.VertexPosition._fX = -1;
	oSideD.Normal._fX = -1;

	VertexFormat botA(topA);
	botA.VertexPosition._fY = -1;
	botA.Normal._fY = -1;
	VertexFormat botB(topB);
	botB.VertexPosition._fY = -1;
	botB.Normal._fY = -1;
	VertexFormat botC(topC);
	botC.VertexPosition._fY = -1;
	botC.Normal._fY = -1;
	VertexFormat botD(topD);
	botD.VertexPosition._fY = -1;
	botD.Normal._fY = -1;


	_rModel.vertices.push_back(frontA);
	_rModel.vertices.push_back(frontB);
	_rModel.vertices.push_back(frontC);
	_rModel.vertices.push_back(frontD);

	_rModel.vertices.push_back(sideA);
	_rModel.vertices.push_back(sideB);
	_rModel.vertices.push_back(sideC);
	_rModel.vertices.push_back(sideD);

	_rModel.vertices.push_back(topA);
	_rModel.vertices.push_back(topB);
	_rModel.vertices.push_back(topC);
	_rModel.vertices.push_back(topD);

	_rModel.vertices.push_back(backA);
	_rModel.vertices.push_back(backB);
	_rModel.vertices.push_back(backC);
	_rModel.vertices.push_back(backD);

	_rModel.vertices.push_back(oSideA);
	_rModel.vertices.push_back(oSideB);
	_rModel.vertices.push_back(oSideC);
	_rModel.vertices.push_back(oSideD);

	_rModel.vertices.push_back(botA);
	_rModel.vertices.push_back(botB);
	_rModel.vertices.push_back(botC);
	_rModel.vertices.push_back(botD);

	_rModel.indices =
	{
		0, 1, 2,
		1, 3, 2,

		4, 5, 6,
		5, 7, 6,

		8, 9, 10,
		9, 11, 10,

		14, 13, 12,
		14, 15, 13,
		//12, 13, 14,
		//13, 15, 14,

		18, 17, 16,
		18, 19, 17,
		//16, 17, 18,
		//17, 19, 18,

		22, 21, 20,
		22, 23, 21,
		//20, 21, 22,
		//21, 23, 22

	};
}

void Utils::SetCircle(Model& _rCircle)
{
	VertexFormat Vertex(0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0); _rCircle.vertices.push_back(Vertex);//Centre point
	GLfloat _iX = 0.0, _iY = 0.5f;//Starting coordinates for circle
	GLfloat xNew = _iX, yNew = _iY;//New coordinates
	GLfloat radius = 1.0f;
	GLfloat angle = 3.14f / 360.0f;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);

	int counter = 0;
	for (int i = 0; i <= 360; i+= 20)
	{
		float degree = i * (3.14f / 180.0f);
		float x = cos(degree) * radius;
		float y = sin(degree) * radius;

		xNew = x * cosAngle - y * sinAngle;
		yNew = x * sinAngle + y * cosAngle;
		_iX = xNew;
		_iY = yNew;

		VertexFormat v1(x, y, 0, 0.5f + xNew, 0.5f - yNew, 1.0, 1.0, 1.0);
		_rCircle.vertices.push_back(v1);
		counter++;
	}

	for (int i = 0; i < counter; i++)//Setting indices
	{
		_rCircle.indices.push_back(0);
		_rCircle.indices.push_back(i + 1);
		_rCircle.indices.push_back(i + 2);
	}
	_rCircle.indices[(counter * 3) - 1] = 1;
}


void Utils::SetSphere(Model& _rModel)
{
	std::vector<VertexFormat> Vertices;
	std::vector<GLuint> Indices;

	double latitudeBands = 15;
	double longitudeBands = 15;
	float radius = 1.0f;

	for (double latNumber = 0; latNumber <= latitudeBands; latNumber++) {
		double theta = latNumber * 3.14159265359 / latitudeBands;
		double sinTheta = sin(theta);
		double cosTheta = cos(theta);
		
		for (double longNumber = 0; longNumber <= longitudeBands; longNumber++) {
			double phi = longNumber * 2 * 3.14159265359 / longitudeBands;
			double sinPhi = sin(phi);
			double cosPhi = cos(phi);

			VertexFormat vs;

			vs.TexturePosition._fX = static_cast<float>(1.0f - (longNumber / longitudeBands));
			vs.TexturePosition._fY = static_cast<float>(1.0f - (latNumber / latitudeBands));

			vs.Normal._fX = static_cast<float>(cosPhi * sinTheta);
			vs.Normal._fY = static_cast<float>(cosTheta);
			vs.Normal._fZ = static_cast<float>(sinPhi * sinTheta);

			vs.VertexPosition._fX = radius * vs.Normal._fX;
			vs.VertexPosition._fY = radius * vs.Normal._fY;
			vs.VertexPosition._fZ = radius * vs.Normal._fZ;

			Vertices.push_back(vs);
		}
	}

	for (GLuint latNumber = 0; latNumber < latitudeBands; latNumber++) {
		for (GLuint longNumber = 0; longNumber < longitudeBands; longNumber++) {
			GLuint first = static_cast<GLuint>((latNumber * (longitudeBands + 1)) + longNumber);
			GLuint second = static_cast<GLuint>(first + longitudeBands + 1);

			Indices.push_back(first);
			Indices.push_back(second);
			Indices.push_back(first + 1);

			Indices.push_back(second);
			Indices.push_back(second + 1);
			Indices.push_back(first + 1);

		}
	}



	_rModel.vertices = Vertices;
	_rModel.indices = Indices;
}

void Utils::SetQuad(std::vector<VertexFormat>& const _krVertices, std::vector<GLuint>& const _krIndices)
{
	VertexFormat v1(-1, 0, 1, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	VertexFormat v2(-1, 0, -1, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	VertexFormat v3(1, 0, 1, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	VertexFormat v4(1, 0, -1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	_krVertices.push_back(v1);
	_krVertices.push_back(v2);
	_krVertices.push_back(v3);
	_krVertices.push_back(v4);

	//Set Indices directly
	_krIndices = { 0, 1, 2, 1, 3, 2 };


	//Struct method. Clunky code.
	//_krIndices.push_back(IndexFormat(0, 1, 3));
	//_krIndices.push_back(IndexFormat(1, 2, 3));
}


/*Author : Cameron Peet
Purpose	:  Define the 3 points required to make a unit triangle */
void Utils::SetTriangle(std::vector<VertexFormat>& const _krVertices, std::vector<GLuint>& const _krIndices)
{
	// Pos1, 2, 3, Tex1, 2, Color1, 2, 3
	VertexFormat v1(0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	VertexFormat v2(0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	VertexFormat v3(-0.5f, 0.0f, 0.0f, 0.0f, 1.0F, 0.0f, 0.0f, 1.0f);

	_krVertices.push_back(v1);
	_krVertices.push_back(v2);
	_krVertices.push_back(v3);

	//Setting indices
	_krIndices = { 0, 1, 2 };

	//_krIndices.push_back(IndexFormat(0, 1, 2));
}
void Utils::SetPyramid(std::vector<VertexFormat>& const _krVertices, std::vector<GLuint>& const _krIndices)
{

	VertexFormat v1(0.0f, 0.5f, 0.0f, 0, 1, 1, 0.0f, 0.0f);
	VertexFormat v2(-0.5f, -0.5f, 0.5f, 0, 0, 0.0f, 1, 0.0f);
	VertexFormat v3(0.5f, -0.5f, 0.5f, 1, 0, 0.0f, 0.0f, 1);
	//Bottom
	VertexFormat v4(0.0f, 0.5f, 0.0f, 0, 1, 1, 0.0f, 0.0f);
	VertexFormat v5(-0.5f, -0.5f, 0.5f, 0, 0, 0.0f, 1, 0.0f);
	VertexFormat v6(0.0f, -0.5f, -0.5f, 1, 0, 0.0f, 0.0f, 1);
	//right
	VertexFormat v7(0.0f, 0.5f, 0.0f, 0, 1, 1, 0.0f, 0.0f);
	VertexFormat v8(0.0f, -0.5f, -0.5, 0, 0, 0.0f, 1, 0.0f);
	VertexFormat v9(0.5f, -0.5f, 0.5f, 1, 0, 0.0f, 0.0f, 1);
	//left
	VertexFormat v10(-0.5f, -0.5f, 0.5f, 0, 1, 1, 0.0f, 0.0f);
	VertexFormat v11(0.0f, -0.5f, -0.5f, 0, 0, 0.0f, 1, 0.0f);
	VertexFormat v12(0.5f, -0.5f, 0.5f, 1, 0, 0.0f, 0.0f, 0.0);

	//top
	_krVertices.push_back(v1);
	_krVertices.push_back(v2);
	_krVertices.push_back(v3);
	//bottom
	_krVertices.push_back(v4);
	_krVertices.push_back(v5);
	_krVertices.push_back(v6);
	//right
	_krVertices.push_back(v7);
	_krVertices.push_back(v8);
	_krVertices.push_back(v9);
	//left
	_krVertices.push_back(v10);
	_krVertices.push_back(v11);
	_krVertices.push_back(v12);


	//Setting indices
	_krIndices = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11
	};

	//_krIndices.push_back(IndexFormat(0, 1, 2));
	//_krIndices.push_back(IndexFormat(3, 4, 5));
	//_krIndices.push_back(IndexFormat(6, 7, 8));
	//_krIndices.push_back(IndexFormat(9, 10, 11));
}



void Utils::SetCube(std::vector<VertexFormat>& const _krVertices, std::vector<GLuint>& const _krIndices)
{

	VertexFormat frontA(-1, 1, 1, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);  //Top Left
	VertexFormat frontB(1, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f); // Top right
	VertexFormat frontC(-1, -1, 1, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); //Bottom Left
	VertexFormat frontD(1, -1, 1, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f); //Bottom Right

	VertexFormat sideA(1, 1, 1, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	VertexFormat sideB(1, 1, -1, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	VertexFormat sideC(1, -1, 1, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	VertexFormat sideD(1, -1, -1, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);

	VertexFormat topA(-1, 1, 1, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	VertexFormat topB(-1, 1, -1, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	VertexFormat topC(1, 1, 1, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	VertexFormat topD(1, 1, -1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	VertexFormat backA(frontA);
	backA.VertexPosition._fZ = -1;
	backA.Normal._fZ = -1;
	VertexFormat backB(frontB);
	backB.VertexPosition._fZ = -1;
	backB.Normal._fZ = -1;
	VertexFormat backC(frontC);
	backC.VertexPosition._fZ = -1;
	backC.Normal._fZ = -1;
	VertexFormat backD(frontD);
	backD.Normal._fZ = -1;
	backD.VertexPosition._fZ = -1;

	VertexFormat oSideA(sideA);
	oSideA.VertexPosition._fX = -1;
	oSideA.Normal._fX = -1;
	VertexFormat oSideB(sideB);
	oSideB.VertexPosition._fX = -1;
	oSideB.Normal._fX = -1;
	VertexFormat oSideC(sideC);
	oSideC.VertexPosition._fX = -1;
	oSideC.Normal._fX = -1;
	VertexFormat oSideD(sideD);
	oSideD.VertexPosition._fX = -1;
	oSideD.Normal._fX = -1;

	VertexFormat botA(topA);
	botA.VertexPosition._fY = -1;
	botA.Normal._fY = -1;
	VertexFormat botB(topB);
	botB.VertexPosition._fY = -1;
	botB.Normal._fY = -1;
	VertexFormat botC(topC);
	botC.VertexPosition._fY = -1;
	botC.Normal._fY = -1;
	VertexFormat botD(topD);
	botD.VertexPosition._fY = -1;
	botD.Normal._fY = -1;


	_krVertices.push_back(frontA);
	_krVertices.push_back(frontB);
	_krVertices.push_back(frontC);
	_krVertices.push_back(frontD);

	_krVertices.push_back(sideA);
	_krVertices.push_back(sideB);
	_krVertices.push_back(sideC);
	_krVertices.push_back(sideD);

	_krVertices.push_back(topA);
	_krVertices.push_back(topB);
	_krVertices.push_back(topC);
	_krVertices.push_back(topD);

	_krVertices.push_back(backA);
	_krVertices.push_back(backB);
	_krVertices.push_back(backC);
	_krVertices.push_back(backD);

	_krVertices.push_back(oSideA);
	_krVertices.push_back(oSideB);
	_krVertices.push_back(oSideC);
	_krVertices.push_back(oSideD);

	_krVertices.push_back(botA);
	_krVertices.push_back(botB);
	_krVertices.push_back(botC);
	_krVertices.push_back(botD);

	_krIndices =
	{
		0, 1, 2,
		1, 3, 2,

		4, 5, 6,
		5, 7, 6,

		8, 9, 10,
		9, 11, 10,

		14, 13, 12,
		14, 15, 13,
		//12, 13, 14,
		//13, 15, 14,

		18, 17, 16,
		18, 19, 17,
		//16, 17, 18,
		//17, 19, 18,

		22, 21, 20,
		22, 23, 21,
		//20, 21, 22,
		//21, 23, 22

	};
}

void Utils::SetCircle(std::vector<VertexFormat>& const _krVertices, std::vector<GLuint>& const _krIndices)
{
	VertexFormat Vertex(0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0); 
	_krVertices.push_back(Vertex);//Centre point
	GLfloat _iX = 0.0, _iY = 0.5f;//Starting coordinates for circle
	GLfloat xNew = _iX, yNew = _iY;//New coordinates
	GLfloat radius = 1.0f;
	GLfloat angle = 3.14f / 360.0f;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);

	int counter = 0;
	for (int i = 0; i <= 360; i += 20)
	{
		float degree = i * (3.14f / 180.0f);
		float x = cos(degree) * radius;
		float y = sin(degree) * radius;

		xNew = x * cosAngle - y * sinAngle;
		yNew = x * sinAngle + y * cosAngle;
		_iX = xNew;
		_iY = yNew;

		VertexFormat v1(x, y, 0, 0.5f + xNew, 0.5f - yNew, 1.0, 1.0, 1.0);
		_krVertices.push_back(v1);
		counter++;
	}

	for (int i = 0; i < counter; i++)//Setting indices
	{
		_krIndices.push_back(0);
		_krIndices.push_back(i + 1);
		_krIndices.push_back(i + 2);
	}
	_krIndices[(counter * 3) - 1] = 1;
}


void Utils::SetSphere(std::vector<VertexFormat>& const _krVertices, std::vector<GLuint>& const _krIndices)
{
	std::vector<VertexFormat> Vertices;
	std::vector<GLuint> Indices;

	double latitudeBands = 15;
	double longitudeBands = 15;
	float radius = 1.0f;

	for (double latNumber = 0; latNumber <= latitudeBands; latNumber++) {
		double theta = latNumber * 3.14159265359 / latitudeBands;
		double sinTheta = sin(theta);
		double cosTheta = cos(theta);

		for (double longNumber = 0; longNumber <= longitudeBands; longNumber++) {
			double phi = longNumber * 2 * 3.14159265359 / longitudeBands;
			double sinPhi = sin(phi);
			double cosPhi = cos(phi);

			VertexFormat vs;

			vs.TexturePosition._fX = static_cast<float>(1.0f - (longNumber / longitudeBands));
			vs.TexturePosition._fY = static_cast<float>(1.0f - (latNumber / latitudeBands));

			vs.Normal._fX = static_cast<float>(cosPhi * sinTheta);
			vs.Normal._fY = static_cast<float>(cosTheta);
			vs.Normal._fZ = static_cast<float>(sinPhi * sinTheta);

			vs.VertexPosition._fX = radius * vs.Normal._fX;
			vs.VertexPosition._fY = radius * vs.Normal._fY;
			vs.VertexPosition._fZ = radius * vs.Normal._fZ;

			Vertices.push_back(vs);
		}
	}

	for (GLuint latNumber = 0; latNumber < latitudeBands; latNumber++) {
		for (GLuint longNumber = 0; longNumber < longitudeBands; longNumber++) {
			GLuint first = static_cast<GLuint>((latNumber * (longitudeBands + 1)) + longNumber);
			GLuint second = static_cast<GLuint>(first + longitudeBands + 1);

			Indices.push_back(first);
			Indices.push_back(second);
			Indices.push_back(first + 1);

			Indices.push_back(second);
			Indices.push_back(second + 1);
			Indices.push_back(first + 1);

		}
	}



	_krVertices = Vertices;
	_krIndices = Indices;

}