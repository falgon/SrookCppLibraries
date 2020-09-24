// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_CONSTEXPR_FUNCTION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_CONSTEXPR_FUNCTION_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>
#if (SROOK_CPP_CONSTEXPR && SROOK_CPP_VARIADIC_TEMPLATES && SROOK_CPP_RVALUE_REFERENCES)
#    include <srook/config/attribute/force_inline.hpp>
#    include <srook/config/feature/inline_namespace.hpp>
#    include <srook/config/noexcept_detection.hpp>
#    include <srook/config/require.hpp>
#    include <srook/type_traits/conjunction.hpp>
#    include <type_traits>

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T>
SROOK_FORCE_INLINE constexpr bool true_(T)
{
    return true;
}

template <class T>
SROOK_FORCE_INLINE constexpr bool is_constexpr_function_impl(bool&&) SROOK_NOEXCEPT_TRUE
{
    return true;
}

template <class T>
SROOK_FORCE_INLINE constexpr bool is_constexpr_function_impl(const bool&&) SROOK_NOEXCEPT_TRUE
{
    return false;
}

template <class FuncType, typename std::add_pointer<FuncType>::type Func, class... Args, REQUIRES(srook::conjunction<std::is_nothrow_constructible<Args>...>::value), bool = true_(Func(Args{}...))>
SROOK_FORCE_INLINE constexpr bool is_constexpr_function_impl(bool&&) SROOK_NOEXCEPT_TRUE
{
    return true;
}

template <class FuncType, typename std::add_pointer<FuncType>::type Func, class... Args>
SROOK_FORCE_INLINE constexpr bool is_constexpr_function_impl(const bool&&) SROOK_NOEXCEPT_TRUE
{
    return false;
}

} // namespace detail
SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END

template <class T, class... Args>
SROOK_FORCE_INLINE constexpr bool is_constexpr_function(Args&&...) SROOK_NOEXCEPT_TRUE
{
    return detail::is_constexpr_function_impl<T, typename std::decay<Args>::type...>(0);
}

template <class FuncType, typename std::add_pointer<FuncType>::type Func, class... Args>
SROOK_FORCE_INLINE constexpr bool is_constexpr_function(Args...) SROOK_NOEXCEPT_TRUE
{
    return detail::is_constexpr_function_impl<FuncType, Func, Args...>(0);
}

} // namespace srook

#    endif
#endif
