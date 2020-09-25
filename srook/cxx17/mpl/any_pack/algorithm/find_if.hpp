// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FIND_IF_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FIND_IF_HPP
#include <type_traits>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <int, template <auto> class, auto...>
struct find_if;
template <int counter, template <auto> class Predicate, auto head, auto... tail>
struct find_if<counter, Predicate, head, tail...> {
    static constexpr int value = std::conditional_t<Predicate<head>::value, std::integral_constant<int, counter>, find_if<counter + 1, Predicate, tail...>>::value;
};
template <int counter, template <auto> class Predicate>
struct find_if<counter, Predicate> {
    static constexpr int value = -counter - 1;
};
template <template <auto> class Predicate, auto... v>
constexpr int find_if_v = find_if<0, Predicate, v...>::value;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook

#endif
