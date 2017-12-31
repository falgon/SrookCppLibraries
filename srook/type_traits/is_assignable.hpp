// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_ASSIGNABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_ASSIGNABLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature.hpp>
#include <srook/type_traits/detail/sfinae_types.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/utility/declval.hpp>
namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, class U>
class is_assignable_impl : public sfinae_types {
    template <class T1, class U1>
    static SROOK_DECLTYPE((srook::declval<T1>() = srook::declval<U1>(), one())) test(int);
    template <class, class>
    static two test(...);

public:
    static SROOK_CONSTEXPR_OR_CONST bool value = sizeof(test<T, U>(0)) == 1;
};

} // namespace detail

template <class T, class U>
struct is_assignable : public srook::integral_constant<bool, detail::is_assignable_impl<T, U>::value> {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_assignable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class U>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_assignable_v = is_assignable<T, U>::value;
#endif

} // namespace srook

#endif
