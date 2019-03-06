// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_REPLACE_ALL_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_REPLACE_ALL_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class, class, class...>
struct ReplaceAll;
template <class T, class R, class Head, class... Tail>
struct ReplaceAll<T, R, Head, Tail...> {
    using type = Concat_t<Head, typename ReplaceAll<T, R, Tail...>::type>;
};
template <class T, class R, class... Tail>
struct ReplaceAll<T, R, T, Tail...> {
    using type = Concat_t<R, typename ReplaceAll<T, R, Tail...>::type>;
};
template <class T, class R>
struct ReplaceAll<T, R> {
    using type = pack<>;
};
template <class T, class R, class Head, class... Tail>
struct ReplaceAll<T, R, pack<Head, Tail...>> : ReplaceAll<T, R, Head, Tail...> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::ReplaceAll;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T, class R, class... Pack>
using ReplaceAll_t = typename ReplaceAll<T, R, Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
