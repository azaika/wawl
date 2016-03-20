#pragma once
#define ENABLE_WAWL_WINDOWBASETYPE

#include "BaseType.hpp"

namespace wawl {
	namespace wnd {

		// window show mode
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

		// window property option
		enum class PropOption : unsigned int {
			AlignClientByByte = CS_BYTEALIGNCLIENT,
			AlignWndByByte = CS_BYTEALIGNWINDOW,
			VRedraw = CS_HREDRAW,
			HRedraw = CS_VREDRAW,
			CallOnDoubleClick = CS_DBLCLKS,
			NoClose = CS_NOCLOSE,
			ShareDC = CS_CLASSDC,
			OriginalDC = CS_OWNDC,
			ParentDC = CS_PARENTDC,
			Global = CS_GLOBALCLASS,
			SaveBitmap = CS_SAVEBITS,
			DropShadow = CS_DROPSHADOW
		};

		using IconHandle = ::HICON;

		// default window icon
		struct DefaultIcon {
			static constexpr Tchar* App = IDI_APPLICATION;
			static constexpr Tchar* Info = IDI_INFORMATION;
			static constexpr Tchar* Question = IDI_QUESTION;
			static constexpr Tchar* Error = IDI_ERROR;
			static constexpr Tchar* Warning = IDI_WARNING;
			static constexpr Tchar* WinLogo = IDI_WINLOGO;
		};

		using CursorHandle = ::HCURSOR;

		// default cursor icon
		struct DefaultCursor {
			static constexpr Tchar* Arrow = IDC_ARROW;
			static constexpr Tchar* Cross = IDC_CROSS;
			static constexpr Tchar* IBeam = IDC_IBEAM;
			static constexpr Tchar* Wait = IDC_WAIT;
		};

		// gdi color brushes
		enum class ColorBrush : int {
			White = WHITE_BRUSH,
			Black = BLACK_BRUSH,
			DarkGray = DKGRAY_BRUSH,
			LightGray = LTGRAY_BRUSH,
			Hollow = HOLLOW_BRUSH
		};

		// window procedure message
		// ToDo: need more
		enum class Msg : unsigned int {
			Activate = WM_ACTIVATE,
			ActivateApp = WM_ACTIVATEAPP,
			Create = WM_CREATE,
			Timer = WM_TIMER,
			Destroy = WM_DESTROY,
			LClick = WM_LBUTTONDOWN,
			MClick = WM_MBUTTONDOWN,
			RClick = WM_RBUTTONDOWN,
			MouseLDoubleClick = WM_LBUTTONDBLCLK,
			MouseMDoubleClick = WM_MBUTTONDBLCLK,
			MouseRDoubleClick = WM_RBUTTONDBLCLK,
			MouseLUp = WM_LBUTTONUP,
			MouseMUp = WM_MBUTTONUP,
			MouseRUp = WM_RBUTTONUP,
			Close = WM_CLOSE,
			Enable = WM_ENABLE,
			Resize = WM_SIZE,
			Resizing = WM_SIZING,
			Move = WM_MOVE,
			Quit = WM_QUIT,
			Null = WM_NULL,
			Paint = WM_PAINT,

			// and more...
		};

		using Message = ::MSG;

		// window option
		enum class Option : Uint32 {
			Bordered = WS_BORDER,
			Caption = WS_CAPTION,
			Child = WS_CHILD,
			NotDrawChildrenRegion = WS_CLIPCHILDREN,
			NotDrawBroserRegion = WS_CLIPSIBLINGS,
			Disabled = WS_DISABLED,
			ControlGroup = WS_GROUP,
			UseHorizontalScroll = WS_HSCROLL,
			UseVerticalScroll = WS_VSCROLL,
			Maxmize = WS_MAXIMIZE,
			EnableMaximize = WS_MAXIMIZEBOX,
			Minimize = WS_MINIMIZE,
			EnableMinimize = WS_MINIMIZEBOX,
			Tiled = WS_TILED,
			Overlapped = WS_OVERLAPPEDWINDOW,
			Popup = WS_POPUP,
			PopupSet = WS_POPUPWINDOW,
			EnableSizeChange = WS_SIZEBOX,
			SysMenu = WS_SYSMENU,
			AcceptTab = WS_TABSTOP,
			Visible = WS_VISIBLE
		};

		// extended window option
		enum class ExtOption : Uint32 {
			EnableFileDD = WS_EX_ACCEPTFILES,
			ShowToTaskbar = WS_EX_APPWINDOW,
			UseEdgeFrame = WS_EX_CLIENTEDGE,
			EnableHelp = WS_EX_CONTEXTHELP,
			DistinguishChild = WS_EX_CONTROLPARENT,
			EmphasisDialog = WS_EX_DLGMODALFRAME,
			Layered = WS_EX_LAYERED,
			LeftOrder = WS_EX_LEFT,
			LeftScrollBar = WS_EX_LEFTSCROLLBAR,
			ReadFromLeft = WS_EX_LTRREADING,
			MdiChiled = WS_EX_MDICHILD,
			NoParentNotify = WS_EX_NOPARENTNOTIFY,
			Overlapped = WS_EX_OVERLAPPEDWINDOW,
			Palette = WS_EX_PALETTEWINDOW,
			RightOrder = WS_EX_RIGHT,
			RightScrollBar = WS_EX_RIGHTSCROLLBAR,
			ReadFromRight = WS_EX_RTLREADING,
			UseFloatFrame = WS_EX_STATICEDGE,
			ToolWindow = WS_EX_TOOLWINDOW,
			TopMost = WS_EX_TOPMOST,
			Transparent = WS_EX_TRANSPARENT
		};

		// window procedure function
		using ProcFunc = std::remove_pointer_t<::WNDPROC>;

	} // ::wawl::wnd
} // ::wawl