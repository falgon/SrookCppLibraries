// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_IS_CONTAINED_IN_LIKE_HPP
#define INCLUDED_SROOK_TMPL_VT_IS_CONTAINED_IN_LIKE_HPP

#include <srook/tmpl/vt/detail/config.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <bool, template <class> class, class...>
struct is_contained_in_like_impl2;

template <template <class> class Likea, class... Ts>
struct is_contained_in_like_impl2<true, Likea, Ts...> : public SROOK_TRUE_TYPE {};

template <template <class> class Likea, class Head, class... Ts>
struct is_contained_in_like_impl2<false, Likea, Head, Ts...> : public is_contained_in_like_impl2<Likea<Head>::value, Likea, Ts...> {};

template <template <class> class Likea>
struct is_contained_in_like_impl2<false, Likea> : public SROOK_FALSE_TYPE {};

template <template <class> class, class...>
struct is_contained_in_like_impl1;

template <template <class> class Likea, class Head, class... Ts>
struct is_contained_in_like_impl1<Likea, Head, Ts...> : public is_contained_in_like_impl2<Likea<Head>::value, Likea, Ts...> {};

template <template <class> class Likea>
struct is_contained_in_like_impl1<Likea> : public SROOK_FALSE_TYPE {};

} // namespace detail

template <template <class> class Likea, class... Ts>
struct is_contained_in_like : public detail::is_contained_in_like_impl1<Likea, Ts...> {};

template <template <class> class Likea, class... Ts>
struct is_contained_in_like<Likea, packer<Ts...>> : public is_contained_in_like<Likea, Ts...> {};

#if SROOK_CPP_VARIADIC_TEMPLATES
template <template <class> class Likea, class... Ts>
SROOK_CONSTEXPR bool is_contained_in_like_v = is_contained_in_like<Likea, Ts...>::value;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
