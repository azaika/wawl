#pragma once
#define ENABLE_WAWL_MENUBASETYPE

#include "BaseType.hpp"

namespace wawl {
	namespace wnd {

		using MenuHandle = ::HMENU;

		enum class MenuOption : Uint {
			LineBreak = MFT_MENUBARBREAK,
			Break = MFT_MENUBREAK,
			OwnerDraw = MFT_OWNERDRAW,
			RightJustify = MFT_RIGHTJUSTIFY,
			RightOrder = MFT_RIGHTORDER
		};

		enum class MenuState : Uint {
			Clear = 0,
			Check = MFS_CHECKED,
			Default = MFS_DEFAULT,
			Disable = MFS_DISABLED,
			Hilite = MFS_HILITE
		};

		using MenuItemInfo = ::MENUITEMINFO;

	} // ::wawl::wnd
} // ::wawl