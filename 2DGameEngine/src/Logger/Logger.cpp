#include "Logger.h"

#define DEFAULT "\Esc[0m"
#define RED "\Esc[31m"
#define GREEN "\Esc[92m"
#define BLUE "\Esc[34m"

HANDLE Logger::logColChanger = GetStdHandle(STD_OUTPUT_HANDLE);

void Logger::Log(const char* message)
{
	SetConsoleTextAttribute(logColChanger, 2);
	time_t timeVal = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string sysTime = std::ctime(&timeVal);
	sysTime[sysTime.size() - 2] = ']'; sysTime[sysTime.size() - 1] = '\0';
	std::cout << "LOG | [" << sysTime << " - " << message << std::endl;
	SetConsoleTextAttribute(logColChanger, 7);
}

void Logger::sLog(const std::string& message)
{
	SetConsoleTextAttribute(logColChanger, 9);
	time_t timeVal = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string sysTime = std::ctime(&timeVal);
	sysTime[sysTime.size() - 2] = ']'; sysTime[sysTime.size() - 1] = '\0';
	std::cout << "LOG | [" << sysTime << " - " << message << std::endl;
	SetConsoleTextAttribute(logColChanger, 7);

}

void Logger::Error(const char* message)
{
	SetConsoleTextAttribute(logColChanger, 4);
	time_t timeVal = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string sysTime = std::ctime(&timeVal);
	sysTime[sysTime.size() - 2] = ']'; sysTime[sysTime.size() - 1] = '\0';
	std::cerr << "LOG | [" << sysTime << " - " << message << std::endl;
	SetConsoleTextAttribute(logColChanger, 7);
}