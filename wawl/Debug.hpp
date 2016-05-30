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
		inline bool activateDebugger(std::uint32_t procID) {
			return ::DebugActiveProcess(procID) != 0;
		}

		// stop debugging for the process
		inline bool stopDebugger(std::uint32_t procID) {
			return ::DebugActiveProcessStop(procID) != 0;
		}

		static auto& occurLocalDebugException = ::DebugBreak;
		inline bool occurDebugException(Handle procHandle) {
			return ::DebugBreakProcess(procHandle) != 0;
		}

		static auto& fatalExit = ::FatalExit;

		inline bool isDebuggerPresent() {
			return ::IsDebuggerPresent() != 0;
		}

		inline std::uint32_t readMemory(
			Handle procHandle,
			const void* begin,
			std::uint8_t* buffer,
			std::uint32_t n
		) {
			::DWORD readByte;

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
		inline std::uint32_t readMemory(
			Handle procHandle,
			const void* begin,
			std::vector<std::uint8_t>& buffer,
			std::uint32_t n
		) {
			buffer.resize(n);
			return
				readMemory(procHandle, begin, buffer.data(), n);
		}

		inline std::uint32_t writeMemory(
			Handle procHandle,
			const void* begin,
			std::vector<std::uint8_t>& buffer
		) {
			::DWORD writtenSize;

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

	} // ::wawl::debug
} // ::wawl