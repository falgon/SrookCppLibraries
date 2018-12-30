// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_TRANSFORM_ITERATOR_HPP
#define INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_TRANSFORM_ITERATOR_HPP

#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_preincrementable.hpp>
#include <srook/type_traits/is_nothrow_constructible.hpp>
#include <srook/iterator/iterator_traits.hpp>
#include <srook/iterator/range_iterators/detail/lambda_wrapper.hpp>

SROOK_NESTED_NAMESPACE(srook, range, iterator) {
SROOK_INLINE_NAMESPACE(v1)

template <class Pred, class Iter>
class transform_iterator : public srook::iterator_traits<Iter> {
    SROOK_STATIC_ASSERT(is_iterator<Iter>::value, "Type must be iterator");
    SROOK_STATIC_ASSERT((type_traits::detail::Land<is_nothrow_destructible<Iter>, is_nothrow_destructible<Pred>>::value), "Iterator and Predicate type must be nothrow destructible");
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Iter iterator;
    typedef iterator const_iterator;

    SROOK_CONSTEXPR SROOK_FORCE_INLINE transform_iterator(Iter first, Iter last, Pred pred)
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_constructible<Iter&, Iter>, is_nothrow_constructible<detail::lambda_wrapper<Pred>, Pred>>::value)
        : first_(first), last_(last), pred_(pred)
    {}

    SROOK_CONSTEXPR SROOK_FORCE_INLINE transform_iterator& operator++() 
    SROOK_NOEXCEPT(is_nothrow_preincrementable<iterator>::value) { return ++first_, *this; }

    SROOK_CXX14_CONSTEXPR SROOK_FORCE_INLINE transform_iterator& operator++(int)
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_constructible<transform_iterator&, transform_iterator>, is_nothrow_preincrementable<iterator>>::value)
    {
        transform_iterator t = *this;
        return ++*this, t;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE transform_iterator& operator=(const transform_iterator& rhs) 
    SROOK_MEMFN_NOEXCEPT(type_traits::detail::Land<bool_constant<noexcept(pred_.reset(rhs.pred_))>, is_nothrow_constructible<Iter&, Iter>>::value)
    {
        return pred_.reset(rhs.pred_), first_ = rhs.first_, last_ = rhs.last_, *this;
    }

    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME srook::invoke_result<Pred, SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::value_type>::type operator*()
    SROOK_NOEXCEPT(is_nothrow_invocable<detail::lambda_wrapper<Pred>, SROOK_DEDUCED_TYPENAME srook::iterator_traits<Iter>::value_type>::value) { return pred_(*first_); }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_FORCE_INLINE const SROOK_DEDUCED_TYPENAME srook::invoke_result<Pred, SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::value_type>::type operator*() const 
    SROOK_NOEXCEPT(is_nothrow_invocavke<detail::lambda_wrapper<Pred>, SROOK_DEDUCED_TYPENAME srook::iterator_traits<Iter>::value_type>::value) { return pred_(*first_); }
#endif
    SROOK_FORCE_INLINE ~transform_iterator() SROOK_NOEXCEPT_TRUE {}
private:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR friend bool operator==(const transform_iterator& lhs, const transform_iterator& rhs)
    SROOK_NOEXCEPT(is_nothrow_equality_comparable<SROOK_DEDUCED_TYPENAME transform_iterator::iterator>::value) { return lhs.first_ == rhs.first_; }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR friend bool operator!=(const transform_iterator& lhs, const transform_iterator& rhs)
    SROOK_NOEXCEPT(lhs == rhs) { return !(lhs == rhs); }
private:
    iterator first_, last_;
    detail::lambda_wrapper<Pred> pred_;
};

#if SROOK_HAS_CONCEPTS
template <class Pred, srook::concepts::Iterator Iter>
#else
template <class Pred, class Iter, SROOK_REQUIRES(is_iterator<Iter>::value)>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR transform_iterator<SROOK_DEDUCED_TYPENAME decay<Pred>::type, Iter>
make_transform_iterator(Pred&& pred, Iter first, Iter last) SROOK_NOEXCEPT(transform_iterator<SROOK_DEDUCED_TYPENAME decay<Pred>::type, Iter>(first, last, srook::forward<Pred>(pred)))
{
    return transform_iterator<SROOK_DEDUCED_TYPENAME decay<Pred>::type, Iter>(first, last, srook::forward<Pred>(pred));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, range, srook)

#endif
