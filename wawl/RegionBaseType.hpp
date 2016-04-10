#pragma once
#define ENABLE_WAWL_REGIONBASETYPE

#include "BaseType.hpp"

namespace wawl {
	namespace wnd {

		// region combine mode
		enum class CombineMode : int {
			And = RGN_AND,
			Copy = RGN_COPY,
			Dif = RGN_DIFF,
			Error = RGN_ERROR,
			Max = RGN_MAX,
			Min = RGN_MIN,
			Or = RGN_OR,
			Xor = RGN_XOR,
		};

		// result of combineRegion
		enum class CombineResult : int {
			Null = NULLREGION,
			Rectangle = SIMPLEREGION,
			Complex = COMPLEXREGION,
			Failed = ERROR
		};

		// region fill mode
		enum class FillMode : int {
			Alternate = ALTERNATE,
			Winding = WINDING
		};

		using RegionHandle = ::HRGN;

	}
}