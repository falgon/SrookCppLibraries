// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_SIZE_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_SIZE_HPP
#include <cstddef>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/algorithm/length.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class... Ts>
struct Size {
    static constexpr std::size_t value = Length<Ts...>::value;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::Size;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class Head, class... Tail>
constexpr std::size_t Size_v = 1 + Length_v<Tail...>;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook
#endif
