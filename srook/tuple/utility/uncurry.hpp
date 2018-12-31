// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_UTILITY_UNCURRY_HPP
#define INCLUDED_SROOK_TUPLE_UTILITY_UNCURRY_HPP

#include <srook/tuple/utility/detail/utils.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple, utility) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

#if !SROOK_CPP_LAMBDAS && SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT
template <class FnType, class ResultType, class ArgType, bool is_noexcept>
class intrinsic_lambda_uncurry : srook::utility::lambda_wrapper<FnType> {
    typedef srook::utility::lambda_wrapper<FnType> base_type;
public:
    SROOK_CONSTEXPR SROOK_FORCE_INLINE ResultType
    operator()(ArgType arg) const SROOK_MEMFN_NOEXCEPT(is_noexcept)
    {
        return srook::apply(static_cast<base_type>(*this), srook::move(arg));
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE
    intrinsic_lambda_uncurry(const intrinsic_lambda_uncurry& other) SROOK_NOEXCEPT_TRUE
        : base_type(static_cast<base_type>(other)) {}
private:
    template <class Fn, SROOK_REQUIRES(is_same<SROOK_DEDUCED_TYPENAME decay<Fn>::type, FnType>::value)>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE 
    intrinsic_lambda_uncurry(Fn&& f)
        : base_type(srook::forward<Fn>(f)) {}
    
    template <class Fn, class Res, class Arg, bool is_n, class F>
    friend SROOK_CONSTEXPR intrinsic_lambda_uncurry<Fn, Res, Arg, is_n> 
    intrinsic_lambda_uncurry_construct(F&&) SROOK_NOEXCEPT_TRUE;
};

template <class FnType, class ResultType, class ArgType, bool is_noexcept, class F>
SROOK_CONSTEXPR intrinsic_lambda_uncurry<FnType, ResultType, ArgType, is_noexcept>
intrinsic_lambda_uncurry_construct(F&& f) SROOK_NOEXCEPT_TRUE
{
    return intrinsic_lambda_uncurry<FnType, ResultType, ArgType, is_noexcept>(srook::forward<F>(f));
}
#endif

} // namespace detail

template <class F,
SROOK_REQUIRES(
    srook::tmpl::vt::transfer<
        srook::is_invocable, 
        SROOK_DEDUCED_TYPENAME srook::tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME decay<F>::type, 
            SROOK_DEDUCED_TYPENAME arguments<SROOK_DEDUCED_TYPENAME decay<F>::type>::type
        >::type
    >::type::value
)>
SROOK_CONSTEXPR SROOK_FORCE_INLINE 
#if SROOK_CPP_LAMBDAS && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
auto
#else
detail::intrinsic_lambda_uncurry<
    SROOK_DEDUCED_TYPENAME decay<F>::type,
    SROOK_DEDUCED_TYPENAME detail::result_type<F>::type,
    SROOK_DEDUCED_TYPENAME detail::argument_type<F>::type,
    detail::is_noexcept_type<F>::value
>
#endif
uncurry(F&& fn) SROOK_NOEXCEPT(detail::is_noexcept_type<F>::value)
{
#if SROOK_CPP_LAMBDAS && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    return 
        [f = srook::forward<F>(fn)](SROOK_DEDUCED_TYPENAME detail::argument_type<F>::type arg) 
        noexcept(detail::is_noexcept_type<F>::value) -> SROOK_DEDUCED_TYPENAME detail::result_type<F>::type {
            return srook::apply(f, srook::move(arg));
        };
#else
    return detail::intrinsic_lambda_uncurry_construct<
        SROOK_DEDUCED_TYPENAME decay<F>::type,
        SROOK_DEDUCED_TYPENAME detail::result_type<F>::type, 
        SROOK_DEDUCED_TYPENAME detail::argument_type<F>::type, 
        detail::is_noexcept_type<F>::value
    >(srook::forward<F>(fn));
#endif
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(utility, tuple, srook)

namespace srook {

using srook::tuple::utility::uncurry;

} // namespace srook
#endif
