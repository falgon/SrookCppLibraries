// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_INVOCABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_INVOCABLE_HPP
#include <srook/type_traits/detail/config.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/library_concepts/INVOKE.hpp>
#include <srook/utility/declval.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class Fn, class... Args>
struct is_invocable_impl {
private:
    template <class X, class... Xs>
    static SROOK_DECLTYPE(library_concepts::INVOKE(declval<X>(), declval<Xs>()...), SROOK_TRUE_TYPE())
    test(int);

    template <class, class...>
    static SROOK_FALSE_TYPE test(...);
public:
    typedef SROOK_DECLTYPE(test<Fn, Args...>(0)) type;
};

} // namespace detail

template <class Fn, class... Args>
struct is_invocable : public detail::is_invocable_impl<Fn, Args...>::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_invocable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_invocable_v = is_invocable<T>::value;
#endif

} // namespace srook

#endif
#endif
