// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_UTILS_HPP
#define INCLUDED_SROOK_MATH_LINEAR_ALGEBRA_MATRIX_UTILS_HPP

#include <srook/config.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/replicate.hpp>
#include <srook/tmpl/vt/size.hpp>
#include <srook/tmpl/vt/apply.hpp>
#include <srook/tmpl/vt/head.hpp>
#include <srook/tmpl/vt/all.hpp>
#include <srook/tmpl/vt/composition.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/type_traits/is_floating_point.hpp>
#include <srook/math/linear_algebra/matrix/helperfn.hpp>
#include <srook/math/linear_algebra/matrix/impl.h>
#include <srook/math/linear_algebra/matrix/linear_equations_algo/elementary_transformer.hpp>
#include <srook/math/constants/algorithm/abs.hpp>
#include <srook/cstdfloat.hpp>

SROOK_NESTED_NAMESPACE(srook, math, linear_algebra) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <typename CastType, class... Row>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
    elementary_transformer,
    SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
        sizeof...(Row),
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            row,
            SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                tmpl::vt::apply<tmpl::vt::size, SROOK_DEDUCED_TYPENAME row_to_packer<SROOK_DEDUCED_TYPENAME tmpl::vt::head<Row...>::type>::type>::value,
                CastType
            >::type
        >::type
    >::type
>::type
to_common_et(const std::tuple<Row...>& tp)
{
    return 
        make_elementary_transformer(
            make_matrix_impl(
                tuple::map([](const auto& row) SROOK_NOEXCEPT_TRUE { 
                    return tuple::map([](const auto& elem) SROOK_NOEXCEPT_TRUE { return static_cast<CastType>(elem); }, row); 
                }, tp))
        );
}

struct m_equality {
    template <class L, class R>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
    enable_if<
        type_traits::detail::Land<
            tmpl::vt::all<tmpl::vt::composition<is_arithmetic, decay>::template generate, L, R>,
            type_traits::detail::Lnot<tmpl::vt::all<tmpl::vt::composition<is_integral, decay>::template generate, L, R>>,
            type_traits::detail::Lnot<tmpl::vt::all<tmpl::vt::composition<is_floating_point, decay>::template generate, L, R>>
        >::value,
        bool
    >::type
    operator()(L&& l, R&& r) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME std::common_type<SROOK_DEDUCED_TYPENAME decay<L>::type, SROOK_DEDUCED_TYPENAME decay<R>::type>::type cm_type;
        return operator()(cm_type(l), cm_type(r));
    }

    template <class L, class R>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
    enable_if<tmpl::vt::all<tmpl::vt::composition<is_integral, decay>::template generate, L, R>::value, bool>::type
    operator()(L&& l, R&& r) const SROOK_NOEXCEPT_TRUE
    {
        return srook::forward<L>(l) == srook::forward<R>(r);
    }

    template <class L, class R>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME
    enable_if<tmpl::vt::all<tmpl::vt::composition<is_floating_point, decay>::template generate, L, R>::value, bool>::type
    operator()(L&& l, R&& r) const SROOK_NOEXCEPT_TRUE
    {
        typedef SROOK_DEDUCED_TYPENAME std::common_type<SROOK_DEDUCED_TYPENAME decay<L>::type, SROOK_DEDUCED_TYPENAME decay<R>::type>::type cm_type;
        return srook::math::abs(cm_type(srook::forward<L>(l)) - cm_type(srook::forward<R>(r))) < numeric_limits<cm_type>::epsilon();
    }
};

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(linear_algebra, math, srook)

#endif
