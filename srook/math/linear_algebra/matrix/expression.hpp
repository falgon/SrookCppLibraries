// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_EXPRESSION_HPP
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_EXPRESSION_HPP

#include <srook/math/linear_algebra/vector/impl.h>
#include <srook/math/linear_algebra/matrix/impl.h>
#include <srook/tmpl/vt/replicate.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tuple/algorithm/replicate.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class L, class Operator, class R>
struct matrix_expression {
    struct matrix_exp_tag;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::size_t row_length = L::row_length;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::size_t column_length = L::column_length;
        
    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_expression(const L& l, const R& r) SROOK_NOEXCEPT_TRUE
        : l_(l), r_(r) {}

    template <std::size_t I, std::size_t J>
    SROOK_CONSTEXPR auto get() const SROOK_NOEXCEPT(Operator()(declval<L&>().template get<I, J>(), declval<R&>().template get<I, J>()))
    -> SROOK_DECLTYPE(Operator()(declval<L&>().template get<I, J>(), declval<R&>().template get<I, J>()))
    {
        typedef SROOK_DECLTYPE(l_.template get<I, J>()) left_type;
        typedef SROOK_DECLTYPE(r_.template get<I, J>()) right_type;
        typedef SROOK_DEDUCED_TYPENAME std::common_type<left_type, right_type>::type cm_type;
        return Operator()(cm_type(l_.template get<I, J>()), cm_type(r_.template get<I, J>()));
    }
private:
    const L l_;
    const R r_;
};

template <class Exp1, class Exp2>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        has_matrix_exp_tag<Exp1>,
        has_matrix_exp_tag<Exp2>
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<Exp1, std::plus<>, Exp2>
>::type
operator+(const Exp1& exp1, const Exp2 exp2) SROOK_NOEXCEPT_TRUE
{
    return srook::math::linear_algebra::detail::matrix_expression<Exp1, std::plus<>, Exp2>(exp1, exp2);
}

template <class Exp1, class Exp2>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        has_matrix_exp_tag<Exp1>,
        has_matrix_exp_tag<Exp2>
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<Exp1, std::minus<>, Exp2>
>::type
operator-(const Exp1& exp1, const Exp2 exp2) SROOK_NOEXCEPT_TRUE
{
    return srook::math::linear_algebra::detail::matrix_expression<Exp1, std::minus<>, Exp2>(exp1, exp2);
}

template <class T, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME enable_if<
    has_matrix_exp_tag<Exp>::value, 
    srook::math::linear_algebra::detail::matrix_expression<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                Exp::row_length,
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Exp::column_length, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
            >::type
        >::type,
        std::multiplies<>,
        Exp
    >
>::type
operator*(T&& val, const Exp& exp) SROOK_NOEXCEPT_TRUE
{
    return srook::math::linear_algebra::detail::matrix_expression<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Exp::row_length, Exp>::type>::type,
        std::multiplies<>,
        Exp
    >(tuple::replicate<Exp::row_length>(tuple::replicate<Exp::column_length>(srook::forward<T>(val))), exp);
}

template <class T, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME enable_if<
    has_matrix_exp_tag<Exp>::value, 
    srook::math::linear_algebra::detail::matrix_expression<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                Exp::row_length,
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Exp::column_length, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
            >::type
        >::type,
        std::multiplies<>,
        Exp
    >
>::type
operator*(const Exp& exp, T&& val) SROOK_NOEXCEPT_TRUE
{
    return srook::forward<T>(val) * exp;
}

template <class T, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME enable_if<
    has_matrix_exp_tag<Exp>::value, 
    srook::math::linear_algebra::detail::matrix_expression<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                Exp::row_length,
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Exp::column_length, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
            >::type
        >::type,
        std::divides<>,
        Exp
    >
>::type
operator/(const Exp& exp, T&& val) SROOK_NOEXCEPT_TRUE
{
    return srook::math::linear_algebra::detail::matrix_expression<
        Exp,
        std::divides<>,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Exp::row_length, Exp>::type>::type
    >(exp, tuple::replicate<Exp::row_length>(tuple::replicate<Exp::column_length>(srook::forward<T>(val))));
}

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
