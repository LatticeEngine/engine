#include "../../../include/Logger/Sink/ConsoleSink.h"
#include <iostream>

namespace lattice 
{
	void ConsoleSink::write(LogLevel logLvl, LogCategory logCategory, const std::string& msg, const std::string& timestamp)
	{
		std::string msgToPrint = getColorCodeFromLevel(logLvl) + timestamp + " - " + getStringLevel(logLvl) + " - " + getStringCategory(logCategory) + " - " + msg + _reset;
		std::cout << msgToPrint << std::endl;
	}

	std::string ConsoleSink::getColorCodeFromLevel(LogLevel logLvl)
	{
		switch (logLvl)
		{
		case lattice::LogLevel::INFO:
			return _reset;
		case lattice::LogLevel::DEBUG:
			return "\033[38;2;200;0;150m";
		case lattice::LogLevel::WARN:
			return "\033[38;2;240;170;40m";
		case lattice::LogLevel::ERROR:
			return "\033[38;2;255;70;70m";
		case lattice::LogLevel::CRITICAL:
			return "\033[38;2;255;0;0m";
		default:
			return "\033[38;2;0;255;0m";
		}
	}
}