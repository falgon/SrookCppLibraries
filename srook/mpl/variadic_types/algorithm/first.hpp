// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_FIRST_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_FIRST_HPP
#include <cstddef>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/libraries/optional.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class...>
struct First;
template <class Head, class... Tail>
struct First<Head, Tail...> {
    using type = Head;
};
template <>
struct First<> {
    using type = srook::libraries::nullopt_t;
};
template <class Head, class... Tail>
struct First<pack<Head, Tail...>> : First<Head> {
};
} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::First;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Pack>
using First_t = typename First<Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook
#endif
