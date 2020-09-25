// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_UTILITY_DECLVAL_HPP
#define INCLUDED_SROOK_UTILITY_DECLVAL_HPP

#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/type_traits/add_rvalue_reference.hpp>

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
typename srook::add_rvalue_reference<T>::type declval() SROOK_NOEXCEPT_TRUE;

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::declval;

} // namespace srook

#endif
