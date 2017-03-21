#pragma once

#include "Scene.h"
#include "Player.h"


class CGame : public CScene
{
	bool Init();
	void Render(GLuint program, Camera& camera);
	void Update(float fDeltaTime);
	void PassiveMotion(int x, int y);
	void Mouse(int button, int state, int x, int y);
	void KeyboardDown(unsigned char c, int x, int y);
	void KeyboardUp(unsigned char c, int x, int y);
	void Reshape(int width, int height);
	void SetTextPositions();


private:

	std::string m_strMenuName;
	std::string m_strServerName;

	std::vector<std::vector<TextLabel*>*> m_pAllText;
	//Vector for easier rendering, re-assigned according to menu depth
	std::vector<TextLabel*>* m_pCurrentMenu = &m_pMainMenu;
	//Vectors to seperate the different menu depths
	std::vector<TextLabel*> m_pMainMenu;

	//Vector for easier rendering
	std::vector<Model*> m_pModels;

	Camera *m_Camera;

	CPlayer* m_pPlayer1;
	CPlayer* m_pPlayer2;
};