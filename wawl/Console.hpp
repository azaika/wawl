#pragma once
#define ENABLE_WAWL_CONSOLE

#include "ConsoleBaseType.hpp"
#include "BaseUtility.hpp"

namespace wawl {
	namespace fs {
		namespace console {

			inline bool allocConsole() {
				return AllocConsole() != 0;
			}
			inline bool freeConsole() {
				return FreeConsole() != 0;
			}

			inline FileHandle getStdInput() {
				return ::GetStdHandle(STD_INPUT_HANDLE);
			}
			inline FileHandle getStdOutput() {
				return ::GetStdHandle(STD_OUTPUT_HANDLE);
			}
			inline FileHandle getStdError() {
				return ::GetStdHandle(STD_ERROR_HANDLE);
			}

			// write to console
			// return written size
			inline Uint32 writeConsole(
				FileHandle consoleOutput,
				const Tstring& str
				) {
				Uint32 writtenSize;

				bool isSuccess = ::WriteConsole(
					consoleOutput,
					str.c_str(),
					static_cast<Uint32>(str.size() + 1),
					&writtenSize,
					nullptr
					) != 0;

				return (isSuccess ? writtenSize : 0);
			}

			inline Uint32 readConsole(
				FileHandle consoleInput,
				Tstring& buffer,
				Uint32 size
				) {
				Uint32 readSize;

				buffer.resize(size);

				bool isSuccess = ::ReadConsole(
					consoleInput,
					&buffer[0],
					size,
					&readSize,
					nullptr
					) != 0;

				return (isSuccess ? readSize : 0);
			}

			inline bool setConsoleStrColor(
				FileHandle consoleOutput,
				StrColor color
				) {
				return ::SetConsoleTextAttribute(consoleOutput, unpackEnum(color)) != 0;
			}

		} // ::wawl::fs::console
	} // ::wawl::fs
} // ::wawl