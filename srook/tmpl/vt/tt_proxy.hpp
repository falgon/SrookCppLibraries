// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_TYPE_PROXY_HPP
#define INCLUDED_SROOK_TMPL_VT_TYPE_PROXY_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <template <class...> class MF>
struct tt_proxy {
    template <class... Xs>
    struct type : MF<Xs...>::type {};

    template <class... Xs>
    struct ftype : MF<Xs...> {};
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
