// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Cameron Peet
// Mail			: Cameron.Peet@mediadesign.school.nz

#pragma once

#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define VALIDATE(a) if (!a) return (false)

class Model;

enum ModelType
{
	CUBE, TRIANGLE, SPHERE, CIRCLE, PYRAMID, QUAD
};


//Position Structure defines a single point for a primitive shape
struct Position {
	Position() {}
	Position(GLfloat x, GLfloat y, GLfloat z)
		: _fX(x), _fY(y), _fZ(z) {

	}

	GLfloat _fX;
	GLfloat _fY;
	GLfloat _fZ;
};

//Normalise texture coordinates
struct TexCoord
{
	GLfloat _fX;
	GLfloat _fY;
};

//Normalised Color values RGB
struct Color
{
	Color() {}
	Color(GLfloat x, GLfloat y, GLfloat z)
		: _fX(x), _fY(y), _fZ(z) {
	}
	GLfloat _fX;
	GLfloat _fY;
	GLfloat _fZ;
};

//Defines 3 points in the vertices array that will define a primitive
//, _fX, _fY, _fZ define Points 1, 2, 3 respectively.
struct IndexFormat
{
	IndexFormat() {}
	IndexFormat(GLfloat x, GLfloat y, GLfloat z) : _fX(x), _fY(y), _fZ(z)
	{
	}

	GLfloat _fX;
	GLfloat _fY;
	GLfloat _fZ;
};

//Structure contatining the 3 attributes used in defining a fragment. 
//The a single vertex(Point on the primitive)
//The texture normal attribute
//The color normal attribute
struct VertexFormat
{
	VertexFormat() {}
	VertexFormat(GLfloat x, GLfloat y, GLfloat z, GLfloat TexX, GLfloat TexY, GLfloat nX, GLfloat nY, GLfloat nZ)
	{
		VertexPosition._fX = x;
		VertexPosition._fY = y;
		VertexPosition._fZ = z;
		TexturePosition._fX = TexX;
		TexturePosition._fY = TexY;
		Color._fX = nX;
		Color._fY = nY;
		Color._fZ = nZ;
	}

	Position VertexPosition;
	TexCoord TexturePosition;
	Color  Color;

};

/*
@Author : Cameron Peet
@Purpose : Static methods define a shape that the Model class will inherit by copy. Creates a polymorphic like attribute by being able to
dynamically define the shape of an individual model instance.
*/
class Utils
{
	Utils() {}
	~Utils() {}

public:

	static void SetCube(Model& _rModel);
	static void SetQuad(Model& _rModel);
	static void SetTriangle(Model& _rModel);
	static void SetPyramid(Model& _rModel);
	static void SetCircle(Model& _rModel);
	static void SetSphere(Model& _rModel);
	static float WIDTH;
	static float HEIGHT;
	static bool g_Play;
};