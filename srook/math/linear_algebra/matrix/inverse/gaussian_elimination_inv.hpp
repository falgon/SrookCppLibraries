// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_INVERSE_GAUSSIAN_ELIMINATION_INV_HPP
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_INVERSE_GAUSSIAN_ELIMINATION_INV_HPP

#include <srook/math/linear_algebra/matrix/utils.hpp>
#include <srook/math/linear_algebra/matrix/linear_equations_algo/elementary_transformer.hpp>
#include <srook/math/constants/algorithm/abs.hpp>
#include <srook/tmpl/vt/at.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <std::size_t I, std::size_t J, std::size_t PI>
struct max_abs {
    template <class... Row>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR std::tuple<Row...> 
    exec(const elementary_transformer<Row...>& et)
    {
        return 
            max_abs<I, J, PI - 1>::exec(
                srook::math::abs(et.template get<PI, J>()) > srook::math::abs(et.template get<I, J>()) ? 
                    make_elementary_transformer(et.template swap<I, PI>()) : et);
    }
};

template <std::size_t I, std::size_t J>
struct max_abs<I, J, 0> {
    template <class... Row>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR std::tuple<Row...>
    exec(const elementary_transformer<Row...>& et)
    {
        return srook::math::abs(et.template get<0, J>()) > srook::math::abs(et.template get<I, J>()) ? et.template swap<0, I>().to_tuple() : et.to_tuple();
    }
};

template <std::size_t RowN>
struct gaussian_elimination_inv {
    typedef srook::floatmax_t max_precision_t;
    typedef max_precision_t result_val_type;
    struct inverse_resolver;

    template <class... Row>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    tmpl::vt::transfer<
        matrix_impl, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
            matrix_impl<Row...>::row_length,
            SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<row, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<matrix_impl<Row...>::column_length / 2, max_precision_t>::type>::type
        >::type
    >::type
    operator()(const matrix_impl<Row...>& m) const
    {
        return 
            make_matrix_impl(
                tuple::map([](const auto& row) SROOK_NOEXCEPT_TRUE {
                    return tuple::drop<matrix_impl<Row...>::column_length / 2>(row);
                }, elimination(to_common_et<max_precision_t>(m.to_tuple()), SROOK_DEDUCED_TYPENAME make_index_sequence_type<RowN>::type{}).to_tuple())
            );
    }
private:
    template <std::size_t I, std::size_t J, class... Row>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::tuple<Row...>
    to_one(const std::tuple<Row...>& t) const
    {
        const SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, Row...>::type use_row = std::get<I>(t);
        return 
            std::tuple_cat(
                tuple::take<I>(t),
                std::tuple_cat(
                    std::make_tuple(
                        tuple::map([&use_row](const auto& elm) SROOK_NOEXCEPT_TRUE {
                            return elm * (1 / std::get<J>(use_row));
                        }, use_row) 
                    ),
                    tuple::drop<I + 1>(t)
                )
            );
    }

    template <std::size_t I, std::size_t J, class... Row>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR elementary_transformer<Row...>
    to_zero(const std::tuple<Row...>& t) const
    {
        const SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, Row...>::type use_row = std::get<I>(t);
        const auto specified_elem = std::get<J>(use_row);
        const auto lm = [&specified_elem, &use_row](const auto& row) SROOK_NOEXCEPT_TRUE {
            const auto target = std::get<J>(row);
            const auto val = -target / specified_elem;
            return
                tuple::zip_with([&val](const auto& x, const auto& y) SROOK_NOEXCEPT_TRUE {
                    return x * val + y;
                }, use_row, row);
            };

        return
            make_elementary_transformer(
                make_matrix_impl(
                    std::tuple_cat(
                        std::tuple_cat(
                            tuple::map(lm, tuple::take<I>(t)), 
                            std::make_tuple(use_row)
                        ),
                        tuple::map(lm, tuple::drop<I + 1>(t))
                    )
                )
            );
    }
    
    template <class... Row>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR elementary_transformer<Row...>
    elimination(const elementary_transformer<Row...>& et, index_sequence<>) const
    {
        return et;
    }

    template <class... Row, std::size_t I, std::size_t... Is>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR elementary_transformer<Row...>
    elimination(const elementary_transformer<Row...>& et, index_sequence<I, Is...>) const
    {
        return elimination(to_zero<I, I>(to_one<I, I>(max_abs<I, I, sizeof...(Row) - 1>::exec(et))), index_sequence<Is...>{});
    }
};

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
