// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_TRANSFER_HPP
#define INCLUDED_SROOK_TMPL_VT_TRANSFER_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <template <class...> class Tuple, class... Ts>
struct transfer : public detail::Transfer<Tuple, Ts...> {};

template <template <class...> class Tuple, class... Ts>
struct transfer<Tuple, packer<Ts...>> : public transfer<Tuple, Ts...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class Tuple, class... Ts>
using transfer_t = SROOK_DEDUCED_TYPENAME transfer<Tuple, Ts...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
