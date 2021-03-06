﻿#pragma once
#define WAWL_CURSOR_BASE_TYPE_HPP

#include "BaseType.hpp"

namespace wawl {
	namespace wnd {

		using CursorHandle = ::HCURSOR;

		// default cursor icon
		struct OEMCursor {
			static constexpr Tchar* Arrow = IDC_ARROW;
			static constexpr Tchar* Cross = IDC_CROSS;
			static constexpr Tchar* IBeam = IDC_IBEAM;
			static constexpr Tchar* Wait = IDC_WAIT;
		};

	} // ::wawl::wnd
} // ::wawl