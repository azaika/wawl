#pragma once
#define ENABLE_WAWL_DEBUG

#include "BaseType.hpp"
#include <vector>

namespace wawl {
	namespace debug {

		// print a degug string to debug console
		inline void print(const Tstring& str) {
			::OutputDebugString(str.c_str());
		}

		// activate debugging for the process
		inline bool activateDebugger(Uint32 procID) {
			return ::DebugActiveProcess(procID) != 0;
		}

		// stop debugging for the process
		inline bool stopDebugger(Uint32 procID) {
			return ::DebugActiveProcessStop(procID) != 0;
		}

		static auto& occurLocalDebugException = ::DebugBreak;
		static auto& occurDebugException = ::DebugBreakProcess;

		static auto& fatalExit = ::FatalExit;

		inline bool isDebuggerPresent() {
			return ::IsDebuggerPresent() != 0;
		}

		inline Uint32 readMemory(
			Handle procHandle,
			const void* begin,
			Uint8* buffer,
			Uint32 n
		) {
			Uint32 readByte;

			return (
				::ReadProcessMemory(
					procHandle,
					begin,
					static_cast<void*>(buffer),
					n,
					&readByte
				) != 0
				? readByte
				: 0
				);
		}
		inline Uint32 readMemory(
			Handle procHandle,
			const void* begin,
			std::vector<Uint8>& buffer,
			Uint32 n
		) {
			buffer.resize(n);
			return
				readMemory(procHandle, begin, buffer.data(), n);
		}

		inline Uint32 writeMemory(
			Handle procHandle,
			const void* begin,
			std::vector<Uint8> buffer
		) {
			Uint32 writtenSize;

			return (
				::WriteProcessMemory(
					procHandle,
					const_cast<void*>(begin),
					buffer.data(),
					buffer.size(),
					&writtenSize
				)
				? writtenSize
				: 0
				);
		}

	} // ::wawl::fs::debug
} // ::wawl