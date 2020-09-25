// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_COMB_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_COMB_SORT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/type_traits/iterator/is_forwarditerator.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_nothrow_invocable.hpp>
#include <srook/type_traits/is_dereferenceable.hpp>
#include <srook/type_traits/is_incrementable.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/functional/op/deduction_less.hpp>
#include <srook/cstdint.hpp>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class ForwardIter, class Compare>
void comb_sort_impl(ForwardIter first, ForwardIter last, Compare comp)
{
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type diff_type;

    diff_type diff = srook::iterator::distance(first, last), space = diff;

    for (bool bs = false; (space > 1) || bs;) {
        space = ((((space << 2) + space) << 1) + 3) / 13;
        
        if ((space == 9) || (space == 10)) space = 11;
        ForwardIter iter = first, next = srook::iterator::next(first, space);
        for (bs = false; next != last; ++iter, ++next) {
            if (comp(*next, *iter)) {
                std::iter_swap(iter, next);
                bs = true;
            }
        }
    }
}

} // namespace detail

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter, class Compare>
#else
template <class ForwardIter, class Compare, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#endif
SROOK_FORCE_INLINE
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_DEDUCED_TYPENAME 
enable_if<detail::iter_ref_apply<is_invocable, Compare, ForwardIter, ForwardIter>::type::value>::type
#else
void
#endif
comb_sort(ForwardIter first, ForwardIter last, Compare comp)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, ForwardIter>::type,
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, ForwardIter>::type,
        is_nothrow_incrementable<ForwardIter>,
        is_nothrow_dereferenceable<ForwardIter>
    >::value
)
{
    srook::algorithm::detail::comb_sort_impl(first, last, srook::move(comp));
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter>
#else
template <class ForwardIter, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#endif
SROOK_FORCE_INLINE void comb_sort(ForwardIter first, ForwardIter last)
SROOK_NOEXCEPT(srook::algorithm::comb_sort(first, last, srook::functional::deduction_less()))
{
    srook::algorithm::comb_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
