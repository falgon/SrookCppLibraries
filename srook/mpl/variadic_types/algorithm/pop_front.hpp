// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_POP_FRONT_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_POP_FRONT_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

// Pop front
template <class...>
struct PopFront;
template <class Head, class... Tail>
struct PopFront<Head, Tail...> {
    using type = pack<Tail...>;
};
template <class Head, class... Tail>
struct PopFront<pack<Head, Tail...>> : PopFront<Head, Tail...> {};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::PopFront;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Pack>
using PopFront_t = typename variadic_types::detail::PopFront<Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
