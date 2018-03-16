// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_CONCAT_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_CONCAT_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class...>
struct Concat;
template <class L, class... R>
struct Concat<L, R...> {
    static constexpr std::size_t size = sizeof...(R) + 1;
    typedef pack<L, R...> type;
};
template <class... L, class... R>
struct Concat<pack<L...>, pack<R...>> : Concat<L..., R...> {
};
template <class L, class... R>
struct Concat<L, pack<R...>> : Concat<L, R...> {
};
template <class... L, class... R>
struct Concat<pack<L...>, R...> : Concat<L..., R...> {
};
template <>
struct Concat<pack<>, pack<>> {
    typedef pack<> type;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::Concat;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class L, class... R>
using Concat_t = typename variadic_types::detail::Concat<L, R...>::type;
#endif

SROOK_INLINE_NAMESPACE_END

} // namespace srook
#endif
#endif
