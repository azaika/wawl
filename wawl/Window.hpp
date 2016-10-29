#pragma once
#define WAWL_WINDOW_HPP

#include "WindowBaseType.hpp"
#include "Cursor.hpp"
#include "Icon.hpp"
#include "Menu.hpp"
#include "BaseUtility.hpp"
#include "Detail.hpp"

namespace wawl {
	namespace wnd {

		struct Property : ::WNDCLASSEX {
			Property() {
				::ZeroMemory(this, sizeof(*this));
				cbSize = sizeof(*this);
			}
			Property(const Property&) = default;
			Property& operator = (const Property&) = default;

			auto& name(const Tstring& v) {
				lpszClassName = v.c_str();
				return *this;
			}
			auto& option(Flags<PropOption> v) {
				style = v.get();
				return *this;
			}
			auto& background(ColorBrush v) {
				hbrBackground = reinterpret_cast<::HBRUSH>(::GetStockObject(unpackEnum(v)));
				return *this;
			}
			auto& menuName(const Tstring& v) {
				lpszMenuName = v.c_str();
				return *this;
			}

			WAWL_DETAIL_DEFINE_SETTER(proc, MsgProc&, lpfnWndProc)
			WAWL_DETAIL_DEFINE_SETTER(appHandle, AppHandle, hInstance)
			WAWL_DETAIL_DEFINE_SETTER(icon, IconHandle, hIcon)
			WAWL_DETAIL_DEFINE_SETTER(smallIcon, IconHandle, hIconSm)
			WAWL_DETAIL_DEFINE_SETTER(cursor, CursorHandle, hCursor)

		};

		inline std::uint16_t registerProperty(const Property& prop) {
			return ::RegisterClassEx(&prop);
		}

		static constexpr Position DefaultWindowPos = { CW_USEDEFAULT, CW_USEDEFAULT };

		namespace detail {
			inline WindowHandle createWindow(
				const Tstring& propName,
				const Tstring& title,
				const Rect& wndRect,
				const Flags<Option>* options,
				const Flags<ExtOption>* extOptions,
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

			inline WindowHandle createChildWindow(
				const Tstring& propName,
				const Tstring& title,
				const Rect& wndRect,
				WindowHandle parent,
				ChildID myID,
				const Flags<Option>* options,
				const Flags<ExtOption>* extOptions,
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
		} // ::wawl::wnd::detail

		inline WindowHandle createWindow(
			const Tstring& propName,
			const Tstring& title,
			const Rect& wndRect
			) {
			return
				detail::createWindow(
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
			Flags<Option> options
			) {
			return
				detail::createWindow(
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
			Flags<Option> options,
			Flags<ExtOption> extOptions,
			MenuHandle menu
			) {
			return
				detail::createWindow(
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
			Flags<Option> options,
			Flags<ExtOption> extOptions,
			MenuHandle menu,
			const CreateStruct& createStruct
			) {
			return
				detail::createWindow(
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
			ChildID myID
			) {
			return
				detail::createChildWindow(
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
			Flags<Option> options,
			Flags<ExtOption> extOptions
			) {
			return
				detail::createChildWindow(
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
			Flags<Option> options,
			Flags<ExtOption> extOptions,
			const CreateStruct& createStruct
			) {
			return
				detail::createChildWindow(
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
			::RECT rect;

			bool res =
				::GetWindowRect(
					window,
					&rect
				) != 0;

			return Rect(rect);
		}
		inline Rect getClientRect(WindowHandle window) {
			::RECT rect;

			bool res =
				::GetClientRect(
					window,
					&rect
				) != 0;

			return Rect(rect);
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
		inline bool setWindowPos(WindowHandle window, const Position& newPos, bool doRedraw = false) {
			Rect&& old = getWindowRect(window);

			return ::MoveWindow(window, newPos.x, newPos.y, old.h, old.w, doRedraw) != 0;
		}

		inline bool resizeWindow(WindowHandle window, const Size& newSize, bool doRedraw = true) {
			Rect&& old = getWindowRect(window);

			return ::MoveWindow(window, old.x, old.y, newSize.x, newSize.y, doRedraw) != 0;
		}

		inline bool setWindowShowMode(WindowHandle window, Flags<ShowMode> modes) {
			return ::ShowWindow(window, modes.get()) != 0;
		}

		inline bool setWindowTitle(WindowHandle window, const Tstring& newTitle) {
			return ::SetWindowText(window, newTitle.c_str()) != 0;
		}

		// get window style
		inline Flags<Option> getWindowStyle(WindowHandle window) {
			return Flags<Option>(::GetWindowLong(window, GWL_STYLE));
		}
		// get window extend style
		inline Flags<ExtOption> getWindowExtStyle(WindowHandle window) {
			return Flags<ExtOption>(::GetWindowLong(window, GWL_EXSTYLE));
		}

		// destroy window (add Msg::Destory to message queue)
		inline bool destroyWindow(WindowHandle window) {
			return ::DestroyWindow(window) != 0;
		}

		// convert client coordinate to screen coordinate
		inline Position toScreenPos(WindowHandle window, const Position& clientPos) {
			::LPPOINT posBuf;
			posBuf->x = clientPos.x;
			posBuf->y = clientPos.y;

			::ClientToScreen(window, posBuf);

			return *posBuf;
		}
		// convert screen coordinate to client coordinate
		inline Position toClientPos(WindowHandle window, const Position& screenPos) {
			::LPPOINT posBuf;
			posBuf->x = screenPos.x;
			posBuf->y = screenPos.y;

			::ScreenToClient(window, posBuf);

			return *posBuf;
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
		inline bool getMessage(MsgProcResult& msg, WindowHandle window, Uint filterMin = 0, Uint filterMax = 0) {
			return ::GetMessage(&msg, window, filterMin, filterMax) > 0;
		}
		// check message
		// if message queue is empty, this function return false
		inline bool checkMessage(MsgProcResult& msg, WindowHandle window, bool doPopMsg, Uint filterMin = 0, Uint filterMax = 0) {
			return
				::PeekMessage(
					&msg,
					window,
					filterMin,
					filterMax,
					(doPopMsg ? PM_REMOVE : PM_NOREMOVE)
				) != 0;
		}

		inline bool translateMessage(const MsgProcResult& msg) {
			return ::TranslateMessage(&msg) != 0;
		}

		inline LongPtr dispatchMessage(const MsgProcResult& msg) {
			return ::DispatchMessage(&msg);
		}

		// call window message procedure
		inline bool updateWindow(WindowHandle window) {
			return ::UpdateWindow(window) != 0;
		}

		inline LongPtr defaultProc(WindowHandle window, Msg msg, UintPtr wp, IntPtr lp) {
			return ::DefWindowProc(window, unpackEnum(msg), wp, lp);
		}

		static auto& postQuitMsg = ::PostQuitMessage;

		// set a timer which calls 'proc' function regularly
		inline UintPtr setTimerEvent(TimerProc proc, Uint elapse) {
			return ::SetTimer(nullptr, 0, elapse, proc);
		}
		// set a timer which sends Msg::Timer message regularly
		inline UintPtr setTimerEvent(WindowHandle window, Uint eventId, Uint elapse) {
			return ::SetTimer(window, eventId, elapse, nullptr);
		}
		// set a timer which sends Msg::Timer message regularly
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