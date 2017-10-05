// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FILTER_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FILTER_HPP
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <template <auto> class, class>
struct filter;
template <template <auto> class Cond, auto head, auto... tail>
struct filter<Cond, any_pack<head, tail...>> {
private:
    template <bool, class, class>
    struct if_append;
    template <auto... seq1, auto... seq2>
    struct if_append<true, any_pack<seq1...>, any_pack<seq2...>> {
	using type = any_pack<seq1..., seq2...>;
    };
    template <auto... seq1, auto... seq2>
    struct if_append<false, any_pack<seq1...>, any_pack<seq2...>> {
	using type = any_pack<seq2...>;
    };
    template <bool condition, class Seq1, class Seq2>
    using if_append_t = typename if_append<condition, Seq1, Seq2>::type;

public:
    using type = if_append_t<Cond<head>::value, any_pack<head>, typename filter<Cond, any_pack<tail...>>::type>;
};
template <template <auto> class Cond>
struct filter<Cond, any_pack<>> {
    using type = any_pack<>;
};
template <template <auto> class Cond, class Seq>
using filter_t = typename filter<Cond, Seq>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace srook

#endif
