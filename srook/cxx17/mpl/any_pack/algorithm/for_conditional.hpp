// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FOR_CONDITIONAL_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FOR_CONDITIONAL_HPP
#include <srook/config/require.hpp>
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/algorithm/for.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/type_traits/is_callable.hpp>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {

template <
    std::size_t,
    class, // end condition
    template <std::size_t, class, class, class> class, // applyer
    class, // Creaser
    class, // parameter any_pack
    class, // parameter other values
    class, // pack
    class = std::nullptr_t // for SFINAE
    >
struct for_conditional_;

template <std::size_t begin, class conditional_End, template <std::size_t, class, class, class> class Invokable, class Crease, auto... param, auto... v, class... Ts>
struct for_conditional_<
    begin,
    conditional_End,
    Invokable,
    Crease,
    any_pack<param...>,
    any_pack<v...>,
    pack<Ts...>,
    std::enable_if_t<(conditional_End().template operator()<begin, any_pack<param...>, any_pack<v...>, pack<Ts...>>()), std::nullptr_t>> {
private:
    using inner_type = any_pack<Invokable<begin, any_pack<v...>, any_pack<param...>, pack<Ts...>>::value>;

public:
    using type = concat_t<inner_type, typename for_conditional_<Crease()(begin), conditional_End, Invokable, Crease, any_pack<param...>, any_pack<v...>, pack<Ts...>>::type>;
};

template <std::size_t begin, class conditional_End, template <std::size_t, class, class, class> class Invokable, class Crease, auto... param, auto... v, class... Ts>
struct for_conditional_<
    begin,
    conditional_End,
    Invokable,
    Crease,
    any_pack<param...>,
    any_pack<v...>,
    pack<Ts...>,
    std::enable_if_t<!(conditional_End().template operator()<begin, any_pack<param...>, any_pack<v...>, pack<Ts...>>()), std::nullptr_t>> {
    using type = any_pack<>;
};

template <
    std::size_t begin,
    class conditional_End,
    template <std::size_t, class, class, class> class Invokable,
    class Crease = Increment,
    class Parameter = any_pack<>,
    class Seq = any_pack<>,
    class TPack = pack<>,
    REQUIRES(
	is_callable_v<Crease> and is_callable_v<conditional_End> and
	    std::is_nothrow_constructible_v<Crease> and std::is_nothrow_constructible_v<conditional_End>)>
using for_conditional_t =
    std::conditional_t<
	(for_conditional_<begin, conditional_End, Invokable, Crease, Parameter, Seq, TPack>::type::size() == Seq::size()),
	typename for_conditional_<begin, conditional_End, Invokable, Crease, Parameter, Seq, TPack>::type,
	std::conditional_t<
	    std::is_same_v<Crease, Increment>,
	    typename for_conditional_<begin, conditional_End, Invokable, Crease, Parameter, Seq, TPack>::type::template concat_type<
		typename Seq::template partial_tail_type<for_conditional_<begin, conditional_End, Invokable, Crease, Parameter, Seq, TPack>::type::size()>>,
	    typename for_conditional_<begin, conditional_End, Invokable, Crease, Parameter, Seq, TPack>::type::template concat_type<
		typename Seq::template partial_head_type<for_conditional_<begin, conditional_End, Invokable, Crease, Parameter, Seq, TPack>::type::size()>>>>;

template <
    std::size_t begin,
    class conditional_End,
    template <std::size_t, class, class, class> class Invokable,
    class Crease = Increment,
    class Parameter = any_pack<>,
    class Seq = any_pack<>,
    class TPack = pack<>,
    REQUIRES(
	is_callable_v<Crease> and is_callable_v<conditional_End> and
	    std::is_nothrow_constructible_v<Crease> and std::is_nothrow_constructible_v<conditional_End>)>
using for_conditional_cut_t = typename for_conditional_<begin, conditional_End, Invokable, Crease, Parameter, Seq, TPack>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace srook

#endif
