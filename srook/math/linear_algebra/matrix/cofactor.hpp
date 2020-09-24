// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_MATRIX_COFACTOR_HPP
#define INCLUDED_SROOK_MATH_MATRIX_COFACTOR_HPP

#include <srook/config.hpp>
#include <srook/math/constants/algorithm/pow.hpp>
#include <srook/math/linear_algebra/matrix/impl.h>
#include <srook/math/linear_algebra/matrix/helperfn.hpp>
#include <srook/tmpl/vt/take.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/drop.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/head.hpp>
#include <srook/tmpl/vt/foldr1.hpp>
#include <srook/tuple/algorithm/take.hpp>
#include <srook/tuple/algorithm/drop.hpp>
#include <srook/tuple/algorithm/map.hpp>
#include <srook/tuple/algorithm/foldr1.hpp>
#include <srook/utility/index_sequence.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t I>
struct drop_to_row {
    template <class Row>
    struct generate 
        : tmpl::vt::transfer<
            row, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME tmpl::vt::take<I, SROOK_DEDUCED_TYPENAME row_to_packer<Row>::type>::type,
                SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I + 1, SROOK_DEDUCED_TYPENAME row_to_packer<Row>::type>::type
            >::type
        > {};
};

struct cofactor {
private:
    template <std::size_t, class... Row, class... Ts>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
    std::common_type<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>::type
    expansion_impl(const matrix_impl<Row...>&, index_sequence<>, Ts&&... ts)
    {
        typedef SROOK_DEDUCED_TYPENAME std::common_type<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>::type cm_type;
        return tuple::foldr1(std::plus<>{}, std::make_tuple(cm_type(srook::forward<Ts>(ts))...));
    }

    template <std::size_t Ln, class... Row, std::size_t I, std::size_t... Idx, class... Ts>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    tmpl::vt::foldr1<
        std::common_type, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<common_row, Row...>::type>::type,
            SROOK_DECLTYPE(srook::math::pow(-1, Ln + I))
        >::type
    >::type
    expansion_impl(const matrix_impl<Row...>& m, index_sequence<I, Idx...>, Ts&&... ts)
    {
        return 
            expansion_impl<Ln>(
                m,
                index_sequence<Idx...>{},
                srook::forward<Ts>(ts)...,
                srook::math::pow(-1, Ln + I) * m.template get<Ln, I>() * expansion_row<0>(take<Ln, I>(m))
            );
    }
public:
    template <std::size_t I, std::size_t J, class... Row>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR 
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME tmpl::vt::map<
            drop_to_row<J>::template generate,
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME tmpl::vt::take<I, Row...>::type,
                SROOK_DEDUCED_TYPENAME tmpl::vt::drop<I + 1, Row...>::type
            >::type
        >::type
    >::type
    take(const matrix_impl<Row...>& m)
    {
        return 
            make_matrix_impl(
                tuple::map([](const auto& row) { 
                    return std::tuple_cat(tuple::take<J>(row), tuple::drop<J + 1>(row)); 
                }, std::tuple_cat(tuple::take<I>(m.to_tuple()), tuple::drop<I + 1>(m.to_tuple())))
            );
    }

    template <std::size_t, class Row>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    tmpl::vt::head<SROOK_DEDUCED_TYPENAME row_to_packer<Row>::type>::type
    expansion_row(const matrix_impl<Row>& m)
    {
        SROOK_STATIC_ASSERT((matrix_impl<Row>::row_length == 1), "The matrix must be square.");
        return m.template get<0, 0>();
    }

    template <std::size_t, class R1, class R2>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
    tmpl::vt::foldr1<std::common_type, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<common_row, R1, R2>::type>::type>::type
    expansion_row(const matrix_impl<R1, R2>& m)
    {
        SROOK_STATIC_ASSERT((matrix_impl<R1, R2>::row_length == 2), "The matrix must be square.");
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<std::common_type, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<common_row, R1, R2>::type>::type>::type cm_type;
        return cm_type(m.template get<0, 0>()) * cm_type(m.template get<1, 1>()) - cm_type(m.template get<0, 1>()) * cm_type(m.template get<1, 0>());
    }

    template <std::size_t Ln, class R1, class R2, class R3, class... Row>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR auto
    expansion_row(const matrix_impl<R1, R2, R3, Row...>& m)
    -> SROOK_DECLTYPE(cofactor::expansion_impl<Ln>(m, SROOK_DEDUCED_TYPENAME make_index_sequence_type<matrix_impl<R1, R2, R3, Row...>::row_length>::type{}))
    {
        SROOK_STATIC_ASSERT((matrix_impl<R1, R2, R3, Row...>::row_length == sizeof...(Row) + 3), "The matrix must be square.");
        return expansion_impl<Ln>(m, SROOK_DEDUCED_TYPENAME make_index_sequence_type<matrix_impl<R1, R2, R3, Row...>::row_length>::type{});
    }

    template <class... Row>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR auto
    expansion(const matrix_impl<Row...>& m)
    -> SROOK_DECLTYPE(cofactor::expansion_row<0>(m))
    {
        return expansion_row<0>(m);
    }
};


} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
