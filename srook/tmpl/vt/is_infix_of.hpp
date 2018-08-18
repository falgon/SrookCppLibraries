// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_IS_INFIX_OF_HPP
#define INCLUDED_SROOK_TMPL_VT_IS_INFIX_OF_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/any.hpp>
#include <srook/tmpl/vt/is_prefix_of.hpp>
#include <srook/tmpl/vt/tails.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class Xs, class Ys>
struct is_infix_of_impl {
private:
    template <class R>
    struct F : is_prefix_of<Xs, R>::type {};
public:
    typedef SROOK_DEDUCED_TYPENAME any<F, SROOK_DEDUCED_TYPENAME tails<Ys>::type>::type type;
};

} // namespace detail

template <class, class...>
struct is_infix_of;

template <class... Xs, class... Ys>
struct is_infix_of<packer<Xs...>, packer<Ys...>> 
    : detail::is_infix_of_impl<packer<Xs...>, packer<Ys...>> {};

template <class... Xs, class... Ys>
struct is_infix_of<packer<Xs...>, Ys...>
    : detail::is_infix_of_impl<packer<Xs...>, packer<Ys...>> {};
    
#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class... R>
using is_infix_of_t = SROOK_DEDUCED_TYPENAME is_infix_of<L, R...>::type;
#endif

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class L, class... R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_infix_of_v = is_infix_of<L, R...>::type::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)
#endif
