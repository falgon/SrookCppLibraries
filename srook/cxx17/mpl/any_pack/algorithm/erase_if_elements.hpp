// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ERASE_IF_ELEMENTS_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ERASE_IF_ELEMENTS_HPP
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <bool, template <auto> class, auto...>
struct erase_if_elements_impl;
template <template <auto> class Predicate, auto head, auto... tail>
struct erase_if_elements_impl<true, Predicate, head, tail...> {
    using type = any_pack<tail...>;
};
template <template <auto> class Predicate, auto head, auto second, auto... tail>
struct erase_if_elements_impl<false, Predicate, head, second, tail...> {
    using type = concat_t<any_pack<head>, typename erase_if_elements_impl<Predicate<second>::value, Predicate, second, tail...>::type>;
};
template <bool b, template <auto> class Predicate, auto tail>
struct erase_if_elements_impl<b, Predicate, tail> {
    using tyep = std::conditional_t<b, any_pack<>, any_pack<tail>>;
};
template <template <auto> class, auto...>
struct erase_if_elements;
template <template <auto> class Predicate, auto head, auto... tail>
struct erase_if_elements<Predicate, head, tail...> {
    using type = typename erase_if_elements_impl<Predicate<head>::value, Predicate, head, tail...>::type;
};
template <template <auto> class Predicate, auto... v>
using erase_if_elements_t = typename erase_if_elements<Predicate, v...>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook

#endif
