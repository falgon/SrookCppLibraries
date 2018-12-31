// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_PREPROCESSOR_IS_TYPENAME_HPP
#define INCLUDED_SROOK_PREPROCESSOR_IS_TYPENAME_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/type_traits/true_false_type.hpp>

namespace srook { namespace preprocessor { namespace detail {

template <class>
struct is_typename : SROOK_FALSE_TYPE {};

template <class T>
struct is_typename<void (char (T))> : SROOK_TRUE_TYPE {};

} } } // namespace detail, preprocessor, srook

#define SROOK_PP_IS_TYPENAME(x) srook::preprocessor::detail::is_typename<void (char(x))>::value

#endif
