#pragma once
#define WAWL_CURSOR_BASE_TYPE_HPP

#include "BaseType.hpp"

namespace wawl {
	namespace wnd {

		using CursorHandle = ::HCURSOR;

		using OEMCursorType = Tchar*;
		// default cursor icon
		struct OEMCursor {
			static constexpr OEMCursorType Arrow = IDC_ARROW;
			static constexpr OEMCursorType Cross = IDC_CROSS;
			static constexpr OEMCursorType IBeam = IDC_IBEAM;
			static constexpr OEMCursorType Wait = IDC_WAIT;
		};

	} // ::wawl::wnd
} // ::wawl