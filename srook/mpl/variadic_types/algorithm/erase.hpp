// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_ERASE_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_ERASE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T, class... Pack>
struct Erase;
template <class T, class L, class... R>
struct Erase<T, L, R...> {
    using type = Concat_t<L, typename Erase<T, R...>::type>;
};
template <class L, class... R>
struct Erase<L, L, R...> {
    using type = pack<R...>;
};
template <class Tail>
struct Erase<Tail> {
    using type = pack<>;
};
template <class T, class L, class... R>
struct Erase<T, pack<L, R...>> : Erase<T, L, R...> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::Erase;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T, class... Pack>
using Erase_t = typename variadic_types::detail::Erase<T, Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook
#endif
