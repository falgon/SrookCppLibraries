// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_COUNT_IF_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_COUNT_IF_HPP
#include <type_traits>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <template <auto> class, auto...>
struct count_if;
template <template <auto> class Predicate, auto head, auto... tail>
struct count_if<Predicate, head, tail...> : std::integral_constant<std::size_t, std::conditional_t<Predicate<head>::value, std::true_type, std::false_type>::value + count_if<Predicate, tail...>::value> {
};
template <template <auto> class Predicate>
struct count_if<Predicate> : std::integral_constant<std::size_t, 0> {
};
template <template <auto> class Predicate, auto... v>
constexpr std::size_t count_if_v = count_if<Predicate, v...>::value;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook

#endif
