#pragma once

#define ENABLE_WAWL_BASEUTILITY

#include <type_traits>

#include "BaseType.hpp"

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
	constexpr auto unpackEnum(const EnumType& val) {
		return static_cast<std::underlying_type_t<EnumType>>(val);
	}

#define WAWL_ENABLE_ENUM_COMPOSE(type) \
	constexpr type composeEnum(type lhv, type rhv) { \
		return static_cast<type>(unpackEnum(lhv) | unpackEnum(rhv)); \
	} \
	template <typename... Others> \
	constexpr type composeEnum(type arg1, type arg2, type arg3, Others... others) { \
		return static_cast<type>(unpackEnum(arg1) | unpackEnum(composeEnum(arg2, arg3, others...))); \
	} \
	inline type& mergeEnum(type& lhv, type rhv) { \
		lhv = static_cast<type>(unpackEnum(lhv) | unpackEnum(rhv)); \
		return lhv; \
	} \
	template <typename... Others> \
	type& mergeEnum(type& arg1, type arg2, type arg3, Others... others) { \
		arg1 = static_cast<type>( \
			unpackEnum(arg1) \
			| unpackEnum( \
				composeEnum(arg2, arg3, others...) \
			) \
			); \
		return arg1; \
	} \
	constexpr type operator | (type lhv, type rhv) { \
		return composeEnum(lhv, rhv); \
	} \
	inline type& operator |= (type& lhv, type rhv) { \
		return mergeEnum(lhv, rhv); \
	}

} // ::wawl