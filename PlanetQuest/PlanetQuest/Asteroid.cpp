#include "Asteroid.h"

CAsteroid::CAsteroid(vec3 spawnPos, vec3 targetPos, ModelType eModelType, char* TextureName)
{
	m_pModel = new Model(eModelType, TextureName);
	m_pModel->SetPosition(spawnPos);
	m_pModel->Initialise();
	m_vSpawnPos = spawnPos;
	m_vTargetPos = targetPos;
	m_fSpeed = 2;
	m_vDirectionNormal = normalize(TargetDirection(m_vSpawnPos, m_vTargetPos));
}

vec3 CAsteroid::SpawnPos()
{
	return(m_vSpawnPos);
}

vec3 CAsteroid::TargetPos()
{
	return(m_vTargetPos);
}

vec3 CAsteroid::TargetDirection(vec3 vSpawnPos, vec3 vTargetPos)
{
	return(vTargetPos - vSpawnPos);
}

void CAsteroid::OnCollisionWithPlayer(CPlayer& pPlayer)
{

}

void CAsteroid::Render(GLuint program, Camera& camera)
{
	m_pModel->Render(program, camera);
}

void CAsteroid::Update(float fDeltaTime)
{
	vec3 newPosition = m_pModel->getPosition();
	newPosition += (m_vDirectionNormal * m_fSpeed) * fDeltaTime;
	m_pModel->SetPosition(newPosition);
	printf("%f %f %f\n", newPosition.x, newPosition.y, newPosition.z);
}

void CAsteroid::SetDirection(vec3 vDirection)
{
	m_vDirectionNormal = vDirection;
}

void CAsteroid::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}