// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_MAX_HPP
#define INCLUDED_SROOK_TMPL_VT_MAX_HPP

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
struct max_impl
    : conditional<Compare<L, R>::type::value, R, L> {};

} // namespace detail

template <class L, class R, template <class, class> class Compare = srook::tmpl::vt::lt>
struct max : detail::max_impl<L, R, Compare> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R, template <class, class> class Compare = srook::tmpl::vt::lt>
using max_t = SROOK_DEDUCED_TYPENAME max<L, R, Compare>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
