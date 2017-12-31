// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_INDEX_OF_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_INDEX_OF_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class, class...>
struct IndexOf;
template <class T, class Head, class... Tail>
struct IndexOf<T, Head, Tail...> {
    static constexpr int value = IndexOf<T, Tail...>::value == -1 ? IndexOf<T, Tail...>::value : 1 + IndexOf<T, Tail...>::value;
};
template <class Head, class... Tail>
struct IndexOf<Head, Head, Tail...> {
    static constexpr int value = 0;
};
template <class Tail>
struct IndexOf<Tail> {
    static constexpr int value = -1;
};
template <class T, class Head, class... Tail>
struct IndexOf<T, pack<Head, Tail...>> : IndexOf<T, Head, Tail...> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::IndexOf;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class... Args>
constexpr int IndexOf_v = variadic_types::detail::IndexOf<T, Args...>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
