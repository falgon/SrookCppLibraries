// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_ALGORITHM_MAP_HPP
#define INCLUDED_SROOK_TUPLE_ALGORITHM_MAP_HPP
#include <srook/config.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/is_nothrow_invocable.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/map.hpp>
#include <srook/tmpl/vt/mapD.hpp>
#include <srook/tmpl/vt/composition.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/tuple/algorithm/apply.hpp>
#include <srook/execution.hpp>
#include <future>

SROOK_NESTED_NAMESPACE(srook, tuple) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT
namespace detail {

template <std::size_t... I, class F, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<tmpl::vt::bind<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>, Ts...>::type>::type
map_impl(index_sequence<I...>, F&& f, const std::tuple<Ts...>& ts)
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Ts>...>::value)
{
    return std::make_tuple(f(std::get<I>(ts))...);
}

template <class>
struct ft_type;

template <class T>
struct ft_type<std::future<T>>
    : type_constant<T> {};

struct getter {
    template <class... Futures>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
    tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::map<ft_type, SROOK_DEDUCED_TYPENAME decay<Futures>::type...>::type>::type
    operator()(Futures&&... ft)
    {
        return std::make_tuple(ft.get()...);
    }
};

template <std::size_t... I, class F, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<tmpl::vt::bind<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>, Ts...>::type>::type
map_impl(srook::execution::parallel_unsequenced_policy, index_sequence<I...>, F&& f, const std::tuple<Ts...>& ts)
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Ts>...>::value)
{
    return tuple::apply(getter{}, std::make_tuple(std::async(std::launch::async, std::bind(f, std::get<I>(ts)))...));
}

} // namespace detail
#endif

template <class F, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
auto
#else
SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<tmpl::vt::bind<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>, Ts...>::type>::type
#endif
map(F&& f, const std::tuple<Ts...>& ts)
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Ts>...>::value)
{
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    return 
        tuple::apply(
            [ff = srook::forward<F>(f)](auto&&... xs) noexcept(type_traits::detail::Land<is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Ts>...>::value) { 
                return std::make_tuple(ff(srook::forward<SROOK_DECLTYPE(xs)>(xs))...); 
            }, ts);
#else
    return detail::map_impl(SROOK_DEDUCED_TYPENAME make_index_sequence_type<std::tuple_size<std::tuple<Ts...>>::value>::type{}, srook::forward<F>(f), ts);
#endif
}

template <class F, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
auto
#else
SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<tmpl::vt::bind<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>, Ts...>::type>::type
#endif
map(srook::execution::sequenced_policy, F&& f, const std::tuple<Ts...>& ts)
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, Ts>...>::value)
{
    return map(srook::forward<F>(f), ts);
}

template <class F, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
auto
#else
SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<tmpl::vt::bind<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>, Ts...>::type>::type
#endif
map(srook::execution::parallel_unsequenced_policy 
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT
        p
#endif
        ,
        F&& f, const std::tuple<Ts...>& ts)
{
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    return 
        tuple::apply(
            [ff = srook::forward<F>(f)](auto&&... xs) { 
                return 
                    tuple::apply(
                        [](auto&&... ps) { return std::make_tuple(ps.get()...); }, 
                        std::make_tuple(std::async(std::launch::async, std::bind(ff, srook::forward<SROOK_DECLTYPE(xs)>(xs)))...)
                    );
            }, ts);
#else
    return detail::map_impl(p, SROOK_DEDUCED_TYPENAME make_index_sequence_type<std::tuple_size<std::tuple<Ts...>>::value>::type{}, srook::forward<F>(f), ts);
#endif
}

template <class F, class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
auto
#else
SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<tmpl::vt::bind<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>, Ts...>::type>::type
#endif
map(srook::execution::parallel_policy 
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT
        p
#endif
        ,
        F&& f, const std::tuple<Ts...>& ts)
{
    return map(srook::execution::par_unseq, srook::forward<F>(f), ts);
}


SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(tuple, srook)

#endif
