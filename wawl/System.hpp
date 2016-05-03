#pragma once
#define ENABLE_WAWL_SYSTEM

#include "WawlBase.hpp"

#pragma comment(lib, "winmm.lib")

namespace wawl {
	namespace sys {

		// get AppHandle of this application
		AppHandle getLocalAppHandle() {
			return static_cast<AppHandle>(::GetModuleHandle(0));
		}

		// get full cmd Line args, which includes this exe name
		inline Tstring getFullCmdArgs() {
			return ::GetCommandLine();
		}

		// get system time milli second
		inline Uint32 getTimeMs() {
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
			Uint32 timeOut = 0,
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

		// if shutDown function has called and it is still waiting for timeOut, cancel it.
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

	} // ::wawl::sys
} // ::wawl