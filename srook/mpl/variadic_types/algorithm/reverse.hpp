// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_REVERSE_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_REVERSE_HPP
#include <cstddef>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>
#include <srook/mpl/variadic_types/algorithm/last.hpp>
#include <srook/mpl/variadic_types/algorithm/pop_back.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

// Reverse
template <class... Args>
struct Reverse {
    using type = Concat_t<Last_t<Args...>, typename Reverse<PopBack_t<Args...>>::type>;
};
template <>
struct Reverse<pack<>> {
    using type = pack<>;
};
template <class... Args>
struct Reverse<pack<Args...>> : Reverse<Args...> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::Reverse;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Args>
using Reverse_t = typename variadic_types::detail::Reverse<Args...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
