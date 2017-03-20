#pragma once
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Model.h
// Description	: Encapsulate required functionality and components to define and render a predefined shape.
// Author		: Cameron Peet
// Mail			: Cameron.Peet@mediadesign.school.nz

//Local Includes
#include "GL_Utils.h"
#include "Camera.h"
#include "ResourceManager.h"
//#include "Light.h"

class Light;

//Library Includes
#include <vector>


/*
@Author : Cameron Peet
@Class : Model
@Purpose: Model Class - Encapsulate initialisation, rendering and positional control over an indiviudual model.
		  Allow for inidividual textures, and can be modified to have an individual shader program per requirements.
*/
class Model
{

public:
	Model();
	Model(ModelType Shape, char* Filename);
	~Model();

	//GLuint program;
	GLuint vao;
	GLuint vbo;
	GLuint ebo; 
	GLuint texture;
	GLuint texture2;

	ModelType Shape;

	//Containers for model vertices and indices, allowing the model class to to define any shape constructible through primitives
	std::vector<VertexFormat>	vertices;
	std::vector<GLuint>			indices;

	//Unused IndexFormat, due to the additional allocation and the clunky code produced.
	//Easier understood however, each vertex clearly defined.
	//std::vector<IndexFormat>	indices;

	//Scale, Position and Rotation Components
	glm::quat m_Rotation;
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_RotationPoint;

	bool isTriangleBased = true;
	bool isLineBased = false;

	ModelType m_Shape;

	//Stored by the constructor for use in the initialiser.
	char* texturePath;

	//Render the model using an externaly provided camera for projection and view matrix, and an externally supplied program.
	void Render(GLuint program, Camera& camera, Light* lightSource = nullptr);
	bool Initialise();

	void SetPosition(glm::vec3 _position);
	glm::vec3 getPosition();
	glm::vec3 getScale();
	void setTexture(char* _texturePath);

	void ChangeShape(ModelType Shape);
	ModelType GetShape() { return m_Shape; }

	//void Render(Camera& camera);
	//void Initialise(vec3 _vPosition = 0, vec3 _vScale = 1, vec3 _qRot = 0);
	

public:
	//Attributes
	float Specular;
	float Ambient;
	glm::vec3 ObjectColor;
};
