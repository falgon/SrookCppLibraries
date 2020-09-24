// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_AT_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_AT_HPP
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

// At
template <std::size_t, class...>
struct At;
template <std::size_t index, class Head, class... Tail>
struct At<index, Head, Tail...> {
    using type = typename At<index - 1, Tail...>::type;
};
template <class Target, class... Tail>
struct At<0, pack<Target, Tail...>> {
    using type = Target;
};
template <class Target, class... Tail>
struct At<0, Target, Tail...> {
    using type = Target;
};
template <std::size_t index>
struct At<index> {
    using type = pack<>;
};
template <std::size_t index, class Head, class... Tail>
struct At<index, pack<Head, Tail...>> : At<index, Head, Tail...> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::At;

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t index, class... Pack>
using At_t = typename At<index, Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
