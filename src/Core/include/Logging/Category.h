#pragma once

#include <cstdint>
#include <string_view>

namespace lattice::logging {
	enum class Category : std::uint8_t
	{
		Core = 0,
		Renderer,
		Audio,
		Physics
	};

	constexpr std::string_view toString(Category category)
	{
		switch (category)
		{
		case Category::Core:     return "CORE";
		case Category::Renderer: return "RENDERER";
		case Category::Audio:    return "AUDIO";
		case Category::Physics:  return "PHYSICS";
		}
		return "UNKNOWN";
	}
}
