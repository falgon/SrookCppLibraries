// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_POP_BACK_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_POP_BACK_HPP
#include <optional>
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <auto...>
struct pop_back;
template <auto head, auto... tail>
struct pop_back<head, tail...> {
    using type = concat_t<any_pack<head>, typename pop_back<tail...>::type>;
};
template <auto tail>
struct pop_back<tail> {
    using type = any_pack<>;
};
template <>
struct pop_back<> {
    using type = std::nullopt_t;
};
template <auto... v>
using pop_back_t = typename pop_back<v...>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook

#endif
