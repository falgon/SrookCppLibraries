// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_REPLICATE_HPP
#define INCLUDED_SROOK_TUPLE_REPLICATE_HPP
#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
#include <srook/utility/forward.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/replicate.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <std::size_t I>
struct replicator {
    template <class T, class... Ts,
    SROOK_REQUIRES(type_traits::detail::Land<is_same<SROOK_DEDUCED_TYPENAME decay<T>::type, SROOK_DEDUCED_TYPENAME decay<Ts>::type>...>::value)>
    static SROOK_CONSTEXPR auto execute(T&& val, Ts&&... vals) SROOK_NOEXCEPT_TRUE
    {
        return replicator<I - 1>::execute(val, val, std::forward<Ts>(vals)...);
    }
};

template <>
struct replicator<1> {
    template <class... Ts>
    static SROOK_CONSTEXPR std::tuple<SROOK_DEDUCED_TYPENAME decay<Ts>::type...> 
    execute(Ts&&... val) SROOK_NOEXCEPT_TRUE
    {
        return std::make_tuple(std::forward<Ts>(val)...);
    }
};

template <>
struct replicator<0> {
    template <class... Ts>
    static SROOK_CONSTEXPR std::tuple<>
    execute(Ts&&...) SROOK_NOEXCEPT_TRUE
    {
        return std::make_tuple();
    }
};

} // namespace detail

template <std::size_t I, class T>
SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<I, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
replicate(T&& val) SROOK_NOEXCEPT_TRUE
{
    return detail::replicator<I>::execute(srook::forward<T>(val));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(tuple, srook)

#endif
#endif
