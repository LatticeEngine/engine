#pragma once

#include <string_view>

#include "Logging/Level.h"
#include "Logging/Category.h"

namespace lattice::logging {
	// A destination for log messages. The Logger serialises calls to write(),
	// so a sink does not need its own locking.
	class Sink {
	public:
		virtual ~Sink() = default;
		virtual void write(Level level, Category category, std::string_view msg, std::string_view timestamp) = 0;
	};
}
