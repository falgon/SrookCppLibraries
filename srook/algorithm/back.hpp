// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_ALGORITHM_EMPLACE_BACK_HPP
#define INCLUDED_ALGORITHM_EMPLACE_BACK_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/type_traits.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, class... Args>
struct has_emplace_back {
private:
    static SROOK_TRUE_TYPE test(SROOK_DEDUCED_TYPENAME voider<SROOK_DECLTYPE(declval<T>().emplace_back(declval<Args>()...))>::type* = 0);
    static SROOK_FALSE_TYPE test(...);
public:
    static SROOK_CONSTEXPR_OR_CONST bool value = SROOK_DECLTYPE(test(0))::value;
};

template <class T, class Arg>
struct has_push_back {
private:
    static SROOK_TRUE_TYPE test(SROOK_DEDUCED_TYPENAME add_pointer<SROOK_DECLTYPE(declval<T>().push_back(declval<Arg>()))>::type = 0);
    static SROOK_FALSE_TYPE test(...);
public:
    static SROOK_CONSTEXPR_OR_CONST bool value = SROOK_DECLTYPE(test(0))::value;
};

} // namespace detail

#if SROOK_CPP_RVALUE_REFERENCES
#if SROOK_CPP_VARIADIC_TEMPLATES
template <class Container, class... Args>
SROOK_FORCE_INLINE 
SROOK_DEDUCED_TYPENAME enable_if<detail::has_emplace_back<SROOK_DEDUCED_TYPENAME decay<Container>::type, Args&&...>::value>::type
emplace_back(Container& container, Args&&... args)
{
    container.emplace_back(srook::forward<Args>(args)...);
}
#endif
template <class Container, class Add_Element>
SROOK_FORCE_INLINE 
SROOK_DEDUCED_TYPENAME enable_if<detail::has_push_back<SROOK_DEDUCED_TYPENAME decay<Container>::type, Add_Element&&>::value>::type
push_back(Container& container, Add_Element&& args)
{
    container.push_back(srook::forward<Add_Element>(args));
}
#endif
SROOK_INLINE_NAMESPACE_END

} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

namespace srook {

using srook::algorithm::emplace_back;
using srook::algorithm::push_back;

} // namespace srook

#endif
#endif
