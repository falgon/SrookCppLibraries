// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_DETAIL_ADVANCE_HPP
#define INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_DETAIL_ADVANCE_HPP
#include <srook/config.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_preincrementable.hpp>
#include <srook/type_traits/is_predecrementable.hpp>

SROOK_NESTED_NAMESPACE(srook, range, iterator) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {
struct next_advance {
    template <class Iter, SROOK_REQUIRES(is_iterator<Iter>::value)>
    static SROOK_CONSTEXPR SROOK_FORCE_INLINE Iter& apply_skip(Iter& iter)
    SROOK_NOEXCEPT(is_nothrow_preincrementable<Iter>::value)
    {
        return ++iter;
    }
};

struct prev_advance {
    template <class Iter, SROOK_REQUIRES(is_iterator<Iter>::value)>
    static SROOK_CONSTEXPR SROOK_FORCE_INLINE Iter& apply_skip(Iter& iter)
    SROOK_NOEXCEPT(is_nothrow_predecrementable<Iter>::value)
    {
        return --iter;
    }
};
} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, range, srook)
#endif
