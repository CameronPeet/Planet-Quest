#include "Game.h"
#include "SceneManager.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

bool CGame::Init()
{
	CAsteroid* newAsteroid;
	m_pPlayer1 = new CPlayer(CIRCLE, "Spacesuit_01.png");
	m_pPlayer2 = new CPlayer(CIRCLE, "Spacesuit_02.png");

	//m_pPlayer1->m_pModel->m_Rotation = glm::rotate(m_pPlayer1->m_pModel->m_Rotation, 90.0f, glm::vec3(1, 0, 0));

	m_pPlayer1->Initialise();
	m_pPlayer2->Initialise();

	m_pPlayer1->Texture1 = "Spacesuit_01.png";
	m_pPlayer2->Texture1 = "Spacesuit_02.png";

	m_pPlayer1->Texture2 = "Spacesuit_Fire_01.png";
	m_pPlayer2->Texture2 = "Spacesuit_Fire_02.png";

	for (int i = 0; i < 5; ++i)
	{
		newAsteroid = new CAsteroid(CIRCLE, "Asteroid.png");
		newAsteroid->Initialise();
		m_pAsteroids.push_back(newAsteroid);
	}

	m_fLastTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
	m_fSplashScreenTimer = 0.0f;
	//	m_fRoundStartTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));

	//m_pModels.push_back(m_pPlayer1->GetModel());
	//m_pModels.push_back(m_pPlayer2->GetModel());

	// Game Text
	// Timer
	m_pTextTimer = new TextLabel(TIMER, "", "Assets//Fonts//Pacifico.ttf");
	m_pTextTimer->setScale(0.6f);
	m_pTextTimer->setPosition(glm::vec3(1130.0f, 750.0f, 0.0f));
	m_pTextTimer->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	AddText(m_pTextTimer);

	m_pTextRoundOver = new TextLabel(GAMEOVER, "Round Over!", "Assets//Fonts//Pacifico.ttf");
	m_pTextRoundOver->setScale(0.9f);
	m_pTextRoundOver->setPosition(glm::vec3(430.0f, 600.0f, 0.0f));
	m_pTextRoundOver->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	AddText(m_pTextRoundOver);

	m_pTextControls = new TextLabel(SPLASH, "Controls", "Assets//Fonts//Pacifico.ttf");
	m_pTextControls->setScale(0.9f);
	m_pTextControls->setPosition(glm::vec3(430.0f, 600.0f, 0.0f));
	m_pTextControls->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	AddText(m_pTextControls);

	m_Player1ScoreText = new TextLabel(GAMEOVER, "", "Assets//Fonts//Pacifico.ttf");
	m_Player1ScoreText->setScale(0.7f);
	m_Player1ScoreText->setPosition(glm::vec3(400.0f, 380.0f, 0.0f));
	m_Player1ScoreText->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	AddText(m_Player1ScoreText);

	m_Player2ScoreText = new TextLabel(GAMEOVER, "", "Assets//Fonts//Pacifico.ttf");
	m_Player2ScoreText->setScale(0.7f);
	m_Player2ScoreText->setPosition(glm::vec3(400.0f, 280.0f, 0.0f));
	m_Player2ScoreText->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	AddText(m_Player2ScoreText);

	m_ShowSplashScreen = true;

	return true;
}

void CGame::Reset()
{
	//Reset timer text
	m_pTextTimer->setText("0");

	//Reset Players
	m_pPlayer1->m_Position = glm::vec3(0, 0, 0);
	m_pPlayer1->SetAlive(true);

	m_pPlayer2->m_Position = glm::vec3(0, 0, 0);
	m_pPlayer2->SetAlive(true);


	//Reset Asteroids Vector
	m_pAsteroids.clear();
	for (int i = 0; i < 5; ++i)
	{
		CAsteroid* newAsteroid = new CAsteroid(CIRCLE, "Asteroid.png");
		newAsteroid->Initialise();
		m_pAsteroids.push_back(newAsteroid);
	}

	m_GameOver = false;
	m_StartNextRound = false;
	m_RoundTimerStarted = false;
}

//calculate new text positions
void CGame::SetTextPositions()
{

}

void CGame::AddText(TextLabel* _text) 
{
	m_textLabels.push_back(_text);
}

void CGame::Render(GLuint program, Camera& camera)
{
	if (!m_GameOver && !m_ShowSplashScreen)
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
		//render all Asteroids
		for (auto itr : m_pAsteroids)
		{
			itr->Render(program, camera);
		}
	}
	
	RenderText(camera);
}

void CGame::RenderText(Camera & camera)
{
	for (auto textLabel = m_textLabels.begin(); textLabel != m_textLabels.end(); textLabel++)
	{
		if ((*textLabel)->GetTextType() == TIMER)
		{
			if (!m_GameOver)
			{
				int Time = static_cast<int>((m_GLfCurrentTime - m_fRoundStartTime) / 1000);
				if (Time < 0) Time = 0;
				(*textLabel)->setText(std::to_string(Time));
			}
			if (!m_ShowSplashScreen)
				(*textLabel)->Render(camera);
		}

		if ((*textLabel)->GetTextType() == GAMEOVER)
		{
			if (m_GameOver)
				(*textLabel)->Render(camera);
		}

		if ((*textLabel)->GetTextType() == SPLASH)
		{
			if (m_ShowSplashScreen)
				(*textLabel)->Render(camera);
		}
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
		m_pPlayer1->w = 1;
		break;
	case 's':
	case 'S':
		m_pPlayer1->s = 1;
		break;
	case 'a':
	case 'A':
		m_pPlayer1->a = 1;
		break;
	case 'd':
	case 'D':
		m_pPlayer1->d = 1;
		break;
	case 'i':
	case 'I':
		m_pPlayer2->w = 1;
		break;
	case 'k':
	case 'K':
		m_pPlayer2->s = 1;
		break;
	case 'j':
	case 'J':
		m_pPlayer2->a = 1;
		break;
	case 'l':
	case 'L':
		m_pPlayer2->d = 1;
		break;
	}
}

void CGame::KeyboardUp(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'w':
	case 'W':
		m_pPlayer1->w = 0;
		break;
	case 's':
	case 'S':
		m_pPlayer1->s = 0;
		break;
	case 'a':
	case 'A':
		m_pPlayer1->a = 0;
		break;
	case 'd':
	case 'D':
		m_pPlayer1->d = 0;
		break;
	case 'i':
	case 'I':
		m_pPlayer2->w = 0;
		break;
	case 'k':
	case 'K':
		m_pPlayer2->s = 0;
		break;
	case 'j':
	case 'J':
		m_pPlayer2->a = 0;
		break;
	case 'l':
	case 'L':
		m_pPlayer2->d = 0;
		break;

	case VK_SPACE:
		m_StartNextRound = true;
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
				
	if (m_ShowSplashScreen)
	{
		m_fSplashScreenTimer += fDeltaTime;

		if (m_fSplashScreenTimer > 1.5f)
			m_ShowSplashScreen = false;
		return;
	}
	
	if (!m_RoundTimerStarted)
	{
		m_fRoundStartTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
		m_RoundTimerStarted = true;
	}

	if (m_pPlayer1->GetAlive() == false || m_pPlayer2->GetAlive() == false)
	{
		if (m_StartNextRound)
		{
			EndRound();
		}
	}

	if (!m_GameOver)
	{
		m_GLfCurrentTime = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME));
		if (m_GLfCurrentTime - m_fLastTime > 2000)
		{
			CAsteroid* newAsteroid = new CAsteroid(CIRCLE, "Asteroid.png");
			newAsteroid->Initialise();
			float scale = static_cast<float>(rand() % 500 / 1000.0f);
			//Random Scaling
			scale += 0.5f;
			newAsteroid->m_pModel->m_Scale = glm::vec3(scale, scale, scale);
			m_pAsteroids.push_back(newAsteroid);

			m_fLastTime = m_GLfCurrentTime;
		}

		for (auto itr : m_pAsteroids)
		{
			itr->Update(fDeltaTime);
			float asteroidRadius = 0.5f * length(itr->m_pModel->m_Scale);
			float _fDistance = length((m_pPlayer1->GetPosition() - itr->GetPosition()));
			float radius = 0.5f * length(m_pPlayer1->m_pModel->m_Scale);
			//EDIT Adding flex value to try and account for texture against shape size
			if (_fDistance + m_fCollisionFlex < radius + asteroidRadius)
			{
				itr->OnCollisionWithPlayer(*m_pPlayer1);
				m_GameOver = true;
			}
			_fDistance = length((m_pPlayer2->GetPosition() - itr->GetPosition()));
			if (_fDistance + m_fCollisionFlex< radius + asteroidRadius)
			{
				itr->OnCollisionWithPlayer(*m_pPlayer2);
				m_GameOver = true;
			}
		}

		m_pPlayer1->Process(fDeltaTime);
		m_pPlayer2->Process(fDeltaTime);
	}
	else
	{
		int player1Alive = 0;
		int player2Alive = 0;
		if (m_pPlayer1->GetAlive())
			player1Alive = 1;
		else
			player2Alive = 1;

		m_Player1ScoreText->setText("Player 1 Score : " + std::to_string(m_iPlayer1Score + player1Alive));
		m_Player2ScoreText->setText("Player 2 Score : " + std::to_string(m_iPlayer2Score + player2Alive));
	}
}


void CGame::EndRound()
{
	if (m_pPlayer1->GetAlive() == false)
	{
		m_iPlayer2Score++;
	}
	else
	{
		m_iPlayer1Score++;
	}


	CGame::Reset();
	//CGame::Init();

}
