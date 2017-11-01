// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_UTILITY_VOID_T_HPP
#define INCLUDED_SROOK_UTILITY_VOID_T_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <cstddef>
#include <srook/config/feature/inline_namespace.hpp>
#if SROOK_CPP_VARIADIC_TEMPLATES

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T, class... Ts>
struct Empty_type {
    constexpr std::size_t size() const noexcept { return sizeof...(Ts); }
    using type = T;
};

template <class... Ts>
struct void_t_impl : Empty_type<void, Ts...> {};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace utility

#if SROOK_CPP_ALIAS_TEMPLATES

template <class... Ts>
using void_t = typename utility::detail::void_t_impl<Ts...>::type;

#endif

template <class... Ts>
struct voider {
    using type = typename utility::detail::void_t_impl<Ts...>::type;
};

} // namespace srook

#else

#include <srook/utility/detail/non_supported/void_t.hpp>

#endif
#endif
