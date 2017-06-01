//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: FileGetter.h
// Description	: File Getter declaration file
// Author		: Cameron Peet
// Mail			: Cameron.Peet@mediadesign.school.nz

#pragma once
#include <Windows.h>
#include <stdio.h>

class FileGetter{
	WIN32_FIND_DATAA found;
	HANDLE hfind;
	char folderstar[255];
	int chk;

public:
	FileGetter(char* folder){
		sprintf_s(folderstar, "%s\\*.*", folder);
		hfind = FindFirstFileA(folderstar, &found);
		//skip .
		FindNextFileA(hfind, &found);
	}

	int getNextFile(std::string&  fname){
		//skips .. when called for the first time
		chk = FindNextFileA(hfind, &found);
		if (chk)
			fname = found.cFileName;
		return chk;
	}

};