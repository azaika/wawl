#pragma once
#define WAWL_SYSTEM_HPP

#include "WawlBase.hpp"

#pragma comment(lib, "winmm.lib")

namespace wawl {
	namespace sys {

		// get AppHandle of this application
		AppHandle getLocalAppHandle() {
			return static_cast<AppHandle>(::GetModuleHandle(0));
		}

		// get full cmd Line args, which includes exe filename
		inline Tstring getFullCmdArgs() {
			return ::GetCommandLine();
		}

		// get system time by milli second
		inline std::uint32_t getTimeMs() {
			return timeGetTime();
		}

		enum class ExitMode : Uint {
			Logoff = EWX_LOGOFF,
			Poweroff = EWX_POWEROFF,
			Reboot = EWX_REBOOT,
			Shutdown = EWX_SHUTDOWN
		};

		inline bool exitComputer(ExitMode mode) {
			return ::ExitWindowsEx(unpackEnum(mode), 0) != 0;
		}
		inline bool exitComputer(ExitMode mode, bool doWaitHang) {
			return ::ExitWindowsEx(
				unpackEnum(mode) |
				(doWaitHang ? EWX_FORCEIFHUNG : EWX_FORCE),
				0
				) != 0;
		}

		inline bool shutdown(
			const Tstring& machineName,
			const Tstring& msg,
			std::uint32_t timeOut = 0,
			bool force = false,
			bool doRestart = false
			) {
			return ::InitiateSystemShutdown(
				const_cast<Tchar*>(machineName.c_str()),
				const_cast<Tchar*>(msg.c_str()),
				timeOut,
				force,
				doRestart
				) != 0;
		}

		// if shutDown function has called and Windows is still waiting for timeout, cancel it.
		inline bool abortShutdown(const Tstring& machineName) {
			return ::AbortSystemShutdown(const_cast<Tchar*>(machineName.c_str())) != 0;
		}

		// change system clock resolution
		// after call this function, you need to call resetTimeResolution fuction with same arg
		bool changeTimeResolution(Uint res) {
			return ::timeBeginPeriod(res) == TIMERR_NOERROR;
		}
		bool resetTimeResolution(Uint res) {
			return ::timeEndPeriod(res) == TIMERR_NOERROR;
		}

		// type of system constant used in getSystemConstant
		enum class SystemConstant : int {
			Arrange = SM_ARRANGE,
			BootMode = SM_CLEANBOOT,
			NumMouseButton = SM_CMOUSEBUTTONS,
			DubblebyteCharSetEnabled = SM_DBCSENABLED,
			DebugEnabled = SM_DEBUG,
			DropdownMenuRightAlignmented = SM_MENUDROPALIGNMENT,
			MideastEnabled = SM_MIDEASTENABLED,
			MouseEnabled = SM_MOUSEPRESENT,
			MouseWheelEnabled = SM_MOUSEWHEELPRESENT,
			NetworkEnabled = SM_NETWORK,
			RemoteSessoned = SM_REMOTESESSION,
			SecurityEnabled = SM_SECURE,
			SoundHelpEnabled = SM_SHOWSOUNDS,
			IsSlowMachine = SM_SLOWMACHINE,
			ButtonSwapped = SM_SWAPBUTTON
		};

		inline int getSystemConstant(SystemConstant which) {
			return ::GetSystemMetrics(unpackEnum(which));
		}

	} // ::wawl::sys
} // ::wawl