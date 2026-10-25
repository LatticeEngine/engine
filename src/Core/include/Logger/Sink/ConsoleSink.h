#pragma once

#include "LogSink.h"

namespace lattice
{
	class ConsoleSink : public LogSink {
	public :
		ConsoleSink() : LogSink() {}

		void write(LogLevel logLvl, LogCategory logCategory, const std::string& msg, const std::string& timestamp) override;
		std::string getColorCodeFromLevel(LogLevel logLvl);
	private:
		std::string _reset = "\033[0m";
	};
}
