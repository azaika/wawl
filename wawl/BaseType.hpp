#pragma once
#define WAWL_BASE_TYPE_HPP

#include <string>
#include <cstdint>
#include <type_traits>

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
		
		// unsigned int
		using Uint = unsigned int;

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

		template <typename EnumType, std::underlying_type_t<EnumType> = 0>
		class Flags {
		public:
			using ThisType = Flags<EnumType>;
			using UnderlyingType = std::underlying_type_t<EnumType>;

			constexpr Flags() = default;
			constexpr Flags(const Flags<EnumType>& rhv) = default;
			Flags<EnumType>& operator = (const Flags<EnumType>& rhv) {
				base = rhv.base;
				return *this;
			}

			constexpr Flags(EnumType val) :
				base(static_cast<UnderlyingType>(val)) {}
			constexpr Flags(UnderlyingType val) :
				base(val) {}

			ThisType& merge(UnderlyingType val) {
				base |= val;
				return *this;
			}
			constexpr ThisType operator | (UnderlyingType val) const {
				return ThisType(base | val);
			}
			ThisType& operator |= (UnderlyingType val) {
				base |= val;
				return *this;
			}

			ThisType& rid(UnderlyingType val) {
				base &= (~val);
				return *this;
			}

			explicit operator UnderlyingType() const {
				return base;
			}
			constexpr UnderlyingType get() const {
				return base;
			}

			constexpr bool has(UnderlyingType val) const {
				return ((base & val) ^ val) == 0;
			}

		private:
			UnderlyingType base = 0;

		};

	} // ::wawl::base

	using namespace base;

} // ::wawl