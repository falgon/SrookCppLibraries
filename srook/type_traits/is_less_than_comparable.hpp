// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_LESS_THAN_COMPARABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_LESS_THAN_COMPARABLE_HPP

#include <srook/config.hpp>
#include <srook/utility.hpp>
#include <srook/type_traits/is_convertible.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class = SROOK_DEDUCED_TYPENAME voider<>::type>
struct is_less_than_comparable_impl
    : SROOK_FALSE_TYPE {};

template <class T>
struct is_less_than_comparable_impl<T, SROOK_DEDUCED_TYPENAME voider<SROOK_DECLTYPE(declval<T>() < declval<T>())>::type>
    : is_convertible<SROOK_DECLTYPE(declval<T>() < declval<T>()), bool>::type {};
            
} // namespace detail

template <class T>
struct is_less_than_comparable : public detail::is_less_than_comparable_impl<T> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_less_than_comparable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_less_than_comparable_v = is_less_than_comparable<T>::value;
#endif

} // namespace srook

#endif
