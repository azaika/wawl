#pragma once
#define ENABLE_WAWL_CONSOLE

#include "BaseType.hpp"

namespace wawl {
	namespace console {
		
		// console background color
		enum BkgColor : Uint32 {
			Blue = BACKGROUND_BLUE,
			Green = BACKGROUND_GREEN,
			Red = BACKGROUND_RED,
			Intensity = BACKGROUND_INTENSITY
		};

	} // ::wawl::console
} // ::wawl