#pragma once

#include <string>
#include <vector>

#include "../LatticeSingleton.h"
#include "Sink/LogSink.h"
#include "LogLevel.h"
#include "LogCategory.h"


namespace lattice {
	class Logger : public Singleton<Logger>
	{
		friend class Singleton<Logger>;
	public:
		Logger();
		~Logger();

		static void printMsg(LogLevel level, LogCategory cat, const std::string& msg);

	protected:
		void createSinks();
		std::string getTimestamp();

	private:
		LogLevel _defaultLogLevel;

		std::string _lastMessage;
		int _repeatCount;
		std::vector<LogSink*> _logSinks;
	};
}