#pragma once
#define ENBALE_WAWL_CONSOLEBASETYPE

#include "BaseType.hpp"

namespace wawl {
	namespace fs {
		namespace console {

			// console background color
			enum class BkgColor : Uint32 {
				Blue = BACKGROUND_BLUE,
				Green = BACKGROUND_GREEN,
				Red = BACKGROUND_RED,
				Intensity = BACKGROUND_INTENSITY
			};

			// console string color
			enum class StrColor : Uint32 {
				Blue = FOREGROUND_BLUE,
				Green = FOREGROUND_GREEN,
				Red = FOREGROUND_RED,
				Intensify = FOREGROUND_INTENSITY
			};

		} // wawl::fs::console
	} // ::wawl::fs
} // ::wawl