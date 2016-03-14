#pragma once
#define ENABLE_WAWL_WINDOWBASETYPE

#include "BaseType.hpp"

namespace wawl {
	namespace wnd {

		//Window表示形式
		enum class ShowMode : Uint16 {
			ForceMinimize = SW_FORCEMINIMIZE,
			Hide = SW_HIDE,
			Maximize = SW_MAXIMIZE,
			Minimize = SW_MINIMIZE,
			Restore = SW_RESTORE,
			Show = SW_SHOW,
			DefaultShow = SW_SHOWDEFAULT,
			MaximizedShow = SW_SHOWMAXIMIZED,
			MinimizedShow = SW_SHOWMINIMIZED,
			InactivateMinimized = SW_SHOWMINNOACTIVE,
			NoactivateShow = SW_SHOWNA,
			NormalShow = SW_SHOWNORMAL,
			NoactivateNormalShow = SW_SHOWNOACTIVATE
		};

	} // ::wawl::wnd
} // ::wawl