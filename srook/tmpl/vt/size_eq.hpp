// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_SIZE_EQ_HPP
#define INCLUDED_SROOK_TMPL_VT_SIZE_EQ_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/type_traits/bool_constant.hpp>
#include <srook/tmpl/vt/size.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <std::size_t x, class... Ts>
struct size_eq : public bool_constant<x == size<Ts...>::value> {}; 

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
