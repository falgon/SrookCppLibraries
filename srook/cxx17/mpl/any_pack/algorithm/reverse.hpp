// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_REVERSE_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_REVERSE_HPP
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/algorithm/pop_back.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <class>
struct reverse;
template <auto... v>
struct reverse<any_pack<v...>> {
    using type = concat_t<any_pack<last_v<v...>>, typename reverse<pop_back_t<v...>>::type>;
};
template <>
struct reverse<any_pack<>> {
    using type = any_pack<>;
};
template <auto... v>
using reverse_t = typename reverse<any_pack<v...>>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace srook

#endif
