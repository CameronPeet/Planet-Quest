// Local Includes
#include "GL_utils.h"

// This Include
#include "Player.h"

int CPlayer::Player1Score = 0;
int CPlayer::Player2Score = 0;
bool CPlayer::Player1WonLastRound = false;
bool CPlayer::Player2WonLastRound = false;

int CPlayer::TimeOfLastRound = 0;


//CPlayer::~CPlayer()
//{
//	Model::~Model();
//}

CPlayer::CPlayer(ModelType eModelType, char* TextureName)
	: m_Rotation()
{
	m_pModel = new Model(eModelType, TextureName);
	m_Position = vec3(0, 0, 0);
	w = 0, s = 0, d = 0, s = 0;
	m_fSpeed = 5.0f;
	m_fTurnSpeed = 2.50f;
}

void CPlayer::Initialise()
{
	m_bAlive = true;
	m_pModel->Initialise();
}

void CPlayer::Render(GLuint program, Camera & camera)
{
	if(m_bAlive)
		m_pModel->Render(program, camera);
}

void CPlayer::Process(GLfloat _deltaTime)
{
	if (m_bAlive)
	{
		MovePlayer(_deltaTime);

		m_Position = glm::clamp(m_Position, vec3(-8.5f, 0, -8.5f), vec3(8.5f, 0, 8.5f));
		m_pModel->m_Position = m_Position;
	}
	//m_pModel->m_Rotation = m_Rotation;
	//Do our stuff
}


void CPlayer::MovePlayer(GLfloat _deltaTime)
{
	if (w || s)
	{
		Accelerate += (w - s) * _deltaTime;
		Accelerate = clamp(Accelerate, 0.0f, 1.0f);
	}

	if (Accelerate > 0.0f)
	{
		m_pModel->setTexture(Texture2);
	}
	else
	{
		m_pModel->setTexture(Texture1);
	}

	vec3 v = vec3(0, 0, Accelerate);
	vec3 u = vec3(0, m_pModel->m_Rotation.y, m_pModel->m_Rotation.z);
	float s = m_pModel->m_Rotation.w;
	vec3 p = 2.0f * dot(u, v) * u + (s * s - dot(u, u)) * v + 2.0f * s * cross(u, v);

	vec3 MoveDir = p;
	//MoveDir *= m_pModel->m_Rotation;
	MoveDir = MoveDir * m_fSpeed * _deltaTime;
	m_Position += MoveDir;

	float RotationDir = static_cast<float>(d - a);
	if (RotationDir != 0.0f)
	{
		m_pModel->m_Rotation = glm::rotate(m_pModel->m_Rotation, m_fTurnSpeed * _deltaTime, glm::vec3(0, 1, 0) * RotationDir);
	}
}

void CPlayer::ResetAcceleration()
{
	Accelerate = 0.0f;
}

void CPlayer::ResetRotation()
{
	m_pModel->m_Rotation = quat(1.0f, 0.0f, 0.0f, 0.0f);
}

void CPlayer::SetAlive(bool _bNewState)
{
	m_bAlive = _bNewState;
}

vec3& CPlayer::GetPosition()
{
	return m_Position;
}

bool CPlayer::GetAlive()
{
	return m_bAlive;
}