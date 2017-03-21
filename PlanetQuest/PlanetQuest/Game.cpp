#include "Game.h"
#include "SceneManager.h"
bool CGame::Init()
{
	m_pPlayer1 = new CPlayer(CUBE, "Type3Enemy.jpg");
	m_pPlayer2 = new CPlayer(CUBE, "Type2Enemy.jpg");

	m_pPlayer1->Initialise();
	m_pPlayer2->Initialise();

	//m_pModels.push_back(m_pPlayer1->GetModel());
	//m_pModels.push_back(m_pPlayer2->GetModel());
	return true;
}

//calculate new text positions
void CGame::SetTextPositions()
{
}

void CGame::Render(GLuint program, Camera& camera)
{
	m_pPlayer1->Render(program, camera);
	m_pPlayer2->Render(program, camera);

	//render all models
	for (auto itr : m_pModels)
	{
		itr->Render(program, camera);
	}
	//render all text in current menu s
	for (auto itr : *m_pCurrentMenu)
	{
		itr->Render(camera);
	}

}


//Highlight and play sound when you mouse over an active button 
void CGame::PassiveMotion(int x, int y)
{

}

//Check clicks against TextLabel Positions, check the name, do something based on name
void CGame::Mouse(int button, int state, int x, int y)
{

}

//Moveintoaclassformovenemt
int w, a, s, d, up, down, left, right;
//Take key input
void CGame::KeyboardDown(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'w':
	case 'W':
		w = 1;
		break;
	case 's':
	case 'S':
		s = 1;
		break;
	}

}

void CGame::KeyboardUp(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'w':
	case 'W':
		w = 0;
		break;
	case 's':
	case 'S':
		s = 0;
		break;
	}
}


//Reshape or reset positions if you need to
void CGame::Reshape(int width, int height)
{
	SetTextPositions();
}

void CGame::Update(float fDeltaTime)
{

}
