// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SORTING_DETAIL_QSORT_HELPER_HPP
#define INCLUDED_SROOK_ALGORITHM_SORTING_DETAIL_QSORT_HELPER_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/algorithm/detail/config.hpp>
#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/type_traits/is_comparable.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

class qsort_helper {
protected:
#if SROOK_HAS_CONCEPTS
    template <class Iter, class Compare> requires srook::concepts::Iterator<Iter> || is_pointer<Iter>::value
#elif SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class Iter, class Compare, SROOK_REQUIRES(type_traits::detail::Lor<is_iterator<Iter>, is_pointer<Iter>>::value)>
#else
    template <class Iter, class Compare>
#endif
    SROOK_FORCE_INLINE 
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_DEDUCED_TYPENAME enable_if<srook::algorithm::detail::iter_ref_apply<is_invocable, Compare, Iter, Iter>::type::value>::type
#else
    void
#endif
    move_median_to_first(Iter result, Iter first, Iter middle, Iter last, Compare comp) const
    SROOK_NOEXCEPT(is_nothrow_comparable<Iter>::value)
    {
        comp(*first, *middle) ? 
            comp(*middle, *last) ? std::iter_swap(result, middle)
            : comp(*first, *last) ? std::iter_swap(result, last) 
                : std::iter_swap(result, first)
        : comp(*first, *last) ? std::iter_swap(result, first)
            : comp(*middle, *last) ? std::iter_swap(result, last) 
                    : std::iter_swap(result, middle);
    }
};

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
