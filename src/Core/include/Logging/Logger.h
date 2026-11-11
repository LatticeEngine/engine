#pragma once

#include <format>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "LatticeSingleton.h"
#include "Logging/Sink/Sink.h"
#include "Logging/Level.h"
#include "Logging/Category.h"

namespace lattice::logging {
	// Thread-safe logger. Consecutive identical messages (same level, category
	// and text) are collapsed into a single "[repeated N times]" line.
	class Logger : public Singleton<Logger>
	{
		friend class Singleton<Logger>;
	public:
		// Formatted logging: Logger::log(Level::Info, Category::Core, "x = {}", x);
		template <typename... Args>
		static void log(Level level, Category cat, std::format_string<Args...> fmt, Args&&... args)
		{
			Logger& logger = getInstance();
			if (!logger.isEnabled(level))
				return;
			logger.write(level, cat, std::format(fmt, std::forward<Args>(args)...));
		}

		static void printMsg(Level level, Category cat, std::string_view msg);

		void write(Level level, Category cat, std::string_view msg);

		void setMinLevel(Level level);
		Level getMinLevel() const;
		bool isEnabled(Level level) const;

		void addSink(std::unique_ptr<Sink> sink);
		// Flushes any pending repeat count, then removes every sink.
		void clearSinks();
		// Emits the pending "[repeated N times]" line, if any, and forgets the last message.
		void flush();

	private:
		Logger();
		~Logger();

		void flushRepeatsLocked(std::string_view timestamp);
		void dispatchLocked(Level level, Category cat, std::string_view msg, std::string_view timestamp);
		static std::string getTimestamp();

		mutable std::mutex _mutex;
		Level _minLevel;
		std::vector<std::unique_ptr<Sink>> _sinks;

		// Deduplication state.
		bool _hasLast = false;
		Level _lastLevel = Level::Info;
		Category _lastCategory = Category::Core;
		std::string _lastMessage;
		int _repeatCount = 0;
	};
}

namespace lattice {
	// Short name for code outside the logging module: lattice::Logger.
	using Logger = logging::Logger;
}

#define LATTICE_LOG_DEBUG(cat, ...)    ::lattice::Logger::log(::lattice::logging::Level::Debug,    ::lattice::logging::Category::cat, __VA_ARGS__)
#define LATTICE_LOG_INFO(cat, ...)     ::lattice::Logger::log(::lattice::logging::Level::Info,     ::lattice::logging::Category::cat, __VA_ARGS__)
#define LATTICE_LOG_WARN(cat, ...)     ::lattice::Logger::log(::lattice::logging::Level::Warn,     ::lattice::logging::Category::cat, __VA_ARGS__)
#define LATTICE_LOG_ERROR(cat, ...)    ::lattice::Logger::log(::lattice::logging::Level::Error,    ::lattice::logging::Category::cat, __VA_ARGS__)
#define LATTICE_LOG_CRITICAL(cat, ...) ::lattice::Logger::log(::lattice::logging::Level::Critical, ::lattice::logging::Category::cat, __VA_ARGS__)
