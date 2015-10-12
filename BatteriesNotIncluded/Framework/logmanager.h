// 717310 C++ SDL Framework
#ifndef __LOGMANAGER_H__
#define __LOGMANAGER_H__

class LogManager
{
	//Member Methods:
public:
	static LogManager& GetInstance();
	~LogManager();

	void Log(const char* pcMessage);
protected:

private:
	LogManager();
	LogManager(const LogManager& logManager);
	LogManager& operator=(const LogManager& logManager);

	//Member Data:
public:

protected:
	static LogManager* sm_pInstance;

private:

};

#endif //__LOGMANAGER_H__
