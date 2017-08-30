// Copyright (C) 2017 roki
#ifndef INCLUDED_TYPE_TRAITS_IS_COPYABLE_HPP
#define INCLUDED_TYPE_TRAITS_IS_COPYABLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <type_traits>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T, T &(T::*)(const T &)>
struct copy_signature {
    typedef T type;
};
template <class T, class = T>
struct copy_f_deleted : std::false_type {
};
template <class T>
struct copy_f_deleted<T, std::enable_if_t<std::is_pod<std::remove_reference_t<T>>{}, T>> : std::true_type {
};
template <class T>
    struct copy_f_deleted < T,
    typename copy_signature < T, &T::operator=> ::type> : std::true_type {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

template <class T>
struct is_copyable {
    SROOK_INLINE_VARIABLE static constexpr bool value = type_traits::detail::copy_f_deleted<T>::value;
};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
constexpr bool is_copyable_v = type_traits::detail::copy_f_deleted<T>::value;
#endif

} // namespace srook
#endif
