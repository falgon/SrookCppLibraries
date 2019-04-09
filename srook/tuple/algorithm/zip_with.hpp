// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_ALGORITHM_ZIP_WITH_HPP
#define INCLUDED_SROOK_TUPLE_ALGORITHM_ZIP_WITH_HPP

#include <srook/config.hpp>
#include <srook/execution.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/zip_with.hpp>
#include <srook/tmpl/vt/and.hpp>
#include <srook/tmpl/vt/mapD.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/tuple/algorithm/apply.hpp>
#include <srook/tuple/algorithm/take.hpp>
#include <future>

SROOK_NESTED_NAMESPACE(srook, tuple) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <template <class...> class HOF, class F>
struct f {
    template <class L, class R>
    struct result_type
        : HOF<F, L, R> {};
};

template <class F, std::size_t... I, class... L, class... R>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<
    bool_constant<sizeof...(L) == sizeof...(R)>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::tuple, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<f<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type
    >::type
>::type
zip_with_impl(F&& f, index_sequence<I...>, const std::tuple<L...>& l, const std::tuple<R...>& r)
SROOK_NOEXCEPT(tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<f<is_nothrow_invocable, F>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type>::type::value)
{
    return std::make_tuple(srook::forward<F>(f)(std::get<I>(l), std::get<I>(r))...); 
}

template <class F, std::size_t... I, class... L, class... R>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    bool_constant<sizeof...(L) == sizeof...(R)>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::tuple,
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<f<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type
    >::type
>::type
zip_with_impl(srook::execution::parallel_unsequenced_policy, F&& f, index_sequence<I...>, const std::tuple<L...>& l, const std::tuple<R...>& r)
{
    return tuple::apply([](auto&&... xs) { return std::make_tuple(xs.get()...); }, std::make_tuple(std::async(std::launch::async, std::bind(f, std::get<I>(l), std::get<I>(r)))...));
}

} // namespace detail

template <class F, class... L, class... R>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<
    bool_constant<sizeof...(L) == sizeof...(R)>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::tuple, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<detail::f<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type
    >::type
>::type
zip_with(F&& f, const std::tuple<L...>& l, const std::tuple<R...>& r)
SROOK_NOEXCEPT(tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<f<is_nothrow_invocable, F>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type>::type::value)
{
    return detail::zip_with_impl(srook::forward<F>(f), SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(L)>::type{}, l, r);
}

template <class F, class... L, class... R>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<
    bool_constant<(sizeof...(L) < sizeof...(R))>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::tuple, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<detail::f<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type
    >::type
>::type
zip_with(F&& f, const std::tuple<L...>& l, const std::tuple<R...>& r)
SROOK_NOEXCEPT(tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<f<is_nothrow_invocable, F>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type>::type::value)
{
    return zip_with(srook::forward<F>(f), l, tuple::take<sizeof...(L)>(r));
}

template <class F, class... L, class... R>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<
    bool_constant<(sizeof...(L) > sizeof...(R))>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::tuple, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<detail::f<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type
    >::type
>::type
zip_with(F&& f, const std::tuple<L...>& l, const std::tuple<R...>& r)
SROOK_NOEXCEPT(tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<f<is_nothrow_invocable, F>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type>::type::value)
{
    return zip_with(srook::forward<F>(f), tuple::take<sizeof...(R)>(l), r);
}

template <class F, class... L, class... R>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
tmpl::vt::transfer<
    std::tuple, 
    SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<detail::f<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type
>::type
zip_with(srook::execution::sequenced_policy, F&& f, const std::tuple<L...>& l, const std::tuple<R...>& r)
SROOK_NOEXCEPT(tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<f<is_nothrow_invocable, F>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type>::type::value)
{
    return zip_with(srook::forward<F>(f), l, r);
}


template <class F, class... L, class... R>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    bool_constant<sizeof...(L) == sizeof...(R)>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::tuple, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<detail::f<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type
    >::type
>::type
zip_with(srook::execution::parallel_unsequenced_policy p, F&& f, const std::tuple<L...>& l, const std::tuple<R...>& r)
{
    return detail::zip_with_impl(p, srook::forward<F>(f), SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(L)>::type{}, l, r);
}

template <class F, class... L, class... R>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    bool_constant<(sizeof...(L) < sizeof...(R))>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::tuple, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<detail::f<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type
    >::type
>::type
zip_with(srook::execution::parallel_unsequenced_policy p, F&& f, const std::tuple<L...>& l, const std::tuple<R...>& r)
{
    return zip_with(p, srook::forward<F>(f), l, tuple::take<sizeof...(L)>(r));
}

template <class F, class... L, class... R>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME
enable_if<
    bool_constant<(sizeof...(L) > sizeof...(R))>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::tuple, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<detail::f<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type
    >::type
>::type
zip_with(srook::execution::parallel_unsequenced_policy p, F&& f, const std::tuple<L...>& l, const std::tuple<R...>& r)
{
    return zip_with(p, srook::forward<F>(f), tuple::take<sizeof...(R)>(l), r);
}

template <class F, class... L, class... R>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
tmpl::vt::transfer<
    std::tuple,
    SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<detail::f<invoke_result, SROOK_DEDUCED_TYPENAME decay<F>::type>::template result_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type
>::type
zip_with(srook::execution::parallel_policy, F&& f, const std::tuple<L...>& l, const std::tuple<R...>& r)
{
    return zip_with(srook::execution::par_unseq, srook::forward<F>(f), l, r);
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(tuple, srook)

#endif
