#pragma once

#include <format>

#include "Logging/Logger.h"

#if defined(_MSC_VER)
	#define LATTICE_DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
	#define LATTICE_DEBUG_BREAK() __builtin_trap()
#else
	#include <cstdlib>
	#define LATTICE_DEBUG_BREAK() std::abort()
#endif

// Usage: LATTICE_ASSERT(ptr != nullptr, Renderer, "Texture must be loaded");
// The category is a bare name, as in the LATTICE_LOG_* macros.
// LATTICE_DEBUG is defined by CMake for Debug builds (see src/CMakeLists.txt).
#ifdef LATTICE_DEBUG
#define LATTICE_ASSERT(condition, cat, msg) \
	do { \
		if (!(condition)) { \
			::lattice::Logger::printMsg(::lattice::logging::Level::Critical, ::lattice::logging::Category::cat, \
				std::format("Assertion failed: ({}) - {} [{}:{}]", #condition, msg, __FILE__, __LINE__)); \
			::lattice::Logger::getInstance().flush(); \
			LATTICE_DEBUG_BREAK(); \
		} \
	} while (0)
#else
// sizeof keeps the condition "used" (no unused-variable warnings) without evaluating it.
#define LATTICE_ASSERT(condition, cat, msg) ((void)sizeof(!(condition)))
#endif
