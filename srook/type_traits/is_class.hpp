// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_CLASS_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_CLASS_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/libraries/nullptr.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T>
char test(int T::*);
struct two {
    char c[2];
};
template <class T>
two test(...);

template <class T>
struct is_class {
    enum { value = sizeof(detail::test<T>(0)) == 1 };
};
template <>
struct is_class<SROOK_NULLPTR_T> : SROOK_FALSE_TYPE {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::is_class;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
constexpr bool is_class_v = type_traits::detail::is_class<T>::value;
#endif

} // namespace srook
#endif
