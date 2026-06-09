#include "logger.h"
#include <chrono>
#include <ctime>
#include <iomanip>

// Вспомогательная функция для безопасного получения локального времени
static std::tm get_local_time(std::time_t t)
{
	std::tm timeinfo;
#if defined(_MSC_VER) // Для Visual Studio (MSVC)
	localtime_s(&timeinfo, &t);
#elif defined(__STDC_LIB_EXT1__) || defined(__unix__) || defined(__APPLE__) // Для GCC / Clang (Linux/Mac)
	localtime_r(&t, &timeinfo);
#else // Резервный вариант, если ничего не подошло
	std::tm* ptr = std::localtime(&t);
	if (ptr) timeinfo = *ptr;
	else std::memset(&timeinfo, 0, sizeof(std::tm));
#endif
	return timeinfo;
}

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
		std::tm timeinfo = get_local_time(t);
		ofs << "--- Log started: " << std::put_time(&timeinfo, "%F %T") << " ---\n";
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
	std::tm timeinfo = get_local_time(t);
	ofs << "[" << std::put_time(&timeinfo, "%F %T") << "] " << msg << "\n";
	ofs.flush();
}
