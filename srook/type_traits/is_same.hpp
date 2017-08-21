// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_SAME_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_SAME_HPP

#if (__has_include(<type_traits>) || (__cplusplus == 201103L))
#include <type_traits>
#define IS_SAME(L, R) std::is_same<L, R>::value
#elif __has_include(<boost/type_traits/is_same.hpp>)
#include <boost/type_traits/is_same.hpp>
#define IS_SAME(L, R) boost::is_same<L, R>::value
#else

#include <srook/type_traits/true_false_type.hpp>

namespace srook {

#if __cplusplus > 201103L
inline namespace v1 {
#endif

template <class, class>
struct is_same : SROOK_FALSE_TYPE {
};

template <class T>
struct is_same<T, T> : SROOK_TRUE_TYPE {
};

#if __cplusplus > 201103L

template <class L, class R>
constexpr bool is_same_v = is_same<L, R>::value;

} // inline namespace v1

#endif

#define IS_SAME(L, R) srook::is_same<L, R>::value

#endif
#endif
