// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITAS_IS_TUPLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITAS_IS_TUPLE_HPP
#include <type_traits>

template <class, class = std::void_t<>>
struct is_tuple : std::false_type {
};

template <class T>
struct is_tuple<T, std::void_t<decltype(std::tuple_size<std::decay_t<T>>::value)>> : std::true_type {
};

template <class, class = std::void_t<>>
constexpr bool is_tuple_v = std::false_type::value;

template <class T>
constexpr bool is_tuple_v<T, std::void_t<decltype(std::tuple_size<std::decay_t<T>>::value)>> = std::true_type::value;

#endif
