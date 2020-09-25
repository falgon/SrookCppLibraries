// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_TYPE_TRAITS_IS_COPYABLE_HPP
#define INCLUDED_TYPE_TRAITS_IS_COPYABLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/remove_reference.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <type_traits>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T, T& (T::*)(const T&)>
struct copy_signature {
    typedef T type;
};
template <class T, class = T>
struct copy_f_deleted : std::false_type {
};
template <class T>
struct copy_f_deleted<T, typename enable_if<std::is_pod<typename remove_reference<T>::type>::value, T>::type> : std::true_type {};
template <class T>
    struct copy_f_deleted < T,
    typename copy_signature < T, &T::operator=> ::type> : std::true_type {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

template <class T>
struct is_copyable {
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR_OR_CONST bool value = type_traits::detail::copy_f_deleted<T>::value;
};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR_OR_CONST bool is_copyable_v = type_traits::detail::copy_f_deleted<T>::value;
#endif

} // namespace srook
#endif
