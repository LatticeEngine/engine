#pragma once

#include <string_view>

#include "Logging/Sink/Sink.h"

namespace lattice::logging
{
	class ConsoleSink : public Sink {
	public:
		ConsoleSink();

		void write(Level level, Category category, std::string_view msg, std::string_view timestamp) override;

		static std::string_view getColorCode(Level level);

	private:
		static constexpr std::string_view _reset = "\033[0m";
	};
}
