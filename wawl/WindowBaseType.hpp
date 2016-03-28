#pragma once
#define ENABLE_WAWL_WINDOWBASETYPE

#include "BaseType.hpp"
#include "MenuBaseType.hpp"

namespace wawl {
	namespace wnd {

		enum class ImageLoadOption : Uint {
			DefaultColor = LR_DEFAULTCOLOR,
			UseDIBSection = LR_CREATEDIBSECTION,
			SysDefaultSize = LR_DEFAULTSIZE,
			Monochrome = LR_MONOCHROME,
			ShareHandle = LR_SHARED,
			UseVGA = LR_VGACOLOR
		};

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
			ChildActivate = WM_CHILDACTIVATE,
			Close = WM_CLOSE,
			Command = WM_COMMAND,
			Create = WM_CREATE,
			Destroy = WM_DESTROY,
			ToggleState = WM_ENABLE,
			Timer = WM_TIMER,
			LClick = WM_LBUTTONDOWN,
			MClick = WM_MBUTTONDOWN,
			RClick = WM_RBUTTONDOWN,
			MouseLDoubleClick = WM_LBUTTONDBLCLK,
			MouseMDoubleClick = WM_MBUTTONDBLCLK,
			MouseRDoubleClick = WM_RBUTTONDBLCLK,
			MouseLUp = WM_LBUTTONUP,
			MouseMUp = WM_MBUTTONUP,
			MouseRUp = WM_RBUTTONUP,
			Resize = WM_SIZE,
			Resizing = WM_SIZING,
			Move = WM_MOVE,
			Quit = WM_QUIT,
			Null = WM_NULL,
			Paint = WM_PAINT,
			CharInput = WM_CHAR,
			CharInputDetail = WM_CHARTOITEM,
			GetFocus = WM_SETFOCUS,
			LostFocus = WM_KILLFOCUS,
			GetClipboardFormats = WM_ASKCBFORMATNAME,
			CancelJaurnal = WM_CANCELJOURNAL,
			MouseCaptureChanged = WM_CAPTURECHANGED,
			ClipboardChainChanged = WM_CHANGECBCHAIN,
			DestroyClipboard = WM_DESTROYCLIPBOARD,
			Disable = WM_CANCELMODE,
			FontChoose = WM_CHOOSEFONT_GETLOGFONT,
			ClearText = WM_CLEAR,
			CopyText = WM_COPY,
			CutText = WM_CUT,
			DeviceChanged = WM_DEVICECHANGE,
			DisplayChanged = WM_DISPLAYCHANGE,
			ClipboardUpdated = WM_DRAWCLIPBOARD,
			SystemShutdown = WM_ENDSESSION,
			SystemFontChanged = WM_FONTCHANGE,
			Help = WM_HELP,
			HotkeyPushed = WM_HOTKEY,

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

		using WindowHandle = ::HWND;
		using ChildID = MenuHandle;

		using CreateStruct = ::CREATESTRUCT;

	} // ::wawl::wnd
} // ::wawl