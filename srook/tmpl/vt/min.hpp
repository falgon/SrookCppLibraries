// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_MIN_HPP
#define INCLUDED_SROOK_TMPL_VT_MIN_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/compare.hpp>
#include <srook/type_traits/conditional.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class L, class R, template <class, class> class Compare>
struct min_impl
    : conditional<Compare<L, R>::type::value, L, R> {};

} // namespace detail

template <class L, class R, template <class, class> class Compare = srook::tmpl::vt::lt>
struct min : detail::min_impl<L, R, Compare> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R, template <class, class> class Compare = srook::tmpl::vt::lt>
using min_t = SROOK_DEDUCED_TYPENAME min<L, R, Compare>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
