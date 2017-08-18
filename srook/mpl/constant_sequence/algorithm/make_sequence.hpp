#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_AlGORITHM_EXPLICIT_MAKE_SEQUENCE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_AlGORITHM_EXPLICIT_MAKE_SEQUENCE_HPP

#include <srook/mpl/constant_sequence/algorithm/transfer_constant.hpp>
#include <srook/type_traits/is_callable.hpp>
#include <type_traits>
#include <utility>

namespace srook {
inline namespace mpl {
namespace constant_sequence {
inline namespace v1 {

namespace make_sequence_utility {

struct Default;
struct Reverse;

} // namespace make_sequence_utility

namespace detail {

template <std::size_t, class, class, class, class = std::nullptr_t>
struct make_sequence_impl;

template <std::size_t size, class Assigner, class DefaultReverse_Tag, decltype(Assigner()(size))... v>
struct make_sequence_impl<size, Assigner, DefaultReverse_Tag, std::integer_sequence<decltype(Assigner()(size)), v...>, std::enable_if_t<(size != 0), std::nullptr_t>> {
private:
    static_assert(srook::is_callable_v<Assigner>, "Second parameter must be callable in compile time");
    static_assert(std::is_same<DefaultReverse_Tag, make_sequence_utility::Default>() or std::is_same<DefaultReverse_Tag, make_sequence_utility::Reverse>(), "");

public:
    using type =
	std::conditional_t<
	    std::is_same<DefaultReverse_Tag, make_sequence_utility::Default>::value,
	    typename make_sequence_impl<size - 1, Assigner, DefaultReverse_Tag, std::integer_sequence<decltype(Assigner()(size - 1)), Assigner()(size - 1), v...>>::type,
	    typename make_sequence_impl<size - 1, Assigner, DefaultReverse_Tag, std::integer_sequence<decltype(Assigner()(size - 1)), v..., Assigner()(size - 1)>>::type>;
};

template <class Assigner, class DefaultReverse_Tag, decltype(Assigner()(std::size_t()))... v>
struct make_sequence_impl<0, Assigner, DefaultReverse_Tag, std::integer_sequence<decltype(Assigner()(std::size_t())), v...>> {
    using type = std::integer_sequence<decltype(Assigner()(std::size_t())), v...>;
};

} // namespace detail

namespace make_sequence_utility {

template <class T, T init_value>
struct initialize {
    constexpr initialize() = default;
    constexpr T operator()(std::size_t) const noexcept
    {
	return init_value;
    }
};

template <class T>
struct cast {
    constexpr cast() = default;
    constexpr T operator()(std::size_t x) const noexcept
    {
	return static_cast<T>(x);
    }
};

template <class, class T, T x, class = std::nullptr_t>
struct expression;

namespace placeholders {
namespace detail {

struct Add;
struct Sub;
struct Mul;
struct Div;
struct Left;
struct Right;

struct Val {
    template <class T, T x>
    friend constexpr expression<Add, T, x> operator+(const Val &, std::integral_constant<T, x>) noexcept
    {
	return expression<Add, T, x>();
    }
    template <class T, T x>
    friend constexpr expression<Add, T, x> operator+(std::integral_constant<T, x>, const Val &) noexcept
    {
	return expression<Add, T, x>();
    }
    template <class T, T x>
    friend constexpr expression<Sub, T, x, Right> operator-(const Val &, std::integral_constant<T, x>) noexcept
    {
	return expression<Sub, T, x>();
    }
    template <class T, T x>
    friend constexpr expression<Sub, T, x, Left> operator-(std::integral_constant<T, x>, const Val &) noexcept
    {
	return expression<Sub, T, x>();
    }
    template <class T, T x>
    friend constexpr expression<Mul, T, x> operator*(const Val &, std::integral_constant<T, x>)noexcept
    {
	return expression<Mul, T, x>();
    }
    template <class T, T x>
    friend constexpr expression<Mul, T, x> operator*(std::integral_constant<T, x>, const Val &)noexcept
    {
	return expression<Mul, T, x>();
    }
    template <class T, T x>
    friend constexpr expression<Div, T, x, Right> operator/(const Val &, std::integral_constant<T, x>) noexcept
    {
	return expression<Div, T, x>();
    }
    template <class T, T x>
    friend constexpr expression<Div, T, x, Left> operator/(std::integral_constant<T, x>, const Val &) noexcept
    {
	return expression<Div, T, x>();
    }
};

} // namespace detail

#if __cplusplus >= 201703L

inline constexpr detail::Val _val{};

#else

extern detail::Val _val;

#endif

} // namespace placeholders

template <class Op, class T, T xx, class Pos>
struct expression {
    explicit constexpr expression() = default;

    static constexpr T x_ = xx;

    constexpr T operator()(std::size_t c) const noexcept
    {
	T x = T(c);
	return std::is_same<Op, placeholders::detail::Add>() ? x_ + x : std::is_same<Op, placeholders::detail::Sub>() and std::is_same<Pos, placeholders::detail::Right>() ? x_ - x : std::is_same<Op, placeholders::detail::Sub>() and std::is_same<Pos, placeholders::detail::Left>() ? x - x_ : std::is_same<Op, placeholders::detail::Mul>() ? x_ * x : std::is_same<Op, placeholders::detail::Div>() and std::is_same<Pos, placeholders::detail::Right>() ? x_ / x : x / x_;
    }
};

} // namespace make_sequence_utility

template <std::size_t size, class Assigner = detail::DoNothing, class DefaultReverse_Tag = make_sequence_utility::Default, class Seq = std::integer_sequence<decltype(Assigner()(size))>>
using make_sequence = typename detail::make_sequence_impl<size, Assigner, DefaultReverse_Tag, Seq>::type;

} // namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook

#endif
