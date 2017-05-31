//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: SceneManager.h
// Description	: Allows for different "Scenes" to be created and controlled individually.
// Author		: Cameron Peet
// Mail			: Cameron.Peet@mediadesign.school.nz
//

#pragma once
#include "SceneManager.h"
#include "Menu.h"
#include "Game.h"

CSceneManager* CSceneManager::s_pGame = 0;

/**
*
* Constructor.
* (Task ID: Scene Manager)
*
* @author Cameron Peet
* @param void
* @return void
*
*/
CSceneManager::CSceneManager()
{

}

/**
*
* Destructor.
* (Task ID: Scene Manager)
*
* @author Cameron Peet
* @param void
* @return void
*
*/
CSceneManager::~CSceneManager()
{
	if (s_pGame != 0)
	{
		DestroyInstance();
	}
}

/**
*
* This function gets the instance.
* (Task ID: Scene Manager)
*
* @author Cameron Peet
* @param void
* @return Returns the scene manager.
*
*/
CSceneManager& CSceneManager::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CSceneManager;
	}
	return (*s_pGame);
}

/**
*
* This function destroys the instance.
* (Task ID: Scene Manager)
*
* @author Cameron Peet
* @param void
* @return void
*
*/
void CSceneManager::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

/**
*
* This function initialises the scene manager.
* (Task ID: Scene Manager)
*
* @author Cameron Peet
* @param void
* @return Returns true if successful, false if not..
*
*/
bool CSceneManager::Initialise()
{
	if (!m_bInit)
	{

		//m_pSceneMap.insert(std::pair<std::string, CScene*>("GameOver", new CGameOver()));
		//m_pSelectedScene = m_pSceneMap.find("GameOver")->second;
		//m_pSelectedScene->Init();

		m_pSceneMap.insert(std::pair<std::string, CScene*>("Game", new CGame()));
		m_pSelectedScene = m_pSceneMap.find("Game")->second;
		m_pSelectedScene->Init();

		m_pSceneMap.insert(std::pair<std::string, CScene*>("Menu", new CMenu()));
		m_pSelectedScene = m_pSceneMap.find("Menu")->second;
		m_pSelectedScene->Init();

		//CResources::LoopSound("TimeHansZimmer.mp3");
		CResources::LoopSound("MenuSound.wav");
		
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

/**
*
* This function selects the scene.
* (Task ID: Scene Manager)
*
* @author Cameron Peet and 
* @param _strSceneName
* @return Returns true if successful, false if not.
*
*/
bool CSceneManager::SelectScene(std::string _strSceneName)
{
	auto itr = m_pSceneMap.find(_strSceneName);
	if (itr == m_pSceneMap.end())
	{
		return false;
	}
	else
	{
		m_pSelectedScene = itr->second;

		if (_strSceneName == "Menu")
		{
			/*
			CResources::StopSound("End.mp3");
			CResources::StopSound("Credits.mp3");
			CResources::StopSound("ImitationGame.mp3");
			CResources::LoopSound("TimeHansZimmer.mp3");
			*/
			CResources::LoopSound("MenuSound.wav");
			CResources::StopSound("GameLoop.wav");
		}
		if (_strSceneName == "Game")
		{
			/*
			CResources::StopSound("End.mp3");
			CResources::StopSound("TimeHansZimmer.mp3");
			CResources::LoopSound("ImitationGame.mp3");
			*/
			CResources::LoopSound("GameLoop.wav");
			CResources::StopSound("MenuSound.wav");
		}
		if (_strSceneName == "GameOver")
		{
			CResources::StopSound("ImitationGame.mp3");
			CResources::LoopSound("End.mp3");
		}
		if (_strSceneName == "Credits")
		{
			CResources::StopSound("End.mp3");
			CResources::LoopSound("Credits.mp3");
		}

		return true;
	}
}

/**
*
* This function gets the scene with a particular name.
* (Task ID: Scene Manager)
*
* @author 
* @param _strSceneName
* @return Returns the scene.
*
*/
CScene* CSceneManager::GetScene(std::string _strSceneName)
{
	auto itr = m_pSceneMap.find(_strSceneName);
	if (itr == m_pSceneMap.end())
	{
		return nullptr;
	}
	else
	{
		return itr->second;
	}
}