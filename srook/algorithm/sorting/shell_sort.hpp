// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SHELL_SORT_HPP
#define INCLUDED_SROOK_ALGORITHM_SHELL_SORT_HPP

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
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class ForwardIter, class Compare>
void shell_sort_impl(ForwardIter first, ForwardIter last, Compare comp)
{
    typedef SROOK_DEDUCED_TYPENAME std::iterator_traits<ForwardIter>::difference_type diff_type;
    if (first == last) return;

    diff_type diff = srook::iterator::distance(first, last), space = 1;
    while (space < diff) space = space * 3 + 1;

    ForwardIter t;
    for (space = (space - 1) / 3; space >= 1; space = (space - 1) / 3) {
        for (diff_type i = 0; i < space; ++i) {
            t = srook::iterator::next(first, i);
            for (ForwardIter iter = srook::iterator::next(t, space); iter < last; srook::iterator::advance(iter, space)) {
                ForwardIter back = iter, c = iter;
                for (srook::iterator::advance(back, -space); c != t && comp(*c, *back); c = back, srook::iterator::advance(back, -space)) {
                    std::iter_swap(c, back);
                }
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
shell_sort(ForwardIter first, ForwardIter last, Compare comp)
SROOK_NOEXCEPT(
    type_traits::detail::Land<
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_swappable, ForwardIter>::type,
        SROOK_DEDUCED_TYPENAME detail::iter_ref_apply<is_nothrow_invocable, Compare, ForwardIter>::type,
        is_nothrow_incrementable<ForwardIter>,
        is_nothrow_dereferenceable<ForwardIter>
    >::value
)
{
    srook::algorithm::detail::shell_sort_impl(first, last, srook::move(comp));
}

#if SROOK_HAS_CONCEPTS
template <srook::concepts::ForwardIterator ForwardIter>
#else
template <class ForwardIter, SROOK_REQUIRES(is_forwarditerator<ForwardIter>::value)>
#endif
SROOK_FORCE_INLINE void shell_sort(ForwardIter first, ForwardIter last)
SROOK_NOEXCEPT(srook::algorithm::shell_sort(first, last, srook::functional::deduction_less()))
{
    srook::algorithm::shell_sort(first, last, srook::functional::deduction_less());
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
