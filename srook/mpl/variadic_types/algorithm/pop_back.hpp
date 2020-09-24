// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_POP_BACK_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_POP_BACK_HPP
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

// Pop back
template <class...>
struct PopBack;
template <class Head, class... Tail>
struct PopBack<Head, Tail...> {
    using type = Concat_t<Head, typename PopBack<Tail...>::type>;
};
template <class Tail>
struct PopBack<Tail> {
    using type = pack<>;
};
template <class Head, class... Tail>
struct PopBack<pack<Head, Tail...>> : PopBack<Head, Tail...> {
};
template <class... Pack>
using PopBack_t = typename PopBack<Pack...>::type;

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::PopBack;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Pack>
using PopBack_t = typename variadic_types::detail::PopBack<Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
