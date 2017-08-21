// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_SAME_ALL_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_SAME_ALL_HPP
#include <type_traits>
namespace srook {
inline namespace v1 {

template <bool, class, class...>
struct is_same_all_core : std::false_type {
};
template <class Target, class Head, class... Tail>
struct is_same_all_core<true, Target, Head, Tail...> {
    static constexpr bool value = is_same_all_core<std::is_same<Target, Head>::value, Tail...>::value;
};
template <class Target>
struct is_same_all_core<true, Target> : std::true_type {
};
template <class Target>
struct is_same_all_core<false, Target> : std::false_type {
};

template <class, class...>
struct is_same_all : std::false_type {
};

template <class Target, class Head, class... Tail>
struct is_same_all<Target, Head, Tail...> {
    static constexpr bool value = is_same_all_core<std::is_same<Target, Head>::value, Target, Tail...>::value;
};

} // namespace v1
} // namespace srook
#endif
