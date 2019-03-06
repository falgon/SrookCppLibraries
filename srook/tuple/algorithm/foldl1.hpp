// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_ALGORITHM_FOLDL1_HPP
#define INCLUDED_SROOK_TUPLE_ALGORITHM_FOLDL1_HPP

#include <srook/tuple/algorithm/foldl.hpp>
#include <srook/tuple/algorithm/drop.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple) {
SROOK_INLINE_NAMESPACE(v1)

template <class F, class T, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT
SROOK_DEDUCED_TYPENAME decay<Init>::type
#else
auto
#endif
foldl1(F&& f, const std::tuple<T, Ts...>& ts) 
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Ts, SROOK_DEDUCED_TYPENAME decay<T>::type>...
    >::value
)
{
    return foldl(srook::forward<F>(f), std::get<0>(ts), drop<1>(ts));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(tuple, srook)

#endif
