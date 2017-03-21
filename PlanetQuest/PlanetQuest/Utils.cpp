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
	VertexFormat v1(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0);
	VertexFormat v2(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.f, 0.0f, 0.0);
	VertexFormat v3(-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0);
	VertexFormat v4(-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0);

	_rModel.vertices.push_back(v1);
	_rModel.vertices.push_back(v2);
	_rModel.vertices.push_back(v3);
	_rModel.vertices.push_back(v4);

	//Set Indices directly
	_rModel.indices = { 0, 1, 3, 1, 2, 3 };

}


/*Author : Cameron Peet
Purpose	:  Define the 3 points required to make a unit triangle */
void Utils::SetTriangle(Model& _rModel)
{
	// Pos1, 2, 3, Tex1, 2, Color1, 2, 3
	VertexFormat v1(0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0);
	VertexFormat v2(0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0);
	VertexFormat v3(-0.5f, -0.5f, 0.0f, 0.0f, 1.0F, 0.0f, 0.0f, 0.0);

	_rModel.vertices.push_back(v1);
	_rModel.vertices.push_back(v2);
	_rModel.vertices.push_back(v3);

	//Setting indices
	_rModel.indices = { 0, 1, 2 };

}

/**
*
* This function sets the pyramid.
* (Task ID: Utils)
*
* @author Cameron Peet
* @param _rModel This is the model
* @return void
*
*/
void Utils::SetPyramid(Model& _rModel)
{
	_rModel.vertices.clear();
	_rModel.indices.clear();

	VertexFormat v1(0.0f, 0.5f, 0.0f, 0, 1, 0, 0.0f, 0.0f);
	VertexFormat v2(-0.5f, -0.5f, 0.5f, 0, 0, 0.0f, 0, 0.0f);
	VertexFormat v3(0.5f, -0.5f, 0.5f, 1, 0, 0.0f, 0.0f, 0);
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
}

/**
*
* This function sets the cube.
* (Task ID: Utils)
*
* @author Cameron Peet
* @param _rModel This is the model
* @return void
*
*/
void Utils::SetCube(Model& _rModel)
{
	//Back face 
	VertexFormat v1(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0);
	VertexFormat v2(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0);
	VertexFormat v3(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0);
	VertexFormat V4(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0);

	////Front face 
	VertexFormat V5(-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0);
	VertexFormat V6(0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0);
	VertexFormat V7(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0);
	VertexFormat V8(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0);

	//Top face 
	VertexFormat V9(-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0);
	VertexFormat V10(-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0);
	VertexFormat V11(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0);
	VertexFormat V12(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0);


	//Bottom face
	VertexFormat V13(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0);
	VertexFormat V14(0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0);
	VertexFormat V15(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0);
	VertexFormat V16(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0);

	//Right face
	VertexFormat V17(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0);
	VertexFormat V18(0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0);
	VertexFormat V19(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0);
	VertexFormat V20(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0);

	//Left face
	VertexFormat V21(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0);
	VertexFormat V22(-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0);
	VertexFormat V23(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0);
	VertexFormat V24(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0);

	_rModel.vertices.push_back(v1);
	_rModel.vertices.push_back(v2);
	_rModel.vertices.push_back(v3);
	_rModel.vertices.push_back(V4);
	_rModel.vertices.push_back(V5);
	_rModel.vertices.push_back(V6);
	_rModel.vertices.push_back(V7);
	_rModel.vertices.push_back(V8);
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
		// front
		0, 1, 2,
		0, 2, 3,
		// top
		4, 5, 6,
		4, 6, 7,
		// back
		8, 9, 10,
		8, 10, 11,
		// bottom
		12, 13, 14,
		12, 14, 15,
		// Right face
		16, 17, 18,
		16, 18, 19,
		// Left Face
		20, 21, 22,
		20, 22, 23,
	};

}

/**
*
* This function sets the circle.
* (Task ID: Utils)
*
* @author Cameron Peet
* @param _rCircle This is the model
* @return void
*
*/
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

/**
*
* This function sets the sphere.
* (Task ID: Utils)
*
* @author Cameron Peet
* @param _rModel This is the model
* @return void
*
*/
void Utils::SetSphere(Model& _rModel)
{

}