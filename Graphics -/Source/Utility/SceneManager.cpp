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
#include "utils.h"
#include "CLogger.h"

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
* @author Cameron Peet and Charmaine Lim
* @param _strSceneName
* @return Returns true if successful, false if not.
*
*/
bool CSceneManager::SelectScene(std::string _strSceneName)
{
	auto itr = m_pSceneMap.find(_strSceneName);
	if (itr == m_pSceneMap.end())
	{
		CLogManager::GetInstance().Write(logSCENE, "Could not fine scene named : " + _strSceneName);
		return false;
	}
	else
	{
		m_pSelectedScene = itr->second;
		CLogManager::GetInstance().Write(logSCENE, "Scene Loaded: " + _strSceneName);
		return true;
	}
}

/**
*
* This function gets the scene with a particular name.
* (Task ID: Scene Manager)
*
* @author Charmaine Lim
* @param _strSceneName
* @return Returns the scene.
*
*/
CScene* CSceneManager::GetScene(std::string _strSceneName)
{
	auto itr = m_pSceneMap.find(_strSceneName);
	if (itr == m_pSceneMap.end())
	{
		CLogManager::GetInstance().Write(logSCENE, "Could not fine scene named : " + _strSceneName);
		return nullptr;
	}
	else
	{
		m_pSelectedScene = itr->second;
		CLogManager::GetInstance().Write(logSCENE, "Scene Loaded: " + _strSceneName);
		return itr->second;
	}
}

bool CSceneManager::AddScene(CScene* _scene, std::string _strSceneName, bool _bMakeCurrent)
{
	VALIDATE(_scene->Init());
	m_pSceneMap.insert(std::pair<std::string, CScene*>(_strSceneName, _scene));
	std::map<std::string, CScene*>::iterator it = m_pSceneMap.find(_strSceneName);
	if (it == m_pSceneMap.end())
	{
		CLogManager::GetInstance().Write(logSCENE, "Failed to add scene: " + _strSceneName + " to the SceneManager");
		return false;
	}
	
	CLogManager::GetInstance().Write(logSCENE, "Added scene: " + _strSceneName + " to the SceneManager");

	if (_bMakeCurrent)
	{
		CLogManager::GetInstance().Write(logSCENE, _strSceneName + " was made the Selected Scene");
		m_pSelectedScene = it->second;
	}

	return true;
}