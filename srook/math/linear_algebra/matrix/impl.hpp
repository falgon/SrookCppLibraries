// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_IMPL_HPP
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_IMPL_HPP

#include <srook/math/linear_algebra/vector/impl.h>
#include <srook/math/linear_algebra/matrix/impl.h>
#include <srook/math/linear_algebra/matrix/expression.hpp>
#include <srook/math/linear_algebra/matrix/linear_equations_algo.hpp>
#include <srook/math/linear_algebra/matrix/inverse.hpp>
#include <srook/math/linear_algebra/matrix/cofactor.hpp>
#include <srook/math/linear_algebra/vector/core.hpp>

#include <srook/algorithm/for_each.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/is_nothrow_constructible.hpp>
#include <srook/type_traits/is_nothrow_move_constructible.hpp>
#include <srook/type_traits/is_scalar.hpp>
#include <srook/type_traits/is_rvalue_reference.hpp>
#include <srook/type_traits/remove_const.hpp>
#include <srook/tmpl/vt/composition.hpp>
#include <srook/tmpl/vt/all.hpp>
#include <srook/tmpl/vt/at.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/tmpl/vt/size.hpp>
#include <srook/tmpl/vt/and.hpp>
#include <srook/tmpl/vt/foldr1.hpp>
#include <srook/tmpl/vt/head.hpp>
#include <srook/tmpl/vt/zip_with.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/pop_front.hpp>
#include <srook/tmpl/vt/reverse.hpp>
#include <srook/tmpl/vt/erase_packer.hpp>
#include <srook/tmpl/vt/mapD.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/tuple/algorithm/split.hpp>
#include <srook/tuple/algorithm/replicate.hpp>
#include <srook/tuple/algorithm/map.hpp>
#include <srook/tuple/algorithm/foldr1.hpp>
#include <srook/tuple/algorithm/iterate.hpp>
#include <srook/tuple/algorithm/zip_with.hpp>
#include <srook/execution.hpp>
#include <tuple>

#if (!SROOK_CPP_LAMBDAS) || (!SROOK_CPP_ALIAS_TEMPLATES)
#   error "This feature needs lambda and alias templates."
#endif

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

// literal operator

struct mx_fill {};

template <template <class> class L, template <class> class R>
struct lrvalue_cond {
    template <class T>
    struct generate 
        : conditional<is_rvalue_reference<T>::value, R<T>, L<T>> {}; 
};

template <class...>
struct rotate_matrix_type_impl;

template <class E, class... Es, class... Row>
struct rotate_matrix_type_impl<row<E, Es...>, Row...>
    : tmpl::vt::concat<E, SROOK_DEDUCED_TYPENAME rotate_matrix_type_impl<Row...>::type> {};
    
template <>
struct rotate_matrix_type_impl<>
    : type_constant<tmpl::vt::packer<>> {};

template <class>
struct rotate_matrix_type;

template <class... Row>
struct rotate_matrix_type<tmpl::vt::packer<Row...>>
    : tmpl::vt::concat<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<row, SROOK_DEDUCED_TYPENAME rotate_matrix_type_impl<Row...>::type>::type, 
        SROOK_DEDUCED_TYPENAME rotate_matrix_type<
            tmpl::vt::packer<SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<row, SROOK_DEDUCED_TYPENAME tmpl::vt::pop_front<SROOK_DEDUCED_TYPENAME row_to_packer<Row>::type>::type>::type...>
        >::type
    > {};

template <class... Row>
struct rotate_matrix_type<tmpl::vt::packer<row<>, Row...>>
    : type_constant<tmpl::vt::packer<>> {};

template <std::size_t, class... Row, class L, class Op, class R>
SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl<Row...>&
matrix_impl_calculate2(matrix_impl<Row...>& this_, const matrix_expression<L, Op, R>&, index_sequence<>) SROOK_NOEXCEPT_TRUE
{
    return this_;
}

template <std::size_t I, class... Row, class L, class Op, class R, std::size_t J1, std::size_t... Js>
SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl<Row...>&
matrix_impl_calculate2(matrix_impl<Row...>& m, const matrix_expression<L, Op, R>& exp, index_sequence<J1, Js...>)
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::at<J1, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, Row...>::type>::type>::type type;
    return m.template get<I, J1>() = type(exp.template get<I, J1>()), matrix_impl_calculate2<I>(m, exp, index_sequence<Js...>{});
}

template <class... Row, class L, class Op, class R>
SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl<Row...>&
matrix_impl_calculate1(matrix_impl<Row...>& this_, const matrix_expression<L, Op, R>&, index_sequence<>) SROOK_NOEXCEPT_TRUE
{
    return this_;
}

template <class... Row, class L, class Op, class R, std::size_t I1, std::size_t... Is>
SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl<Row...>&
matrix_impl_calculate1(matrix_impl<Row...>& m, const matrix_expression<L, Op, R>& exp, index_sequence<I1, Is...>)
{
    return matrix_impl_calculate2<I1>(m, exp, SROOK_DEDUCED_TYPENAME make_index_sequence_type<matrix_impl<Row...>::column_length>::type{}),
           matrix_impl_calculate1(m, exp, index_sequence<Is...>{});
}
    

namespace compo {

struct foldr_cm {
    template <class... Ts>
    struct generate : tmpl::vt::foldr1<std::common_type, Ts...> {};
};

template <class, class>
struct composition_common_row;

template <class L, class... Ls, class... RRow>
struct composition_common_row<tmpl::vt::packer<L, Ls...>, tmpl::vt::packer<RRow...>>
    : tmpl::vt::concat<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            row, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::map<
                foldr_cm::template generate,
                SROOK_DEDUCED_TYPENAME tmpl::vt::map<row_to_packer, SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<tmpl::vt::bind<common_row, L>, RRow...>::type>::type
            >::type
        >::type, 
        SROOK_DEDUCED_TYPENAME composition_common_row<tmpl::vt::packer<Ls...>, tmpl::vt::packer<RRow...>>::type
    > {};

template <class L, class... Ls, class RRow>
struct composition_common_row<tmpl::vt::packer<L, Ls...>, tmpl::vt::packer<RRow>>
    : tmpl::vt::concat<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            row, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<std::common_type, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME common_row<L, RRow>::type>::type>::type
        >::type,
        SROOK_DEDUCED_TYPENAME composition_common_row<tmpl::vt::packer<Ls...>, tmpl::vt::packer<RRow>>::type
    > {};
    
template <class... RRow>
struct composition_common_row<tmpl::vt::packer<>, tmpl::vt::packer<RRow...>>
    : type_constant<tmpl::vt::packer<>> {};

} // namespace compo

template <bool>
struct tracer {
    template <class... Row, std::size_t... I>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR static SROOK_DEDUCED_TYPENAME
    tmpl::vt::foldr1<
        std::common_type, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::at<
            I, 
            SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, SROOK_DEDUCED_TYPENAME matrix_impl<Row...>::packed_type>::type>::type
        >::type...
    >::type
    exec(const matrix_impl<Row...>& m, index_sequence<I...>)
    {
#if !SROOK_CPP_FOLD_EXPRESSIONS
        return (m.template get<I, I>() + ...);
#else
        return tuple::foldr1(std::plus<>{}, std::make_tuple(m.template get<I, I>()...));
#endif
    }
};

template <>
struct tracer<false> {
    template <class... Row, std::size_t... I>
    SROOK_CONSTEXPR static SROOK_DEDUCED_TYPENAME
    tmpl::vt::foldr1<std::common_type, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<common_row, Row...>::type>::type>::type
    exec(const matrix_impl<Row...>&, index_sequence<I...>);
};


template <class... Row>
class matrix_impl {
    SROOK_STATIC_ASSERT((tmpl::vt::all<tmpl::vt::composition<is_row, decay>::template generate, Row...>::value), 
        "srook::math::detail::matrix_impl: Row types must be row<Ts...>");
public:
    typedef tmpl::vt::packer<Row...> packed_type;
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, packed_type>::type mat_type;
    typedef SROOK_DEDUCED_TYPENAME rotate_matrix_type<packed_type>::type transposed_type;
    typedef SROOK_DEDUCED_TYPENAME rotate_matrix_type<SROOK_DEDUCED_TYPENAME tmpl::vt::reverse<packed_type>::type>::type rotate_type;
    
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::size_t row_length = tmpl::vt::apply<tmpl::vt::size, packed_type>::value;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::size_t column_length = tmpl::vt::apply<
        tmpl::vt::size, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::head<packed_type>::type>::type
    >::value;
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR bool is_square_length = row_length == column_length;

    template <class T, SROOK_REQUIRES(is_scalar<SROOK_DEDUCED_TYPENAME decay<T>::type>::value)>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl(mx_fill, T&& val) SROOK_NOEXCEPT_TRUE
        : m_(tuple::replicate<row_length>(tuple::replicate<column_length>(srook::forward<T>(val)))) {}

    template <class... Ts,
    SROOK_REQUIRES(
        type_traits::detail::Land<
            tmpl::vt::all<tmpl::vt::composition<is_row, decay>::template generate, Ts...>,
            tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_same, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Ts...>::type, packed_type>::type>
        >::value
    )>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl(Ts&&... ts) 
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            row_elems_apply<tmpl::vt::all, tmpl::vt::composition<lrvalue_cond<is_nothrow_constructible, is_nothrow_move_constructible>::template generate, decay>::template generate, Ts>...
        >::value
    )
        : m_(srook::forward<Ts>(ts)...) {}

    template <class... Ts, 
    SROOK_REQUIRES(
        type_traits::detail::Land<
            tmpl::vt::all<tmpl::vt::composition<is_row, decay>::template generate, Ts...>,
            tmpl::vt::and_<SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<is_same, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Ts...>::type, packed_type>::type>
        >::value
    )>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl(const std::tuple<Ts...>& ts) 
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            row_elems_apply<tmpl::vt::all, tmpl::vt::composition<lrvalue_cond<is_nothrow_constructible, is_nothrow_move_constructible>::template generate, decay>::template generate, Ts>...
        >::value
    )
        : m_(ts) {}

    template <class... Vec,
    SROOK_REQUIRES(type_traits::detail::Land<is_vector<SROOK_DEDUCED_TYPENAME decay<Vec>::type>...>::value)>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl(Vec&&... vec) SROOK_NOEXCEPT_TRUE
        : matrix_impl(
            matrix_impl<SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<row, SROOK_DEDUCED_TYPENAME decay<Vec>::type::packed_type>::type...>(
                vec2row(srook::forward<Vec>(vec), SROOK_DEDUCED_TYPENAME make_index_sequence_type<decay<Vec>::type::size>::type{})...
            ).get_transposed()
        ) {}

    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl(const matrix_impl& other)
        : m_(other.m_) {}

    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl(matrix_impl&& other)
        : m_(srook::move(other.m_)) {}

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    template <class... Ts,
    SROOK_REQUIRES(
        type_traits::detail::Land<
            tmpl::vt::and_<
                SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<
                    is_same, 
                    SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Ts...>::type, 
                    SROOK_DEDUCED_TYPENAME tmpl::vt::erase_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::map<row_to_packer, packed_type>::type>::type
                >::type
            >,
            bool_constant<sizeof...(Ts) == (row_length * column_length)>
        >::value
    )>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl(Ts&&... ts)
    SROOK_NOEXCEPT(tmpl::vt::all<tmpl::vt::composition<lrvalue_cond<is_nothrow_constructible, is_nothrow_move_constructible>::template generate, decay>::template generate, Ts...>::value)
        : m_(make_mat(std::make_tuple(srook::forward<Ts>(ts)...))) {}
#endif

    template <class L, class Operator, class R>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl(const srook::math::linear_algebra::detail::matrix_expression<L, Operator, R>& exp)
    {
        matrix_impl_calculate1(*this, exp, SROOK_DEDUCED_TYPENAME srook::make_index_sequence_type<row_length>::type{});
    }

    template <class L, class Operator, class R>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl& 
    operator=(const srook::math::linear_algebra::detail::matrix_expression<L, Operator, R>& exp)
    {
        return matrix_impl_calculate1(*this, exp, SROOK_DEDUCED_TYPENAME srook::make_index_sequence_type<row_length>::type{});
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR matrix_impl&
    operator=(const matrix_impl& other)
    {
        return m_ = other.m_, *this;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_EXPLICIT
    operator mat_type() const
    {
        return to_tuple();
    }

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    template <std::size_t I, std::size_t J>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const SROOK_DEDUCED_TYPENAME 
    tmpl::vt::at<J, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, packed_type>::type>::type>::type& 
    get() const SROOK_NOEXCEPT_TRUE
    {
        return std::get<J>(std::get<I>(m_));
    }
#endif

    template <std::size_t I, std::size_t J>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
    tmpl::vt::at<J, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, packed_type>::type>::type>::type& 
    get() SROOK_NOEXCEPT_TRUE
    {
        return std::get<J>(std::get<I>(m_));
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, transposed_type>::type 
    get_transposed() const SROOK_NOEXCEPT_TRUE
    {
        return get_transposed_impl1(SROOK_DEDUCED_TYPENAME make_index_sequence_type<std::tuple_size<SROOK_DEDUCED_TYPENAME tmpl::vt::head<packed_type>::type>::value>::type());
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::size_t 
    row_size() const SROOK_NOEXCEPT_TRUE
    {
        return row_length;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::size_t 
    column_size() const SROOK_NOEXCEPT_TRUE
    {
        return column_length;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool
    is_square() const SROOK_NOEXCEPT_TRUE
    {
        return is_square_length;
    }

    template <class... ORow>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool
    is_compositable(const matrix_impl<ORow...>&) const SROOK_NOEXCEPT_TRUE
    {
        return column_length == matrix_impl<ORow...>::row_length;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR const mat_type&
    to_tuple() const SROOK_NOEXCEPT_TRUE 
    { 
        return m_; 
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool 
    is_identity() const
    {
        return row_length == column_length ? is_identity_impl1(SROOK_DEDUCED_TYPENAME make_index_sequence_type<row_length>::type{}) : false;
    }

    template <class... RRow>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR 
    SROOK_DEDUCED_TYPENAME enable_if<
        bool_constant<column_length == matrix_impl<RRow...>::row_length>::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME compo::composition_common_row<packed_type, SROOK_DEDUCED_TYPENAME matrix_impl<RRow...>::transposed_type>::type
        >::type
    >::type
    product(const matrix_impl<RRow...>& other) const
    {
        return *this * other;
    }

    template <class... RRow>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        bool_constant<column_length == matrix_impl<RRow...>::row_length>::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME compo::composition_common_row<packed_type, SROOK_DEDUCED_TYPENAME matrix_impl<RRow...>::transposed_type>::type
        >::type
    >::type
    product(srook::execution::sequenced_policy, const matrix_impl<RRow...>& other) const
    {
        return *this * other;
    }

    template <class... RRow>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        bool_constant<column_length == matrix_impl<RRow...>::row_length>::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME compo::composition_common_row<packed_type, SROOK_DEDUCED_TYPENAME matrix_impl<RRow...>::transposed_type>::type
        >::type
    >::type
    product(srook::execution::parallel_unsequenced_policy p, const matrix_impl<RRow...>& r) const
    {
        const SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME matrix_impl<RRow...>::transposed_type>::type::mat_type transposed = r.get_transposed().to_tuple(); 
        typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, SROOK_DEDUCED_TYPENAME compo::composition_common_row<packed_type, SROOK_DEDUCED_TYPENAME matrix_impl<RRow...>::transposed_type>::type
        >::type result_type;

        return 
            result_type(
                tuple::map(
                    p, 
                    [&transposed](auto&& lrow) SROOK_CXX17_CONSTEXPR {
                        return 
                            tuple::map([&lrow](auto&& rrow) SROOK_CXX17_CONSTEXPR { 
                                return tuple::foldr1(std::plus<>{}, tuple::zip_with(std::multiplies<>{}, lrow, rrow)); 
                            }, transposed);
                    }, m_
                )
            );
    }
    
    template <class... RRow>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        bool_constant<column_length == matrix_impl<RRow...>::row_length>::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME compo::composition_common_row<packed_type, SROOK_DEDUCED_TYPENAME matrix_impl<RRow...>::transposed_type>::type
        >::type
    >::type
    product(srook::execution::parallel_policy, const matrix_impl<RRow...>& r) const
    {
        return product(srook::execution::par, r);
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR auto eigenvals() const; // not implemented yet
#if 0
    {
        SROOK_STATIC_ASSERT(is_square(), "matrix_impl::eigenvals(): The matrix must be square.");
    }
#endif

    SROOK_FORCE_INLINE SROOK_CONSTEXPR auto eigenvectors() const; // not implemented yet
#if 0
    {
        SROOK_STATIC_ASSERT(is_square(), "matrix_impl::eigenvectors(): The matrix must be square.");
    }
#endif

    SROOK_FORCE_INLINE SROOK_CONSTEXPR auto is_regular() const; // not implemented yet
    SROOK_FORCE_INLINE SROOK_CONSTEXPR auto pow() const; // not implemented yet

    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
    tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
            row_length,
            SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                row, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                    column_length, 
                    SROOK_DEDUCED_TYPENAME gaussian_elimination_inv<column_length>::result_val_type
                >::type
            >::type
        >::type
    >::type
    inverse() const
    {
        SROOK_STATIC_ASSERT(determinant() != 0, "The matrix must be regular.");
        return
            gaussian_elimination_inv<column_length>()(
                make_matrix_impl(
                    tuple::zip_with([](const auto& l, const auto& r) SROOK_NOEXCEPT_TRUE {
                        return std::tuple_cat(l, r); 
                    }, to_tuple(), make_identity_impl<column_length>().to_tuple())
                )
            );
    }

protected:
    /*template <std::size_t... I>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
    conditional<
        column_length == row_length,
        SROOK_DEDUCED_TYPENAME tmpl::vt::foldr1<
            std::common_type, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::at<I, packed_type>::type>::type>::type...
        >::type,
        int
    >::type
    trace_impl(index_sequence<I...>) const
    {
#if !SROOK_CPP_FOLD_EXPRESSIONS
        return (get<I, I>() + ...);
#else
        return tuple::foldr1(std::plus<>{}, std::make_tuple(get<I, I>()...));
#endif
    }*/

public:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR auto
    trace() const
    -> SROOK_DECLTYPE(tracer<column_length == row_length>::exec(declval<matrix_impl>(), SROOK_DEDUCED_TYPENAME make_index_sequence_type<row_length>::type{}))
    {
        SROOK_STATIC_ASSERT(is_square_length, "The matrix must be square.");
        return tracer<column_length == row_length>::exec(*this, SROOK_DEDUCED_TYPENAME make_index_sequence_type<row_length>::type{});
        //trace_impl(SROOK_DEDUCED_TYPENAME make_index_sequence_type<row_length>::type{});
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR auto
    determinant() const
    -> SROOK_DECLTYPE(cofactor::expansion(declval<matrix_impl>()))
    {
        SROOK_STATIC_ASSERT(is_square_length, "The matrix muse be square.");
        return cofactor::expansion(*this);
    }
    
    template <class Algo, class... Elems>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
    enable_if<
        type_traits::detail::Land<bool_constant<sizeof...(Elems) == column_length>, has_equations_resolver<SROOK_DEDUCED_TYPENAME decay<Algo>::type>>::value, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<vector, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<column_length, SROOK_DEDUCED_TYPENAME Algo::result_val_type>::type>::type
    >::type
    compute_equations(const srook::math::linear_algebra::vector<Elems...>& vec, Algo&& algo = gaussian_elimination_eq()) const
    {
        return algo(make_matrix_impl(tuple::zip_with([](const auto& l, const auto& r) SROOK_NOEXCEPT_TRUE { return std::tuple_cat(l, std::make_tuple(r)); }, to_tuple(), vec.to_tuple())));
    }

    template <class... RRow>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            bool_constant<row_length == matrix_impl<RRow...>::row_length>, 
            bool_constant<column_length == matrix_impl<RRow...>::column_length>
        >::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<common_row, packed_type, RRow...>::type>::type
    >::type
    operator+=(const matrix_impl<RRow...>& r) SROOK_NOEXCEPT_TRUE
    {
        return *this = srook::math::linear_algebra::detail::matrix_expression<matrix_impl, std::plus<>, matrix_impl<RRow...>>(*this, r);
    }

    template <class Exp>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    /*SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            bool_constant<row_length == Exp::row_length>, 
            bool_constant<column_length == Exp::column_length>,
            has_matrix_exp_tag<Exp>
        >::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<common_row, packed_type, RRow...>::type>::type
        srook::math::linear_algebra::detail::matrix_expression<matrix_impl, std::plus<>, Exp>
    >::type*/ auto
    operator+=(const Exp& exp) SROOK_NOEXCEPT_TRUE
    {
        return *this = srook::math::linear_algebra::detail::matrix_expression<matrix_impl, std::plus<>, Exp>(*this, exp);
    }
    
    template <class... RRow>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            bool_constant<row_length == matrix_impl<RRow...>::row_length>, 
            bool_constant<column_length == matrix_impl<RRow...>::column_length>
        >::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<common_row, packed_type, RRow...>::type>::type
    >::type
    operator-=(const matrix_impl<RRow...>& r) SROOK_NOEXCEPT_TRUE
    {
        return *this = srook::math::linear_algebra::detail::matrix_expression<matrix_impl, std::minus<>, matrix_impl<RRow...>>(*this, r);
    }

    template <class Exp>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    /*SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            bool_constant<row_length == Exp::row_length>, 
            bool_constant<column_length == Exp::column_length>,
            has_matrix_exp_tag<Exp>
        >::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<common_row, packed_type, RRow...>::type>::type
        srook::math::linear_algebra::detail::matrix_expression<matrix_impl, std::plus<>, Exp>
    >::type*/ auto
    operator-=(const Exp& exp) SROOK_NOEXCEPT_TRUE
    {
        return *this = srook::math::linear_algebra::detail::matrix_expression<matrix_impl, std::minus<>, Exp>(*this, exp);
    }

    template <class T>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        tmpl::vt::and_<
            SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<
                tmpl::vt::bind<is_convertible, SROOK_DEDUCED_TYPENAME decay<T>::type>, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::erase_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::map<row_to_packer, packed_type>::type>::type
            >::type
        >::value,
        srook::math::linear_algebra::detail::matrix_expression<
            SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                matrix_impl, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                    row_length, 
                    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                        std::tuple, 
                        SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<column_length, SROOK_DEDUCED_TYPENAME decay<T>::type>::type
                    >::type
                >::type
            >::type,
            std::multiplies<>,
            matrix_impl
        >
    >::type
    operator*=(T&& val) SROOK_NOEXCEPT_TRUE
    {
        return *this = *this * srook::forward<T>(val);
    }

    template <class T>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        tmpl::vt::and_<
            SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<
                tmpl::vt::bind<is_convertible, SROOK_DEDUCED_TYPENAME decay<T>::type>, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::erase_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::map<row_to_packer, packed_type>::type>::type
            >::type
        >::value,
        srook::math::linear_algebra::detail::matrix_expression<
            matrix_impl,
            std::divides<>,
            SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                matrix_impl, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                    row_length, 
                    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
                        std::tuple, 
                        SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<column_length, SROOK_DEDUCED_TYPENAME decay<T>::type>::type
                    >::type
                >::type
            >::type
        >       
    >::type
    operator/=(T&& val)
    {
        return *this = *this / srook::forward<T>(val);
    }

    template <class... RRow>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        bool_constant<column_length == matrix_impl<RRow...>::row_length>::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME compo::composition_common_row<packed_type, SROOK_DEDUCED_TYPENAME matrix_impl<RRow...>::transposed_type>::type
        >::type
    >::type
    operator*=(const matrix_impl<RRow...>& r)
    {
        return *this = *this * r;
    }

    template <class... Elems>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR
    SROOK_DEDUCED_TYPENAME enable_if<
        bool_constant<column_length == vector<Elems...>::size>::value,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl,
            SROOK_DEDUCED_TYPENAME compo::composition_common_row<packed_type, tmpl::vt::packer<row<Elems...>>>::type
        >::type
    >::type
    operator*(const vector<Elems...>& vec)
    {
        return *this = *this * vec;
    }
protected:
#if !SROOK_CPP_FOLD_EXPRESSIONS
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool is_identity_impl2(bool b, index_sequence<>) const SROOK_NOEXCEPT_TRUE
    {
        return b;
    }

    template <std::size_t I, std::size_t... Is>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool is_identity_impl2(bool b, index_sequence<I, Is...>) const SROOK_NOEXCEPT_TRUE
    {
        return is_identity_impl2(b && (get<I, I>() == 1), index_sequence<Is...>{});
    }
#endif

    template <std::size_t... I>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool is_identity_impl1(index_sequence<I...>) const SROOK_NOEXCEPT_TRUE
    {
#if SROOK_CPP_FOLD_EXPRESSIONS
        return ([](auto&& val) SROOK_CXX17_CONSTEXPR { return val == 1; }(get<I, I>()) && ...);
#else
        return is_identity_impl2(true, index_sequence<I...>{});
#endif
    }

    template <class... Ts, std::size_t... Is>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR row<Ts...>
    vec2row(const srook::math::linear_algebra::vector<Ts...>& vec, index_sequence<Is...>) SROOK_NOEXCEPT_TRUE
    {
        return make_row(vec.template get<Is>()...);
    }

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    template <class T, class... Ts>
    SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR auto
    make_mat(const std::tuple<T, Ts...>& t) const SROOK_NOEXCEPT_TRUE
    {
        const auto st = tuple::split<column_length - 1>(t);
        return std::tuple_cat(std::make_tuple(st.first), make_mat(st.second)); 
    }
    
    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::tuple<> make_mat(const std::tuple<>&) const SROOK_NOEXCEPT_TRUE { return std::make_tuple(); }
#endif

    template <std::size_t I1, std::size_t... Is, class... Ts>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, transposed_type>::type
    get_transposed_impl1(index_sequence<I1, Is...>, Ts&&... ts) const SROOK_NOEXCEPT_TRUE
    {
        return get_transposed_impl1(index_sequence<Is...>{}, srook::forward<Ts>(ts)..., get_transposed_impl2<I1>(SROOK_DEDUCED_TYPENAME make_index_sequence_type<std::tuple_size<mat_type>::value>::type()));
    }

    template <class... Ts>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, transposed_type>::type
    get_transposed_impl1(index_sequence<>, Ts&&... ts) const SROOK_NOEXCEPT_TRUE
    {
        return SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Ts...>::type>::type(srook::forward<Ts>(ts)...);
    }

    template <std::size_t I1, std::size_t... RIs>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR std::tuple<SROOK_DEDUCED_TYPENAME std::tuple_element<I1, SROOK_DEDUCED_TYPENAME std::tuple_element<RIs, mat_type>::type>::type...>
    get_transposed_impl2(index_sequence<RIs...>) const SROOK_NOEXCEPT_TRUE
    {
        return std::make_tuple(std::get<I1>(std::get<RIs>(m_))...); 
    }

    friend SROOK_FORCE_INLINE std::ostream& 
    operator<<(std::ostream& os, const matrix_impl& this_)
    {
        srook::for_each(this_.m_, [&os](const auto& x){ srook::for_each(x, [&os](const auto& y) { os << y << ' '; }); os << '\n'; });
        return os;
    }
protected:
    mat_type m_;
};

template <>
class matrix_impl<> {};

template <class... LRow, class... RRow>
SROOK_FORCE_INLINE SROOK_CONSTEXPR bool
operator==(const matrix_impl<LRow...>& l, const matrix_impl<RRow...>& r) SROOK_NOEXCEPT_TRUE
{
    return 
        matrix_impl<LRow...>::row_length == matrix_impl<RRow...>::row_length && matrix_impl<LRow...>::column_length == matrix_impl<RRow...>::column_length ?
            tuple::foldr1(
                std::logical_and<>{}, 
                tuple::zip_with([](const auto& lrow, const auto& rrow) SROOK_NOEXCEPT_TRUE { 
                    return tuple::foldr1(std::logical_and<>{}, tuple::zip_with(m_equality{}, lrow, rrow)); 
                }, l.to_tuple(), r.to_tuple())
            ) : false;
}

template <class... LRow, class... RRow>
SROOK_FORCE_INLINE SROOK_CONSTEXPR bool
operator!=(const matrix_impl<LRow...>& l, const matrix_impl<RRow...>& r) SROOK_NOEXCEPT_TRUE
{
    return !(l == r);
}

// matrix additional
template <class... LRow, class... RRow>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<matrix_impl<LRow...>::row_length == matrix_impl<RRow...>::row_length>, 
        bool_constant<matrix_impl<LRow...>::column_length == matrix_impl<RRow...>::column_length>
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<matrix_impl<LRow...>, std::plus<>, matrix_impl<RRow...>>
>::type
operator+(const matrix_impl<LRow...>& l, const matrix_impl<RRow...>& r) SROOK_NOEXCEPT_TRUE
{
    return srook::math::linear_algebra::detail::matrix_expression<matrix_impl<LRow...>, std::plus<>, matrix_impl<RRow...>>(l, r);
}

template <class... LRow, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<matrix_impl<LRow...>::row_length == Exp::row_length>, 
        bool_constant<matrix_impl<LRow...>::column_length == Exp::column_length>,
        has_matrix_exp_tag<Exp>
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<matrix_impl<LRow...>, std::plus<>, Exp>
>::type
operator+(const matrix_impl<LRow...>& l, const Exp& exp) SROOK_NOEXCEPT_TRUE
{
    return srook::math::linear_algebra::detail::matrix_expression<matrix_impl<LRow...>, std::plus<>, Exp>(l, exp);
}

template <class... RRow, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<matrix_impl<RRow...>::row_length == Exp::row_length>, 
        bool_constant<matrix_impl<RRow...>::column_length == Exp::column_length>,
        has_matrix_exp_tag<Exp>
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<matrix_impl<RRow...>, std::plus<>, Exp>
>::type
operator+(const Exp& exp, const matrix_impl<RRow...>& r) SROOK_NOEXCEPT_TRUE
{
    return r + exp;
}

// matrix subtraction
template <class... LRow, class... RRow>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<matrix_impl<LRow...>::row_length == matrix_impl<RRow...>::row_length>, 
        bool_constant<matrix_impl<LRow...>::column_length == matrix_impl<RRow...>::column_length>
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<matrix_impl<LRow...>, std::minus<>, matrix_impl<RRow...>>
>::type
operator-(const matrix_impl<LRow...>& l, const matrix_impl<RRow...>& r) SROOK_NOEXCEPT_TRUE
{
    return srook::math::linear_algebra::detail::matrix_expression<matrix_impl<LRow...>, std::minus<>, matrix_impl<RRow...>>(l, r);
}

template <class... LRow, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<matrix_impl<LRow...>::row_length == Exp::row_length>, 
        bool_constant<matrix_impl<LRow...>::column_length == Exp::column_length>,
        detail::has_matrix_exp_tag<Exp>
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<matrix_impl<LRow...>, std::minus<>, Exp>
>::type
operator-(const matrix_impl<LRow...>& l, const Exp& exp) SROOK_NOEXCEPT_TRUE
{
    return srook::math::linear_algebra::detail::matrix_expression<matrix_impl<LRow...>, std::minus<>, Exp>(l, exp);
}

template <class... RRow, class Exp>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        bool_constant<matrix_impl<RRow...>::row_length == Exp::row_length>, 
        bool_constant<matrix_impl<RRow...>::column_length == Exp::column_length>,
        detail::has_matrix_exp_tag<Exp>
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<Exp, std::minus<>, matrix_impl<RRow...>>
>::type
operator-(const Exp& exp, const matrix_impl<RRow...>& r) SROOK_NOEXCEPT_TRUE
{
    return srook::math::linear_algebra::detail::matrix_expression<Exp, std::minus<>, matrix_impl<RRow...>>(exp, r);
}

// Scalar multiplies
template <class T, class... Row>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        tmpl::vt::and_<
            SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<
                tmpl::vt::bind<is_convertible, SROOK_DEDUCED_TYPENAME decay<T>::type>, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::erase_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::map<row_to_packer, Row...>::type>::type
            >::type
        >,
        is_scalar<SROOK_DEDUCED_TYPENAME decay<T>::type>
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                matrix_impl<Row...>::row_length, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<matrix_impl<Row...>::column_length, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
            >::type
        >::type,
        std::multiplies<>,
        matrix_impl<Row...>
    >
>::type
operator*(T&& val, const matrix_impl<Row...>& m) SROOK_NOEXCEPT_TRUE
{
    typedef matrix_impl<Row...> mtype;
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<mtype::column_length, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type row_type;
    
    return srook::math::linear_algebra::detail::matrix_expression<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<mtype::row_length, row_type>::type>::type,
        std::multiplies<>,
        mtype
    >(tuple::replicate<mtype::row_length>(tuple::replicate<mtype::column_length>(srook::forward<T>(val))), m);
}

template <class T, class... Row>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    tmpl::vt::and_<
        SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<
            tmpl::vt::bind<is_convertible, SROOK_DEDUCED_TYPENAME decay<T>::type>, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::erase_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::map<row_to_packer, Row...>::type>::type
        >::type
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                matrix_impl<Row...>::row_length, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<matrix_impl<Row...>::column_length, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
            >::type
        >::type,
        std::multiplies<>,
        matrix_impl<Row...>
    >       
>::type
operator*(const matrix_impl<Row...>& m, T&& val) SROOK_NOEXCEPT_TRUE
{
    return srook::forward<T>(val) * m;
}

// Product/Composition
template <class... LRow, class... RRow>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    bool_constant<matrix_impl<LRow...>::column_length == matrix_impl<RRow...>::row_length>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl, 
        SROOK_DEDUCED_TYPENAME compo::composition_common_row<tmpl::vt::packer<LRow...>, SROOK_DEDUCED_TYPENAME matrix_impl<RRow...>::transposed_type>::type
    >::type
>::type
operator*(const matrix_impl<LRow...>& l, const matrix_impl<RRow...>& r)
{
    const SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME matrix_impl<RRow...>::transposed_type>::type::mat_type transposed = r.get_transposed().to_tuple(); 
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl, SROOK_DEDUCED_TYPENAME compo::composition_common_row<tmpl::vt::packer<LRow...>, SROOK_DEDUCED_TYPENAME matrix_impl<RRow...>::transposed_type>::type
    >::type result_type;

    return 
        result_type(
            tuple::map(
                [&transposed](auto&& lrow) SROOK_CXX17_CONSTEXPR {
                    return 
                        tuple::map([&lrow](auto&& rrow) SROOK_CXX17_CONSTEXPR { 
                            return tuple::foldr1(std::plus<>{}, tuple::zip_with(std::multiplies<>{}, lrow, rrow)); 
                        }, transposed);
                }, l.to_tuple()
            )
        );
}

template <class... LRow, class... Elems>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    bool_constant<matrix_impl<LRow...>::column_length == vector<Elems...>::size>::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME compo::composition_common_row<tmpl::vt::packer<LRow...>, tmpl::vt::packer<row<Elems...>>>::type
    >::type
>::type
operator*(const matrix_impl<LRow...>& l, const vector<Elems...>& vec)
{
    return l * make_matrix_impl(vec);
}

// division
template <class T, class... Row>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
SROOK_DEDUCED_TYPENAME enable_if<
    tmpl::vt::and_<
        SROOK_DEDUCED_TYPENAME tmpl::vt::mapD<
            tmpl::vt::bind<is_convertible, SROOK_DEDUCED_TYPENAME decay<T>::type>, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::erase_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::map<row_to_packer, Row...>::type>::type
        >::type
    >::value,
    srook::math::linear_algebra::detail::matrix_expression<
        matrix_impl<Row...>,
        std::divides<>,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            matrix_impl, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                matrix_impl<Row...>::row_length, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<matrix_impl<Row...>::column_length, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type
            >::type
        >::type
    >       
>::type
operator/(const matrix_impl<Row...>& m, T&& val)
{
    typedef matrix_impl<Row...> mtype;
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<mtype::column_length, SROOK_DEDUCED_TYPENAME decay<T>::type>::type>::type row_type;
    
    return srook::math::linear_algebra::detail::matrix_expression<
        mtype,
        std::divides<>,
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<mtype::row_length, row_type>::type>::type
    >(m, tuple::replicate<mtype::row_length>(tuple::replicate<mtype::column_length>(srook::forward<T>(val))));
}

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
