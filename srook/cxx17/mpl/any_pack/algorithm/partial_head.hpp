// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_PARTIAL_HEAD_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_PARTIAL_HEAD_HPP
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <std::size_t, class>
struct partial_head;
template <std::size_t target, auto head, auto... tail>
struct partial_head<target, any_pack<head, tail...>> {
    using type = concat_t<any_pack<head>, typename partial_head<target - 1, any_pack<tail...>>::type>;
};
template <auto tail, auto... args>
struct partial_head<1, any_pack<tail, args...>> {
    using type = any_pack<tail>;
};
template <std::size_t target>
struct partial_head<target, any_pack<>> {
    using type = any_pack<>;
};
template <std::size_t target, auto... v>
using partial_head_t = typename partial_head<target, any_pack<v...>>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace srook

#endif
