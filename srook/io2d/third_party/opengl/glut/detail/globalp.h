// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENGL_GLUT_DETAIL_GLOBALP_H
#define INCLUDED_SROOK_IO2D_THIRD_PARTY_OPENGL_GLUT_DETAIL_GLOBALP_H

#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

SROOK_NESTED_NAMESPACE(srook, io2d, glut) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class>
struct globalp;

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(glut, io2d, srook)

#endif
#endif
