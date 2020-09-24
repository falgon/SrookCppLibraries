// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_ERASE_ALL_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_ERASE_ALL_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

// Erase All
template <class T, class... Pack>
struct EraseAll;
template <class T, class L, class... R>
struct EraseAll<T, L, R...> {
    using type = Concat_t<L, typename EraseAll<T, R...>::type>;
};
template <class L, class... R>
struct EraseAll<L, L, R...> {
    using type = typename EraseAll<L, R...>::type;
};
template <class Tail>
struct EraseAll<Tail> {
    using type = pack<>;
};
template <class T, class L, class... R>
struct EraseAll<T, pack<L, R...>> : EraseAll<T, L, R...> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::EraseAll;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T, class... Pack>
using EraseAll_t = typename variadic_types::detail::EraseAll<T, Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook
#endif
