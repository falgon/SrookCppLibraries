// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_DROP_ITERATOR_HPP
#define INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_DROP_ITERATOR_HPP
#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_preincrementable.hpp>
#include <srook/type_traits/is_predecrementable.hpp>
#include <srook/type_traits/is_nothrow_assignable.hpp>
#include <srook/iterator/iterator_traits.hpp>
#include <srook/iterator/range_iterators/detail/advance.hpp>
#include <srook/utility/move.hpp>

SROOK_NESTED_NAMESPACE(srook, range, iterator) {
SROOK_INLINE_NAMESPACE(v1)

template <class Iter>
class drop_iterator : public srook::iterator_traits<Iter> {
    SROOK_STATIC_ASSERT(is_iterator<Iter>::value, "Type must be iterator");
    SROOK_STATIC_ASSERT(is_nothrow_destructible<Iter>::value, "Iterator and Predicate type must be nothrow destructible");
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Iter iterator;
    typedef iterator const_iterator;

    SROOK_CONSTEXPR SROOK_FORCE_INLINE drop_iterator(Iter first, Iter last, std::size_t n)
    SROOK_MEMFN_NOEXCEPT(type_trait::detail::Land<is_nothrow_constructible<Iter&, Iter>, bool_constant<noexcept(skip<srook::range::iterator::detail::next_advance>(srook::move(n)))>>::value)
        : first_(first), last_(last)
    {
        skip<srook::range::iterator::detail::next_advance>(srook::move(n));
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE drop_iterator& operator++() 
    SROOK_MEMFN_NOEXCEPT(type_traits::detail::Land<is_nothrow_preincrementable<iterator>, bool_constant<noexcept(skip())>>::value)
    {
        return srook::range::iterator::detail::next_advance::apply_skip(first_), *this; 
    }

    SROOK_CXX14_CONSTEXPR SROOK_FORCE_INLINE drop_iterator& operator++(int)
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_constructible<drop_iterator&, drop_iterator>, is_nothrow_preincrementable<iterator>>::value)
    {
        drop_iterator t = *this;
        return ++*this, t;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE drop_iterator& operator=(const drop_iterator& rhs)
    SROOK_MEMFN_NOEXCEPT(type_traits::detail::Land<bool_constant<noexcept(pred_.reset(rhs.pred_))>, is_nothrow_assignable<Iter>>::value)
    {
        return first_ = rhs.first_, last_ = rhs.last_, *this;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference operator*() { return *first_; }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_CONSTEXPR SROOK_FORCE_INLINE const SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference operator*() const { return *first_; }
#endif
    SROOK_FORCE_INLINE ~drop_iterator() SROOK_NOEXCEPT_TRUE {}
private:
    template <class F>
    SROOK_CONSTEXPR drop_iterator& skip(std::size_t n)
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_equality_comparable<iterator>, 
            bool_constant<noexcept(F::apply_skip(first_))>,
            is_nothrow_dereferenceable<iterator>,
            is_nothrow_invocable<Pred, SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference>
        >::value
    )
    {
        return first_ != last_ && n ? F::apply_skip(first_), skip<F>(n - 1) : *this;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE friend bool operator==(const drop_iterator& lhs, const drop_iterator& rhs)
    SROOK_NOEXCEPT(is_nothrow_equality_comparable<SROOK_DEDUCED_TYPENAME drop_iterator::iterator>::value) { return lhs.first_ == rhs.first_; }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE friend bool operator!=(const drop_iterator& lhs, const drop_iterator& rhs)
    SROOK_NOEXCEPT(lhs == rhs) { return !(lhs == rhs); }
private:
    iterator first_, last_;
};

#if SROOK_HAS_CONCEPTS
template <srook::concepts::Iterator Iter>
#else
template <class Iter, SROOK_REQUIRES(is_iterator<Iter>::value)>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR drop_iterator<Iter>
make_drop_iterator(std::size_t s, Iter first, Iter last) SROOK_NOEXCEPT(drop_iterator<Iter>(first, last, srook::move(s)))
{ 
    return drop_iterator<Iter>(first, last, srook::move(s)); 
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, range, srook)

#endif
