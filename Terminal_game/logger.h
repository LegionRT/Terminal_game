#pragma once
#include <string>
#include <fstream>

class Logger
{
public:
	static Logger& instance();
	void log(const std::string& msg);
private:
	Logger();
	~Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	std::ofstream ofs;
};