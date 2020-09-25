// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_RANGE_ITERATORS_HPP
#define INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_RANGE_ITERATORS_HPP
#include <srook/iterator/iterator_traits.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_nothrow_constructible.hpp>
#include <srook/cxx20/concepts/iterator/Iterator.hpp>

SROOK_NESTED_NAMESPACE(srook, range, iterator) {
SROOK_INLINE_NAMESPACE(v1)

template <class Iterator>
class range_iterator : public srook::iterator_traits<Iterator> {
    SROOK_STATIC_ASSERT(is_iterator<Iterator>::value, "Type must be iterator");
public:
    typedef Iterator iterator;
    typedef iterator const_iterator;

    SROOK_FORCE_INLINE SROOK_CONSTEXPR range_iterator(iterator first, iterator last) SROOK_NOEXCEPT_TRUE
        : first_(first), last_(last) {}
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR iterator begin() const SROOK_NOEXCEPT_TRUE { return first_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR iterator end() const SROOK_NOEXCEPT_TRUE { return last_; }
#endif
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const_iterator cbegin() const SROOK_NOEXCEPT_TRUE { return first_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const_iterator cend() const SROOK_NOEXCEPT_TRUE { return last_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR iterator begin() SROOK_NOEXCEPT_TRUE { return first_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR iterator end() SROOK_NOEXCEPT_TRUE { return last_; }
    SROOK_FORCE_INLINE ~range_iterator() SROOK_NOEXCEPT_TRUE {}
private:
    iterator first_, last_;
};

#if SROOK_HAS_CONCEPTS
template <srook::concepts::Iterator Iter>
#else
template <class Iter, SROOK_REQUIRES(is_iterator<Iter>::value)>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR range_iterator<Iter> make_range_iterator(Iter first, Iter last)
SROOK_NOEXCEPT(is_nothrow_constructible<range_iterator<Iter>, Iter, Iter>::value) { return range_iterator<Iter>(first, last); }

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, range, srook)
#endif
