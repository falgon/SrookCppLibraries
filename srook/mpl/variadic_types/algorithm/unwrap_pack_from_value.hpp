// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_UNWRAP_PACK_FROM_VALUE_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_UNWRAP_PACK_FROM_VALUE_HPP
#include <srook/array.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/inline_variable.hpp>
#include <srook/mpl/variadic_types/algorithm/first.hpp>
#include <srook/mpl/variadic_types/pack.hpp>
#include <tuple>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace constant_sequence {
namespace unwrap_pack {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class>
struct array;
template <class... Ts>
struct array<pack<Ts...>> {
    static constexpr srook::array<typename First<decltype(Ts::value)...>::type, sizeof...(Ts)> value{Ts::value...};
};
template <class, template <class...> class = std::tuple>
struct tuple;
template <class... Ts, template <class...> class Tuple>
struct tuple<pack<Ts...>, Tuple> {
    static constexpr Tuple<decltype(Ts::value)...> value{Ts::value...};
};

} // namespace detail

using detail::array;
using detail::tuple;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class Pack>
SROOK_INLINE_VARIABLE static constexpr decltype(auto) array_v = array<Pack>::value;

template <class Pack, template <class...> class Tuple>
SROOK_INLINE_VARIABLE static constexpr decltype(auto) tuple_v = tuple<Pack, Tuple>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace unwrap_pack
} // namespace constant_sequence
SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
