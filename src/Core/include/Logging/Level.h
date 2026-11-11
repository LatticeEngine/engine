#pragma once

#include <cstdint>
#include <string_view>

namespace lattice::logging {
	// Ordered from least to most severe: filtering keeps every level >= the minimum.
	// PascalCase values on purpose: <windows.h> defines an ERROR macro.
	enum class Level : std::uint8_t
	{
		Debug = 0,
		Info,
		Warn,
		Error,
		Critical
	};

	constexpr std::string_view toString(Level level)
	{
		switch (level)
		{
		case Level::Debug:    return "DEBUG";
		case Level::Info:     return "INFO";
		case Level::Warn:     return "WARNING";
		case Level::Error:    return "ERROR";
		case Level::Critical: return "CRITICAL";
		}
		return "UNKNOWN";
	}
}
