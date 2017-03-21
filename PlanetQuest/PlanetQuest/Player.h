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
	void MovePlayer(GLfloat deltaTime);


public:

	Model* m_pModel;

	vec3 m_Position;
	vec3 m_Velocity;
	quat m_Rotation;

	float m_fRadius;
	float m_fSpeed;

	bool m_bAlive;

	vec3 MovementDelta;
	vec3 RotationDelta;

	int w, a, s, d;
	float Accelerate, Decelerate;
};