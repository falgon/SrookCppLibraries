// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/noexcept_detection.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T, T v>
struct integral_constant {
	static SROOK_CONSTEXPR T value = v;
	typedef T value_type;
	typedef integral_constant type;

	SROOK_CONSTEXPR operator value_type() SROOK_NOEXCEPT_TRUE { return value; }
	SROOK_CONSTEXPR value_type operator()() const SROOK_NOEXCEPT_TRUE { return value; }
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::integral_constant;

} // namespace srook

#endif
