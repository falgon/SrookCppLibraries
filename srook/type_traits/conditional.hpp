// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRIATS_CONDITIONAL_HPP
#define INCLUDED_SROOK_TYPE_TRIATS_CONDITIONAL_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <bool, class, class R>
struct conditional {
    typedef R type;
};

template <class L, class R>
struct conditional<true, L, R> {
    typedef L type;
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::conditional;

#if SROOK_CPP_ALIAS_TEMPLATES
template <bool b, class L, class R>
using conditional_t = typename type_traits::detail::conditional<b, L, R>::type;
#endif

} // namespace srook

#endif
