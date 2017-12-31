// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_MAKE_ANY_PACK_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_MAKE_ANY_PACK_HPP
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <std::size_t, auto, class>
struct make_any_pack;
template <std::size_t size, auto init_value, auto... v>
struct make_any_pack<size, init_value, any_pack<v...>> {
    using type = typename make_any_pack<size - 1, init_value, any_pack<v..., init_value>>::type;
};
template <auto init_value, auto... v>
struct make_any_pack<0, init_value, any_pack<v...>> {
    using type = any_pack<v...>;
};
template <std::size_t size, auto init_value, class Seq = any_pack<>>
using make_any_pack_t = typename make_any_pack<size, init_value, Seq>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace srook

#endif
