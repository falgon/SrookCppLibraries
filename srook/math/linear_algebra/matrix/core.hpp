// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_MATRIX_CORE_HPP
#define INCLUDED_SROOK_MATH_MATRIX_CORE_HPP
#include <srook/math/linear_algebra/matrix/impl.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)

template <class...>
class matrix;

namespace detail {

template <class... Row>
struct is_matrix<matrix<Row...>> : SROOK_TRUE_TYPE {};

} // namespace detail

using detail::row;
using detail::gaussian_elimination_eq;

template <class... Row>
SROOK_FORCE_INLINE SROOK_CONSTEXPR auto
make_matrix(Row&&... row)
-> SROOK_DECLTYPE(detail::make_matrix_impl(srook::forward<Row>(row)...))
{
    return detail::make_matrix_impl(srook::forward<Row>(row)...);
}

template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR auto
make_diag(Ts&&... ts)
-> SROOK_DECLTYPE(detail::make_diag_impl(srook::forward<Ts>(ts)...))
{
    return detail::make_diag_impl(srook::forward<Ts>(ts)...);
}

template <std::size_t N, class T
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
= int
#endif
>
SROOK_FORCE_INLINE SROOK_CONSTEXPR auto
make_identity()
-> SROOK_DECLTYPE(detail::make_identity_impl<N, T>())
{
    return detail::make_identity_impl<N, T>();
}

template <class... Row>
class matrix : public detail::matrix_impl<Row...> {
    typedef detail::matrix_impl<Row...> base_type;
public:
    using base_type::base_type;
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
