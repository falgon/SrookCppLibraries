// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_NO_DUPLICATE_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_ALGORITHM_NO_DUPLICATE_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>
#include <srook/mpl/variadic_types/algorithm/erase.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class...>
struct NoDuplicate;
template <class Head, class... Tail>
struct NoDuplicate<Head, Tail...> {
private:
    using inner_type = Erase_t<Head, typename NoDuplicate<Tail...>::type>;

public:
    using type = Concat_t<Head, inner_type>;
};
template <class Head, class... Tail>
struct NoDuplicate<pack<Head, Tail...>> : NoDuplicate<Head, Tail...> {
};
template <>
struct NoDuplicate<> {
    using type = pack<>;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::detail::NoDuplicate;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Pack>
using NoDuplicate_t = typename variadic_types::detail::NoDuplicate<Pack...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook
#endif
