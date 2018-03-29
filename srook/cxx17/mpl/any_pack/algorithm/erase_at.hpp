// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ERASE_AT_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ERASE_AT_HPP
#include <optional>
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <std::size_t, auto...>
struct erase_at;
template <std::size_t n, auto head, auto... tail>
struct erase_at<n, head, tail...> {
    using type = concat_t<any_pack<head>, typename erase_at<n - 1, tail...>::type>;
};
template <auto target, auto... tail>
struct erase_at<0, target, tail...> {
    using type = any_pack<tail...>;
};
template <std::size_t target, auto... v>
using erase_at_t = typename erase_at<target, v...>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook

#endif
