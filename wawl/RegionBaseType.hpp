#pragma once
#define ENABLE_WAWL_BITMAPBASETYPE

#include"Region.hpp"

namespace wawl {
	namespace wnd {

		enum class CombineMode {
			And = RGN_AND,
			Copy = RGN_COPY,
			Dif = RGN_DIFF,
			Error = RGN_ERROR,
			Max = RGN_MAX,
			Min = RGN_MIN,
			Or = RGN_OR,
			Xor = RGN_XOR,
		};

		enum class FillMode {
			Alternate = ALTERNATE,
			Winding = WINDING
		};

		using RegionData = ::HRGN;

	}
}