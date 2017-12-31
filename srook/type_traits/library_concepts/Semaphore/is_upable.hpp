// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_UPABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_UPABLE_HPP
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/declval.hpp>
#include <srook/utility/void_t.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class, class = SROOK_DEDUCED_TYPENAME voider<void>::type>
struct is_upable : public SROOK_FALSE_TYPE {};

template <class T>
struct is_upable<
    T,
    SROOK_DEDUCED_TYPENAME voider<
        SROOK_DECLTYPE(declval<T>().up()),
        SROOK_DECLTYPE(declval<T>().resource())>::type> : public SROOK_TRUE_TYPE {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_upable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_upable_v = is_upable<T>::value;
#endif

} // namespace srook

#endif
