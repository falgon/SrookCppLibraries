// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_PARTIAL_TAIL_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_PARTIAL_TAIL_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

// Partial Tail
template <class... Args>
struct Apply_Partial_Tail;
template <class Head, class... Tail>
struct Apply_Partial_Tail<Head, Tail...> {
    using type = Concat_t<Head, typename Apply_Partial_Tail<Tail...>::type>;
};
template <class Tail>
struct Apply_Partial_Tail<Tail> {
    using type = Tail;
};
template <>
struct Apply_Partial_Tail<> {
    using type = pack<>;
};
template <std::size_t N, class Head, class... Tail>
struct PartialTail {
    using type = typename PartialTail<N - 1, Tail...>::type;
};
template <class Head, class... Tail>
struct PartialTail<0, Head, Tail...> {
    using type = Concat_t<Head, typename Apply_Partial_Tail<Tail...>::type>;
};
template <std::size_t N, class Head, class... Tail>
struct PartialTail<N, pack<Head, Tail...>> : PartialTail<N, Head, Tail...> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::PartialTail;

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t N, class... Args>
using PartialTail_t = typename variadic_types::detail::PartialTail<N, Args...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
