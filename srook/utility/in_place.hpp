// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_UTILITY_IN_PLACE_HPP
#define INCLUDED_SROOK_UTILITY_IN_PLACE_HPP
#include<cstddef>
namespace srook{
inline namespace v1{
constexpr struct in_place_t{
	explicit in_place_t()=default;
}in_place{};

template<class T>
struct in_place_type_t{
	explicit in_place_type_t()=default;
};
template<class T>
constexpr in_place_type_t<T> in_place_type{};

template<std::size_t I>
struct in_place_index_t{
	explicit in_place_index_t()=default;
};
template<std::size_t I>
constexpr in_place_index_t<I> in_place_index{};
} // inline namespace v1
} // srook
#endif
