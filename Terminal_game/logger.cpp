#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "logger.h"
#include <chrono>
#include <ctime>
#include <iomanip>

Logger& Logger::instance()
{
	static Logger lg;
	return lg;
}

Logger::Logger()
{
	ofs.open("game_log.txt", std::ios::out | std::ios::app);
	if (ofs)
	{
		auto now = std::chrono::system_clock::now();
		std::time_t t = std::chrono::system_clock::to_time_t(now);

		std::tm timeinfo;
#ifdef _MSC_VER
		// Только для Visual Studio
		if (localtime_s(&timeinfo, &t) == 0)
#else
		// Универсальный способ для MinGW и Linux
		std::tm* ptr = std::localtime(&t);
		if (ptr) {
			timeinfo = *ptr;
#endif
			{
				ofs << "--- Log started: " << std::put_time(&timeinfo, "%F %T") << " ---\n";
			}
#ifndef _MSC_VER
		}
#endif
	}
}

Logger::~Logger()
{
	if (ofs)
	{
		ofs << "--- Log closed ---\n";
		ofs.close();
	}
}

void Logger::log(const std::string& msg)
{
	if (!ofs)
		return;

	auto now = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(now);

	std::tm timeinfo;
#ifdef _MSC_VER
	if (localtime_s(&timeinfo, &t) == 0)
#else
	std::tm* ptr = std::localtime(&t);
	if (ptr) {
		timeinfo = *ptr;
#endif
		{
			ofs << "[" << std::put_time(&timeinfo, "%F %T") << "] " << msg << "\n";
		}
#ifndef _MSC_VER
	}
#endif
	ofs.flush();
}