// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_NUMERIC_ALGORITHM_CORRELATION_COFFICIENT_HPP
#define INCLUDED_SROOK_NUMERIC_ALGORITHM_CORRELATION_COFFICIENT_HPP

#include <srook/numeric/algorithm/detail/config.hpp>
#include <srook/iterator/iterator_traits.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/tmpl/vt/proxy_by.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/apply.hpp>
#include <srook/tmpl/vt/head.hpp>
#include <srook/tmpl/vt/composition.hpp>
#include <srook/tmpl/vt/last.hpp>
#include <srook/tmpl/vt/concat.hpp>
#include <srook/optional.hpp>
#include <srook/math/constants/algorithm/sqrt.hpp>
#include <srook/math/constants/algorithm/pow.hpp>

SROOK_NESTED_NAMESPACE(srook, numeric, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
struct pow_type 
    : type_constant<SROOK_DECLTYPE(math::pow(declval<T>(), int()))> {};

} // namespace detail

template <SROOK_ARITHMETIC_ITER Iter1, SROOK_ARITHMETIC_ITER Iter2, 
SROOK_REQUIRES(type_traits::detail::Land<SROOK_ARITHMETIC_ITER_REQUIRES(Iter1), SROOK_ARITHMETIC_ITER_REQUIRES(Iter2)>::value)>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR SROOK_DEDUCED_TYPENAME 
srook::optional<
    SROOK_DEDUCED_TYPENAME tmpl::vt::apply<
        std::common_type, 
        SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
            SROOK_DEDUCED_TYPENAME tmpl::vt::map<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, Iter1, Iter2>::type,
            SROOK_DEDUCED_TYPENAME tmpl::vt::map<tmpl::vt::composition<detail::pow_type, tmpl::vt::proxy_by_value_type<iterator_traits>::template generate>::template generate, Iter1, Iter2>::type
        >::type
    >::type
>
correlation_coefficient(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::map<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, Iter1, Iter2>::type val_traits_types;
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::head<val_traits_types>::type first_val_t;
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::last<val_traits_types>::type second_val_t;
    typedef SROOK_DEDUCED_TYPENAME iterator_traits<Iter1>::difference_type first_diff_t;
    typedef SROOK_DEDUCED_TYPENAME std::common_type<first_val_t, second_val_t>::type cm_type;
    typedef SROOK_DEDUCED_TYPENAME 
        tmpl::vt::apply<
            std::common_type,
            SROOK_DEDUCED_TYPENAME tmpl::vt::concat<
                cm_type, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::map<detail::pow_type, first_val_t, second_val_t>::type
            >::type
        >::type more_cm_type;

    const first_diff_t fdiff = iterator::distance(first1, last1);
    if (fdiff != iterator::distance(first2, last2)) return srook::nullopt;

    first_val_t sx = 0;
    more_cm_type sx2 = 0;
    second_val_t sy = 0;
    more_cm_type sy2 = 0;
    cm_type sxy = 0;

    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
        sxy += *first1 * *first2;
        sx += *first1;
        sy += *first2;
        sx2 += math::pow(*first1, 2);
        sy2 += math::pow(*first2, 2);
    }
    
    return srook::make_optional((more_cm_type(fdiff) * sxy - sx * sy) / math::sqrt((more_cm_type(fdiff) * sx2 - math::pow(sx, 2)) * (more_cm_type(fdiff) * sy2 - math::pow(sy, 2))));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, numeric, srook)

#endif
