// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_TAKE_ITERATOR_HPP
#define INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_TAKE_ITERATOR_HPP
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
class take_iterator : public srook::iterator_traits<Iter> {
    SROOK_STATIC_ASSERT(is_iterator<Iter>::value, "Type must be iterator");
    SROOK_STATIC_ASSERT(is_nothrow_destructible<Iter>::value, "Iterator and Predicate type must be nothrow destructible");
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Iter iterator;
    typedef iterator const_iterator;

    SROOK_CONSTEXPR SROOK_FORCE_INLINE take_iterator(Iter first, Iter last, std::size_t n)
    SROOK_NOEXCEPT(is_nothrow_constructible<Iter&, Iter>::value)
        : first_(first), last_(last), n_(n ? n - 1 : 0)
    {
        if (!n) first_ = last_;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE take_iterator& operator++() 
    SROOK_MEMFN_NOEXCEPT(type_traits::detail::Land<is_nothrow_preincrementable<iterator>, bool_constant<noexcept(skip())>>::value)
    {
        return skip<srook::range::iterator::detail::next_advance>();
    }

    SROOK_CXX14_CONSTEXPR SROOK_FORCE_INLINE take_iterator& operator++(int)
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_constructible<take_iterator&, take_iterator>, is_nothrow_preincrementable<iterator>>::value)
    {
        take_iterator t = *this;
        return ++*this, t;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE take_iterator& operator=(const take_iterator& rhs)
    SROOK_MEMFN_NOEXCEPT(type_traits::detail::Land<bool_constant<noexcept(pred_.reset(rhs.pred_))>, is_nothrow_assignable<Iter>>::value)
    {
        return n_ = rhs.n_, first_ = rhs.first_, last_ = rhs.last_, *this;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference operator*() { return *first_; }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_CONSTEXPR SROOK_FORCE_INLINE const SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference operator*() const { return *first_; }
#endif
    SROOK_FORCE_INLINE ~take_iterator() SROOK_NOEXCEPT_TRUE {}
private:
    template <class F>
    SROOK_CONSTEXPR take_iterator& skip()
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_equality_comparable<iterator>, 
            is_nothrow_preincrementable<iterator>, 
            is_nothrow_dereferenceable<iterator>
        >::value
    )
    {
        return first_ != last_ && n_ ? --n_, F::apply_skip(first_), *this : (first_ = last_, *this); 
    }
            
    SROOK_CONSTEXPR SROOK_FORCE_INLINE friend bool operator==(const take_iterator& lhs, const take_iterator& rhs)
    SROOK_NOEXCEPT(is_nothrow_equality_comparable<SROOK_DEDUCED_TYPENAME take_iterator::iterator>::value) { return lhs.first_ == rhs.first_; }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE friend bool operator!=(const take_iterator& lhs, const take_iterator& rhs)
    SROOK_NOEXCEPT(lhs == rhs) { return !(lhs == rhs); }
private:
    iterator first_, last_;
    std::size_t n_;
};

#if SROOK_HAS_CONCEPTS
template <srook::concepts::Iterator Iter>
#else
template <class Iter, SROOK_REQUIRES(is_iterator<Iter>::value)>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR take_iterator<Iter>
make_take_iterator(std::size_t s, Iter first, Iter last) SROOK_NOEXCEPT(take_iterator<Iter>(first, last, srook::move(s))) 
{ 
    return take_iterator<Iter>(first, last, srook::move(s)); 
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, range, srook)

#endif
