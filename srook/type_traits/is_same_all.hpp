// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_SAME_ALL_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_SAME_ALL_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <type_traits>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <bool, class, class...>
struct SROOK_DEPRECATED is_same_all_core : SROOK_FALSE_TYPE {
};
template <class Target, class Head, class... Tail>
struct SROOK_DEPRECATED is_same_all_core<true, Target, Head, Tail...> {
    static constexpr bool value = is_same_all_core<std::is_same<Target, Head>::value, Tail...>::value;
};
template <class Target>
struct SROOK_DEPRECATED is_same_all_core<true, Target> : SROOK_TRUE_TYPE {
};
template <class Target>
struct SROOK_DEPRECATED is_same_all_core<false, Target> : SROOK_FALSE_TYPE {
};
template <class, class...>
struct SROOK_DEPRECATED is_same_all : SROOK_FALSE_TYPE {
};

template <class Target, class Head, class... Tail>
struct SROOK_DEPRECATED is_same_all<Target, Head, Tail...> {
    static constexpr bool value = is_same_all_core<std::is_same<Target, Head>::value, Target, Tail...>::value;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::is_same_all;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class Target, class Head, class... Tail>
SROOK_DEPRECATED constexpr bool is_same_all_v = type_traits::detail::is_same_all<Target, Head, Tail...>::value;
#endif
} // namespace srook
#endif
#endif
