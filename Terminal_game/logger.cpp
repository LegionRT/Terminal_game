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
		// В Windows localtime_s возвращает 0 при успешном выполнении
		if (localtime_s(&timeinfo, &t) == 0)
		{
			ofs << "--- Log started: " << std::put_time(&timeinfo, "%F %T") << " ---\n";
		}
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
	if (localtime_s(&timeinfo, &t) == 0)
	{
		ofs << "[" << std::put_time(&timeinfo, "%F %T") << "] " << msg << "\n";
	}
	ofs.flush();
}
