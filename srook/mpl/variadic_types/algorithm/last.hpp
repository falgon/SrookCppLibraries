// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_LAST_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_LAST_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class...>
struct Last;
template <class Head, class... Tail>
struct Last<Head, Tail...> {
    using type = typename Last<Tail...>::type;
};
template <>
struct Last<> {
    using type = NULLOPT_T;
};
template <class Tail>
struct Last<Tail> {
    using type = Tail;
};
template <class Head, class... Tail>
struct Last<pack<Head, Tail...>> : Last<Head, Tail...> {
};
template <class... Pack>
using Last_t = typename Last<Pack...>::type;

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::Last;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Pack>
using Last_t = typename variadic_types::detail::Last<Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
