// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_LENGTH_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_LENGTH_HPP
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class Head, class... Tail>
struct Length {
    static constexpr std::size_t value = 1 + Length<Tail...>::value;
};
template <class Tail>
struct Length<Tail> {
    static constexpr std::size_t value = 1;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::Length;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class... Ts>
constexpr std::size_t Length_v = variadic_types::detail::Length<Ts...>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook
#endif
