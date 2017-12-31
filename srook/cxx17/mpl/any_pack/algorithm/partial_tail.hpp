// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_PARTIAL_TAIL_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_PARTIAL_TAIL_HPP
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <std::size_t, class>
struct partial_tail;
template <std::size_t target, auto head, auto... tail>
struct partial_tail<target, any_pack<head, tail...>> {
    using type = typename partial_tail<target - 1, any_pack<tail...>>::type;
};
template <auto head, auto... t>
struct partial_tail<0, any_pack<head, t...>> {
    using type = any_pack<head, t...>;
};
template <std::size_t target>
struct partial_tail<target, any_pack<>> {
    using type = any_pack<>;
};
template <std::size_t index, auto... v>
using partial_tail_t = typename partial_tail<index, any_pack<v...>>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace srook

#endif
