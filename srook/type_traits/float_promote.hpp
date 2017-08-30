#ifndef INCLUDED_SROOK_MATH_DETAIL_FLOAT_PROMOTE_HPP
#define INCLUDED_SROOK_MATH_DETAIL_FLOAT_PROMOTE_HPP

#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <type_traits>

namespace srook {

#if (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T>
struct float_promote1 : std::conditional<std::is_floating_point<T>::value, T, double> {
    static_assert(std::is_arithmetic<T>::value, "float_promote must be arithmetic type");
};

template <class T, class U>
struct float_promote2
    : std::conditional<(std::is_same<T, long double>::value or std::is_same<U, long double>::value), long double, typename std::conditional<(std::is_same<T, float>::value and std::is_same<U, float>::value), float, double>::type> {
    static_assert(std::is_arithmetic<T>::value and std::is_arithmetic<U>::value, "float_promote must be arithmetic type");
};

template <class... Ts>
struct float_promote_impl;
template <class T, class U, class... Ts>
struct float_promote_impl<T, U, Ts...> : float_promote_impl<typename float_promote2<T, U>::type, Ts...> {
};

template <class T>
struct float_promote_impl<T> : float_promote1<T> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

template <class... Ts>
struct float_promote : srook::type_traits::detail::float_promote_impl<typename std::decay<Ts>::type...> {};

#if SROOK_CPP_ALIAS_TEMPLATES

template <class... Ts>
using float_promote_t = typename float_promote<Ts...>::type;

#endif

#endif
}

#endif
