// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_REMOVE_CONST_HPP
#define INCLUDED_SROOK_REMOVE_CONST_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct remove_const {
    typedef T type;
};

template <class T>
struct remove_const<const T> {
    typedef T type;
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::remove_const;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
using remove_const_t = typename remove_const<T>::type;
#endif

} // namespace srook

#endif
