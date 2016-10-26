#pragma once
#define WAWL_MESSAGE_BOX_HPP

#include "BaseType.hpp"
#include "BaseUtility.hpp"

namespace wawl {
	namespace wnd {
		namespace mb {

			// button type in message box
			enum class Button : Uint {
				Failed = MB_ABORTRETRYIGNORE,
				Help = MB_HELP,
				OK = MB_OK,
				IsOK = MB_OKCANCEL,
				DoRetry = MB_RETRYCANCEL,
				YesNo = MB_YESNO,
				YesNoCancel = MB_YESNOCANCEL
			};

			// icon type in message box
			enum class Icon : Uint {
				Warning = MB_ICONWARNING,
				Info = MB_ICONINFORMATION,
				Question = MB_ICONQUESTION,
				Stop = MB_ICONSTOP
			};

			// regulation level for other window while showing message box
			enum class CtrlRegLevel : Uint {
				App = MB_APPLMODAL,
				System = MB_SYSTEMMODAL,
				Task = MB_TASKMODAL
			};

			// message box's show style
			enum class ShowStyle : Uint {
				OnlyDefaultDesktop = MB_DEFAULT_DESKTOP_ONLY,
				RightText = MB_RIGHT,
				RightToLeft = MB_RTLREADING,
				Foreground = MB_SETFOREGROUND,
				TopMost = MB_TOPMOST,
				Notification = MB_SERVICE_NOTIFICATION,
				NotificationOnNT351 = MB_SERVICE_NOTIFICATION_NT3X
			};

			// result of message box
			enum class Result : int {
				Abort = IDABORT,
				Cancel = IDCANCEL,
				Continue = IDCONTINUE,
				Ignore = IDIGNORE,
				No = IDNO,
				OK = IDOK,
				Retry = IDRETRY,
				TryAgain = IDTRYAGAIN,
				Yes = IDYES
			};

			// show message box
			inline Result show(
				const Tstring& title,
				const Tstring& text,
				Button button,
				Icon* icon,
				CtrlRegLevel* ctrlLevel,
				Flags<ShowStyle>* style
				) {
				return static_cast<Result>(
					::MessageBox(
						nullptr,
						text.c_str(),
						title.c_str(),
						unpackEnum(button)
						| (icon ? unpackEnum(*icon) : 0)
						| (ctrlLevel ? unpackEnum(*ctrlLevel) : 0)
						| (style ? style->get() : 0)
						)
					);
			}
			inline Result show(
				const Tstring& title,
				const Tstring& text,
				Button button,
				Icon icon = static_cast<Icon>(0),
				CtrlRegLevel ctrlLevel = static_cast<CtrlRegLevel>(0),
				Flags<ShowStyle> style = Flags<ShowStyle>()
				) {
				return
					show(
						title,
						text,
						button,
						&icon,
						&ctrlLevel,
						&style
						);
			}

		} // ::wawl::wnd::mb
	} // ::wawl::wnd

	WAWL_DETAIL_ENABLE_FLAG(wnd::mb::ShowStyle)

} // ::wawl