#pragma once

#include <string>
#include <chrono>

#include "../LogLevel.h"
#include "../LogCategory.h"

namespace lattice {
	class LogSink {
	public : 
		virtual ~LogSink() = default;
		virtual void write(LogLevel logLvl, LogCategory logCategory, const std::string& msg, const std::string& timestamp) = 0;
	protected:
		std::string getStringLevel(LogLevel logLvl);
		std::string getStringCategory(LogCategory logCategory);
	};
}