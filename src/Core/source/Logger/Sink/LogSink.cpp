#include "../../../include/Logger/Sink/LogSink.h"

namespace lattice {
	std::string LogSink::getStringLevel(LogLevel logLvl)
	{
		switch (logLvl)
		{
		case lattice::LogLevel::INFO:
			return "[INFO]";
		case lattice::LogLevel::DEBUG:
			return "[DEBUG]";
		case lattice::LogLevel::WARN:
			return "[WARNING]";
		case lattice::LogLevel::ERROR:
			return "[ERROR]";
		case lattice::LogLevel::CRITICAL:
			return "[CRITICAL]";
		default:
			return "[UNKNOWN]";
		}
	}

	std::string LogSink::getStringCategory(LogCategory logCategory)
	{
		switch (logCategory)
		{
		case lattice::LogCategory::CORE:
			return "[CORE]";
		case lattice::LogCategory::RENDERER:
			return "[RENDERER]";
		case lattice::LogCategory::AUDIO:
			return "[AUDIO]";
		case lattice::LogCategory::PHYSICS:
			return "[PHYSICS]";
		default:
			return "[UNKNOWN]";
		}
	}
}