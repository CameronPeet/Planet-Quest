#include "Game.h"
#include "SceneManager.h"


bool CGame::Init()
{
	//Initialise all models etc
	return true;
}

//calculate new text positions
void CGame::SetTextPositions()
{
}

void CGame::Render(GLuint program, Camera& camera)
{
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
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;

	for (auto itr : *m_pCurrentMenu)
	{
		if (itr->isActive() && itr->isButton())
		{
			if (x > itr->position.x && x < itr->position.x + itr->width && y > itr->position.y && y < itr->position.y + itr->height)
			{
				if (!itr->isHighlighted())
				{
					CResources::PlayAudio("mouseover.wav");
				}
				itr->setHighlighted(true);
				itr->setHighlight(glm::vec3(0, 0, 1));
			}
			else
			{
				if (itr->isHighlighted())
				{
					itr->setHighlighted(false);
				}
			}
		}
	}
}

//Check clicks against TextLabel Positions, check the name, do something based on name
void CGame::Mouse(int button, int state, int x, int y)
{
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	//Dp Nothing
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			for (auto itr : *m_pCurrentMenu)
			{
				if (itr->isActive() && itr->isButton())
				{

					if (x > itr->position.x && x < itr->position.x + itr->width && y > itr->position.y && y < itr->position.y + itr->height)
					{
						std::string text = itr->getText();
						if (text == "Play")
						{
							CSceneManager& _rSceneManager = CSceneManager::GetInstance();
							_rSceneManager.SelectScene("Game");
						}

						else if (text == "Quit")
						{
							glutLeaveMainLoop();
							//Utils::g_Play = false;
						}

						itr->setHighlighted(false);
						break;
					}
				}
			}
		}
	}
}

//Take key input
void CGame::KeyboardDown(unsigned char c, int x, int y)
{

}

void CGame::KeyboardUp(unsigned char c, int x, int y)
{

}


//Reshape or reset positions if you need to
void CGame::Reshape(int width, int height)
{
	SetTextPositions();
}

void CGame::Update(float fDeltaTime)
{

}
