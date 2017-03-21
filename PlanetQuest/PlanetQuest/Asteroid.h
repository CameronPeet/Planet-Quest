#pragma once

#include "Model.h"
#include "Player.h"

#define PI 3.14159265359

using namespace glm;

class CAsteroid
{
public:
	CAsteroid(ModelType eModelType, char* TextureName);
	void Initialise();
	vec3 SpawnPos();
	vec3 TargetPos();
	vec3 TargetDirection(vec3 vSpawnPos, vec3 vTargetPos);
	void OnCollisionWithPlayer(CPlayer& pPlayer);
	void Render(GLuint program, Camera& camera);
	void Update(float fDeltaTime);
	void SetDirection(vec3 vDirection);
	void SetSpeed(float fSpeed);
private:
	vec3& GetRandomPosition(float fRadius);
public:
	vec3 m_vSpawnPos;
	vec3 m_vTargetPos;
	vec3 m_vDirectionNormal;
	float m_fSpeed;

	Model* m_pModel;
private:
	vec3 m_vPosition;
};