// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FOR_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_FOR_HPP
#include <srook/config/require.hpp>
#include <srook/cxx17/mpl/any_pack/algorithm/concat.hpp>
#include <srook/cxx17/mpl/any_pack/algorithm/size.hpp>
#include <srook/cxx17/mpl/any_pack/algorithm/through_anypack/partial_head.hpp>
#include <srook/cxx17/mpl/any_pack/algorithm/through_anypack/partial_tail.hpp>
#include <srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include <srook/type_traits/is_callable.hpp>

namespace srook {
inline namespace mpl {
inline namespace v1 {
namespace detail {

struct Increment {
    explicit constexpr Increment() noexcept = default;
    template <class T>
    constexpr T operator()(T &&v) const noexcept
    {
	return v + 1;
    }
};

struct Decrement {
    explicit constexpr Decrement() noexcept = default;
    template <class T>
    constexpr T operator()(T &&v) const noexcept
    {
	return v - 1;
    }
};

struct Less {
    explicit constexpr Less() noexcept = default;
    template <class T>
    constexpr bool operator()(T &&l, T &&r) const noexcept
    {
	return l < r;
    }
};
struct Greater {
    explicit constexpr Greater() noexcept = default;
    template <class T>
    constexpr bool operator()(T &&l, T &&r) const noexcept
    {
	return l > r;
    }
};
struct Less_or_equal {
    explicit constexpr Less_or_equal() noexcept = default;
    template <class T>
    constexpr bool operator()(T &&l, T &&r) const noexcept
    {
	return l <= r;
    }
};
struct Greater_or_equal {
    explicit constexpr Greater_or_equal() noexcept = default;
    template <class T>
    constexpr bool operator()(T &&l, T &&r) const noexcept
    {
	return l >= r;
    }
};

template <std::size_t, std::size_t, template <std::size_t, class, class, class> class, class, class, class, class, class, class = std::nullptr_t>
struct for_;

template <std::size_t begin, std::size_t end, template <std::size_t, class, class, class> class Invokable, class Crease, class Pred, auto... param, auto... v, class... Ts>
struct for_<begin, end, Invokable, Crease, Pred, any_pack<param...>, any_pack<v...>, pack<Ts...>, std::enable_if_t<Pred()(begin, end), std::nullptr_t>> {
private:
    using inner_type = any_pack<Invokable<begin, any_pack<v...>, any_pack<param...>, pack<Ts...>>::value>;

public:
    using type = concat_t<inner_type, typename for_<Crease()(begin), end, Invokable, Crease, Pred, any_pack<param...>, any_pack<v...>, pack<Ts...>>::type>;
};
template <std::size_t begin, std::size_t end, template <std::size_t, class, class, class> class Invokable, class Crease, class Pred, auto... param, auto... v, class... Ts>
struct for_<begin, end, Invokable, Crease, Pred, any_pack<param...>, any_pack<v...>, pack<Ts...>, std::enable_if_t<!Pred()(begin, end), std::nullptr_t>> {
    using type = any_pack<>;
};

template <
    std::size_t begin,
    std::size_t end,
    template <std::size_t, class, class, class> class Invokable,
    class Crease = std::conditional_t<(begin < end), Increment, Decrement>,
    class Parameter = any_pack<>,
    class Seq = any_pack<>,
    class TPack = pack<>,
    REQUIRES(std::is_nothrow_constructible_v<Crease> and is_callable_v<Crease>)>
using for_to_t =
    std::conditional_t<
	(detail::size<typename for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less_or_equal, Greater_or_equal>, Parameter, Seq, TPack>::type::size()> == detail::size<Seq>),
	typename for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less_or_equal, Greater_or_equal>, Parameter, Seq, TPack>::type,
	std::conditional_t<
	    (begin < end),
	    detail::concat_t<
		typename for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less_or_equal, Greater_or_equal>, Parameter, Seq, TPack>::type,
		through::partial_tail_t<size<for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less_or_equal, Greater_or_equal>, Parameter, Seq, TPack>::type>, Seq>>,
	    detail::concat_t<
		typename for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less_or_equal, Greater_or_equal>, Parameter, Seq, TPack>::type,
		through::partial_head_t<size<for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less_or_equal, Greater_or_equal>, Parameter, Seq, TPack>::type>, Seq>>>>;

template <
    std::size_t begin,
    std::size_t end,
    template <std::size_t, class, class, class> class Invokable,
    class Crease = std::conditional_t<(begin < end), Increment, Decrement>,
    class Parameter = any_pack<>,
    class Seq = any_pack<>,
    class TPack = pack<>,
    REQUIRES(std::is_nothrow_constructible_v<Crease> and is_callable_v<Crease>)>
using for_until_t =
    std::conditional_t<
	(detail::size<typename for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less, Greater>, Parameter, Seq, TPack>::type> == detail::size<Seq>),
	typename for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less, Greater>, Parameter, Seq, TPack>::type,
	std::conditional_t<
	    (begin < end),
	    detail::concat_t<
		typename detail::for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less, Greater>, Parameter, Seq, TPack>::type,
		through::partial_tail_t<
		    detail::size<typename for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less, Greater>, Parameter, Seq, TPack>::type>,
		    Seq>>,
	    detail::concat_t<
		typename detail::for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less, Greater>, Parameter, Seq, TPack>::type,
		through::partial_head_t<
		    detail::size<typename for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less, Greater>, Parameter, Seq, TPack>::type>,
		    Seq>>>>;

template <
    std::size_t begin,
    std::size_t end,
    template <std::size_t, class, class, class> class Invokable,
    class Crease = std::conditional_t<(begin < end), Increment, Decrement>,
    class Parameter = any_pack<>,
    class Seq = any_pack<>,
    class TPack = pack<>,
    REQUIRES(std::is_nothrow_constructible_v<Crease> and is_callable_v<Crease>)>
using for_cut_to_t = typename for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less_or_equal, Greater_or_equal>, Parameter, Seq, TPack>::type;

template <
    std::size_t begin,
    std::size_t end,
    template <std::size_t, class, class, class> class Invokable,
    class Crease = std::conditional_t<(begin < end), Increment, Decrement>,
    class Parameter = any_pack<>,
    class Seq = any_pack<>,
    class TPack = pack<>,
    REQUIRES(std::is_nothrow_constructible_v<Crease> and is_callable_v<Crease>)>
using for_cut_until_t = typename for_<begin, end, Invokable, Crease, std::conditional_t<(begin < end), Less, Greater>, Parameter, Seq, TPack>::type;

} // namespace detail
} // namespace v1
} // namespace mpl
} // namespace srook

#endif
