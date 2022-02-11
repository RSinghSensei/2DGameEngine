#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <ctime>

class Logger {
public:

	static void Log(const char* message);
	// Elements with numbers
	static void sLog(const std::string& message);
	static void Error(const char* message);

private:
	static HANDLE logColChanger;

};