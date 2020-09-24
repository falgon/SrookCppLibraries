// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MATH_GEOMETORY_LINE_STRAIGHT_LEAST_SQUARES_HPP
#define INCLUDED_SROOK_MATH_GEOMETORY_LINE_STRAIGHT_LEAST_SQUARES_HPP

#include <srook/optional.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/tmpl/vt/all.hpp>
#include <srook/tmpl/vt/apply.hpp>
#include <srook/tmpl/vt/transfer.hpp>
#include <srook/tmpl/vt/composition.hpp>
#include <srook/tmpl/vt/replicate.hpp>
#include <srook/tmpl/vt/proxy_by.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>
#include <srook/iterator/iterator_traits.hpp>
#include <srook/math/algorithm/constants/pow.hpp>
#include <srook/execution.hpp>
#include <srook/tuple/algorithm/map.hpp>
#include <numeric>

SROOK_NESTED_NAMESPACE(srook, math, geometry, algorithm, line, straight) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

SROOK_INLINE_VARIABLE SROOK_CONSTEXPR std::size_t least_squares_threshold = 0xff;

template <class ForwardIterator1, class ForwardIterator2>
SROOK_FORCE_INLINE srook::optional<
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::pair,
        SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
            2,
            SROOK_DEDUCED_TYPENAME tmpl::vt::apply<
                std::common_type,
                SROOK_DEDUCED_TYPENAME tmpl::vt::map<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, ForwardIterator1, ForwardIterator2>::type
            >::type
        >::type
    >::type
>
least_squares_impl(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, const std::size_t dis)
{
    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::apply<
        std::common_type,
        SROOK_DEDUCED_TYPENAME tmpl::vt::map<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, ForwardIterator1, ForwardIterator2>::type
    >::type cm_type;

    cm_type sxy = 0, sx = 0, sy = 0, sx2 = 0;
    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
        sxy += *first1 * *first2;
        sx += *first1;
        sy += *first2;
        sx2 += math::pow(*first1, 2); 
    }

    return srook::make_optional(std::make_pair((cm_type(dis) * sxy - sx * sy) / (cm_type(dis) * sx2 - math::pow(sx, 2)), (sx2 * sy - sxy * sx) / (cm_type(dis) * sx2 - math::pow(sx, 2))));
}

template <class ForwardIterator1, class ForwardIterator2>
SROOK_FORCE_INLINE srook::optional<
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::pair,
        SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
            2, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::apply<
                std::common_type, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::map<
                    tmpl::vt::composition<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, decay>::template generate, 
                    ForwardIterator1, ForwardIterator2
                >::type
            >::type
        >::type
    >::type
>
least_squares_impl(execution::sequenced_policy, ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, const std::size_t dis)
{
    return least_squares_impl(first1, last1, first2, last2, srook::move(dis));
}

template <class ForwardIterator1, class ForwardIterator2>
SROOK_FORCE_INLINE srook::optional<
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::pair,
        SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
            2, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::apply<
                std::common_type, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::map<
                    tmpl::vt::composition<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, decay>::template generate, 
                    ForwardIterator1, ForwardIterator2
                >::type
            >::type
        >::type
    >::type
>
least_squares_impl(execution::parallel_policy par, ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, const std::size_t dis)
{
    if (dis < least_squares_threshold) return least_squares_impl(first1, last1, first2, last2, dis);

    typedef SROOK_DEDUCED_TYPENAME tmpl::vt::apply<
        std::common_type,
        SROOK_DEDUCED_TYPENAME tmpl::vt::map<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, ForwardIterator1, ForwardIterator2>::type
    >::type cm_type;
    
    const SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<std::tuple, SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<4, cm_type>::type>::type res = 
        tuple::map(
            par, 
            [](auto&& t) SROOK_NOEXCEPT_TRUE { return t; },
            std::tuple_cat(
                tuple::map(par, [](auto&& t) { 
                    return std::accumulate(std::get<0>(t), std::get<1>(t), 0, std::get<2>(t)); 
                }, std::make_tuple(
                    std::make_tuple(first1, last1, std::plus<cm_type>{}), 
                    std::make_tuple(first2, last2, std::plus<cm_type>{})
                )),
                tuple::map([](auto&& p) SROOK_NOEXCEPT_TRUE {
                    typedef SROOK_DEDUCED_TYPENAME std::tuple_element<0, SROOK_DEDUCED_TYPENAME decay<SROOK_DECLTYPE(p)>::type>::type Iter;
                    cm_type val = 0;
                    Iter f = p.first, l = p.second;
                    for (; f != l; ++f) val += *f * *f;
                    return val;
                }, std::make_tuple(std::make_pair(first1, last1))),
                tuple::map([](auto&& t) SROOK_NOEXCEPT_TRUE {
                    typedef SROOK_DEDUCED_TYPENAME std::tuple_element<0, SROOK_DEDUCED_TYPENAME decay<SROOK_DECLTYPE(t)>::type>::type FirstIter;
                    typedef SROOK_DEDUCED_TYPENAME std::tuple_element<2, SROOK_DEDUCED_TYPENAME decay<SROOK_DECLTYPE(t)>::type>::type SecondIter;
                    
                    cm_type val = 0;
                    FirstIter f1 = std::get<0>(t), l1 = std::get<1>(t);
                    SecondIter f2 = std::get<2>(t), l2 = std::get<3>(t);
                    for (; f1 != l1 && f2 != l2; ++f1, ++f2) val += *f1 * *f2;
                    return val;
                }, std::make_tuple(std::make_tuple(first1, last1, first2, last2)))
            )
        );
    const cm_type sxy = std::get<3>(res), sx = std::get<0>(res), sy = std::get<1>(res), sx2 = std::get<2>(res);
    return srook::make_optional(std::make_pair((cm_type(dis) * sxy - sx * sy) / (cm_type(dis) * sx2 - sx * sx), (sx2 * sy - sxy * sx) / (cm_type(dis) * sx2 - sx * sx)));
}

template <class ForwardIterator1, class ForwardIterator2>
SROOK_FORCE_INLINE srook::optional<
    SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
        std::pair,
        SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
            2, 
            SROOK_DEDUCED_TYPENAME tmpl::vt::apply<
                std::common_type, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::map<
                    tmpl::vt::composition<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, decay>::template generate, 
                    ForwardIterator1, ForwardIterator2
                >::type
            >::type
        >::type
    >::type
>
least_squares_impl(execution::parallel_unsequenced_policy, ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, const std::size_t dis)
{
    return least_squares_impl(execution::par, first1, last1, first2, last2, srook::move(dis));
}

} // namespace detail

template <class ForwardIterator1, class ForwardIterator2>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        tmpl::vt::all<tmpl::vt::composition<is_forwarditerator, decay>::template generate, ForwardIterator1, ForwardIterator2>,
        tmpl::vt::all<tmpl::vt::composition<is_arithmetic, tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, decay>::template generate, ForwardIterator1, ForwardIterator2>,
        tmpl::vt::apply<
            is_convertible,
            SROOK_DEDUCED_TYPENAME tmpl::vt::map<
                tmpl::vt::composition<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, decay>::template generate, 
                ForwardIterator1, ForwardIterator2
            >::type
        >
    >::value,
    srook::optional<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            std::pair,
            SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                2, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::apply<
                    std::common_type, 
                    SROOK_DEDUCED_TYPENAME tmpl::vt::map<
                        tmpl::vt::composition<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, decay>::template generate, 
                        ForwardIterator1, ForwardIterator2
                    >::type
                >::type
            >::type
        >::type
    >
>::type
least_squares(ForwardIterator1&& first1, ForwardIterator1&& last1, ForwardIterator2&& first2, ForwardIterator2&& last2)
{
    const SROOK_DEDUCED_TYPENAME tmpl::vt::composition<tmpl::vt::proxy_by_difference_type<iterator_traits>::template generate, decay>::template generate<ForwardIterator1>::type
        dis = iterator::distance(first1, last1);
    return dis == iterator::distance(first2, last2) ? detail::least_squares_impl(first1, last1, first2, last2, srook::move(dis)) : srook::nullopt;
}


template <class ExecutionPolicy, class ForwardIterator1, class ForwardIterator2>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME enable_if<
    type_traits::detail::Land<
        execution::is_execution_policy<ExecutionPolicy>,
        tmpl::vt::all<tmpl::vt::composition<is_forwarditerator, decay>::template generate, ForwardIterator1, ForwardIterator2>,
        tmpl::vt::all<tmpl::vt::composition<is_arithmetic, tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, decay>::template generate, ForwardIterator1, ForwardIterator2>,
        tmpl::vt::apply<
            is_convertible,
            SROOK_DEDUCED_TYPENAME tmpl::vt::map<
                tmpl::vt::composition<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, decay>::template generate, 
                ForwardIterator1, ForwardIterator2
            >::type
        >
    >::value,
    srook::optional<
        SROOK_DEDUCED_TYPENAME tmpl::vt::transfer<
            std::pair,
            SROOK_DEDUCED_TYPENAME tmpl::vt::replicate<
                2, 
                SROOK_DEDUCED_TYPENAME tmpl::vt::apply<
                    std::common_type, 
                    SROOK_DEDUCED_TYPENAME tmpl::vt::map<
                        tmpl::vt::composition<tmpl::vt::proxy_by_value_type<iterator_traits>::template generate, decay>::template generate, 
                        ForwardIterator1, ForwardIterator2
                    >::type
                >::type
            >::type
        >::type
    >
>::type
least_squares(ExecutionPolicy policy, ForwardIterator1&& first1, ForwardIterator1&& last1, ForwardIterator2&& first2, ForwardIterator2&& last2)
{
    const SROOK_DEDUCED_TYPENAME tmpl::vt::composition<tmpl::vt::proxy_by_difference_type<iterator_traits>::template generate, decay>::template generate<ForwardIterator1>::type
        dis = iterator::distance(first1, last1);
    return dis == iterator::distance(first2, last2) ? detail::least_squares_impl(policy, first1, last1, first2, last2, srook::move(dis)) : srook::nullopt;
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(straight, line, algorithm, geometry, math, srook)

#endif
