// 717310 C++ SDL Framework

// This include:
#include "logmanager.h"

// Library includes:
#include <Windows.h>

// Static Members:
LogManager* LogManager::sm_pInstance = 0;

LogManager& 
LogManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new LogManager();
	}

	return (*sm_pInstance);
}

LogManager::LogManager()
{

}

LogManager::~LogManager()
{

}

void 
LogManager::Log(const char* pcMessage)
{
	OutputDebugStringA(pcMessage);
	OutputDebugStringA("\n"); 
}
