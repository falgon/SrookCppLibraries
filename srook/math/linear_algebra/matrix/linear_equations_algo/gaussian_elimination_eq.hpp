// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_LINEAR_EQUATIONS_ALGO_GAUSSIAN_ELIMINATION_EQ_HPP
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_LINEAR_EQUATIONS_ALGO_GAUSSIAN_ELIMINATION_EQ_HPP

#include <srook/config.hpp>
#include <srook/cstdfloat.hpp>
#include <srook/tmpl/vt/foldr1.hpp>
#include <srook/tmpl/vt/replicate.hpp>
#include <srook/tmpl/vt/size.hpp>
#include <srook/tmpl/vt/head.hpp>
#include <srook/tuple/algorithm/split.hpp>
#include <srook/tuple/algorithm/map.hpp>
#include <srook/tuple/algorithm/foldr1.hpp>
#include <srook/math/linear_algebra/vector/core.hpp>
#include <srook/math/linear_algebra/matrix/linear_equations_algo/elementary_transformer.hpp>
#include <srook/math/linear_algebra/matrix/utils.hpp>
#include <srook/math/constants/algorithm/abs.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/mpl/constant_sequence/algorithm/pop_front.hpp>
#include <srook/mpl/constant_sequence/algorithm/reverse.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <bool, std::size_t PivI, std::size_t PivJ, std::size_t I>
struct do_max_abs {
    template <class... Row>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR elementary_transformer<Row...>
    exec(const elementary_transformer<Row...>& et) 
    {
        return 
            do_max_abs<(I + 1 < sizeof...(Row)), PivI, PivJ, I + 1>::exec(
                srook::math::abs(et.template get<PivI, PivJ>()) < srook::math::abs(et.template get<I, PivJ>()) ? make_elementary_transformer(et.template swap<PivI, I>()) : et
            );
    }
};

template <std::size_t PivI, std::size_t PivJ, std::size_t I>
struct do_max_abs<false, PivI, PivJ, I> {
    template <class... Row>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR elementary_transformer<Row...>
    exec(const elementary_transformer<Row...>& et)
    {
        return et;
    }
};

template <std::size_t I, std::size_t J>
struct do_to_zero_forward {
    template <class... Row>
    SROOK_FORCE_INLINE static SROOK_CXX14_CONSTEXPR elementary_transformer<Row...>
    exec(const std::tuple<Row...>& t)
    {
        const SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, Row...>::type use_row = std::get<I>(t);
        return 
            make_elementary_transformer(
                make_matrix_impl(
                    std::tuple_cat(
                        tuple::take<I + 1>(t),
                        tuple::map([&use_row](const auto& row) SROOK_NOEXCEPT_TRUE {  
                                const auto cofficient = std::get<J>(row) / std::get<J>(use_row);
                                return tuple::zip_with([&cofficient](const auto& x, const auto& y) { return y - (x * cofficient); }, use_row, row);
                        }, tuple::drop<I + 1>(t))
                    )
                )
            );
    }
};

template <std::size_t I, std::size_t J>
struct do_to_zero_backward {
    template <class... Row>
    SROOK_FORCE_INLINE static SROOK_CXX14_CONSTEXPR elementary_transformer<Row...>
    exec(const std::tuple<Row...>& t)
    {
        const SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, Row...>::type use_row = std::get<I>(t);
        return
            make_elementary_transformer(
                make_matrix_impl(
                    std::tuple_cat(
                        tuple::map([&use_row](const auto& row) SROOK_NOEXCEPT_TRUE {
                            const auto coefficient = std::get<J>(row) / std::get<J>(use_row);
                            return tuple::zip_with([&coefficient](const auto& x, const auto& y) { return y - (x * coefficient); }, use_row, row);
                        }, tuple::split<I - 1>(t).first), 
                        tuple::drop<I>(t)
                    )
                )
            );
    }
};

struct gaussian_elimination_eq {
    typedef srook::floatmax_t max_precision_t;
    typedef max_precision_t result_val_type;
    struct equations_resolver;

    template <class R1, class R2, class... Row>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<matrix_impl<R1, R2, Row...>::row_length, max_precision_t>::type>::type
    operator()(const matrix_impl<R1, R2, Row...>& m) const
    {
        using constant_sequence::reverse;
        using constant_sequence::pop_front;

        return
            finalize<matrix_impl<R1, R2, Row...>::column_length - 1>(
                backward_substitution(
                    forward_elimination(to_common_et<max_precision_t>(m.to_tuple()), SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(Row) + 1>::type{}),
                    SROOK_DEDUCED_TYPENAME reverse<SROOK_DEDUCED_TYPENAME pop_front<std::make_index_sequence<sizeof...(Row) + 2>>::type>::type{}
                ).to_tuple(),
                std::make_tuple(),
                SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(Row) + 2>::type{}
            );
    }
private:
    template <std::size_t, class... Row, class... Res>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR vector<Res...>
    finalize(const std::tuple<Row...>&, const std::tuple<Res...>& rs, index_sequence<>) const
    {
        return vector<Res...>(rs);
    }

    template <std::size_t Last, class... Row, class... Res, std::size_t I, std::size_t... Is>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR 
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<matrix_impl<Row...>::row_length, max_precision_t>::type>::type
    finalize(const std::tuple<Row...>& t, const std::tuple<Res...>& rs, index_sequence<I, Is...>) const
    {
        return finalize<Last>(t, std::tuple_cat(rs, std::make_tuple(std::get<Last>(std::get<I>(t)) / std::get<I>(std::get<I>(t)))), index_sequence<Is...>{});
    }

    template <class... Row>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR elementary_transformer<Row...>
    backward_substitution(const elementary_transformer<Row...>& et, std::index_sequence<>) const
    {
        return et;
    }

    template <class... Row, std::size_t I, std::size_t... Is>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR elementary_transformer<Row...>
    backward_substitution(const elementary_transformer<Row...>& et, std::index_sequence<I, Is...>) const
    {
        return backward_substitution(do_to_zero_backward<I, I>::exec(et.to_tuple()), std::index_sequence<Is...>{});
    }

    template <class... Row>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR elementary_transformer<Row...>
    forward_elimination(const elementary_transformer<Row...>& et, index_sequence<>) const
    {
        return et;
    }

    template <class... Row, std::size_t I, std::size_t... Is>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR elementary_transformer<Row...>
    forward_elimination(const elementary_transformer<Row...>& et, index_sequence<I, Is...>) const
    {
        return forward_elimination(to_zero_forward<I, I>(max_abs<I, I>(et)), index_sequence<Is...>{});
    }

    template <std::size_t I, std::size_t J, class... Row>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR elementary_transformer<Row...>
    to_zero_forward(const elementary_transformer<Row...>& et) const
    {
        return do_to_zero_forward<I, J>::exec(et.to_tuple());
    }

#if 1
    template <std::size_t PivI, std::size_t PivJ, class... Row>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR elementary_transformer<Row...>
    max_abs(const elementary_transformer<Row...>& et) const 
    {
        SROOK_STATIC_ASSERT(
            (PivI + 1 < elementary_transformer<Row...>::row_length && PivJ < elementary_transformer<Row...>::column_length), 
            "gaussign_elimination::max_abs(): Indexes are out of bounds.");
        
        return do_max_abs<true, PivI, PivJ, PivI + 1>::exec(et);
    }
#endif
};

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
