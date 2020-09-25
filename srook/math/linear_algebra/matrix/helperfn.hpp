// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_HELPERFN_HPP
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_HELPERFN_HPP

#include <srook/config.hpp>
#include <srook/math/linear_algebra/vector/impl.h>
#include <srook/math/linear_algebra/matrix/impl.h>
#include <srook/type_traits/is_scalar.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/bind.hpp>
#include <srook/tmpl/vt/and.hpp>
#include <srook/tmpl/vt/replicate.hpp>
#include <srook/tmpl/vt/composition.hpp>
#include <srook/utility/forward.hpp>
#include <srook/tuple/algorithm/replicate.hpp>
#include <srook/tuple/algorithm/apply.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<type_traits::detail::Land<is_scalar<SROOK_DEDUCED_TYPENAME decay<Ts>::type>...>::value, matrix_impl<row<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>>::type
make_matrix_impl(Ts&&... ts) SROOK_NOEXCEPT_TRUE
{
    return matrix_impl<row<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>(srook::forward<Ts>(ts)...);
}

template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<
    tmpl::vt::and_<
        SROOK_DEDUCED_TYPENAME tmpl::vt::map<
            type_traits::detail::Lnot,
            SROOK_DEDUCED_TYPENAME row_elems_apply<tmpl::vt::map, tmpl::vt::composition<is_row, decay>::template generate, Ts...>::type
        >::type
    >::value,
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Ts...>::type>::type
>::type
make_matrix_impl(Ts&&... ts) SROOK_NOEXCEPT_TRUE
{
    return SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, /*T1, T2,*/ Ts...>::type>::type(srook::forward<Ts>(ts)...);
}

template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
enable_if<
    type_traits::detail::Land<is_vector<SROOK_DEDUCED_TYPENAME decay<Ts>::type>...>::value, 
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME matrix_impl<SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<row, SROOK_DEDUCED_TYPENAME decay<Ts>::type::packed_type>::type...>::transposed_type
    >::type
>::type
make_matrix_impl(Ts&&... ts) SROOK_NOEXCEPT_TRUE
{
    return SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl, 
        SROOK_DEDUCED_TYPENAME matrix_impl<SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<row, SROOK_DEDUCED_TYPENAME decay<Ts>::type::packed_type>::type...>::transposed_type
    >::type(srook::forward<Ts>(ts)...);
}

template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
tmpl::vt::transfer<matrix_impl, Ts...>::type
make_matrix_impl(const std::tuple<Ts...>& tp) SROOK_NOEXCEPT_TRUE
{
    return SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        matrix_impl,
        Ts...
    >::type(tp);
}

template <std::size_t, class, class, class...>
struct diag_type;

template <std::size_t Max, class Common>
struct diag_type<Max, Common, index_sequence<>>
    : type_constant<tmpl::vt::packer<>> {};

template <std::size_t Max, class Common, std::size_t I, std::size_t... Is, class T, class... Ts>
struct diag_type<Max, Common, index_sequence<I, Is...>, T, Ts...>
    : tmpl::vt::concat<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            row, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                SROOK_DEDUCED_TYPENAME tmpl::vt::concat<SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<I, Common>::type, T>::type,
                SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<Max - (I + 1), Common>::type
            >::type
        >::type,
        SROOK_DEDUCED_TYPENAME diag_type<Max, Common, index_sequence<Is...>, Ts...>::type
    > {};

template <std::size_t Max, class... Bs>
struct make_diagonal_impl {
    template <class... Tp, class CommonVal>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR std::tuple<Tp...>
    exec(const std::tuple<Tp...>& tp, index_sequence<>, CommonVal&&) SROOK_NOEXCEPT_TRUE
    {
        return tp;
    }

    template <class... Tp, std::size_t I, std::size_t... Is, class CommonVal, class T, class... Ts>
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
    tmpl::vt::transfer<
        matrix_impl,
        SROOK_DEDUCED_TYPENAME diag_type<
            Max,
            SROOK_DEDUCED_TYPENAME decay<CommonVal>::type,
            SROOK_DEDUCED_TYPENAME make_index_sequence_type<Max>::type,
            SROOK_DEDUCED_TYPENAME decay<Bs>::type...
        >::type
    >::type
    exec(const std::tuple<Tp...>& tp, index_sequence<I, Is...>, CommonVal&& val, T&& t, Ts&&... ts)
    {
        return
            make_diagonal_impl<Max, Bs...>::exec(
                std::tuple_cat(tp, std::make_tuple(std::tuple_cat(std::tuple_cat(std::tuple_cat(tuple::replicate<I>(val), std::make_tuple(srook::forward<T>(t)), tuple::replicate<Max - (I + 1)>(val)))))),
                index_sequence<Is...>{},
                val,
                srook::forward<Ts>(ts)...
            );
    }
};

// make diag
template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
    matrix_impl, 
    SROOK_DEDUCED_TYPENAME diag_type<
        sizeof...(Ts),
        SROOK_DEDUCED_TYPENAME std::common_type<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>::type,
        SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(Ts)>::type, 
        SROOK_DEDUCED_TYPENAME decay<Ts>::type...
    >::type
>::type
make_diag_impl(Ts&&... ts)
{
    typedef SROOK_DEDUCED_TYPENAME std::common_type<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>::type cm_type;
    return make_diagonal_impl<sizeof...(Ts), SROOK_DEDUCED_TYPENAME decay<Ts>::type...>::exec(std::make_tuple(), SROOK_DEDUCED_TYPENAME make_index_sequence_type<sizeof...(Ts)>::type{}, cm_type(0), srook::forward<Ts>(ts)...);
}

// make identity
template <std::size_t N, class T 
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
= int
#endif
>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
tmpl::vt::transfer<
    matrix_impl, 
    SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<N, SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<row, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<N, T>::type>::type>::type
>::type
make_identity_impl()
{
    return 
        tuple::apply([](auto&&... xs) SROOK_CXX17_CONSTEXPR SROOK_NOEXCEPT(make_diag_impl(declval<SROOK_DECLTYPE(xs)>...)) { 
            return make_diag_impl(srook::forward<SROOK_DECLTYPE(xs)>(xs)...); 
        }, tuple::replicate<N>(T(1)));
}

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
