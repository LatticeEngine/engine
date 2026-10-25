#include "../../include/Logger/LatticeLogger.h"
#include "../../include/Logger/Sink/ConsoleSink.h"
#include "../../include/Logger/Sink/LogSink.h"

namespace lattice {
	Logger::Logger() :
		_defaultLogLevel(LogLevel::INFO),
		_lastMessage(""),
		_repeatCount(0)
	{
		createSinks();
	}

	Logger::~Logger()
	{
	}

	void Logger::createSinks()
	{
		_logSinks.push_back(new ConsoleSink());
	}

	std::string Logger::getTimestamp()
	{
		auto now = std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now());
		return std::format("{:%Y-%m-%d %H:%M:%S}", now);
	}
	
	void Logger::printMsg(LogLevel level, LogCategory cat, const std::string& msg)
	{
		Logger& logger = getInstance();

		if (logger._lastMessage == msg)
		{
			logger._repeatCount++;
			return;
		}

		std::string timestamp = logger.getTimestamp();
		/*if (logger._repeatCount > 0)
		{
			for (auto& sink : logger._logSinks)
				sink->write(level, cat, std::format("[repeated {} times]", logger._repeatCount), timestamp);

			logger._repeatCount = 0;
		}*/

		for (auto& sink : logger._logSinks)
			sink->write(level, cat, msg, timestamp);

		logger._lastMessage = msg;
	}
}