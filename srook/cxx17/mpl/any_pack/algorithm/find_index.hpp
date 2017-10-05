// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FIND_INDEX_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FIND_INDEX_HPP

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <std::size_t, auto, auto...>
struct find_index;
template <std::size_t counter, auto target, auto head, auto... tail>
struct find_index<counter, target, head, tail...> {
    static constexpr int value = find_index<counter + 1, target, tail...>::value;
};
template <std::size_t counter, auto target, auto... tail>
struct find_index<counter, target, target, tail...> {
    static constexpr int value = counter;
};
template <std::size_t counter, auto target>
struct find_index<counter, target> {
    static constexpr int value = -1;
};
template <std::size_t target, auto... v>
constexpr int find_index_v = find_index<0, target, v...>::value;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace srook

#endif
