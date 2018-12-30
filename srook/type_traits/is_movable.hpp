// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_TYPE_TRAITS_IS_MOVABLE_HPP
#define INCLUDED_TYPE_TRAITS_IS_MOVABLE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/remove_reference.hpp>
#include <type_traits>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T, T& (T::*)(T&&)>
struct move_signature {
    typedef T type;
};
template <class T, class = T>
struct move_f_deleted : SROOK_FALSE_TYPE {};
template <class T>
struct move_f_deleted<T, typename enable_if<std::is_pod<typename remove_reference<T>::type>::value, T>::type> : SROOK_TRUE_TYPE {};
template <class T>
struct move_f_deleted<T,typename move_signature<T, &T::operator=> ::type> : SROOK_TRUE_TYPE {};
} // namespace detail

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

template <class T>
struct is_moveable {
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR_OR_CONST bool value = type_traits::detail::move_f_deleted<T>::value;
};

template <class T>
struct is_movable : is_moveable<T> {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_CONSTEXPR_OR_CONST bool is_moveable_v = type_traits::detail::move_f_deleted<T>::value;

template <class T>
SROOK_CONSTEXPR_OR_CONST bool is_movable_v = is_moveable_v<T>;
#endif

} // namespace srook
#endif
