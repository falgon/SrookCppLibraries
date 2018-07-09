// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_ITERATE_HPP
#define INCLUDED_SROOK_TMPL_VT_ITERATE_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/erase_packer.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t i, template <class> class F, class X>
struct iterate_impl
    : concat<X, SROOK_DEDUCED_TYPENAME iterate_impl<i - 1, F, SROOK_DEDUCED_TYPENAME F<X>::type>::type> {};

template <template <class> class F, class X>
struct iterate_impl<0, F, X>
    : type_constant<packer<>> {};

} // namespace detail

template <std::size_t i, template <class> class F, class X>
struct iterate : detail::iterate_impl<i, F, X> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t i, template <class> class F, class X>
using iterate_t = SROOK_DEDUCED_TYPENAME iterate<i, F, X>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
