// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_ALROTIHM_ITERATE_HPP
#define INCLUDED_SROOK_TUPLE_ALROTIHM_ITERATE_HPP

#include <srook/config.hpp>
#include <tuple>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/replicate.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_nothrow_invocable.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/enable_if.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t N, class Res>
struct iterate_impl {
    template <class F, class T, class... Ts>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR Res 
    execute(F&& f, T&& val, Ts&&... ts)
    {
        return iterate_impl<N - 1, Res>::execute(f, f(val), srook::forward<Ts>(ts)..., val);
    }
};

template <class Res>
struct iterate_impl<1, Res> {
    template <class F, class T, class... Ts>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR Res
    execute(F&&, T&& val, Ts&&... ts) SROOK_NOEXCEPT_TRUE
    {
        return std::make_tuple(srook::forward<Ts>(ts)..., srook::forward<T>(val));
    }
};

template <class Res>
struct iterate_impl<0, Res> {
    template <class F, class... Ts>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR Res
    execute(F&&, Ts&&...) SROOK_NOEXCEPT_TRUE
    {
        return std::make_tuple();
    }
};

} // namespace detail

template <std::size_t N, class F, class T>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<
    is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, T&&>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::tuple, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<N, SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type, T&&>::type>::type 
    >::type
>::type
iterate(F&& f, T&& val) SROOK_NOEXCEPT(is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, T&&>::value)
{
    typedef 
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            std::tuple,
            SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<N, SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type, T&&>::type>::type
        >::type result_type;
    
    return detail::iterate_impl<N, result_type>::execute(srook::forward<F>(f), srook::forward<T>(val));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(tuple, srook)

#endif
