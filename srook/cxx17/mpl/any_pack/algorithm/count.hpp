// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_COUNT_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_COUNT_HPP
#include <type_traits>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <auto, auto...>
struct count;
template <auto target, auto head, auto... tail>
struct count<target, head, tail...> : std::integral_constant<std::size_t, std::conditional_t<(target == head), std::true_type, std::false_type>::value + count<target, tail...>::value> {
};

template <auto target>
struct count<target> : std::integral_constant<std::size_t, 0> {
};
template <auto target, auto... v>
constexpr std::size_t count_v = count<target, v...>::value;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook

#endif
