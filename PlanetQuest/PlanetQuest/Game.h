#pragma once

#include "Scene.h"
#include "Player.h"
#include "Asteroid.h"


class CGame : public CScene
{
	bool Init();
	void Reset();
	void Render(GLuint program, Camera& camera);
	void RenderText(Camera& camera);
	void Update(float fDeltaTime);
	void PassiveMotion(int x, int y);
	void Mouse(int button, int state, int x, int y);
	void KeyboardDown(unsigned char c, int x, int y);
	void KeyboardUp(unsigned char c, int x, int y);
	void Reshape(int width, int height);
	void SetTextPositions();
	void AddText(TextLabel* _text);

private:

	void EndRound();

	std::string m_strMenuName;
	std::string m_strServerName;

	std::vector<std::vector<TextLabel*>*> m_pAllText;
	//Vector for easier rendering, re-assigned according to menu depth
	std::vector<TextLabel*>* m_pCurrentMenu = &m_pMainMenu;
	//Vectors to seperate the different menu depths
	std::vector<TextLabel*> m_pMainMenu;

	//Vector for easier rendering
	std::vector<Model*> m_pModels;

	std::vector<TextLabel*> m_textLabels;

	Camera *m_Camera;

	int m_iPlayer1Score;
	int m_iPlayer2Score;
	CPlayer* m_pPlayer1;
	CPlayer* m_pPlayer2;
	std::vector<CAsteroid*> m_pAsteroids;
	TextLabel* m_pTextLabel;


	float m_fLastTime;
	float m_fRoundStartTime;
	float m_fSplashScreenTimer;
	float m_fCollisionFlex = 0.3f; //collision detection flex value to account for texture being smaller than shape
	GLfloat m_GLfCurrentTime;

	//Textlabels to keep track of
	TextLabel* m_pTextTimer;
	TextLabel* m_pTextRoundOver;
	TextLabel* m_pTextControls;
	TextLabel* m_Player1ScoreText;
	TextLabel* m_Player2ScoreText;

	bool m_GameOver = false;
	bool m_StartNextRound = false;
	bool m_RoundTimerStarted = false;
	bool m_ShowSplashScreen = false;

};