#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_MATH_MAKE_COSTABLE_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_MATH_MAKE_COSTABLE_HPP
#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/math/constants/algorithm/cos.hpp>
#include <srook/mpl/constant_sequence/algorithm/concat.hpp>
#include <srook/mpl/constant_sequence/algorithm/transfer_constant.hpp>
#include <srook/mpl/constant_sequence/math/detail/convert_type.hpp>
#include <srook/mpl/variadic_player.hpp>

namespace srook {
inline namespace mpl {
namespace constant_sequence {
namespace math {
namespace v1 {

namespace detail {

template <std::size_t i, std::size_t j>
SROOK_DEPRECATED constexpr double cos_value = srook::math::cos((2 * j + 1) * i * (srook::math::pi<double> / 16));

template <std::size_t, std::size_t, class>
struct make_costable_y_impl;
template <std::size_t i, std::size_t j, std::int64_t... v>
struct SROOK_DEPRECATED make_costable_y_impl<i, j, std::integer_sequence<std::int64_t, v...>> {
    using type = typename make_costable_y_impl<i, j - 1, std::integer_sequence<std::int64_t, std::int64_t(cos_value<i, j> *to_integer), v...>>::type;
};
template <std::size_t i, std::int64_t... v>
struct SROOK_DEPRECATED make_costable_y_impl<i, 0, std::integer_sequence<std::int64_t, v...>> {
    using type = std::integer_sequence<std::int64_t, std::int64_t(cos_value<i, 0> *to_integer), v...>;
};
template <std::size_t x, std::size_t y, class Pack = std::integer_sequence<std::int64_t>>
using make_costable_y SROOK_DEPRECATED = typename make_costable_y_impl<x, y, Pack>::type;

template <std::size_t, std::size_t, class>
struct make_costable_x_impl;
template <std::size_t i, std::size_t j, std::int64_t... v>
struct SROOK_DEPRECATED make_costable_x_impl<i, j, std::integer_sequence<std::int64_t, v...>> {
    using type = typename make_costable_x_impl<i - 1, j, constant_sequence::concat_t<make_costable_y<i, j>, std::integer_sequence<std::int64_t, v...>>>::type;
};
template <std::size_t j, std::int64_t... v>
struct SROOK_DEPRECATED make_costable_x_impl<0, j, std::integer_sequence<std::int64_t, v...>> {
    using type = constant_sequence::concat_t<make_costable_y<0, j>, std::integer_sequence<std::int64_t, v...>>;
};
template <std::size_t x, std::size_t y, class Pack = std::integer_sequence<std::int64_t>>
using make_costable_x SROOK_DEPRECATED = typename make_costable_x_impl<x - 1, y - 1, Pack>::type;

} // namespace detail

template <std::size_t x, std::size_t y>
SROOK_DEPRECATED constexpr decltype(auto) cos_table = constant_sequence::transfer_constant<std::tuple, std::int64_t, detail::make_costable_x<x, y>, detail::Realvalue>;

} // namespace v1

inline namespace v2 {
namespace detail {

template <std::size_t i, std::size_t j>
struct cos_value {
    static constexpr double value = srook::math::cos((2 * j + 1) * i * (srook::math::PI<double>::value() / 16));
};

template <std::size_t, std::size_t, class... AnyConstant>
struct make_costable_y_impl;
template <std::size_t i, std::size_t j, class... CosWrapper>
struct make_costable_y_impl<i, j, pack<CosWrapper...>> {
    typedef typename make_costable_y_impl<i, j - 1, pack<cos_value<i, j>, CosWrapper...>>::type type;
};
template <std::size_t i, class... CosWrapper>
struct make_costable_y_impl<i, 0, pack<CosWrapper...>> {
    typedef pack<cos_value<i, 0>, CosWrapper...> type;
};

template <std::size_t, std::size_t, class>
struct make_costable_x_impl;
template <std::size_t i, std::size_t j, class... CosWrapper>
struct make_costable_x_impl<i, j, pack<CosWrapper...>> {
    typedef typename make_costable_x_impl<i - 1, j, typename Concat<typename make_costable_y_impl<i, j, pack<>>::type, pack<CosWrapper...>>::type>::type type;
};
template <std::size_t j, class... CosWrapper>
struct make_costable_x_impl<0, j, pack<CosWrapper...>> {
    typedef typename Concat<typename make_costable_y_impl<0, j, pack<>>::type, pack<CosWrapper...>>::type type;
};

} // namespace detail

template <std::size_t x, std::size_t y, class Pack = pack<>>
struct make_costable {
    typedef typename detail::make_costable_x_impl<x - 1, y - 1, Pack>::type type;
};

namespace unwrap_costable {

template <class>
struct array;
template <class... Ts>
struct array<pack<Ts...>> {
    static constexpr std::array<typename First<decltype(Ts::value)...>::type, sizeof...(Ts)> value{Ts::value...};
};

template <class, template <class...> class = std::tuple>
struct tuple;
template <class... Ts, template <class...> class Tuple>
struct tuple<pack<Ts...>, Tuple> {
    static constexpr Tuple<decltype(Ts::value)...> value{Ts::value...};
};

#if SROOK_CPP_VARIABLE_TEMPLATES

template <class Pack>
static constexpr decltype(auto) array_v = array<Pack>::value;

template <class Pack, template <class...> class Tuple>
static constexpr decltype(auto) tuple_v = tuple<Pack, Tuple>::value;

#endif

} // namespace unwrap_costable

#if SROOK_CPP_ALIAS_TEMPLATES

template <std::size_t x, std::size_t y, class Pack = pack<>>
using make_costable_t = typename make_costable<x, y, Pack>::type;

#endif

} // namespace v2
} // namespace math
} // namespace constant_sequence
} // namespace mpl
} // namespace srook

#endif
