// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_REPLACE_ELEMENTS_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_REPLACE_ELEMENTS_HPP
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <auto, auto, auto...>
struct replace_elements;
template <auto replace_element, auto target, auto head, auto... tail>
struct replace_elements<replace_element, target, head, tail...> {
    using type = concat_t<any_pack<head>, typename replace_elements<replace_element, target, tail...>::type>;
};
template <auto replace_element, auto target, auto... tail>
struct replace_elements<replace_element, target, target, tail...> {
    using type = concat_t<any_pack<replace_element>, typename replace_elements<replace_element, target, tail...>::type>;
};
template <auto replace_element, auto target>
struct replace_elements<replace_element, target> {
    using type = any_pack<>;
};
template <auto replace_element, auto target, auto... v>
using replace_elements_t = typename replace_elements<replace_element, target, v...>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook

#endif
