// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ERASE_IF_ALL_ELEMENTS_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ERASE_IF_ALL_ELEMENTS_HPP
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
namespace vmpl {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <template <auto> class, auto...>
struct erase_if_all_elements;
template <template <auto> class Predicate, auto head, auto... tail>
struct erase_if_all_elements<Predicate, head, tail...> {
    using type = concat_t<std::conditional_t<Predicate<head>::value, any_pack<>, any_pack<head>>, typename erase_if_all_elements<Predicate, tail...>::type>;
};
template <template <auto> class Predicate>
struct erase_if_all_elements<Predicate> {
    using type = any_pack<>;
};
template <template <auto> class Predicate, auto... v>
using erase_if_all_elements_t = typename erase_if_all_elements<Predicate, v...>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace vmpl
} // namespace srook
#endif
