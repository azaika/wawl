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
		const Handle InvalidHandle = INVALID_HANDLE_VALUE;
		inline bool closeHandle(Handle h) {
			return ::CloseHandle(h) != 0;
		}

		// application handle
		using AppHandle = ::HINSTANCE;
		using ModuleHandle = ::HINSTANCE;

		struct Position {
			long x = 0, y = 0;

			constexpr Position() = default;
			constexpr Position(const Position&) = default;
			constexpr Position& operator = (const Position&) = default;

			constexpr Position(long _x, long _y) :
				x(_x), y(_y) {}
			constexpr Position(const ::POINT& p) :
				x(p.x), y(p.y) {}

			constexpr Position operator + (const Position& p) {
				return Position{ x + p.x, y + p.y };
			}
			constexpr Position& operator += (const Position& p) {
				x += p.x;
				y += p.y;
				return *this;
			}
			constexpr Position operator - (const Position& p) {
				return Position{ x - p.x, y - p.y };
			}
			constexpr Position& operator -= (const Position& p) {
				x -= p.x;
				y -= p.y;
				return *this;
			}

			constexpr operator const ::POINT& () {
				return *reinterpret_cast<::POINT*>(this);
			}
			constexpr operator const ::POINT& () const {
				return *reinterpret_cast<const ::POINT*>(this);
			}
		};
		using Size = Position;

		struct Rect {
			long x = 0, y = 0;
			long w = 0, h = 0;

			constexpr Rect() = default;
			constexpr Rect(const Rect&) = default;

			constexpr Rect(long _x, long _y, long _w, long _h) :
				x(_x), y(_y), w(_w), h(_h) {}
			constexpr Rect(const Position& p, long _w, long _h) :
				x(p.x), y(p.y), w(_w), h(_h) {}
			constexpr Rect(long _x, long _y, const Size& size) :
				x(_x), y(_y), w(size.x), h(size.y) {}
			constexpr Rect(const Position& p, const Size& size) :
				x(p.x), y(p.y), w(size.x), h(size.y) {}

			constexpr Rect(const ::RECT& rect) :
				x(rect.left),
				y(rect.top),
				w(rect.right - rect.left),
				h(rect.bottom - rect.top) {}

			constexpr operator ::RECT() const {
				return{ x, y, x + w, y + h };
			}
		};

		template <typename EnumType, std::underlying_type_t<EnumType> = 0>
		class Flags {
		public:
			using ThisType = Flags<EnumType>;
			using UnderlyingType = std::underlying_type_t<EnumType>;

			constexpr Flags() = default;
			constexpr Flags(const Flags&) = default;
			Flags<EnumType>& operator = (const Flags<EnumType>& rhv) {
				base = rhv.base;
				return *this;
			}

			constexpr Flags(EnumType val) :
				base(static_cast<UnderlyingType>(val)) {}
			constexpr Flags(UnderlyingType val) :
				base(val) {}

			constexpr ThisType& merge(UnderlyingType val) {
				base |= val;
				return *this;
			}
			constexpr ThisType operator | (UnderlyingType val) const {
				return ThisType(base | val);
			}
			constexpr ThisType& operator |= (UnderlyingType val) {
				base |= val;
				return *this;
			}

			constexpr ThisType& rid(UnderlyingType val) {
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