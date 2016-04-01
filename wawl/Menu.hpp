#pragma once
#define ENABLE_WAWL_MENU

#include "BaseType.hpp"
#include "BaseUtility.hpp"
#include "MenuBaseType.hpp"
#include "Bitmap.hpp"

namespace wawl {
	namespace wnd {

		struct OEMMenuBarBitmap {
			static constexpr BitmapHandle Callback = HBMMENU_CALLBACK;
			static constexpr BitmapHandle Close = HBMMENU_MBAR_CLOSE;
			static constexpr BitmapHandle DisabledClose = HBMMENU_MBAR_CLOSE_D;
			static constexpr BitmapHandle Minimize = HBMMENU_MBAR_MINIMIZE;
			static constexpr BitmapHandle DisabledMinimize = HBMMENU_MBAR_MINIMIZE_D;
			static constexpr BitmapHandle Restore = HBMMENU_MBAR_RESTORE;
			static constexpr BitmapHandle System = HBMMENU_SYSTEM;
		};

		struct OEMPopupMenuBitmap {
			static constexpr BitmapHandle Callback = HBMMENU_CALLBACK;
			static constexpr BitmapHandle Close = HBMMENU_POPUP_CLOSE;
			static constexpr BitmapHandle Maximize = HBMMENU_POPUP_MAXIMIZE;
			static constexpr BitmapHandle Minimize = HBMMENU_POPUP_MINIMIZE;
			static constexpr BitmapHandle Restore = HBMMENU_POPUP_RESTORE;
			static constexpr BitmapHandle System = HBMMENU_SYSTEM;
		};

		static auto& createMenu = ::CreateMenu;
		static auto& createPopupMenu = ::CreatePopupMenu;

		inline MenuItemInfo makeMenuSeparator(Uint id, bool drawByOwer = false) {
			MenuItemInfo info = {};
			info.cbSize = sizeof(MenuItemInfo);
			info.fMask |= MIIM_FTYPE;
			info.fType = MFT_SEPARATOR;

			info.wID = id;
			if (drawByOwer)
				info.fType = MFT_OWNERDRAW;
		}

		inline MenuItemInfo makeMenuString(
			Uint id,
			Tstring& str,
			const MenuOption* options,
			const MenuState* states,
			Handle menuBmp,
			BitmapHandle checkMark,
			BitmapHandle uncheckMark,
			MenuHandle subMenu
			) {
			MenuItemInfo info = {};
			info.cbSize = sizeof(MenuItemInfo);

			info.fMask |= MIIM_STRING;
			info.dwTypeData = &str[0];

			if (options)
				info.fMask |= MIIM_FTYPE,
				info.fType |= unpackEnum(*options);
			if (states)
				info.fMask |= MIIM_STATE,
				info.fState |= unpackEnum(*states);
			if (menuBmp)
				info.fMask |= MIIM_BITMAP,
				info.hbmpItem = static_cast<::HBITMAP>(menuBmp);
			if (checkMark)
				info.fMask |= MIIM_CHECKMARKS,
				info.hbmpChecked = checkMark;
			if (uncheckMark)
				info.fMask |= MIIM_CHECKMARKS,
				info.hbmpUnchecked = uncheckMark;
			if (subMenu)
				info.fMask |= MIIM_SUBMENU,
				info.hSubMenu = subMenu;

			return info;
		}
		inline MenuItemInfo makeMenuString(Uint id, Tstring& str) {
			return
				makeMenuString(
					id,
					str,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr
					);
		}
		inline MenuItemInfo makeMenuString(
			Uint id,
			Tstring& str,
			MenuOption options,
			MenuState states
			) {
			return
				makeMenuString(
					id,
					str,
					&options,
					&states,
					nullptr,
					nullptr,
					nullptr,
					nullptr
					);
		}
		inline MenuItemInfo makeMenuString(
			Uint id,
			Tstring& str,
			MenuHandle subMenu
			) {
			return
				makeMenuString(
					id,
					str,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					subMenu
					);
		}
		inline MenuItemInfo makeMenuString(
			Uint id,
			Tstring& str,
			MenuOption options,
			MenuState states,
			MenuHandle subMenu
			) {
			return
				makeMenuString(
					id,
					str,
					&options,
					&states,
					nullptr,
					nullptr,
					nullptr,
					subMenu
					);
		}
		inline MenuItemInfo makeMenuString(
			Uint id,
			Tstring& str,
			MenuOption options,
			MenuState states,
			Handle menuBmp,
			BitmapHandle checkMark,
			BitmapHandle uncheckMark
			) {
			return
				makeMenuString(
					id,
					str,
					&options,
					&states,
					menuBmp,
					checkMark,
					uncheckMark,
					nullptr
					);
		}
		inline MenuItemInfo makeMenuString(
			Uint id,
			Tstring& str,
			MenuOption options,
			MenuState states,
			Handle menuBmp,
			BitmapHandle checkMark,
			BitmapHandle uncheckMark,
			MenuHandle subMenu
			) {
			return
				makeMenuString(
					id,
					str,
					&options,
					&states,
					menuBmp,
					checkMark,
					uncheckMark,
					subMenu
					);
		}

		inline bool addMenuItem(
			MenuHandle base,
			Uint id,
			Tstring& str,
			MenuHandle newItem
			) {
			auto child = makeMenuString(id, str, newItem);

			return
				::InsertMenuItem(
					base,
					id,
					false,
					&child
					) != 0;
		}

	} // ::wawl::wnd
} // ::wawl