#pragma once
#define ENABLE_WAWL_PROCESS

#include "WawlBase.hpp"
#include "ConsoleBaseType.hpp"
#include "FileBaseType.hpp"
#include "WindowBaseType.hpp"

namespace wawl {
	namespace fs {
		namespace proc {

			// information for application startup
			using StartupInfo = ::STARTUPINFO;

			// make an initialized StartupInfo
			inline StartupInfo makeStartupInfo(
				const Position* wndPos,
				const Size* wndSize,
				StartupOption* startupOptions,
				wnd::ShowMode* wndShowModes,
				Tstring* wndTitle,
				Tstring* desktopName,
				const Size* consoleBufSize,
				console::StrColor* consoleStrColor,
				console::BkgColor* consoleBkgColor,
				FileHandle stdInput,
				FileHandle stdOutput,
				FileHandle stdError
				) {
				StartupInfo si = {};

				si.cb = sizeof(StartupInfo);
				if (desktopName != nullptr)
					si.lpDesktop = &(*desktopName)[0];
				// set window title
				if (wndTitle != nullptr)
					si.lpTitle = &(*wndTitle)[0];
				// set window position
				if (wndPos != nullptr)
					si.dwFlags |= STARTF_USEPOSITION,
					si.dwX = wndPos->x,
					si.dwY = wndPos->y;
				// set window size
				if (wndSize != nullptr)
					si.dwFlags |= STARTF_USESIZE,
					si.dwXSize = wndSize->x,
					si.dwYSize = wndSize->y;
				// set console buffer width and height
				if (consoleBufSize != nullptr)
					si.dwFlags |= STARTF_USECOUNTCHARS,
					si.dwXCountChars = consoleBufSize->x,
					si.dwYCountChars = consoleBufSize->y;
				// set console string's and background's color
				if (consoleStrColor != nullptr)
					si.dwFlags |= STARTF_USEFILLATTRIBUTE,
					si.dwFillAttribute = unpackEnum(*consoleStrColor);
				if (consoleBkgColor != nullptr)
					si.dwFlags |= STARTF_USEFILLATTRIBUTE,
					si.dwFillAttribute = unpackEnum(*consoleBkgColor);
				// set application startup option
				if (startupOptions != nullptr)
					si.dwFlags |= unpackEnum(*startupOptions);
				// set window show modes
				if (wndShowModes != nullptr)
					si.dwFlags |= STARTF_USESHOWWINDOW,
					si.wShowWindow = unpackEnum(*wndShowModes);
				//標準入力、出力、エラー出力ファイルの設定
				if (stdInput != nullptr)
					si.dwFlags |= STARTF_USESTDHANDLES,
					si.hStdInput = stdInput;
				if (stdOutput != nullptr)
					si.dwFlags |= STARTF_USESTDHANDLES,
					si.hStdOutput = stdOutput;
				if (stdError != nullptr)
					si.dwFlags |= STARTF_USESTDHANDLES,
					si.hStdError = stdError;

				return std::move(si);
			}
			inline StartupInfo makeStartupInfo() {
				return makeStartupInfo(
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr
					);
			}
			inline StartupInfo makeStartupInfo(
				const Position& wndPos
				) {
				return makeStartupInfo(
					&wndPos,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr
					);
			}
			inline StartupInfo makeStartupInfo(
				const Position& wndPos,
				const Size& wndSize
				) {
				return makeStartupInfo(
					&wndPos,
					&wndSize,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr
					);
			}
			inline StartupInfo makeStartupInfo(
				StartupOption startupOptions,
				wnd::ShowMode wndShowModes
				) {
				return makeStartupInfo(
					nullptr,
					nullptr,
					&startupOptions,
					&wndShowModes,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr
					);
			}
			inline StartupInfo makeStartupInfo(
				const Size& consoleBufSize,
				console::StrColor consoleStrColor,
				console::BkgColor consoleBkgColor
				) {
				return makeStartupInfo(
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					&consoleBufSize,
					&consoleStrColor,
					&consoleBkgColor,
					nullptr,
					nullptr,
					nullptr
					);
			}
			inline StartupInfo makeStartupInfo(
				FileHandle stdInput,
				FileHandle stdOutput,
				FileHandle stdError
				) {
				return makeStartupInfo(
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					stdInput,
					stdOutput,
					stdError
					);
			}
			inline StartupInfo makeStartupInfo(
				const Size& consoleBufSize,
				console::StrColor consoleStrColor,
				console::BkgColor consoleBkgColor,
				FileHandle stdInput,
				FileHandle stdOutput,
				FileHandle stdError
				) {
				return makeStartupInfo(
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					&consoleBufSize,
					&consoleStrColor,
					&consoleBkgColor,
					stdInput,
					stdOutput,
					stdError
					);
			}
			inline StartupInfo makeStartupInfo(
				const Position& wndPos,
				const Size& wndSize,
				StartupOption startupOptions,
				wnd::ShowMode wndShowModes,
				Tstring& wndTitle,
				Tstring& desktopName,
				const Size& consoleBufSize,
				console::StrColor consoleStrColor,
				console::BkgColor consoleBkgColor,
				FileHandle stdInput,
				FileHandle stdOutput,
				FileHandle stdError
				) {
				return makeStartupInfo(
					&wndPos,
					&wndSize,
					&startupOptions,
					&wndShowModes,
					&wndTitle,
					&desktopName,
					&consoleBufSize,
					&consoleStrColor,
					&consoleBkgColor,
					stdInput,
					stdOutput,
					stdError
					);
			}

			inline StartupInfo getLocalStarupInfo() {
				StartupInfo si;
				::GetStartupInfo(&si);

				return si;
			}
			
			// process creation provision
			enum class ProcessCreateProv : Uint32 {
				NotInheritJob = CREATE_BREAKAWAY_FROM_JOB,
				NotInheritErrorMode = CREATE_DEFAULT_ERROR_MODE,
				DosMode = CREATE_FORCEDOS,
				CreateNewConsole = CREATE_NEW_CONSOLE,
				CreateNewProcGroup = CREATE_NEW_PROCESS_GROUP,
				NotCreateWindow = CREATE_NO_WINDOW,
				VdmMode = CREATE_SEPARATE_WOW_VDM,
				SharedVdmMode = CREATE_SHARED_WOW_VDM,
				SuspendPrimary = CREATE_SUSPENDED,
				DebugMode = DEBUG_PROCESS,
				NotInheritDebugMode = DEBUG_ONLY_THIS_PROCESS,
				DisallowAccessConsole = DETACHED_PROCESS,

				PriorityLv1 = IDLE_PRIORITY_CLASS,
				PriorityLv2 = BELOW_NORMAL_PRIORITY_CLASS,
				PriorityLv3 = NORMAL_PRIORITY_CLASS,
				PriorityLv4 = ABOVE_NORMAL_PRIORITY_CLASS,
				PriorityLv5 = HIGH_PRIORITY_CLASS,
				MaxPriority = REALTIME_PRIORITY_CLASS
			};

			// process infomation
			using ProcessInfo = ::PROCESS_INFORMATION;

			// initialize an ProcessInfo
			inline bool createProcess(
				ProcessInfo& procInfo,
				const Tstring* appName,
				const Tstring* cmdLineArgs,
				const SecurityAttr* procAttr,
				const SecurityAttr* threadAttr,
				bool doInheritHandle,
				ProcessCreateProv* createProv,
				const Tstring* envVars,
				const Tstring* currentDir,
				const StartupInfo* startupInfo
				) {
				StartupInfo si = (startupInfo ? *startupInfo : StartupInfo{});
				SecurityAttr psa = (procAttr ? *procAttr : SecurityAttr{});
				SecurityAttr tsa = (threadAttr ? *threadAttr : SecurityAttr{});

				return
					::CreateProcess(
						(appName ? appName->c_str() : nullptr),
						(cmdLineArgs ? const_cast<Tchar*>(cmdLineArgs->c_str()) : nullptr),
						(procAttr ? &psa : nullptr),
						(threadAttr ? &tsa : nullptr),
						doInheritHandle,
						(createProv ? unpackEnum(*createProv) : NORMAL_PRIORITY_CLASS),
						(envVars ? const_cast<Tchar*>(envVars->c_str()) : nullptr),
						(currentDir ? currentDir->c_str() : nullptr),
						&si,
						&procInfo
						) != 0;
			}
			inline bool createProcess(
				ProcessInfo& procInfo,
				const Tstring& cmdLine
				) {
				return
					createProcess(
						procInfo,
						nullptr,
						&cmdLine,
						nullptr,
						nullptr,
						false,
						nullptr,
						nullptr,
						nullptr,
						nullptr
						);
			}
			inline bool createProcess(
				ProcessInfo& procInfo,
				const Tstring& cmdLine,
				const StartupInfo& startupInfo
				) {
				return
					createProcess(
						procInfo,
						nullptr,
						&cmdLine,
						nullptr,
						nullptr,
						false,
						nullptr,
						nullptr,
						nullptr,
						&startupInfo
						);
			}
			inline bool createProcess(
				ProcessInfo& procInfo,
				const Tstring& cmdLine,
				const StartupInfo& startupInfo,
				ProcessCreateProv createProv
				) {
				return
					createProcess(
						procInfo,
						nullptr,
						&cmdLine,
						nullptr,
						nullptr,
						false,
						&createProv,
						nullptr,
						nullptr,
						&startupInfo
						);
			}
			inline bool createProcess(
				ProcessInfo& procInfo,
				const Tstring& cmdLine,
				const StartupInfo& startupInfo,
				ProcessCreateProv createProv,
				const Tstring& currentDir
				) {
				return
					createProcess(
						procInfo,
						nullptr,
						&cmdLine,
						nullptr,
						nullptr,
						false,
						&createProv,
						nullptr,
						&currentDir,
						&startupInfo
						);
			}
			inline bool createProcess(
				ProcessInfo& procInfo,
				const Tstring& appName,
				const Tstring& cmdLineArgs,
				SecurityAttr& procAttr,
				SecurityAttr& threadAttr,
				bool doInheritHandle,
				ProcessCreateProv createProv,
				const Tstring& envVars,
				const Tstring& currentDir,
				const StartupInfo& startupInfo
				) {
				return
					createProcess(
						procInfo,
						&appName,
						&cmdLineArgs,
						&procAttr,
						&threadAttr,
						doInheritHandle,
						&createProv,
						&envVars,
						&currentDir,
						&startupInfo
						);
			}

			// force terminate process (normally deprecated)
			inline bool terminateProcess(
				const ProcessInfo& proc,
				Uint exitCode = 0
				) {
				return ::TerminateProcess(proc.hProcess, exitCode) != 0;
			}

			// represent the process is still runnning
			constexpr Uint32 StillActive = STILL_ACTIVE;

			// get exit code of process
			// if the process is still running, return StillActive
			inline Uint32 getExitCode(const ProcessInfo& proc) {
				Uint32 exitCode;

				::GetExitCodeProcess(proc.hProcess, &exitCode);

				return exitCode;
			}

		} // ::wawl::fs::proc
	} // ::wawl::fs
} // ::wawl