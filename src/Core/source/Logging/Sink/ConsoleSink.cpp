#include "Logging/Sink/ConsoleSink.h"

#include <iostream>

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
	#include <windows.h>
#endif

namespace lattice::logging
{
	ConsoleSink::ConsoleSink()
	{
#ifdef _WIN32
		// The legacy Windows console only interprets ANSI colour codes once
		// virtual terminal processing is enabled.
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD mode = 0;
		if (out != INVALID_HANDLE_VALUE && GetConsoleMode(out, &mode))
			SetConsoleMode(out, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
	}

	void ConsoleSink::write(Level level, Category category, std::string_view msg, std::string_view timestamp)
	{
		std::cout << getColorCode(level) << timestamp
			<< " - [" << toString(level) << "] - [" << toString(category) << "] - "
			<< msg << _reset << '\n';

		// Make sure serious messages reach the console even if we crash right after.
		if (level >= Level::Error)
			std::cout.flush();
	}

	std::string_view ConsoleSink::getColorCode(Level level)
	{
		switch (level)
		{
		case Level::Debug:    return "\033[38;2;200;0;150m";
		case Level::Info:     return _reset;
		case Level::Warn:     return "\033[38;2;240;170;40m";
		case Level::Error:    return "\033[38;2;255;70;70m";
		case Level::Critical: return "\033[38;2;255;0;0m";
		}
		return _reset;
	}
}
