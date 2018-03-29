// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FIRST_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FIRST_HPP
#include <srook/mpl/variadic_player.hpp>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <auto...>
struct first;
template <auto head, auto... tail>
struct first<head, tail...> {
    static constexpr decltype(head) value = head;
};
template <>
struct first<> {
    static constexpr NULLOPT_T value = NULLOPT;
};

template <auto... v>
constexpr std::conditional_t<!sizeof...(v), NULLOPT_T, First_t<decltype(v)...>> first_v = first<v...>::value;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook

#endif
