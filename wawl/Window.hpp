#pragma once
#define ENABLE_WAWL_WINDOW

#include "WindowBaseType.hpp"
#include "Cursor.hpp"
#include "Icon.hpp"
#include "Menu.hpp"
#include "BaseUtility.hpp"

namespace wawl {
	namespace wnd {

		struct Property : ::WNDCLASSEX {
			Property(
				const Tstring& name,
				MsgProc& procFunc,
				AppHandle app,
				UnifyEnum<PropOption> options,
				IconHandle icon,
				IconHandle smallIcon,
				CursorHandle cursor,
				ColorBrush bkgColor
			) :
				Property(
					name,
					procFunc,
					app,
					&options,
					icon,
					smallIcon,
					cursor,
					&bkgColor,
					nullptr
				) {}

		private:
			Property(
				const Tstring& name,
				MsgProc& procFunc,
				AppHandle app,
				UnifyEnum<PropOption>* options,
				IconHandle icon,
				IconHandle smallIcon,
				CursorHandle cursor,
				ColorBrush* bkgColor,
				const Tstring* menuName
			) {
				cbSize = sizeof(Property);
				lpfnWndProc = procFunc;
				hInstance = app;
				lpszClassName = name.c_str();

				if (options)
					style = options->get();
				if (icon)
					hIcon = icon;
				if (smallIcon)
					hIconSm = smallIcon;
				if (bkgColor)
					hbrBackground = reinterpret_cast<::HBRUSH>(::GetStockObject(unpackEnum(*bkgColor)));
				if (menuName)
					lpszMenuName = menuName->c_str();
			}
			Property(
				const Tstring& name,
				MsgProc& procFunc,
				AppHandle app,
				UnifyEnum<PropOption> options,
				IconHandle icon,
				IconHandle smallIcon,
				CursorHandle cursor,
				ColorBrush bkgColor,
				const Tstring& menuName
			) :
				Property(
					name,
					procFunc,
					app,
					&options,
					icon,
					smallIcon,
					cursor,
					&bkgColor,
					&menuName
				) {}

		};

		inline std::uint16_t registerProperty(const Property& prop) {
			return ::RegisterClassEx(&prop);
		}

		static constexpr Position DefaultWindowPos = { CW_USEDEFAULT, CW_USEDEFAULT };

		inline WindowHandle createWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rect& wndRect,
			const UnifyEnum<Option>* options,
			const UnifyEnum<ExtOption>* extOptions,
			MenuHandle menu,
			const CreateStruct* createStruct
			) {
			return
				::CreateWindowEx(
					(extOptions ? extOptions->get() : 0),
					propName.c_str(),
					title.c_str(),
					(options ? options->get() : 0),
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
			const Rect& wndRect
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
			const Rect& wndRect,
			UnifyEnum<Option> options
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
			const Rect& wndRect,
			UnifyEnum<Option> options,
			UnifyEnum<ExtOption> extOptions,
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
			const Rect& wndRect,
			UnifyEnum<Option> options,
			UnifyEnum<ExtOption> extOptions,
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
			const Rect& wndRect,
			WindowHandle parent,
			ChildID myID,
			const UnifyEnum<Option>* options,
			const UnifyEnum<ExtOption>* extOptions,
			const CreateStruct* createStruct
			) {
			return
				::CreateWindowEx(
					(extOptions ? extOptions->get() : 0),
					propName.c_str(),
					title.c_str(),
					(options ? options->get() : 0),
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
			const Rect& wndRect,
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
			const Rect& wndRect,
			WindowHandle parent,
			ChildID myID,
			UnifyEnum<Option> options,
			UnifyEnum<ExtOption> extOptions
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
			const Rect& wndRect,
			WindowHandle parent,
			ChildID myID,
			UnifyEnum<Option> options,
			UnifyEnum<ExtOption> extOptions,
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

		inline Rect getWindowRect(WindowHandle window) {
			::RECT rect = {};

			bool res =
				::GetWindowRect(
					window,
					&rect
				) != 0;

			return{ rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top };
		}
		inline Rect getClientRect(WindowHandle window) {
			::RECT rect = {};

			bool res =
				::GetClientRect(
					window,
					&rect
				) != 0;

			return{ rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top };
		}

		// set window potision and size
		inline bool setWindowRect(WindowHandle window, const Rect& newRect, bool doRedraw = true) {
			return ::MoveWindow(window, newRect.x, newRect.y, newRect.w, newRect.h, doRedraw) != 0;
		}
		// set client potision and size
		inline bool setClientRect(WindowHandle window, const Rect& newRect, bool doRedraw = true) {
			Rect oldRect = getWindowRect(window);
			Rect oldScreen = getClientRect(window);

			return
				::MoveWindow(
					window,
					oldRect.x,
					oldRect.y,
					oldRect.w - oldScreen.w + newRect.w,
					oldRect.h - oldScreen.h + newRect.h,
					doRedraw
				) != 0;
		}
		
		// set window position
		inline bool setPos(WindowHandle window, const Position& newPos, bool doRedraw = false) {
			Rect&& old = getWindowRect(window);

			return ::MoveWindow(window, newPos.x, newPos.y, old.h, old.w, doRedraw) != 0;
		}

		// resize window
		inline bool resize(WindowHandle window, const Size& newSize, bool doRedraw = true) {
			Rect&& old = getWindowRect(window);

			return ::MoveWindow(window, old.x, old.y, newSize.x, newSize.y, doRedraw) != 0;
		}

		inline bool setShowMode(WindowHandle window, UnifyEnum<ShowMode> modes) {
			return ::ShowWindow(window, modes.get()) != 0;
		}

		// set window title
		inline bool setTitle(WindowHandle window, const Tstring& newTitle) {
			return ::SetWindowText(window, newTitle.c_str()) != 0;
		}

		// get window style
		inline UnifyEnum<Option> getStyle(WindowHandle window) {
			return UnifyEnum<Option>(::GetWindowLong(window, GWL_STYLE));
		}
		// get window extend style
		inline UnifyEnum<ExtOption> getExtStyle(WindowHandle window) {
			return UnifyEnum<ExtOption>(::GetWindowLong(window, GWL_EXSTYLE));
		}

		// destroy window (add Msg::Destory to message queue)
		inline bool destroy(WindowHandle window) {
			return ::DestroyWindow(window) != 0;
		}

		// convert client coordinate to screen coordinate
		inline Position toScreenPos(WindowHandle window, const Position& clientPos) {
			::LPPOINT posBuf;
			posBuf->x = clientPos.x;
			posBuf->y = clientPos.y;

			::ClientToScreen(window, posBuf);

			return{ posBuf->x, posBuf->y };
		}
		// convert screen coordinate to client coordinate
		inline Position toClientPos(WindowHandle window, const Position& screenPos) {
			::LPPOINT posBuf;
			posBuf->x = screenPos.x;
			posBuf->y = screenPos.y;

			::ScreenToClient(window, posBuf);

			return{ posBuf->x, posBuf->y };
		}

		// get top most window
		inline WindowHandle getForegroundWindow() {
			return ::GetForegroundWindow();
		}
		// get active window, which has focus
		inline WindowHandle getActiveWindow() {
			return ::GetActiveWindow();
		}

		// get message
		// if message queue is empty, this function wait for new message with blocking
		inline bool getMessage(Message& msg, WindowHandle window, Uint filterMin = 0, Uint filterMax = 0) {
			return ::GetMessage(&msg, window, filterMin, filterMax) > 0;
		}
		// check message
		// if message queue is empty, this function return false
		inline bool checkMessage(Message& msg, WindowHandle window, bool doPopMsg, Uint filterMin = 0, Uint filterMax = 0) {
			return
				::PeekMessage(
					&msg,
					window,
					filterMin,
					filterMax,
					(doPopMsg ? PM_REMOVE : PM_NOREMOVE)
				) != 0;
		}

		inline bool translateMessage(const Message& msg) {
			return ::TranslateMessage(&msg) != 0;
		}

		inline LongPtr dispatchMessage(const Message& msg) {
			return ::DispatchMessage(&msg);
		}

		// call window message procedure
		inline bool update(WindowHandle window) {
			return ::UpdateWindow(window) != 0;
		}

		inline LongPtr defaultProc(WindowHandle window, Msg msg, UintPtr wp, IntPtr lp) {
			return ::DefWindowProc(window, unpackEnum(msg), wp, lp);
		}

		static auto& quitAll = ::PostQuitMessage;

		// set the timer to add Msg::Timer to message queue regularly
		inline UintPtr setTImerEvent(Uint elapse, TimerProc proc) {
			return ::SetTimer(nullptr, 0, elapse, proc);
		}
		// set the timer to add Msg::Timer to message queue regularly
		inline UintPtr setTimerEvent(WindowHandle window, Uint eventId, Uint elapse) {
			return ::SetTimer(window, eventId, elapse, nullptr);
		}
		// set the timer to add Msg::Timer to message queue regularly
		inline UintPtr setTimerEvent(WindowHandle window, Uint eventId, Uint elapse, TimerProc proc) {
			return ::SetTimer(window, eventId, elapse, proc);
		}

		// kill the timer, which has setted by setTimerEvent function
		inline bool killTimerEvent(Uint eventId) {
			return ::KillTimer(nullptr, eventId) != 0;
		}
		// kill the timer, which has setted by setTimerEvent function
		inline bool killTimerEvent(WindowHandle window, Uint eventId) {
			return ::KillTimer(window, eventId) != 0;
		}

		inline int getWindowMetrics(WindowMetrics type) {
			return ::GetSystemMetrics(unpackEnum(type));
		}

	} // ::wawl::wnd
} // ::wawl