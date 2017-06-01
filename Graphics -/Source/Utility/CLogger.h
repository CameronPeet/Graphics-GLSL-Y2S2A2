// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2016 Media Design School
// File Name	: CLogger
// Description	: Write to an INI file anywhere in a program by getting the log instance
// Author		: Cameron Peet


#ifndef _CLOGM_H_
#define _CLOGM_H_
#include <string>
#include <fstream>
#include <ctime>
#include <vector>



enum ELogLevel
{
	logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logMEMORYLEAK,
	logTEXTURES, logENTITY, logSCENE, logMAIN, logSOUND, logFONT
};

class CLogFile
{
public:
	CLogFile()
	{

	}
	~CLogFile()
	{
	
	}

	ELogLevel LogLevel;
	std::string m_strFileName;
	bool Initialise(std::string _strLogFileName)
	{
		std::fstream log_file(
			_strLogFileName, std::ios_base::out);
		m_strFileName = _strLogFileName;
		log_file.clear();
		Write("Log Created");
		log_file.close();
		return true;
	}
	void Write(std::string _strMessage)
	{
		std::fstream log_file(
			m_strFileName, std::ios_base::out | std::ios_base::app | std::ios_base::in);
		time_t rawtime;
		struct tm * timeinfo = new tm;
		char buffer[80];

		time(&rawtime);
		localtime_s(timeinfo, &rawtime);

		strftime(buffer, 80, "%I:%M%p.", timeinfo);

		log_file << " - " << buffer << "			" << _strMessage << std::endl;

		log_file.close();
	}

	void Write(ELogLevel eLogLevel, std::string _strMessage)
	{
		std::fstream log_file(
			m_strFileName, std::ios_base::out | std::ios_base::app | std::ios_base::in);
		time_t rawtime;
		struct tm * timeinfo = new tm;
		char buffer[80];

		time(&rawtime);
		localtime_s(timeinfo, &rawtime);

		strftime(buffer, 80, "%I:%M%p.", timeinfo);
		puts(buffer);

		log_file << " - " << buffer << " " << ToString(eLogLevel) << "		" << _strMessage << std::endl;
		log_file.close();
	}
	std::string ToString(ELogLevel eLogLevel)
	{
		switch (eLogLevel)
		{
		case logERROR:
			return "ERROR";
		case logWARNING:
			return "WARNING";
		case logINFO:
			return "INFO";
		case logDEBUG:
			return "DEBUG";
		case logDEBUG1:
			return "DEBUG1";
		case logDEBUG2:
			return "DEBUG2";
		case logDEBUG3:
			return "DEBUG3";
		case logMEMORYLEAK:
			return "MEMORY LEAK";
		case logTEXTURES:
			return "TEXTURES";
		case logMAIN:
			return "MAIN";
		case logENTITY:
			return "ENTITY";
		case logSCENE:
			return "SCENE";
		case logSOUND:
			return "SOUND";
		case logFONT:
			return "FONT";
		default:
			return "UNDEFINED";
		}
	}
	ELogLevel GetLogLevel() { return LogLevel; }
	void SetLogLevel(ELogLevel _eLogLevel) { LogLevel = _eLogLevel; }


protected:
private:

};
//Has a container for ILogTargets
class CLogManager
{
public:
	~CLogManager()
	{
		for (unsigned int i = 0; i < LogFiles.size(); i++)
		{
			delete LogFiles[i];
		}
	}
	static CLogManager& GetInstance() 
	{
		if (s_pLogManager == 0)
		{
			s_pLogManager = new CLogManager();

		}
		return *s_pLogManager; 
	}
	void AddLog(CLogFile* _logFile)
	{
		LogFiles.push_back(_logFile);
	}
	void RemoveLog(CLogFile* _logFile)
	{
		for (unsigned int i = 0; i < LogFiles.size(); i++)
		{
			if (LogFiles[i] == _logFile)
			{
				delete LogFiles[i];
			}
		}
	}
	void Write(std::string _strMessage)
	{
		LogFiles[0]->Write(_strMessage);
	}
	void Write(ELogLevel _eLogLevel, std::string _strMessage)
	{
		LogFiles[0]->Write(_eLogLevel, _strMessage);
	}

	void WriteToAll(std::string _strMessage)
	{
		for (unsigned int i = 0; i < LogFiles.size(); i++)
		{
			LogFiles[i]->Write(_strMessage);
		}
	}
	void WriteToAll(ELogLevel _eLogLevel, std::string _strMessage)
	{
		for (unsigned int i = 0; i < LogFiles.size(); i++)
		{
			LogFiles[i]->Write(_eLogLevel, _strMessage);
		}
	}
	std::vector<CLogFile*> LogFiles;
protected:
private:
	CLogManager()
	{
		CLogFile* MainLogFile = new CLogFile;
		MainLogFile->Initialise("MainLogFile.ini");
		LogFiles.push_back(MainLogFile);
	}

	static CLogManager* s_pLogManager;
};


#endif // _LOGS_H_