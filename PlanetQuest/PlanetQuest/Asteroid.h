#pragma once

#include "Model.h"
#include "Player.h"

using namespace glm;

class CAsteroid
{
public:
	CAsteroid(vec3 SpawnPos, vec3 TargetPos, ModelType eModelType, char* TextureName);
	vec3 SpawnPos();
	vec3 TargetPos();
	vec3 TargetDirection(vec3 vSpawnPos, vec3 vTargetPos);
	void OnCollisionWithPlayer(CPlayer& pPlayer);
	void Render(GLuint program, Camera& camera);
	void Update(float fDeltaTime);
	void SetDirection(vec3 vDirection);
	void SetSpeed(float fSpeed);
public:
	vec3 m_vSpawnPos;
	vec3 m_vTargetPos;
	vec3 m_vDirectionNormal;
	float m_fSpeed;

	Model* m_pModel;
};