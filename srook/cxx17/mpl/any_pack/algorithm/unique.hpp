// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_UNIQUE_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_UNIQUE_HPP
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <class>
struct unique;
template <auto head, auto... tail>
struct unique<any_pack<head, tail...>> {
    using type = concat_t<any_pack<head>, typename unique<erase_all_elements_t<head, tail...>>::type>;
};
template <>
struct unique<any_pack<>> {
    using type = any_pack<>;
};
template <auto... v>
using unique_t = typename unique<any_pack<v...>>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook

#endif
