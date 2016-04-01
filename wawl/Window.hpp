#pragma once
#define ENABLE_WAWL_WINDOW

#include "WindowBaseType.hpp"
#include "Cursor.hpp"
#include "Icon.hpp"
#include "Menu.hpp"
#include "BaseUtility.hpp"

namespace wawl {
	namespace wnd {

		using Property = ::WNDCLASSEX;

		inline Property makeProperty(
			const Tstring& name,
			ProcFunc& procFunc,
			AppHandle app,
			PropOption* options,
			IconHandle icon,
			IconHandle smallIcon,
			CursorHandle cursor,
			ColorBrush* bkgColor,
			const Tstring* menuName
			) {
			Property prop = {};
			prop.cbSize = sizeof(Property);
			prop.lpfnWndProc = procFunc;
			prop.hInstance = app;
			prop.lpszClassName = name.c_str();

			if (options)
				prop.style = unpackEnum(*options);
			if (icon)
				prop.hIcon = icon;
			if (smallIcon)
				prop.hIconSm = smallIcon;
			if (bkgColor)
				prop.hbrBackground = reinterpret_cast<::HBRUSH>(::GetStockObject(unpackEnum(*bkgColor)));
			if (menuName)
				prop.lpszMenuName = menuName->c_str();

			return std::move(prop);
		}
		inline Property makeProperty(
			const Tstring& name,
			ProcFunc& procFunc,
			AppHandle app,
			PropOption options,
			IconHandle icon,
			IconHandle smallIcon,
			CursorHandle cursor,
			ColorBrush bkgColor
			) {
			return
				makeProperty(
					name,
					procFunc,
					app,
					&options,
					icon,
					smallIcon,
					cursor,
					&bkgColor,
					nullptr
					);
		}
		inline Property makeProperty(
			const Tstring& name,
			ProcFunc& procFunc,
			AppHandle app,
			PropOption options,
			IconHandle icon,
			IconHandle smallIcon,
			CursorHandle cursor,
			ColorBrush bkgColor,
			const Tstring& menuName
			) {
			return
				makeProperty(
					name,
					procFunc,
					app,
					nullptr,
					nullptr,
					smallIcon,
					cursor,
					&bkgColor,
					&menuName
					);
		}

		inline Uint16 registerProperty(const Property& prop) {
			return ::RegisterClassEx(&prop);
		}

		static constexpr Position DefaultWindowPos = { CW_USEDEFAULT, CW_USEDEFAULT };

		inline WindowHandle createWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rectangle& wndRect,
			const Option* options,
			const ExtOption* extOptions,
			MenuHandle menu,
			const CreateStruct* createStruct
			) {
			return
				::CreateWindowEx(
					(extOptions ? unpackEnum(*extOptions) : 0),
					propName.c_str(),
					title.c_str(),
					(options ? unpackEnum(*options) : 0),
					wndRect.x,
					wndRect.y,
					wndRect.w,
					wndRect.h,
					nullptr,
					menu,
					nullptr,
					(createStruct ? const_cast<CreateStruct*>(createStruct) : nullptr)
					);
		}
		inline WindowHandle createWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rectangle& wndRect
			) {
			return
				createWindow(
					propName,
					title,
					wndRect,
					nullptr,
					nullptr,
					nullptr,
					nullptr
					);
		}
		inline WindowHandle createWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rectangle& wndRect,
			Option options
			) {
			return
				createWindow(
					propName,
					title,
					wndRect,
					&options,
					nullptr,
					nullptr,
					nullptr
					);
		}
		inline WindowHandle createWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rectangle& wndRect,
			Option options,
			ExtOption extOptions,
			MenuHandle menu
			) {
			return
				createWindow(
					propName,
					title,
					wndRect,
					&options,
					&extOptions,
					menu,
					nullptr
					);
		}
		inline WindowHandle createWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rectangle& wndRect,
			Option options,
			ExtOption extOptions,
			MenuHandle menu,
			const CreateStruct& createStruct
			) {
			return
				createWindow(
					propName,
					title,
					wndRect,
					&options,
					&extOptions,
					menu,
					&createStruct
					);
		}

		inline WindowHandle createChildWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rectangle& wndRect,
			WindowHandle parent,
			ChildID myID,
			const Option* options,
			const ExtOption* extOptions,
			const CreateStruct* createStruct
			) {
			return
				::CreateWindowEx(
					(extOptions ? unpackEnum(*extOptions) : 0),
					propName.c_str(),
					title.c_str(),
					(options ? unpackEnum(*options) : 0),
					wndRect.x,
					wndRect.y,
					wndRect.w,
					wndRect.h,
					parent,
					myID,
					nullptr,
					(createStruct ? const_cast<CreateStruct*>(createStruct) : nullptr)
					);
		}
		inline WindowHandle createChildWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rectangle& wndRect,
			WindowHandle parent,
			ChildID myID
			) {
			return
				createChildWindow(
					propName,
					title,
					wndRect,
					parent,
					myID,
					nullptr,
					nullptr,
					nullptr
					);
		}
		inline WindowHandle createChildWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rectangle& wndRect,
			WindowHandle parent,
			ChildID myID,
			Option options,
			ExtOption extOptions
			) {
			return
				createChildWindow(
					propName,
					title,
					wndRect,
					parent,
					myID,
					&options,
					&extOptions,
					nullptr
					);
		}
		inline WindowHandle createChildWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rectangle& wndRect,
			WindowHandle parent,
			ChildID myID,
			Option options,
			ExtOption extOptions,
			const CreateStruct& createStruct
			) {
			return
				createChildWindow(
					propName,
					title,
					wndRect,
					parent,
					myID,
					&options,
					&extOptions,
					&createStruct
					);
		}

		inline bool setRect(WindowHandle window, const Rectangle& rect, bool doRedraw = true) {
			return ::MoveWindow(window, rect.x, rect.y, rect.w, rect.h, doRedraw) != 0;
		}
		inline Rectangle getRect(WindowHandle window) {
			::RECT rect = {};

			bool res =
				::GetWindowRect(
					window,
					&rect
					) != 0;

			return { rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top };
		}

		inline bool moveWindow(WindowHandle window, const Position& newPos, bool doRedraw = false) {
			Rectangle&& old = getRect(window);

			return ::MoveWindow(window, newPos.x, newPos.y, old.h, old.w, doRedraw) != 0;
		}

		inline bool resizeWindow(WindowHandle window, const Size& newSize, bool doRedraw = true) {
			Rectangle&& old = getRect(window);

			return ::MoveWindow(window, old.x, old.y, newSize.x, newSize.y, doRedraw) != 0;
		}

		inline bool setShowWindow(WindowHandle window, ShowMode mode) {
			return ::ShowWindow(window, unpackEnum(mode)) != 0;
		}

		inline Option getStyle(WindowHandle window) {
			return static_cast<Option>(::GetWindowLong(window, GWL_STYLE));
		}

		inline Position toScreenPos(WindowHandle window, const Position& clientPos) {
			::LPPOINT posBuf;
			posBuf->x = clientPos.x;
			posBuf->y = clientPos.y;

			::ClientToScreen(window, posBuf);

			return{ posBuf->x, posBuf->y };
		}
		inline Position toClientPos(WindowHandle window, const Position& screenPos) {
			::LPPOINT posBuf;
			posBuf->x = screenPos.x;
			posBuf->y = screenPos.y;

			::ScreenToClient(window, posBuf);

			return{ posBuf->x, posBuf->y };
		}

		inline LongPtr defaultProc(WindowHandle window, Msg msg, UintPtr lp, IntPtr rp) {
			return ::DefWindowProc(window, unpackEnum(msg), lp, rp);
		}

	} // ::wawl::wnd
} // ::wawl