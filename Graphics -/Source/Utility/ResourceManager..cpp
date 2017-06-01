//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: ResourceManager.h
// Description	: Resource Manager implementation file.
// Author		: Cameron Peet
// Mail			: Cameron.Peet@mediadesign.school.nz
//

#pragma once
#include "ResourceManager.h"

std::map<std::string, GLuint> CResources::Shaders;
std::map<std::string, MyFont*> CResources::Fonts;
std::map<std::string, Texture> CResources::Textures;
std::map<std::string, FMOD::Sound*> CResources::Sounds;
std::map < std::string, FMOD::Channel*> CResources::Channels;
bool CResources::m_bSoundsLoaded;
bool CResources::m_bTexturesLoaded;
FMOD::System* CResources::audioMgr;