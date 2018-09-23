// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_BOOLEAN_HPP
#define INCLUDED_SROOK_TMPL_VT_BOOLEAN_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/tmpl/vt/compare.hpp>
#include <srook/type_traits/conditional.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <template <class...> class WhenFalse, template <class...> class, bool, class... Xs>
struct boolean_impl 
    : WhenFalse<Xs...> {};

template <template <class...> class WhenFalse, template <class...> class WhenTrue, class... Xs>
struct boolean_impl<WhenFalse, WhenTrue, true, Xs...> 
    : WhenTrue<Xs...> {};

} // namespace detail

template <template <class...> class WhenFalse, template <class...> class WhenTrue, template <class...> class Condition, class... Xs>
struct boolean 
    : detail::boolean_impl<WhenFalse, WhenTrue, Condition<Xs...>::value, Xs...> {};

template <template <class...> class WhenFalse, template <class...> class WhenTrue, template <class...> class Condition, class... Xs>
struct boolean<WhenFalse, WhenTrue, Condition, packer<Xs...>>
    : boolean<WhenFalse, WhenTrue, Condition, Xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <template <class...> class WhenFalse, template <class...> class WhenTrue, template <class...> class Condition, class... Xs>
using boolean_t = SROOK_DEDUCED_TYPENAME boolean<WhenFalse, WhenTrue, Condition, Xs...>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
