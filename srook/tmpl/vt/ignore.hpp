// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_IGNORE_HPP
#define INCLUDED_SROOK_TMPL_VT_IGNORE_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class X>
struct ignore {
    template <class...>
    struct generate : type_constant<X> {};
};

#if SROOK_CPP_ALIAS_TEMPLATES
template <class X>
using ignore_generate = SROOK_DEDUCED_TYPENAME ignore<X>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
