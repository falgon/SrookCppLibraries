// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_DROP_WHILE_ITERATOR_HPP
#define INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_DROP_WHILE_ITERATOR_HPP
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
class drop_while_iterator : public srook::iterator_traits<Iter> {
    SROOK_STATIC_ASSERT(is_iterator<Iter>::value, "Type must be iterator");
    SROOK_STATIC_ASSERT((is_nothrow_destructible<Iter>::value), "Iterator and Predicate type must be nothrow destructible");
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Iter iterator;
    typedef iterator const_iterator;

    template <class Pred>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE drop_while_iterator(Iter first, Iter last, Pred pred)
    SROOK_MEMFN_NOEXCEPT(type_traits::detail::Land<is_nothrow_constructible<Iter&, Iter>, bool_constant<noexcept(skip(pred))>>::value)
        : first_(first), last_(last)
    {
        skip<srook::range::iterator::detail::next_advance>(srook::move(pred));
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE drop_while_iterator& operator++() 
    SROOK_MEMFN_NOEXCEPT(type_traits::detail::Land<is_nothrow_preincrementable<iterator>, bool_constant<noexcept(skip())>>::value)
    {
        return srook::range::iterator::detail::next_advance::apply_skip(first_), *this;
    }

    SROOK_CXX14_CONSTEXPR SROOK_FORCE_INLINE drop_while_iterator& operator++(int)
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_constructible<drop_while_iterator&, drop_while_iterator>, is_nothrow_preincrementable<iterator>>::value)
    {
        drop_while_iterator t = *this;
        return ++*this, t;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE drop_while_iterator& operator=(const drop_while_iterator& rhs)
    SROOK_MEMFN_NOEXCEPT(type_traits::detail::Land<bool_constant<noexcept(pred_.reset(rhs.pred_))>, is_nothrow_assignable<Iter>>::value)
    {
        return first_ = rhs.first_, last_ = rhs.last_, *this;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference operator*() { return *first_; }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_CONSTEXPR SROOK_FORCE_INLINE const SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference operator*() const { return *first_; }
#endif
    SROOK_FORCE_INLINE ~drop_while_iterator() SROOK_NOEXCEPT_TRUE {}
private:
    template <class F, class Pred>
    SROOK_CONSTEXPR drop_while_iterator& skip(Pred pred)
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_equality_comparable<iterator>, 
            bool_constant<noexcept(F::apply_skip(first_))>,
            is_nothrow_dereferenceable<iterator>,
            is_nothrow_invocable<Pred, SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference>
        >::value
    )
    {
        return first_ != last_ && pred(*first_) ? F::apply_skip(first_), skip<F>(pred) : *this;
    }
            
    SROOK_CONSTEXPR SROOK_FORCE_INLINE friend bool operator==(const drop_while_iterator& lhs, const drop_while_iterator& rhs)
    SROOK_NOEXCEPT(is_nothrow_equality_comparable<SROOK_DEDUCED_TYPENAME drop_while_iterator::iterator>::value) { return lhs.first_ == rhs.first_; }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE friend bool operator!=(const drop_while_iterator& lhs, const drop_while_iterator& rhs)
    SROOK_NOEXCEPT(lhs == rhs) { return !(lhs == rhs); }
private:
    iterator first_, last_;
};

#if SROOK_HAS_CONCEPTS
template <class Pred, srook::concepts::Iterator Iter>
#else
template <class Pred, class Iter, SROOK_REQUIRES(is_iterator<Iter>::value)>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR drop_while_iterator<Iter>
make_drop_while_iterator(Pred&& pred, Iter first, Iter last) 
SROOK_NOEXCEPT(drop_while_iterator<Iter>(first, last, srook::forward<Pred>(pred)))
{ 
    return drop_while_iterator<Iter>(first, last, srook::forward<Pred>(pred)); 
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, range, srook)

#endif
