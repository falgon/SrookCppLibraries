// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <cstddef>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct remove_all_extents {
	typedef T type;
};

template <class T, std::size_t Size>
struct remove_all_extents<T[Size]> {
	typedef typename remove_all_extents<T>::type type;
};

template <class T>
struct remove_all_extents<T[]> {
	typedef typename remove_all_extents<T>::type type;
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::remove_all_extents;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T, std::size_t Size>
using remove_all_extents_t = typename remove_all_extents<T>::type;
#endif

} // namespace srook

#endif
