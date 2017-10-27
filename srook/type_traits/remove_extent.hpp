// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_REMOVE_EXTENT_HPP
#define INCLUDED_SROOK_REMOVE_EXTENT_HPP
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <typename T>
struct remove_extent {
    typedef T type;
};

template <class T, std::size_t Size>
struct remove_extent<T[Size]> {
    typedef T type;
};

template <class T>
struct remove_extent<T[]> {
    typedef T type;
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::remove_extent;

#if SROOK_CPP_ALIAS_TEMPALTES
template <class T>
using remove_extent_t = typename remove_extent<T>::type;
#endif

} // namespace srook

#endif
