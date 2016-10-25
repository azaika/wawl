#pragma once

#define WAWL_BASE_UTILITY_HPP

#include <type_traits>

#include "BaseType.hpp"
#include "Detail.hpp"

namespace wawl {

	// convert Astring to Wstring
	Wstring toWstring(const Astring& str) {
		size_t wstrLen;
		// get size and check error on convert
		if (mbstowcs_s(&wstrLen, nullptr, 0, str.c_str(), 0) != 0)
			return Wstring();

		// convert
		Wstring wstrBuf(wstrLen, L'\0');
		if (mbstowcs_s(&wstrLen, &wstrBuf[0], wstrLen, str.c_str(), str.size()) != 0)
			wstrBuf.clear();

		return wstrBuf;
	}
	// convert Wstring to Astring
	Astring toAstring(const Wstring& wstr) {
		size_t astrLen;
		// get size and check error on convert
		if (wcstombs_s(&astrLen, nullptr, 0, wstr.c_str(), 0) != 0)
			return Astring();

		// convert
		Astring astrBuf(astrLen, '\0');
		if (wcstombs_s(&astrLen, &astrBuf[0], astrLen, wstr.c_str(), wstr.size()) != 0)
			astrBuf.clear();

		return astrBuf;
	}

#ifdef UNICODE

	inline Tstring toTstring(const Wstring& str) {
		return Tstring(str);
	}
	inline Tstring toTstring(const Astring& str) {
		return toWstring(str);
	}
	template<typename T>
	inline Tstring valToTstr(const T& val) {
		return std::to_wstring(val);
	}

#else //UNICODE

	inline Tstring toTstring(const Astring& str) {
		return Tstring(str);
	}
	inline Tstring toTString(const Wstring& str) {
		return toAstring(str);
	}
	template<typename T>
	inline Tstring valToTstr(const T& val) {
		return std::to_string(val);
	}

#endif //UNICODE
	
	// get underlying value of enum
	template <typename EnumType, std::underlying_type_t<EnumType> = 0>
	constexpr auto unpackEnum(EnumType val) {
		return static_cast<std::underlying_type_t<EnumType>>(val);
	}

	template <typename EnumType, std::underlying_type_t<EnumType>  = 0>
	constexpr bool hasIncluded(EnumType base, EnumType val) {
		auto unpacked = unpackEnum(val);
		return static_cast<std::underlying_type_t<EnumType>>(base) & unpacked == unpacked;
	}

	template <
		typename T,
		detail::FlagEnablerType<T> = nullptr >
	constexpr Flags<T> operator | (T lhv, T rhv) {
		return Flags<T>(unpackEnum(lhv) | unpackEnum(rhv));
	}

} // ::wawl