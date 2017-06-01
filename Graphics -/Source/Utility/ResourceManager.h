// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: ResourceManager.h
// Description	: Resource Manager declaration file
// Author		: Cameron Peet
// Mail			: Cameron.Peet@mediadesign.school.nz

#pragma once
#include <glew\glew.h>
#include <soil\SOIL.h>
#include <freetype\ft2build.h>
#include FT_FREETYPE_H  

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

#include "ShaderLoader.h"
#include "fmod/fmod.hpp"
#include "FileGetter.h"
#include "CLogger.h"
#include <map>

struct Character 
{
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

struct MyFont
{
	Character characters[128];
};

struct Texture
{
	int width, height;
	GLuint texture;
};


class CResources
{
public:

	/**
	*
	* This function adds the shader.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _strShaderName This is the shader name.
	* @param program This is the program.
	* @return void
	*
	*/
	static void AddShader(std::string _strShaderName, GLuint program)
	{
		Shaders.insert(std::pair<std::string, GLuint>(_strShaderName, program));
	}

	/**
	*
	* This function gets the program.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param void
	* @return Returns the program
	*
	*/
	static GLuint GetStandardProgram()
	{
		GLuint program = 0;
		program = Shaders.find("Shader")->second;
		return program;
	}

	/**
	*
	* This function gets the shader.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _strShaderName This is the shader name.
	* @param program This is the program.
	* @return Returns the true if successful, false if not.
	*
	*/
	static bool GetShader(std::string _strShaderName, GLuint& program)
	{
		auto itr = Shaders.find(_strShaderName);
		if (itr != Shaders.end())
		{
			program = itr->second;
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	*
	* This function adds the font.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param fontName This is the font name.
	* @param _FontArray This is the font array.
	* @return void
	*
	*/
	static void AddFont(std::string fontName, Character* _FontArray)
	{
		//Fonts.insert(std::pair<std::string, Character*>(fontName, _FontArray));
	}

	/**
	*
	* This function gets the font.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param fontName This is the font name.
	* @param _FontArray This is the font array.
	* @return Returns the true if successful, false if not.
	*
	*/
	static bool GetFont(std::string fontName, MyFont* _FontArray)
	{
		auto itr = Fonts.find(fontName);
		if (itr != Fonts.end())
		{
			for (GLubyte c = 0; c < 128; c++)
			{
				_FontArray->characters[c] = itr->second->characters[c];
			}
			return true;
			//_FontArray = itr->second;
		}
		else
		{
			return false;
		}
	}

	/**
	*
	* This function adds the texture.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _strName This is the name.
	* @param _ucTexture This is the texture.
	* @return void
	*
	*/
	static void AddTexture(std::string _strName, Texture _ucTexture)
	{
		Textures.insert(std::pair<std::string, Texture>(_strName, _ucTexture));
	}

	/**
	*
	* This function gets the texture.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _strName This is the name.
	* @param _ucTexture This is the texture.
	* @return Returns the true if successful, false if not.
	*
	*/
	static bool GetTexture(std::string _strName, Texture& _ucTexture)
	{
		auto itr = Textures.find(_strName);
		if (itr != Textures.end())
		{
			_ucTexture = itr->second;
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	*
	* This function loads all textures.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _void
	* @return Returns the true if successful, false if not.
	*
	*/
	static	bool LoadAllTextures()
	{
		if (!m_bTexturesLoaded)
		{
			Texture texture;
			std::string FolderPath = "Assets\\Textures";
			std::string FullPath;
			std::string FileName;
			FileGetter TexturesFolder("Assets\\Textures");
			while (TexturesFolder.getNextFile(FileName))
			{
				FullPath.clear();
				FullPath += FolderPath;
				FullPath += "\\";
				FullPath += FileName;
				unsigned char* image = SOIL_load_image(FullPath.c_str(), &texture.width, &texture.height, 0, SOIL_LOAD_RGB);
				if (image != 0)
				{

					glGenTextures(1, &texture.texture);
					glBindTexture(GL_TEXTURE_2D, texture.texture);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
					glGenerateMipmap(GL_TEXTURE_2D);
					SOIL_free_image_data(image);
					glBindTexture(GL_TEXTURE_2D, 0);

					CLogManager& Log = CLogManager::GetInstance();
					std::string success = "Texture Loaded: ";
					success += FileName;
					Log.WriteToAll(logTEXTURES, success);
					//return false;
					Textures.insert(std::pair<std::string, Texture>(FileName, texture));
				}
				else
				{
					CLogManager& Log = CLogManager::GetInstance();
					std::string error = "Failed to load texture: ";
					error += FileName;
					Log.WriteToAll(logERROR, error);
					//return false;
				}
			}
			m_bTexturesLoaded = true;
		}
		return m_bTexturesLoaded;
	}

	/**
	*
	* This function loads all fonts.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _void
	* @return Returns the true if successful, false if not.
	*
	*/
	static void LoadAllFonts()
	{
		std::string FolderPath = "Assets\\Fonts";
		std::string FullPath;
		std::string FileName;
		FileGetter FontsFolder("Assets\\Fonts");
		while (FontsFolder.getNextFile(FileName))
		{
			FullPath.clear();
			FullPath += FolderPath;
			FullPath += "\\";
			FullPath += FileName;
			std::string path = FullPath;
			// FreeType
			FT_Library ft;

			// All functions return a value different than 0 whenever an error occurred
			if (FT_Init_FreeType(&ft))
				std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			else
			{
				// Load font as face
				FT_Face face;
				if (path.size() != 0)
				{
					if (FT_New_Face(ft, path.c_str(), 0, &face))
					{
						CLogManager& Log = CLogManager::GetInstance();
						std::string error = "Failed to load font : ";
						error += FileName;
						Log.WriteToAll(logFONT, error);
					}
					else
					{
						MyFont* font = new MyFont();

						// Set size to load glyphs as
						FT_Set_Pixel_Sizes(face, 0, 48);

						// Disable byte-alignment restriction
						glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

						// Load first 128 characters of ASCII set
						for (GLubyte c = 0; c < 128; c++)
						{
							// Load character glyph 
							if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
								std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
								CLogManager& Log = CLogManager::GetInstance();
								std::string error = "Failed to load glyph : ";
								error += FileName;
								error += " - ";
								error += c;
								Log.WriteToAll(logFONT, error);
								continue;
							}
							else
							{
								// Generate texture
								GLuint texture;
								glGenTextures(1, &texture);
								glBindTexture(GL_TEXTURE_2D, texture);

								glTexImage2D(
									GL_TEXTURE_2D,
									0,
									GL_RED,
									face->glyph->bitmap.width,
									face->glyph->bitmap.rows,
									0,
									GL_RED,
									GL_UNSIGNED_BYTE,
									face->glyph->bitmap.buffer
									);
								// Set texture options
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
								// Now store character for later use

								font->characters[c] = {
									texture,
									glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
									glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
									static_cast<GLuint>(face->glyph->advance.x)
								};
							}
						}

						// Destroy FreeType once we're finished
						FT_Done_Face(face);
						FT_Done_FreeType(ft);

						Fonts.insert(std::pair<std::string, MyFont*>(FileName, font));
					}
					
				}
			}
		}
		
	}

	/**
	*
	* This function loads all sounds.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _void
	* @return Returns the true if successful, false if not.
	*
	*/
	static void LoadAllSounds()
	{
		InitFmod();
		std::string FolderPath = "Assets\\Audio";
		std::string FullPath;
		std::string FileName;
		FileGetter FontsFolder("Assets\\Audio");
		while (FontsFolder.getNextFile(FileName))
		{
			FullPath.clear();
			FullPath += FolderPath;
			FullPath += "\\";
			FullPath += FileName;
			std::string path = FullPath;

			FMOD_RESULT result;
			FMOD::Sound* sound;
			result = audioMgr->createSound(FullPath.c_str(), FMOD_DEFAULT, 0, &sound);
			if (result != FMOD_OK)
			{
				std::string error = "Failed to load sound : ";
				error += FileName;
				CLogManager& LogManager = CLogManager::GetInstance();
				LogManager.Write(logSOUND, error);
			}
			else
			{
				FMOD::Channel* channel = nullptr;
				Sounds.insert(std::pair<std::string, FMOD::Sound*>(FileName, sound));
				Channels.insert(std::pair<std::string, FMOD::Channel*>(FileName, channel));
				std::string success = "Loaded sound succefuly : ";
				success += FileName;
				CLogManager& LogManager = CLogManager::GetInstance();
				LogManager.Write(logSOUND, success);
			}
		}
	}

	/**
	*
	* This function plays audio.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _strSoundName This is the sound name.
	* @return Returns the true if successful, false if not.
	*
	*/
	static bool PlayAudio(std::string _strSoundName)
	{
		auto itr = Sounds.find(_strSoundName);
		if (itr != Sounds.end())
		{
			auto channel = Channels.find(_strSoundName);
			if (channel != Channels.end())
			{
				if (channel->second != nullptr)
				{
					bool* paused = 0;
					channel->second->getPaused(paused);
					if (paused)
					{
						channel->second->setPaused(false);
					}
					audioMgr->playSound(itr->second, 0, false, &channel->second);
				}
				else
				{
					audioMgr->playSound(itr->second, 0, false, &channel->second);
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	*
	* This function loops the audio.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _strSoundName This is the sound name.
	* @return Returns the true if successful, false if not.
	*
	*/
	static bool LoopSound(std::string _strSoundName)
	{
		auto itr = Sounds.find(_strSoundName);
		if (itr != Sounds.end())
		{
			auto channel = Channels.find(_strSoundName);
			if (channel != Channels.end())
			{
				if (channel->second != nullptr)
				{
					bool* paused = 0;
					channel->second->getPaused(paused);
					if (paused)
					{
						channel->second->setPaused(false);
					}
					else
					{
						audioMgr->playSound(itr->second, 0, false, &channel->second);
					}				
				}
				else
				{
					itr->second->setMode(FMOD_LOOP_NORMAL);
					audioMgr->playSound(itr->second, 0, false, &channel->second);
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	*
	* This function stops the audio.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _strSoundName This is the sound name.
	* @return Returns the true if successful, false if not.
	*
	*/
	static bool StopSound(std::string _strSoundName)
	{

		auto channel = Channels.find(_strSoundName);
		if (channel != Channels.end())
		{
			channel->second->stop();
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	*
	* This function pauses the audio.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param _strSoundName This is the sound name.
	* @return Returns the true if successful, false if not.
	*
	*/
	static bool PauseSound(std::string _strSoundName)
	{
		auto channel = Channels.find(_strSoundName);
		if (channel != Channels.end())
		{
			channel->second->setPaused(true);
			return true;
		}
		else
		{
			return false;
		}

	}

	/**
	*
	* This function initialises the audio.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param void
	* @return Returns the true if successful, false if not.
	*
	*/
	static bool InitFmod()
	{
		FMOD_RESULT result;

		result = FMOD::System_Create(&audioMgr);
		if (result != FMOD_OK) return false;

		result = audioMgr->init(50, FMOD_INIT_NORMAL, 0);
		if (result != FMOD_OK) return false;

		return true;
	}

	/**
	*
	* Destructor.
	* (Task ID: Resources)
	*
	* @author Cameron Peet
	* @param void
	* @return void
	*
	*/
	~CResources()
	{
		Fonts.clear();
		Shaders.clear();
		Textures.clear();
		Sounds.clear();
		Channels.clear();
	}
private:
	static std::map<std::string, GLuint> Shaders;
	static std::map<std::string, MyFont*> Fonts;
	static std::map<std::string, Texture> Textures;
	static std::map<std::string, FMOD::Sound*> Sounds;
	static std::map < std::string, FMOD::Channel*> Channels;
	static	FMOD::System* audioMgr;
	static bool m_bTexturesLoaded;
	static bool m_bSoundsLoaded;

};