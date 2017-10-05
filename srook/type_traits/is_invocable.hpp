// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_INVOCABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_INVOCABLE_HPP
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_convertible.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/utility/void_t.hpp>
#include <srook/utility/declval.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class, typename = typename voider<>::type>
struct is_invocable_impl : SROOK_FALSE_TYPE {};

template <class Result, class Ret>
struct is_invocable_impl<Result, Ret, typename voider<typename Result::type>::type> : Lor<is_void<Ret>,is_convertible<typename Result::type, Ret>>::type {};

} // namespace detail

template <class Fn, class... Args>
struct is_invocable : public detail::is_invocable_impl<invoke_result<Fn, Args...>, typename voider<>::type>::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_invocable;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class U>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_invocable_v = is_invocable<T>::value;
#endif

} // namespace srook

#endif
