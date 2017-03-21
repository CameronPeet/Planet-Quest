#pragma once


#include "Model.h"

using namespace glm;

class CPlayer 
{
public:

	CPlayer(ModelType eModelType, char* TextureName);
	void Initialise();
	void Render(GLuint program, Camera& camera);
	void Process(GLfloat _deltaTime);

public:

	Model* m_pModel;
	bool m_bAlive;

	vec3 m_Position;

};