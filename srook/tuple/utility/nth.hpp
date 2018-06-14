// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_UTILITY_NTH_HPP
#define INCLUDED_SROOK_TUPLE_UTILITY_NTH_HPP

#include <srook/tuple/utility/detail/utils.hpp>
#include <srook/tuple/utility/take.hpp>
#include <srook/tuple/utility/drop.hpp>
#include <srook/type_traits/is_tuple.hpp>
#include <srook/utility/index_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple, utility) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class>
struct rewrap;

template <class... Ts>
struct rewrap<std::tuple<Ts...>>
    : type_constant<srook::tmpl::vt::packer<Ts...>> {};

template <class L, class R>
struct rewrap<std::pair<L, R>>
    : type_constant<srook::tmpl::vt::packer<L, R>> {};

template <class F, std::size_t I, class Tuple>
struct return_type 
    : srook::tmpl::vt::transfer<
        std::tuple,
        SROOK_DEDUCED_TYPENAME srook::tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME srook::tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME srook::tmpl::vt::take<I, SROOK_DEDUCED_TYPENAME rewrap<SROOK_DEDUCED_TYPENAME decay<Tuple>::type>::type>::type,
                SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME std::tuple_element<I, SROOK_DEDUCED_TYPENAME decay<Tuple>::type>::type>::type
            >::type,
            SROOK_DEDUCED_TYPENAME srook::tmpl::vt::drop<I + 1, SROOK_DEDUCED_TYPENAME detail::rewrap<decay_t<Tuple>>::type>::type
        >::type
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
    SROOK_DEDUCED_TYPENAME detail::return_type<F, I, SROOK_DEDUCED_TYPENAME decay<T>::type>::type
    operator()(T&& tpl) SROOK_MEMFN_NOEXCEPT(detail::is_noexcept_type<F>::value)
    {
        return std::tuple_cat(take<I>(tpl), std::make_tuple(base_type::operator()(std::get<I>(tpl))), drop<I + 1>(tpl));
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
        -> SROOK_DEDUCED_TYPENAME detail::return_type<F, I, SROOK_DECLTYPE(tpl)>::type
        {
            return std::tuple_cat(srook::tuple::utility::take<I>(tpl), std::make_tuple(f(std::get<I>(tpl))), srook::tuple::utility::drop<I + 1>(tpl));
        };
#else
    return detail::intrinsic_lambda_nth<SROOK_DEDUCED_TYPENAME decay<F>::type, I>(srook::forward<F>(fn));
#endif
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(utility, tuple, srook)
#endif
