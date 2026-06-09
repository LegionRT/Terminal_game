#pragma once

#include <iostream>
#include <limits>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

inline void clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

inline void waitForEnter()
{
	std::cout << "Press Enter...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

inline void initConsole()
{
#ifdef _WIN32
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
#endif
}