// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_VARIADIC_CONJUNCTION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_VARIADIC_CONJUNCTION_HPP

#include <srook/type_traits/strong_variadic_check.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <template <class, class> class, class, class>
struct variadic_conjunction;

template <template <class, class> class Checker, class... L, class... R>
struct variadic_conjunction<Checker, pack<L...>, pack<R...>>
    : public strong_variadic_check<Checker, pack<L...>, pack<R...>> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::variadic_conjunction;

#if SROOK_CPP_ALIAS_TEMPLATES
template <template<class, class> class Checker, class L, class R>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool variadic_conjunction_v = variadic_conjunction<Checker, L, R>::value;
#endif

} // namespace srook

#endif
