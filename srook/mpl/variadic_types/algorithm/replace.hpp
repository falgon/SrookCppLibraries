// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_REPLACE_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_REPLACE_HPP
#include <srook/mpl/variadic_types/algorithm/concat.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class, class, class...>
struct Replace;
template <class T, class R, class Head, class... Tail>
struct Replace<T, R, Head, Tail...> {
    using type = Concat_t<Head, typename Replace<T, R, Tail...>::type>;
};
template <class T, class R, class... Tail>
struct Replace<T, R, T, Tail...> {
    using type = Concat_t<R, Tail...>;
};
template <class T, class R>
struct Replace<T, R> {
    using type = pack<>;
};
template <class T, class R, class Head, class... Tail>
struct Replace<T, R, pack<Head, Tail...>> : Replace<T, R, Head, Tail...> {
};
template <class T, class R, class... Pack>
using Replace_t = typename Replace<T, R, Pack...>::type;

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::Replace;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T, class R, class... Pack>
using Replace_t = typename Replace<T, R, Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
