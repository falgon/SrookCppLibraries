// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_LINEAR_EQUATIONS_ALGO_ELEMENTARY_TRANSFORMER_HPP
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_LINEAR_EQUATIONS_ALGO_ELEMENTARY_TRANSFORMER_HPP
#include <srook/config.hpp>
#include <srook/math/linear_algebra/vector/impl.h>
#include <srook/math/linear_algebra/matrix/impl.h>
#include <srook/math/linear_algebra/matrix/helperfn.hpp>
#include <srook/tuple/algorithm/swap.hpp>
#include <srook/tuple/algorithm/map.hpp>
#include <srook/tuple/algorithm/zip_with.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/type_traits/is_convertible.hpp>
#include <srook/type_traits/detail/has_type_gen.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

SROOK_TT_DEF_HAS_TYPE_IMPL(equations_resolver);
SROOK_TT_DEF_HAS_TYPE(equations_resolver);

template <class>
struct tuple2packer;

template <class... Ts>
struct tuple2packer<std::tuple<Ts...>>
    : type_constant<tmpl::vt::packer<Ts...>> {};

template <class... Row>
class elementary_transformer {
public:
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::size_t column_length = matrix_impl<Row...>::column_length;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::size_t row_length = matrix_impl<Row...>::row_length;

    SROOK_FORCE_INLINE SROOK_CONSTEXPR 
    elementary_transformer(const matrix_impl<Row...>& m) SROOK_NOEXCEPT_TRUE
        : m_(m) {}

    template <std::size_t I1, std::size_t I2>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR 
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME tuple2packer<SROOK_DEDUCED_TYPENAME tuple::detail::swap_result_type<I1, I2, Row...>::type>::type
    >::type
    swap() const SROOK_NOEXCEPT_TRUE
    {
        return I1 == I2 ? m_ : swap_row_impl<I1, I2>(m_.to_tuple());
    }

    template <std::size_t I, class T>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME tmpl::vt::take<I, Row...>::type,
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                    row,
                    SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<
                        tmpl::vt::bind<std::common_type, SROOK_DEDUCED_TYPENAME decay<T>::type>,
                        SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, Row...>::type>::type
                    >::type
                >::type
            >::type,
            SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I + 1, Row...>::type
        >::type
    >::type
    mul(T&& val) const SROOK_NOEXCEPT_TRUE
    {
        return mul_row_impl<I>(m_.to_tuple(), srook::forward<T>(val));
    }

    template <std::size_t Target, std::size_t ExpI1, std::size_t ExpI2>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME tmpl::vt::take<Target, Row...>::type,
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME common_row<SROOK_DEDUCED_TYPENAME tmpl::vt::at<ExpI1, Row...>::type, SROOK_DEDUCED_TYPENAME tmpl::vt::at<ExpI2, Row...>::type>::type,
                SROOK_DEDUCED_TYPENAME tmpl::vt::drop<Target + 1, Row...>::type
            >::type
        >::type
    >::type
    add() const SROOK_NOEXCEPT_TRUE
    {
        return add_row_impl<Target, ExpI1, ExpI2>(m_.to_tuple());
    }

    template <std::size_t I, std::size_t J>
    SROOK_CONSTEXPR const SROOK_DEDUCED_TYPENAME 
    tmpl::vt::at<J, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, Row...>::type>::type>::type&
    get() const SROOK_NOEXCEPT_TRUE
    {
        return m_.template get<I, J>();
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::tuple<Row...> to_tuple() const
    {
        return m_.to_tuple();
    }
private:
    friend std::ostream& operator<<(std::ostream& os, const elementary_transformer& et)
    {
        return os << et.m_;
    }

    template <std::size_t Target, std::size_t ExpI1, std::size_t ExpI2, class... Ts>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME tmpl::vt::take<Target, Ts...>::type,
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME common_row<SROOK_DEDUCED_TYPENAME tmpl::vt::at<ExpI1, Ts...>::type, SROOK_DEDUCED_TYPENAME tmpl::vt::at<ExpI2, Ts...>::type>::type,
                SROOK_DEDUCED_TYPENAME tmpl::vt::drop<Target + 1, Ts...>::type
            >::type
        >::type
    >::type
    add_row_impl(const std::tuple<Ts...>& ts) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl,
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME tmpl::vt::take<Target, Ts...>::type,
                SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                    SROOK_DEDUCED_TYPENAME common_row<SROOK_DEDUCED_TYPENAME tmpl::vt::at<ExpI1, Ts...>::type, SROOK_DEDUCED_TYPENAME tmpl::vt::at<ExpI2, Ts...>::type>::type,
                    SROOK_DEDUCED_TYPENAME tmpl::vt::drop<Target + 1, Ts...>::type
                >::type
            >::type
        >::type result_type;

        return 
            result_type(
                std::tuple_cat(
                    std::tuple_cat(tuple::take<Target>(ts), std::make_tuple(tuple::zip_with(std::plus<>(), std::get<ExpI1>(ts), std::get<ExpI2>(ts)))), // left and result
                    tuple::drop<Target + 1>(ts)
                )
            );
    }
    
    template <std::size_t I1, std::size_t I2, class... Ts>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR 
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME tuple2packer<SROOK_DEDUCED_TYPENAME tuple::detail::swap_result_type<I1, I2, Ts...>::type>::type
    >::type
    swap_row_impl(const std::tuple<Ts...>& ts) const SROOK_NOEXCEPT_TRUE
    {
        return 
            SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                matrix_impl,
                SROOK_DEDUCED_TYPENAME tuple2packer<SROOK_DEDUCED_TYPENAME tuple::detail::swap_result_type<I1, I2, Ts...>::type>::type
            >::type(tuple::swap<I1, I2>(ts));
    }

    template <std::size_t I, class T, class... Ts>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME tmpl::vt::take<I, Ts...>::type,
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                    row,
                    SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<
                        tmpl::vt::bind<std::common_type, SROOK_DEDUCED_TYPENAME decay<T>::type>,
                        SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, Ts...>::type>::type
                    >::type
                >::type
            >::type,
            SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I + 1, Ts...>::type
        >::type
    >::type
    mul_row_impl(const std::tuple<Ts...>& ts, T&& val) const
    {
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl,
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                    SROOK_DEDUCED_TYPENAME tmpl::vt::take<I, Ts...>::type,
                    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                        row,
                        SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<
                            tmpl::vt::bind<std::common_type, SROOK_DEDUCED_TYPENAME decay<T>::type>,
                            SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, Ts...>::type>::type
                        >::type
                    >::type
                >::type,
                SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I + 1, Ts...>::type
            >::type
        >::type result_type;
        
        return 
            result_type(
                std::tuple_cat(
                    std::tuple_cat(
                        tuple::take<I>(ts), 
                        std::make_tuple(
                            tuple::map(
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
                                [&val](const auto& x) SROOK_CXX17_CONSTEXPR SROOK_NOEXCEPT_TRUE { 
                                    typedef SROOK_DEDUCED_TYPENAME std::common_type<SROOK_DEDUCED_TYPENAME decay<SROOK_DECLTYPE(x)>::type, SROOK_DEDUCED_TYPENAME decay<T>::type>::type cm_type;
                                    return cm_type(srook::forward<SROOK_DECLTYPE(x)>(x)) * cm_type(val); 
                                }
#else
                                multiplier<SROOK_DEDUCED_TYPENAME decay<T>::type>{srook::forward<T>(val)}
#endif
                                ,
                                std::get<I>(ts)
                            )
                        )
                    ),
                    tuple::drop<I + 1>(ts)
                )
            );
    }
#if SROOK_CPLUSPLUS < SROOK_CPLUSPLUS14_CONSTANT
private:
    template <class T>
    struct multiplier {
        template <class U, SROOK_REQUIRES(is_same<T, SROOK_DEDUCED_TYPENAME decay<U>::type>::value)>
        SROOK_FORCE_INLINE SROOK_CONSTEXPR multiplier(U&& val)
            : val_(srook::forward<U>(val)) {}
        
        template <class U>
        SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME enable_if<
            is_convertible<T, SROOK_DEDUCED_TYPENAME decay<U>::type>::value, 
            SROOK_DEDUCED_TYPENAME std::common_type<T, SROOK_DEDUCED_TYPENAME decay<U>::type>::type
        >::type 
        operator()(U&& val) const SROOK_NOEXCEPT_TRUE
        {
            typedef SROOK_DEDUCED_TYPENAME std::common_type<T, SROOK_DEDUCED_TYPENAME decay<U>::type>::type cm_type;
            return cm_type(srook::forward<U>(val)) * cm_type(val_);
        }
    private:
        T val_;
    };
public:
#endif
private:
    const matrix_impl<Row...> m_;
};

template <class... Row>
SROOK_FORCE_INLINE SROOK_CONSTEXPR elementary_transformer<Row...>
make_elementary_transformer(const matrix_impl<Row...>& m)
SROOK_NOEXCEPT_TRUE
{
    return elementary_transformer<Row...>(m);
}

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
