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


#pragma once

#include "Scene.h"
#include "Entity.h"


class CMenu : public CScene
{
public:

	bool Init();
	void Render(GLuint program, Camera& camera);
	void Update(float fDeltaTime);
	//void NetworkProcess();
	void PassiveMotion(int x, int y);
	void Mouse(int button, int state, int x, int y);
	void KeyboardDown(unsigned char c, int x, int y);
	void KeyboardUp(unsigned char c, int x, int y);
	//bool FindGames();
	void Reshape(int width, int height);
	//void HostProcess();
	//void ClientProcess();
	void SetTextPositions();

	//std::vector<std::string> GetPlayers();  { return m_vecPlayerNames; }

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

	//For dynamic control over individual elements, easier understood by name rather than by index number of the vector.
	Model* m_pEditBox;

	//Vector for easier rendering
	std::vector<CEntity*> m_pEntities;

	float LowerYSpacing = 0.0f;

	int iSetupCount;
};