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
#include "Scene.h"

#include <ctime>
#include <iostream>
#include <vector>
#include <map>

//Scene manager
class CSceneManager
{
public:
	~CSceneManager();

	// Singleton Methods
	static CSceneManager& GetInstance();
	static void DestroyInstance();
	bool Initialise();
	CScene* GetScene() { return m_pSelectedScene; };
	CScene* m_pSelectedScene;
	bool SelectScene(std::string _strSceneName);
	CScene* GetScene(std::string _strSceneName);
	bool AddScene(CScene* _scene, std::string _strSceneName, bool _bMakeCurrent = false);

private:
	CSceneManager();
	CSceneManager(const CSceneManager& _kr);
	CSceneManager& operator= (const CSceneManager& _kr);

	std::map<std::string, CScene* > m_pSceneMap;
	bool m_bInit;
protected:

	// Singleton Instance
	static CSceneManager* s_pGame;

};