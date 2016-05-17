#pragma once
#define ENABLE_WAWL_BASETYPE

#include <string>
#include <cstdint>

// WinAPI Header
#define NOMINMAX
#include <Windows.h>
#include <tchar.h>
#undef NOMINMAX

namespace wawl {
	namespace base {

		// ascii char type
		using Achar = ::CHAR;
		// wide char type
		using Wchar = ::WCHAR;
		// generic char type
		using Tchar = ::TCHAR;

		// ascii string type
		using Astring = std::basic_string<Achar>;
		// wide string type
		using Wstring = std::basic_string<Wchar>;
		// generic string type
		using Tstring = std::basic_string<Tchar>;
		
		// signed 8bit int
		using Int8 = std::int8_t;
		// signed 16bit int
		using Int16 = std::int16_t;
		// signed 32bit int
		using Int32 = std::int32_t;
		// signed 64bit int
		using Int64 = std::int64_t;

		// unsigned int
		using Uint = unsigned int;
		// unsigned 8bit int
		using Uint8 = ::BYTE;
		// unsigned 16bit int
		using Uint16 = ::WORD;
		// unsigned 32bit int
		using Uint32 = ::DWORD;
		// unsigned 64bit int
		using Uint64 = std::uint64_t;

		// integer which can contain pointer
		using IntPtr = ::INT_PTR;
		// unsigned integer which cantain pointer
		using UintPtr = ::UINT_PTR;
		// larger than IntPtr
		using LongPtr = ::LONG_PTR;

		// any handle
		using Handle = ::HANDLE;
		constexpr Handle InvalidHandle = INVALID_HANDLE_VALUE;
		inline bool closeHandle(Handle h) {
			return ::CloseHandle(h) != 0;
		}

		// application handle
		using AppHandle = ::HINSTANCE;
		using ModuleHandle = ::HINSTANCE;

		struct Position {
			int x, y;

			Position operator + (const Position& p) {
				return Position{ x + p.x, y + p.y };
			}
			Position& operator += (const Position& p) {
				x += p.x;
				y += p.y;
				return *this;
			}
			Position operator - (const Position& p) {
				return Position{ x - p.x, y - p.y };
			}
			Position& operator -= (const Position& p) {
				x -= p.x;
				y -= p.y;
				return *this;
			}
		};
		using Size = Position;

		struct Rect {
			int x, y;
			int w, h;
		};

	} // ::wawl::base

	using namespace base;

} // ::wawl