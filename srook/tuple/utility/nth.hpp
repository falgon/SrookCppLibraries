// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_UTILITY_NTH_HPP
#define INCLUDED_SROOK_TUPLE_UTILITY_NTH_HPP

#include <srook/tuple/utility/detail/utils.hpp>
#include <srook/tuple/algorithm/split.hpp>
#include <srook/type_traits/is_tuple.hpp>
#include <srook/utility/index_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple, utility) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class, class, std::size_t>
struct nth_tuple_elements_impl;

template <class Tuple, std::size_t... I, std::size_t offset>
struct nth_tuple_elements_impl<Tuple, srook::utility::index_sequence<I...>, offset>
    : type_constant<srook::tmpl::vt::packer<SROOK_DEDUCED_TYPENAME std::tuple_element<offset + I, Tuple>::type...>> {};

template <class Tuple, std::size_t I, std::size_t offset>
struct nth_tuple_elements 
    : nth_tuple_elements_impl<Tuple, SROOK_DEDUCED_TYPENAME srook::utility::make_index_sequence_type<I>::type, offset> {};

template <class T, std::size_t I, class F>
struct get_return_type
    : srook::tmpl::vt::concat<
        SROOK_DEDUCED_TYPENAME srook::tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME nth_tuple_elements<T, I - 1, 0>::type,
            SROOK_DEDUCED_TYPENAME invoke_result<F, SROOK_DEDUCED_TYPENAME std::tuple_element<I, T>::type>::type
        >::type,
        SROOK_DEDUCED_TYPENAME nth_tuple_elements<T, I + 1, I - 1>::type    
      > {};

#if !SROOK_CPP_LAMBDAS && SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT
template <class F, std::size_t I>
class intrinsic_lambda_nth : srook::utility::lambda_wrapper<F> {
    typedef srook::utility::lambda_wrapper<F> base_type;
public:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    intrinsic_lambda_nth(F f) SROOK_NOEXCEPT(is_nothrow_constructive<base_type, F>::value)
        : base_type(srook::forward<F>(f)) {}
    
    template <class T, SROOK_REQUIRES(is_tuple<SROOK_DEDUCED_TYPENAME decay<T>::type>::value)>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE 
    SROOK_DEDUCED_TYPENAME detail::get_return_type<SROOK_DEDUCED_TYPENAME decay<T>::type, I, F>::type
    operator()(T&& tpl) SROOK_MEMFN_NOEXCEPT(detail::is_noexcept_type<F>::value)
    {
        return std::tuple_cat(srook::tuple::split_first<I>(tpl), std::make_tuple(base_type::operator()(std::get<I>(tpl))), srook::tuple::split_last<I + 1>(tpl));
    }
};
#endif

} // namespace detail

template <std::size_t I, class F, SROOK_REQUIRES(is_callable<SROOK_DEDUCED_TYPENAME decay<F>::type>::value)>
#if SROOK_CPP_LAMBDAS && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
auto
#else
detail::intrinsic_lambda_nth<SROOK_DEDUCED_TYPENAME decay<F>::type, I>
#endif
nth(F&& fn) SROOK_NOEXCEPT(detail::is_noexcept_type<F>::value)
{
#if SROOK_CPP_LAMBDAS && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    return
        [f = srook::forward<F>(fn)](auto&& tpl) SROOK_CXX17_CONSTEXPR
        noexcept(detail::is_noexcept_type<F>::value) 
        //-> SROOK_DEDUCED_TYPENAME srook::tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME detail::get_return_type<decay_t<SROOK_DECLTYPE(tpl)>, I, F>::type>::type
        {
            return std::tuple_cat(srook::tuple::split_first<I>(tpl), std::make_tuple(f(std::get<I>(tpl))), srook::tuple::split_last<I + 1>(tpl));
        };
#else
    return detail::intrinsic_lambda_nth<SROOK_DEDUCED_TYPENAME decay<F>::type, I>(srook::forward<F>(fn));
#endif
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(utility, tuple, srook)
#endif
