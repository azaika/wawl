#pragma once
#define WAWL_PROCESS_HPP

#include "WawlBase.hpp"
#include "ConsoleBaseType.hpp"
#include "FileBaseType.hpp"
#include "WindowBaseType.hpp"
#include "ProcessBaseType.hpp"

namespace wawl {
	namespace fs {
		namespace proc {

			// information for application startup
			struct StartupInfo : ::STARTUPINFO {
				StartupInfo() :
					StartupInfo(
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
					) {}
				StartupInfo(
					const Position& wndPos
				) :
					StartupInfo(
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
					) {}
				StartupInfo(
					const Position& wndPos,
					const Size& wndSize
				) :
					StartupInfo(
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
					) {}
				StartupInfo(
					Flags<StartupOption> startupOptions,
					Flags<wnd::ShowMode> wndShowModes
				) :
					StartupInfo(
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
					) {}
				StartupInfo(
					const Size& consoleBufSize,
					console::StrColor consoleStrColor,
					console::BkgColor consoleBkgColor
				) :
					StartupInfo(
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
					) {}
				StartupInfo(
					FileHandle stdInput,
					FileHandle stdOutput,
					FileHandle stdError
				) :
					StartupInfo(
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
					) {}
				StartupInfo(
					const Size& consoleBufSize,
					console::StrColor consoleStrColor,
					console::BkgColor consoleBkgColor,
					FileHandle stdInput,
					FileHandle stdOutput,
					FileHandle stdError
				) :
					StartupInfo(
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
					) {}
				StartupInfo(
					const Position& wndPos,
					const Size& wndSize,
					Flags<StartupOption> startupOptions,
					Flags<wnd::ShowMode> wndShowModes,
					Tstring& wndTitle,
					Tstring& desktopName,
					const Size& consoleBufSize,
					console::StrColor consoleStrColor,
					console::BkgColor consoleBkgColor,
					FileHandle stdInput,
					FileHandle stdOutput,
					FileHandle stdError
				) :
					StartupInfo(
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
					) {}

			private:
				StartupInfo(
					const Position* wndPos,
					const Size* wndSize,
					Flags<StartupOption>* startupOptions,
					Flags<wnd::ShowMode>* wndShowModes,
					Tstring* wndTitle,
					Tstring* desktopName,
					const Size* consoleBufSize,
					console::StrColor* consoleStrColor,
					console::BkgColor* consoleBkgColor,
					FileHandle stdInput,
					FileHandle stdOutput,
					FileHandle stdError
				) {
					ZeroMemory(this, sizeof(*this));
					cb = sizeof(StartupInfo);

					if (desktopName != nullptr)
						lpDesktop = &(*desktopName)[0];
					// set window title
					if (wndTitle != nullptr)
						lpTitle = &(*wndTitle)[0];
					// set window position
					if (wndPos != nullptr)
						dwFlags |= STARTF_USEPOSITION,
						dwX = wndPos->x,
						dwY = wndPos->y;
					// set window size
					if (wndSize != nullptr)
						dwFlags |= STARTF_USESIZE,
						dwXSize = wndSize->x,
						dwYSize = wndSize->y;
					// set console buffer width and height
					if (consoleBufSize != nullptr)
						dwFlags |= STARTF_USECOUNTCHARS,
						dwXCountChars = consoleBufSize->x,
						dwYCountChars = consoleBufSize->y;
					// set console string's and background's color
					if (consoleStrColor != nullptr)
						dwFlags |= STARTF_USEFILLATTRIBUTE,
						dwFillAttribute = unpackEnum(*consoleStrColor);
					if (consoleBkgColor != nullptr)
						dwFlags |= STARTF_USEFILLATTRIBUTE,
						dwFillAttribute = unpackEnum(*consoleBkgColor);
					// set application startup option
					if (startupOptions != nullptr)
						dwFlags |= startupOptions->get();
					// set window show modes
					if (wndShowModes != nullptr)
						dwFlags |= STARTF_USESHOWWINDOW,
						wShowWindow = wndShowModes->get();
					// set standerd IO handle
					if (stdInput != nullptr)
						dwFlags |= STARTF_USESTDHANDLES,
						hStdInput = stdInput;
					if (stdOutput != nullptr)
						dwFlags |= STARTF_USESTDHANDLES,
						hStdOutput = stdOutput;
					if (stdError != nullptr)
						dwFlags |= STARTF_USESTDHANDLES,
						hStdError = stdError;
				}

			};

			inline StartupInfo getLocalStarupInfo() {
				StartupInfo si;
				::GetStartupInfo(&si);

				return std::move(si);
			}
			
			namespace detail {

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

			} // ::wawl::fs::proc::detail
			
			inline bool createProcess(
				ProcessInfo& procInfo,
				const Tstring& cmdLine
				) {
				return
					detail::createProcess(
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
					detail::createProcess(
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
					detail::createProcess(
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
					detail::createProcess(
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
					detail::createProcess(
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
			constexpr std::uint32_t StillActive = STILL_ACTIVE;

			// get exit code of process
			// if the process is still running, return StillActive
			inline std::uint32_t getExitCode(const ProcessInfo& proc) {
				::DWORD exitCode;

				::GetExitCodeProcess(proc.hProcess, &exitCode);

				return exitCode;
			}

		} // ::wawl::fs::proc
	} // ::wawl::fs
} // ::wawl