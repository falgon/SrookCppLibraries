// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP

#include <srook/type_traits/is_convertible.hpp>
#include <srook/type_traits/is_nothrow_constructible.hpp>
#include <srook/type_traits/is_nothrow_invocable.hpp>
#include <srook/utility/void_t.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class, class = SROOK_DEDUCED_TYPENAME voider<void>::type>
struct is_nt_invocable_r_impl : SROOK_FALSE_TYPE {};

template <class Result, class Ret>
struct is_nt_invocable_r_impl<Result, Ret, SROOK_DEDUCED_TYPENAME voider<SROOK_DEDUCED_TYPENAME Result::type>::type>
    : Land<is_convertible<SROOK_DEDUCED_TYPENAME Result::type, Ret>, is_nothrow_constructible<Ret, SROOK_DEDUCED_TYPENAME Result::type> > {};

template <class Result>
struct is_nt_invocable_r_impl<Result, void, SROOK_DEDUCED_TYPENAME voider<SROOK_DEDUCED_TYPENAME Result::type>::type>
    : SROOK_TRUE_TYPE {};

} // namespace detail

template <class Ret, class F, class... Args>
struct is_nothrow_invocable_r
    : detail::Land<detail::is_nt_invocable_r_impl<detail::invoke_resulter<F, Args...>, Ret>, detail::call_is_nothrow<F, Args...> >::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_nothrow_invocable_r;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class F, class... Args>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<F, Args...>::value;
#endif

} // namespace srook

#endif
