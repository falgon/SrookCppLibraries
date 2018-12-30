// Inspired by n4115
// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#include <srook/config.hpp>
#include <srook/mpl/variadic_types/pack.hpp>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace variadic_types {
SROOK_INLINE_NAMESPACE(v1)

template <class, class...>
struct is_contained_in;

template <class T, class H, class... P>
struct is_contained_in<T, H, P...> : public is_contained_in<T, P...> {};

template <class T>
struct is_contained_in<T> : public SROOK_FALSE_TYPE {};

template <class T, class... P>
struct is_contained_in<T, T, P...> : public SROOK_TRUE_TYPE {};

template <class T, class... P>
struct is_contained_in<T, pack<P...>> : public is_contained_in<T, P...> {};

SROOK_INLINE_NAMESPACE_END
} // namespace variadic_types

using variadic_types::is_contained_in;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class... P>
SROOK_CONSTEXPR bool is_contained_in_v = is_contained_in<T, P...>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace srook
