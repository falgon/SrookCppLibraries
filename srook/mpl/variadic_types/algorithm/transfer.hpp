// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_TRANSFER_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_TRANSFER_HPP
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <template <class...> class Tuple, class... Arg>
struct Transfer {
    using type = Tuple<Arg...>;
};
template <template <class...> class Tuple, class... Arg>
struct Transfer<Tuple, pack<Arg...>> : Transfer<Tuple, Arg...> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::Transfer;

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class Tuple, class... Args>
using Transfer_t = typename variadic_types::detail::Transfer<Tuple, Args...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook
#endif
