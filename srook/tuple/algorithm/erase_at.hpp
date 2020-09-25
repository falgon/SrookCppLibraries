// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_ERASE_AT_HPP
#define INCLUDED_SROOK_TUPLE_ERASE_AT_HPP
#include <srook/mpl/variadic_player.hpp>
#include <srook/tuple/algorithm/deprecated/split.hpp>
#include <tuple>

namespace srook {
namespace tuple{
inline namespace v1{

template <std::size_t target, class... Args>
constexpr Transfer_t<std::tuple, Erase_At_t<target, Args...>> erase_at(const std::tuple<Args...> &tpl)
{
    static_assert(std::tuple_size<std::tuple<Args...>>::value >= target, "The index value is out of range.");
    return std::tuple_cat(split_first<target>(tpl), split_last<target + 1>(tpl));
}

} // inline namespace v1
} // namespace tuple
} // namespace srook

#endif
