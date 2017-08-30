// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_PARTIAL_HEAD_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_PARTIAL_HEAD_HPP
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

// Partial Head
template <std::size_t, class...>
struct PartialHead;
template <std::size_t N, class Head, class... Args>
struct PartialHead<N, Head, Args...> {
    using type = Concat_t<Head, typename PartialHead<N - 1, Args...>::type>;
};
template <class Tail, class... Args>
struct PartialHead<1, Tail, Args...> {
    using type = Tail;
};
template <std::size_t N, class Head, class... Args>
struct PartialHead<N, pack<Head, Args...>> : PartialHead<N, Head, Args...> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::PartialHead;

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t N, class... Pack>
using PartialHead_t = typename PartialHead<N, Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
