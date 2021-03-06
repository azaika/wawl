#pragma once

#include <type_traits>

#define WAWL_DETAiL_HPP

// define setter of the member
#define WAWL_DETAIL_DEFINE_SETTER(func, type, member) \
auto& func (type v) { this->##member = v; return *this; } \

namespace wawl {
	namespace detail {

		template <typename T>
		struct FlagEnabler {
			using Type = void;
		};

		template <typename T>
		using FlagEnablerType = typename FlagEnabler<T>::Type;

	} // wawl::detail
} // wawl

#define WAWL_DETAIL_ENABLE_FLAG(type) \
template <> \
struct ::wawl::detail::FlagEnabler<type> { \
	using Type = std::nullptr_t; \
};
