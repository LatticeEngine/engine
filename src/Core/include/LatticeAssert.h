#pragma once
#include <format>
#include "Logger/LatticeLogger.h"

#ifdef _DEBUG
#define LATTICE_ASSERT(condition, cat, msg) \
        do { \
            if (!(condition)) { \
                lattice::Logger::printMsg(lattice::LogLevel::CRITICAL, cat, \
                    std::format("Assertion failed: ({}) - {} [{}:{}]", #condition, msg, __FILE__, __LINE__)); \
                __debugbreak(); \
            } \
        } while (0)
#else
#define LATTICE_ASSERT(condition, cat, msg) ((void)0)
#endif