// Local Includes
#include "GL_utils.h"

// This Include
#include "Player.h"

//CPlayer::~CPlayer()
//{
//	Model::~Model();
//}

CPlayer::CPlayer(ModelType eModelType, char* TextureName)
{
	m_pModel = new Model(eModelType, TextureName);
	m_Position = vec3(0, 0, 0);
}

void CPlayer::Initialise()
{
	m_pModel->Initialise();
}

void CPlayer::Render(GLuint program, Camera & camera)
{
	m_pModel->Render(program, camera);
}

void CPlayer::Process(GLfloat _deltaTime)
{
	m_pModel->m_Position = m_Position;
	//Do our stuff
}
