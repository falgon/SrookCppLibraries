// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_RESULT_OF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_RESULT_OF_HPP

#include <srook/type_traits/is_nothrow_invocable.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class> struct result_of;

template <class F, class... Args>
struct result_of<F(Args...)> : public detail::invoke_resulter<F, Args...> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::result_of;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class T>
using result_of_t = SROOK_DEDUCED_TYPENAME result_of<T>::type;
#endif

} // namespace srook
#endif
#endif
