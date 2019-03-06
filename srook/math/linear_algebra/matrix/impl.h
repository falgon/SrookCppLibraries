// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_IMPL_H
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_IMPL_H
#include <srook/config.hpp>
#include <srook/type_traits/detail/has_type_gen.hpp>
#include <srook/type_traits/is_scalar.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/map.hpp>
#include <srook/tmpl/vt/zip_with.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class...>
class matrix_impl;

SROOK_TT_DEF_HAS_TYPE_IMPL(matrix_exp_tag);
SROOK_TT_DEF_HAS_TYPE(matrix_exp_tag);

template <class>
struct is_matrix : SROOK_FALSE_TYPE {};

template <class... Row>
struct is_matrix<matrix_impl<Row...>> : SROOK_TRUE_TYPE {};

template <class... Ts>
using row = std::tuple<Ts...>;

template <class>
struct is_row : SROOK_FALSE_TYPE {};

template <class... Ts>
struct is_row<row<Ts...>> : SROOK_TRUE_TYPE {};

template <class... Ts>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME 
tmpl::vt::transfer<row, SROOK_DEDUCED_TYPENAME tmpl::vt::map<decay, Ts...>::type>::type
make_row(Ts&&... ts)
{
    return std::make_tuple(srook::forward<Ts>(ts)...);
}

template <template <template <class...> class, class...> class, template <class...> class, class>
struct row_elems_apply;

template <template <template <class...> class, class...> class HighOrderF, template <class...> class F, class... Ts>
struct row_elems_apply<HighOrderF, F, row<Ts...>>
    : HighOrderF<F, Ts...> {};

template <class>
struct row_to_packer;

template <class... Ts>
struct row_to_packer<row<Ts...>> 
    : tmpl::vt::transfer<tmpl::vt::packer, Ts...> {};


template <class, class>
struct common_row;

template <class... L, class... R>
struct common_row<row<L...>, row<R...>>
    : tmpl::vt::transfer<row, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<std::common_type, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type> {};

template <class, class>
struct common_matrix;

template <class... L, class... R>
struct common_matrix<matrix_impl<L...>, matrix_impl<R...>>
    : tmpl::vt::transfer<matrix_impl, SROOK_DEDUCED_TYPENAME tmpl::vt::zip_with<common_row, tmpl::vt::packer<L...>, tmpl::vt::packer<R...>>::type> {};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
