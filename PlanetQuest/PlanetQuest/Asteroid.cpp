#include "Asteroid.h"

CAsteroid::CAsteroid(ModelType eModelType, char* TextureName)
{
	m_pModel = new Model(eModelType, TextureName);
	m_pModel->SetPosition(vec3(0.0f, 0.0f, 0.0f));
}

void CAsteroid::Initialise()
{
	srand(time(NULL));
	m_vSpawnPos = GetRandomPosition(10.0f);
	m_vTargetPos = GetRandomPosition(4.0f);
	m_vPosition = m_vSpawnPos;
	m_fSpeed = 2;

	m_vDirectionNormal = normalize(TargetDirection(m_vSpawnPos, m_vTargetPos));
	m_pModel->Initialise();
}

vec3& CAsteroid::GetRandomPosition(float fRadius)
{
	int _iRand = rand() % 360;
	vec3* _vRandom = new vec3(sin(_iRand * PI / 180.0), 0.0f, cos(_iRand * PI / 180.0));
	*_vRandom *= fRadius;

	return *_vRandom;
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
	m_vPosition += (m_vDirectionNormal * m_fSpeed) * fDeltaTime;
	m_pModel->SetPosition(m_vPosition);
}

void CAsteroid::SetDirection(vec3 vDirection)
{
	m_vDirectionNormal = vDirection;
}

void CAsteroid::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}