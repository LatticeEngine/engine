#include "Logging/Logger.h"

#include <chrono>

#include "Logging/Sink/ConsoleSink.h"

namespace lattice::logging {
	Logger::Logger() :
#ifdef LATTICE_DEBUG
		_minLevel(Level::Debug)
#else
		_minLevel(Level::Info)
#endif
	{
		_sinks.push_back(std::make_unique<ConsoleSink>());
	}

	Logger::~Logger()
	{
		flush();
	}

	void Logger::printMsg(Level level, Category cat, std::string_view msg)
	{
		getInstance().write(level, cat, msg);
	}

	void Logger::write(Level level, Category cat, std::string_view msg)
	{
		if (!isEnabled(level))
			return;

		std::string timestamp = getTimestamp();
		std::lock_guard lock(_mutex);

		if (_hasLast && level == _lastLevel && cat == _lastCategory && msg == _lastMessage)
		{
			++_repeatCount;
			return;
		}

		flushRepeatsLocked(timestamp);
		dispatchLocked(level, cat, msg, timestamp);

		_hasLast = true;
		_lastLevel = level;
		_lastCategory = cat;
		_lastMessage = msg;
	}

	void Logger::setMinLevel(Level level)
	{
		std::lock_guard lock(_mutex);
		_minLevel = level;
	}

	Level Logger::getMinLevel() const
	{
		std::lock_guard lock(_mutex);
		return _minLevel;
	}

	bool Logger::isEnabled(Level level) const
	{
		return level >= getMinLevel();
	}

	void Logger::addSink(std::unique_ptr<Sink> sink)
	{
		if (!sink)
			return;
		std::lock_guard lock(_mutex);
		_sinks.push_back(std::move(sink));
	}

	void Logger::clearSinks()
	{
		flush();
		std::lock_guard lock(_mutex);
		_sinks.clear();
	}

	void Logger::flush()
	{
		std::string timestamp = getTimestamp();
		std::lock_guard lock(_mutex);
		flushRepeatsLocked(timestamp);
		_hasLast = false;
		_lastMessage.clear();
	}

	void Logger::flushRepeatsLocked(std::string_view timestamp)
	{
		if (_repeatCount == 0)
			return;

		dispatchLocked(_lastLevel, _lastCategory,
			std::format("[repeated {} times] {}", _repeatCount, _lastMessage), timestamp);
		_repeatCount = 0;
	}

	void Logger::dispatchLocked(Level level, Category cat, std::string_view msg, std::string_view timestamp)
	{
		for (auto& sink : _sinks)
			sink->write(level, cat, msg, timestamp);
	}

	std::string Logger::getTimestamp()
	{
		auto now = std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now());
		return std::format("{:%Y-%m-%d %H:%M:%S}", now);
	}
}
