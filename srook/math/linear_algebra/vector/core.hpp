// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_VECTOR_CORE_HPP
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_VECTOR_CORE_HPP

#ifndef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/math/linear_algebra/vector/impl.hpp>
#include <srook/math/linear_algebra/matrix/impl.hpp>
#include <srook/tmpl/vt/at.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/tmpl/vt/map.hpp>
#include <srook/tmpl/vt/mapD.hpp>
#include <srook/tmpl/vt/composition.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <complex>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)

template <class... Ts>
class vector : public detail::vector_impl<Ts...> {
    typedef detail::vector_impl<Ts...> base_type;
public:
    using base_type::base_type;
};

template <class T>
class vector<T> : public detail::vector_impl<T> {
    typedef detail::vector_impl<T> base_type;
public:
    using base_type::base_type;

    template <class U>
    SROOK_CONSTEXPR int cross_product(const vector<U>&) const SROOK_NOEXCEPT_TRUE { return 0; }
    template <class U>
    SROOK_CONSTEXPR int cross_product(const std::complex<U>&) const SROOK_NOEXCEPT_TRUE { return 0; }
};

namespace detail {

template <class... Ts>
struct is_vector<vector<Ts...>> : SROOK_TRUE_TYPE {};

template <class... Ts>
struct holder;

template <class, class>
struct type2i;

template <class... Ts, std::size_t I>
struct type2i<holder<Ts...>, integral_constant<std::size_t, I>>
    : tmpl::vt::at<I, tmpl::vt::packer<Ts...>> {};

template <class L, class Operator, class R>
struct Expression<L, Operator, R, 3> : Expression<L, Operator, R, 0> {
private:
    typedef Expression<L, Operator, R, 0> base_type;
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::at<0, SROOK_DEDUCED_TYPENAME base_type::packed_type>::type T1;
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::at<1, SROOK_DEDUCED_TYPENAME base_type::packed_type>::type T2;
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::at<2, SROOK_DEDUCED_TYPENAME base_type::packed_type>::type T3;
public:
    using base_type::base_type;

    template <class U1, class U2, class U3>
    SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<
        tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, tmpl::vt::packer<U1, U2, U3>, SROOK_DEDUCED_TYPENAME base_type::packed_type>::type>::value,
        detail::Expression<
            detail::Expression<vector<T2, T3, T1>, std::multiplies<>, vector<U3, U1, U2>>,
            std::minus<>,
            detail::Expression<vector<T3, T1, T2>, std::multiplies<>, vector<U2, U3, U1>>
        >
    >::type
    cross_product(const vector<U1, U2, U3>& r) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME base_type::packed_type>::type vec_type;
        return vec_type(*this).cross_product(r);
    }

    template <class L1, class Op, class R1>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR 
    SROOK_DEDUCED_TYPENAME enable_if<
        tmpl::vt::and_<
            SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<
                is_convertible, 
                SROOK_DEDUCED_TYPENAME Expression<L1, Op, R1, 3>::packed_type, 
                SROOK_DEDUCED_TYPENAME base_type::packed_type
            >::type
        >::value,
        detail::Expression<
            detail::Expression<
                vector<T2, T3, T1>, 
                std::multiplies<>, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                    vector,
                    SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<
                        tmpl::vt::bind<
                            type2i, 
                            SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<holder, SROOK_DEDUCED_TYPENAME Expression<L1, Op, R1, 3>::packed_type>::type
                        >,
                        tmpl::vt::packer<integral_constant<std::size_t, 2>, integral_constant<std::size_t, 0>, integral_constant<std::size_t, 1>>
                    >::type
                >::type
            >,
            std::minus<>,
            detail::Expression<
                vector<T3, T1, T2>, 
                std::multiplies<>, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                    vector,
                    SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<
                        tmpl::vt::bind<
                            type2i, 
                            SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<holder, SROOK_DEDUCED_TYPENAME Expression<L1, Op, R1, 3>::packed_type>::type
                        >,
                        tmpl::vt::packer<integral_constant<std::size_t, 1>, integral_constant<std::size_t, 2>, integral_constant<std::size_t, 0>>
                    >::type
                >::type
            >
        >
    >::type
    cross_product(const Expression<L1, Op, R1, 3>& exp) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME Expression<L1, Op, R1, 3>::packed_type>::type vec_type;
        return cross_product(vec_type(exp));
    }
};

} // namespace detail

template <class T1, class T2, class T3>
class vector<T1, T2, T3> : public detail::vector_impl<T1, T2, T3> {
    typedef detail::vector_impl<T1, T2, T3> base_type;
public:
    using base_type::base_type;

    template <class U1, class U2, class U3>
    SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<
        tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_convertible, tmpl::vt::packer<U1, U2, U3>, tmpl::vt::packer<T1, T2, T3>>::type>::value,
        detail::Expression<
            detail::Expression<vector<T2, T3, T1>, std::multiplies<>, vector<U3, U1, U2>>,
            std::minus<>,
            detail::Expression<vector<T3, T1, T2>, std::multiplies<>, vector<U2, U3, U1>>
        >
    >::type
    cross_product(const vector<U1, U2, U3>& rhs) const
    {
        typedef detail::Expression<vector<T2, T3, T1>, std::multiplies<>, vector<U3, U1, U2>> left_exp;
        typedef detail::Expression<vector<T3, T1, T2>, std::multiplies<>, vector<U2, U3, U1>> right_exp;
        typedef detail::Expression<left_exp, std::minus<>, right_exp> expression_type;
        return 
            expression_type(
                left_exp(
                    vector<T2, T3, T1>(this->template get<1>(), this->template get<2>(), this->template get<0>()),
                    vector<U3, U1, U2>(rhs.template get<2>(), rhs.template get<0>(), rhs.template get<1>())),
                right_exp(
                    vector<T3, T1, T2>(this->template get<2>(), this->template get<0>(), this->template get<1>()),
                    vector<U2, U3, U1>(rhs.template get<1>(), rhs.template get<2>(), rhs.template get<0>())));
    }
    
    template <class U1, class U2, class U3>
    SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<
        tmpl::vt::and_<
            SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<
                is_convertible, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, U1, U2, U3>::type, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, T1, T2, T3>::type
            >::type
        >::value,
        detail::Expression<
            detail::Expression<
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, T2, T3, T1>::type>::type, 
                std::multiplies<>, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, U3, U1, U2>::type>::type
            >,
            std::minus<>,
            detail::Expression<
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, T3, T1, T2>::type>::type, 
                std::multiplies<>, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, U2, U3, U1>::type>::type
            >
        >
    >::type
    cross_product(U1&& u1, U2&& u2, U3&& u3) const
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, U1, U2, U3>::type>::type vec_type;
        return cross_product(vec_type(srook::forward<U1>(u1), srook::forward<U2>(u2), srook::forward<U3>(u3)));
    }
};

// helper functions
template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<type_traits::detail::Land<type_traits::detail::Lnot<detail::is_matrix<SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>::value, vector<Ts...>>::type
make_vector(Ts&&... ts) SROOK_NOEXCEPT_TRUE
{
    return vector<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>(srook::forward<Ts>(ts)...);
}

template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR vector<Ts...> 
make_vector(const std::tuple<Ts...>& ts) SROOK_NOEXCEPT_TRUE
{
    return vector<Ts...>(ts);
}

template <class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
enable_if<detail::has_exp_tag<SROOK_DEDUCED_TYPENAME decay<Exp>::type>::value, SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME decay<Exp>::type::packed_type>::type>::type
make_vector(Exp&& exp) SROOK_NOEXCEPT_TRUE
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME decay<Exp>::type::packed_type>::type vec_type;
    return vec_type(srook::forward<Exp>(exp));
}

template <class... Row>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<detail::matrix_impl<Row...>::column_length == 1, vector<SROOK_DEDUCED_TYPENAME std::tuple_element<0, Row>::type...>>::type
make_vector(const detail::matrix_impl<Row...>& m) SROOK_NOEXCEPT_TRUE
{
    typedef vector<SROOK_DEDUCED_TYPENAME std::tuple_element<0, Row>::type...> vec_type;
    return vec_type(m);
}

#if SROOK_CPP_DEDUCTION_GUIDES
template <class... Ts>
vector(Ts&&...) -> vector<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>;

template <class... Ts>
vector(const std::tuple<Ts...>&) -> vector<Ts...>;
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

namespace std {

template <class... Ts>
struct tuple_size<srook::math::linear_algebra::vector<Ts...>> : integral_constant<std::size_t, sizeof...(Ts)> {};

template <std::size_t I, class... Ts>
struct tuple_element<I, srook::math::linear_algebra::vector<Ts...>> 
    : srook::tmpl::vt::boolean<
        srook::tmpl::vt::ignore<SROOK_NULLOPT_T>::template generate,
        srook::math::linear_algebra::detail::index_bind<I>::template generate,
        srook::math::linear_algebra::detail::is_onemore,
        Ts...
    > {};
    
} // namespace std

#endif
#endif
