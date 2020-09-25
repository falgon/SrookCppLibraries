// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_ALGORITHM_FOLDR_HPP
#define INCLUDED_SROOK_TUPLE_ALGORITHM_FOLDR_HPP

#include <srook/config.hpp>
#include <srook/algorithm/for_each.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_nothrow_invocable.hpp>
#include <srook/type_traits/is_convertible.hpp>
#include <srook/type_traits/is_assignable.hpp>
#include <srook/tuple/algorithm/take.hpp>
#include <srook/tuple/algorithm/reverse.hpp>
#include <srook/utility/index_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class F, class Init>
SROOK_FORCE_INLINE SROOK_CONSTEXPR Init&&
foldr_rec(F&&, Init&& init, const std::tuple<>&) SROOK_NOEXCEPT_TRUE
{
    return srook::forward<Init>(init);
}

template <class F, class Init, class T, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR Init
foldr_rec(F&& f, Init&& acc, const std::tuple<T, Ts...>& ts)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        is_nothrow_invocable<SROOK_DEDUCED_TYPENAME deacy<F>::type, T, SROOK_DEDUCED_TYPENAME decay<Init>::type>,
        is_nothrow_invocable<SROOK_DEDUCED_TYPENAME deacy<F>::type, Ts, SROOK_DEDUCED_TYPENAME decay<Init>::type>...
    >::value
)
{
    return foldr_rec(f, f(std::get<std::tuple_size<std::tuple<T, Ts...>>::value - 1>(ts), acc), take<std::tuple_size<std::tuple<T, Ts...>>::value - 1>(ts));
}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
template <bool>
struct foldr_impl {
    template <class F, class Init, class... Ts>
    SROOK_FORCE_INLINE static SROOK_CXX14_CONSTEXPR auto
    exec(F&& f, Init&& acc, const std::tuple<Ts...>& ts) 
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Ts, SROOK_DEDUCED_TYPENAME decay<Init>::type>...
        >::value
    )
    {
        SROOK_DEDUCED_TYPENAME decay<Init>::type res = srook::forward<Init>(acc);
        srook::for_each(tuple::reverse(ts), [&f, &res](auto&& x) SROOK_CXX17_CONSTEXPR { res = f(srook::forward<SROOK_DECLTYPE(x)>(x), res); });
        return res;
    }
};

template <>
struct foldr_impl<false> {
    template <class F, class Init, class... Ts>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR auto
    exec(F&& f, Init&& acc, const std::tuple<Ts...>& ts)
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Ts, SROOK_DEDUCED_TYPENAME decay<Init>::type>...
        >::value
    )
    {
        return foldr_rec(srook::forward<F>(f), srook::forward<Init>(acc), ts);
    }
};
#endif

} // namespace detail

template <class F, class Init, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT
SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<
        is_convertible<Init, Ts>...,
        is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Ts, SROOK_DEDUCED_TYPENAME decay<Init>::type>...
    >::value, 
    SROOK_DEDUCED_TYPENAME decay<Init>::type
>::type
#else
auto
#endif
foldr(F&& f, Init&& acc, const std::tuple<Ts...>& ts) 
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Ts, SROOK_DEDUCED_TYPENAME decay<Init>::type>...
    >::value
)
{
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT
    return detail::foldr_rec(srook::forward<F>(f), srook::forward<Init>(acc), ts);
#else
    return detail::foldr_impl<is_assignable<SROOK_DEDUCED_TYPENAME decay<Init>::type&, SROOK_DEDUCED_TYPENAME decay<Init>::type>::value>::exec(srook::forward<F>(f), srook::forward<Init>(acc), ts);
#endif
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(tuple, srook)

#endif
