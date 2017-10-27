// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_REMOVE_VOLATILE_HPP
#define INCLUDED_SROOK_REMOVE_VOLATILE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct remove_volatile {
    typedef T type;
};

template <class T>
struct remove_volatile<volatile T> {
    typedef T type;
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::remove_volatile;

#if SROOK_CPP_ALIAS_TEMPALTES
template <class T>
using remove_volatile_t = typename remove_volatile<T>::type;
#endif

} // namespace srook

#endif
