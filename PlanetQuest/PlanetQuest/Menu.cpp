//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Menu.h
// Description	: Creates a Menu that can be navigated and determines the programmes next execution task based on menu selection
// Author		: Cameron Peet
// Mail			: Cameron.Peet@mediadesign.school.nz
//


#include "Menu.h"
#include "SceneManager.h"

/**
*
* This function initialises the menu.
* (Task ID: Menu)
*
* @author  and Cameron Peet
* @param void
* @return Returns true if successful
*
*/
bool CMenu::Init()
{
	m_pAllText.push_back(&m_pMainMenu);

	/*MainMenu*/
	//Menu Text in order seen top to bottom.
	//Play button - Clicked to open the Play Menu
	m_pMainMenu.push_back(new TextLabel(MENU, "Play", "Assets/Fonts/waltographUI.ttf"));
	m_pMainMenu[0]->setColor(glm::vec3(0.9f, 0.9f, 0.9f));

	m_pMainMenu.push_back(new TextLabel(MENU, "Controls", "Assets/Fonts/waltographUI.ttf"));
	m_pMainMenu[1]->setColor(glm::vec3(0.9f, 0.9f, 0.9f));

	//Quit Application Button - Click to glutLeaveMainLoop() and end application
	m_pMainMenu.push_back(new TextLabel(MENU, "Quit", "Assets/Fonts/waltographUI.ttf"));
	m_pMainMenu[2]->setColor(glm::vec3(0.9f, 0.9f, 0.9f));

	m_pCurrentMenuItem = m_pMainMenu[0];
	m_pCurrentMenuItem->m_bIsHighlighted = true;
	m_pCurrentMenuItem->setHighlight(glm::vec3(0, 0, 1));
	CurrentMenuIndex = 0;

	m_pSplashScreen = new Model(QUAD, "Controls.png");
	VALIDATE(m_pSplashScreen->Initialise());
	m_pSplashScreen->m_Scale = glm::vec3(18, 1, 18);
	m_bShowControlsImage = false;
	
	/*********
	Models
	**********/
	//EditBox - To represent the text field in which the users character presses will appear.
	m_pEditBox = new Model(QUAD, "TitleScreen.png");
	VALIDATE(m_pEditBox->Initialise());
	m_pEditBox->m_Scale = glm::vec3(20, 1, 20);
	//m_pEditBox->m_Rotation = glm::quat(1.0f, glm::radians(45.0f), 0.0f, 0.0f);
	m_pModels.push_back(m_pEditBox);

	//Current Menu State - Used to determine rendering and proccessing.
	m_strMenuName = "MainMenu";

	SetTextPositions();

	return true;
}

void CMenu::SetTextPositions()
{
	float centreX, centreY;
	centreX = Utils::WIDTH / 2;
	centreY = Utils::HEIGHT / 2;
	float maxItems = 8.0f;
	float spacing = Utils::HEIGHT / maxItems;
	float yTop = Utils::HEIGHT - spacing * 4;


	m_pMainMenu[0]->setPosition(glm::vec3(centreX + spacing, yTop, 10));
	m_pMainMenu[1]->setPosition(glm::vec3(centreX + spacing, yTop - spacing, 10));
	m_pMainMenu[2]->setPosition(glm::vec3(centreX + spacing, yTop - spacing * 2, 10));
	//m_pMainMenu[3]->setPosition(glm::vec3(centreX / 2 + spacing * 2, yTop - spacing * 3, 10));
	//m_pMainMenu[4]->setPosition(glm::vec3(centreX / 2 + spacing * 2, yTop - spacing * 4, 10));
	m_pEditBox->m_Position = glm::vec3(0, -1, 0);

}


void CMenu::Render(GLuint program, Camera& camera)
{
	for (auto itr : m_pModels)
	{
		itr->Render(program, camera);
	}

	if (m_bShowControlsImage)
	{
		m_pSplashScreen->Render(program, camera);
	}

	for (auto itr : *m_pCurrentMenu)
	{
		if(itr->m_bIsActive)
			itr->Render(camera);
	}


}

/**
*
* Handles mouse over.
* (Task ID: Menu)
*
* @author Cameron Peet
* @param x This is the mouse position.
* @param y This is the mouse position.
* @return void
*/
void CMenu::PassiveMotion(int x, int y)
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
				SelectItem(itr);
				itr->setHighlighted(true);
				itr->setHighlight(glm::vec3(0, 0, 1));
			}
			else
			{
				if (itr->isHighlighted() && itr != m_pCurrentMenuItem)
				{
					itr->setHighlighted(false);
				}
			}
		}
	}
}

/**
*
* Handles mouse clicks.
* (Task ID: Menu)
*
* @author Cameron Peet
* @param button This is the button.
* @param state This is the state.
* @param x This is the mouse position.
* @param y This is the mouse position.
* @return void
*/
void CMenu::Mouse(int button, int state, int x, int y)
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

						else if (text == "Controls")
						{
							ShowControls();
						}

						else if (text == "Exit")
						{
							HideControls();
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

void CMenu::KeyboardDown(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'w':
	case 'W':
		NextMenuItem(-1);
		break;
	case 's':
	case 'S':
		NextMenuItem(1);
		break;
	case 'i':
	case 'I':
		NextMenuItem(-1);
		break;
	case 'k':
	case 'K':
		NextMenuItem(1);
		break;

	case VK_SPACE:
	case '/n':
		{
			std::string text = m_pCurrentMenuItem->getText();
			if (text == "Play")
			{
				CSceneManager& _rSceneManager = CSceneManager::GetInstance();
				_rSceneManager.SelectScene("Game");
			}

			else if (text == "Controls")
			{
				ShowControls();
			}

			else if (text == "Exit")
			{
				HideControls();
			}

			else if (text == "Quit")
			{
				glutLeaveMainLoop();
				//Utils::g_Play = false;
			}

			m_pCurrentMenuItem->setHighlighted(false);
		}
		break;
	}
}

void CMenu::KeyboardUp(unsigned char c, int x, int y)
{
	
}


void CMenu::Reshape(int width, int height)
{
	SetTextPositions();
}



void CMenu::Update(float fDeltaTime)
{

}



void CMenu::ShowControls()
{
	m_bShowControlsImage = true;

	for (auto itr : *m_pCurrentMenu)
	{
		if (itr->getText() == "Controls")
		{
			itr->setText("Exit");
			itr->setPosition(itr->position + glm::vec3(-152, 0, 0));
		}
		else
		{
			itr->m_bIsActive = false;
		}
	}
}


void CMenu::HideControls()
{
	m_bShowControlsImage = false;
	for (auto itr : *m_pCurrentMenu)
	{
		if (itr->getText() == "Exit")
		{
			itr->setText("Controls");
			itr->setPosition(itr->position + glm::vec3(+152, 0, 0));
		}
		else
		{
			itr->m_bIsActive = true;
		}
	}
}


void CMenu::NextMenuItem(int next)
{
	CurrentMenuIndex += next;

	if (CurrentMenuIndex >= m_pMainMenu.size())
	{
		CurrentMenuIndex = 0;
	}
	else if (CurrentMenuIndex < 0)
	{
		CurrentMenuIndex = m_pMainMenu.size() - 1;
	}

	m_pCurrentMenuItem->setHighlighted(false);
	m_pCurrentMenuItem = m_pMainMenu[CurrentMenuIndex];
	m_pCurrentMenuItem->setHighlight(glm::vec3(0, 0, 1));
	m_pCurrentMenuItem->setHighlighted(true);
}

void CMenu::SelectItem(TextLabel* label)
{
	for (auto itr : m_pMainMenu)
	{
		if (itr->getText() == label->getText())
		{
			m_pCurrentMenuItem->setHighlighted(false);
			m_pCurrentMenuItem = itr;
			m_pCurrentMenuItem->setHighlight(glm::vec3(0, 0, 1));
			m_pCurrentMenuItem->setHighlighted(true);
			return;
		}
	}
}
