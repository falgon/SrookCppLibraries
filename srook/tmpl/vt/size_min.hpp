// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_SIZE_MIN_HPP
#define INCLUDED_SROOK_TMPL_VT_SIZE_MIN_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/size_compare.hpp>
#include <srook/type_traits/conditional.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class L, class R, template <class, class> class Compare>
struct size_min_impl
    : conditional<Compare<L, R>::type::value, L, R> {};

} // namespace detail

template <class L, class R, template <class, class> class Compare = srook::tmpl::vt::size_lt>
struct size_min : detail::size_min_impl<L, R, Compare> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class R, template <class, class> class Compare = srook::tmpl::vt::size_lt>
using size_min_t = SROOK_DEDUCED_TYPENAME size_min<L, R, Compare>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
