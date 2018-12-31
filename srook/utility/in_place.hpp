// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_UTILITY_IN_PLACE_HPP
#define INCLUDED_SROOK_UTILITY_IN_PLACE_HPP
#include <cstddef>
#include <srook/config/compiler.hpp>
#include <srook/config/feature.hpp>

namespace srook{
SROOK_INLINE_NAMESPACE(v1)

SROOK_CONSTEXPR struct in_place_t {
	explicit in_place_t() SROOK_DEFAULT
} in_place{};

template<class T>
struct in_place_type_t{
	explicit in_place_type_t() SROOK_DEFAULT
};
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT && SROOK_CPP_VARIABLE_TEMPLATES
template<class T>
SROOK_CONSTEXPR_OR_CONST in_place_type_t<T> in_place_type{};
#endif

template<std::size_t I>
struct in_place_index_t{
	explicit in_place_index_t() SROOK_DEFAULT
};

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT && SROOK_CPP_VARIABLE_TEMPLATES
template<std::size_t I>
SROOK_CONSTEXPR_OR_CONST in_place_index_t<I> in_place_index{};
#endif
SROOK_INLINE_NAMESPACE_END
} // srook
#endif
