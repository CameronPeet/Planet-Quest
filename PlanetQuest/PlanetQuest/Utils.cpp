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


#include "GL_Utils.h"
#include "Model.h"

float Utils::WIDTH = 1200.0f;
float Utils::HEIGHT = 800.0f;
bool Utils::g_Play = false;

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
	VertexFormat v1(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	VertexFormat v2(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	VertexFormat v3(-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	VertexFormat v4(-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	_rModel.vertices.push_back(v1);
	_rModel.vertices.push_back(v2);
	_rModel.vertices.push_back(v3);
	_rModel.vertices.push_back(v4);

	//Set Indices directly
	_rModel.indices = { 0, 1, 3, 1, 2, 3 };


	//Struct method. Clunky code.
	//_rModel.indices.push_back(IndexFormat(0, 1, 3));
	//_rModel.indices.push_back(IndexFormat(1, 2, 3));
}


/*Author : Cameron Peet
Purpose	:  Define the 3 points required to make a unit triangle */
void Utils::SetTriangle(Model& _rModel)
{
	// Pos1, 2, 3, Tex1, 2, Color1, 2, 3
	VertexFormat v1(0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	VertexFormat v2(0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	VertexFormat v3(-0.5f, 0.0f, 0.0f, 0.0f, 1.0F, 0.0f, 0.0f, 1.0f);

	_rModel.vertices.push_back(v1);
	_rModel.vertices.push_back(v2);
	_rModel.vertices.push_back(v3);

	//Setting indices
	_rModel.indices = { 0, 1, 2 };

	//_rModel.indices.push_back(IndexFormat(0, 1, 2));
}
void Utils::SetPyramid(Model& _rModel)
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
	//Back face 
	VertexFormat v1(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -0.5f);
	VertexFormat v2(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -0.5f);
	VertexFormat v3(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -0.5f);
	VertexFormat V4(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f);

	////Front face 
	VertexFormat V5(-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f);
	VertexFormat V6(0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.5f);
	VertexFormat V7(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f);
	VertexFormat V8(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f);

	//Top face 
	VertexFormat V9(-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f);
	VertexFormat V10(-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.5f, 0.0f);
	VertexFormat V11(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f);
	VertexFormat V12(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f);


	//Bottom face
	VertexFormat V13(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -0.5f, 0.0f);
	VertexFormat V14(0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -0.5f, 0.0f);
	VertexFormat V15(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -0.5f, 0.0f);
	VertexFormat V16(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -0.5f, 0.0f);

	//Right face
	VertexFormat V17(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f);
	VertexFormat V18(0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, 0.0f, 0.0f);
	VertexFormat V19(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f);
	VertexFormat V20(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f);

	//Left face
	VertexFormat V21(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f);
	VertexFormat V22(-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.0f, 0.0f);
	VertexFormat V23(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -0.5f, 0.0f, 0.0f);
	VertexFormat V24(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -0.5f, 0.0f, 0.0f);

	_rModel.vertices.push_back(v1);
	_rModel.vertices.push_back(v2);
	_rModel.vertices.push_back(v3);
	_rModel.vertices.push_back(V4);
	_rModel.vertices.push_back(V5);
	_rModel.vertices.push_back(V6);
	_rModel.vertices.push_back(V8);
	_rModel.vertices.push_back(V9);
	_rModel.vertices.push_back(V9);
	_rModel.vertices.push_back(V10);
	_rModel.vertices.push_back(V11);
	_rModel.vertices.push_back(V12);
	_rModel.vertices.push_back(V13);
	_rModel.vertices.push_back(V14);
	_rModel.vertices.push_back(V15);
	_rModel.vertices.push_back(V16);
	_rModel.vertices.push_back(V17);
	_rModel.vertices.push_back(V18);
	_rModel.vertices.push_back(V19);
	_rModel.vertices.push_back(V20);
	_rModel.vertices.push_back(V21);
	_rModel.vertices.push_back(V22);
	_rModel.vertices.push_back(V23);
	_rModel.vertices.push_back(V24);

	_rModel.indices = {
		//// front
		0, 1, 2,
		0, 2, 3,
		//// top
		4, 5, 6,
		4, 6, 7,
		//// back
		8, 9, 10,
		8, 10, 11,
		//// bottom
		12, 13, 14,
		12, 14, 15,
		// Right face
		16, 17, 18,
		16, 18, 19,
		//// Left Face
		20, 21, 22,
		20, 22, 23,
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

			vs.Color._fX = static_cast<float>(cosPhi * sinTheta);
			vs.Color._fY = static_cast<float>(cosTheta);
			vs.Color._fZ = static_cast<float>(sinPhi * sinTheta);

			vs.VertexPosition._fX = radius * vs.Color._fX;
			vs.VertexPosition._fY = radius * vs.Color._fY;
			vs.VertexPosition._fZ = radius * vs.Color._fZ;

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