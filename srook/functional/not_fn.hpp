// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_FUNCTIONAL_NOT_FN_HPP
#define INCLUDED_SROOK_FUNCTIONAL_NOT_FN_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/is_nothrow_constructible.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/utility/declval.hpp>
#include <srook/functional/invoke.hpp>
#include <type_traits>

SROOK_NESTED_NAMESPACE(srook, functional) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class Fn>
class not_fnfn {
    template <class T>
    static SROOK_DECLTYPE(!std::declval<T>()) not_decl() SROOK_NOEXCEPT(!declval<T>());
public:
    template <class Fn2>
    not_fnfn(Fn2&& f, int)
        : fn_(srook::forward<Fn2>(f)) {}
    not_fnfn(const not_fnfn&) SROOK_DEFAULT
    not_fnfn(not_fnfn&&) SROOK_DEFAULT
    //SROOK_DEDUCED_TYPENAME srook::invoke_result<Fn QUALS, Args...>::type\
    //SROOK_NOEXCEPT(not_decl<SROOK_DEDUCED_TYPENAME srook::invoke_result<Fn QUALS, Args...>::type>())\

#define SROOK_NOT_FN_CALL_OP(QUALS)\
    template <class... Args>\
    SROOK_DEDUCED_TYPENAME srook::invoke_result<Fn, Args...>::type operator()(Args&&... args) QUALS\
    SROOK_NOEXCEPT(srook::invoke(declval<Fn QUALS&>(), srook::forward<Args>(args)...))\
    {\
        return !srook::invoke(srook::forward<Fn QUALS>(fn_), srook::forward<Args>(args)...);\
    }
    SROOK_NOT_FN_CALL_OP(&)
    SROOK_NOT_FN_CALL_OP(const &)
    SROOK_NOT_FN_CALL_OP(&&)
    SROOK_NOT_FN_CALL_OP(const &&)
#undef SROOK_NOT_FN_CALL_OP
private:
    Fn fn_;
};

} // namespace detail

template <class Fn>
SROOK_FORCE_INLINE detail::not_fnfn<SROOK_DEDUCED_TYPENAME decay<Fn>::type>
not_fn(Fn&& fn) SROOK_NOEXCEPT(is_nothrow_constructible<SROOK_DEDUCED_TYPENAME decay<Fn>::type, Fn&&>::value)
{
    return detail::not_fnfn<SROOK_DEDUCED_TYPENAME decay<Fn>::type>{ srook::forward<Fn>(fn), 0 };
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(functional, srook)
#endif
#endif
