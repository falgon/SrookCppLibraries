// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_FILTERD_ITERATOR_HPP
#define INCLUDED_FILTERD_ITERATOR_HPP
#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_preincrementable.hpp>
#include <srook/type_traits/is_predecrementable.hpp>
#include <srook/type_traits/is_nothrow_assignable.hpp>
#include <srook/iterator/iterator_traits.hpp>
#include <srook/iterator/range_iterators/detail/lambda_wrapper.hpp>
#include <srook/iterator/range_iterators/detail/advance.hpp>

SROOK_NESTED_NAMESPACE(srook, range, iterator) {
SROOK_INLINE_NAMESPACE(v1)

template <class Pred, class Iter>
class filter_iterator : public srook::iterator_traits<Iter> {
    SROOK_STATIC_ASSERT(is_iterator<Iter>::value, "Type must be iterator");
    SROOK_STATIC_ASSERT((type_traits::detail::Land<is_nothrow_destructible<Iter>, is_nothrow_destructible<Pred>>::value), "Iterator and Predicate type must be nothrow destructible");
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Iter iterator;
    typedef iterator const_iterator;

    SROOK_CONSTEXPR SROOK_FORCE_INLINE filter_iterator(Iter first, Iter last, Pred pred)
    SROOK_MEMFN_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_constructible<Iter&, Iter>, 
            is_nothrow_constructible<lambda_wrapper<Pred>&, Pred>, 
            bool_constant<noexcept(skip<srook::range::iterator::detail::next_advance>())>
        >::value
    )
        : first_(first), last_(last), pred_(pred)
    {
        skip<srook::range::iterator::detail::next_advance>();
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE filter_iterator& operator++() 
    SROOK_MEMFN_NOEXCEPT(type_traits::detail::Land<is_nothrow_preincrementable<iterator>, bool_constant<noexcept(skip())>>::value)
    {
        typedef srook::range::iterator::detail::next_advance skip_type;
        return skip_type::apply_skip(first_), skip<skip_type>();
    }

    SROOK_CXX14_CONSTEXPR SROOK_FORCE_INLINE filter_iterator& operator++(int)
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_constructible<filter_iterator&, filter_iterator>, is_nothrow_preincrementable<iterator>>::value)
    {
        filter_iterator t = *this;
        return ++*this, t;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE filter_iterator& operator=(const filter_iterator& rhs)
    SROOK_MEMFN_NOEXCEPT(type_traits::detail::Land<bool_constant<noexcept(pred_.reset(rhs.pred_))>, is_nothrow_assignable<Iter>>::value)
    {
        return pred_.reset(rhs.pred_), first_ = rhs.first_, last_ = rhs.last_, *this;
    }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference operator*() { return *first_; }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_CONSTEXPR SROOK_FORCE_INLINE const SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference operator*() const { return *first_; }
#endif
    SROOK_FORCE_INLINE ~filter_iterator() SROOK_NOEXCEPT_TRUE {}
private:
    template <class F>
    SROOK_CONSTEXPR filter_iterator& skip()
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_equality_comparable<iterator>, 
            is_nothrow_preincrementable<iterator>, 
            is_nothrow_dereferenceable<iterator>,
            is_nothrow_invocable<pred_, SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference>
        >::value
    )
    {
        return first_ != last_ && !pred_(*first_) ? static_cast<void>(F::apply_skip(first_)), skip<F>() : *this;
    }
            
    SROOK_CONSTEXPR SROOK_FORCE_INLINE friend bool operator==(const filter_iterator& lhs, const filter_iterator& rhs)
    SROOK_NOEXCEPT(is_nothrow_equality_comparable<SROOK_DEDUCED_TYPENAME filter_iterator::iterator>::value) { return lhs.first_ == rhs.first_; }

    SROOK_CONSTEXPR SROOK_FORCE_INLINE friend bool operator!=(const filter_iterator& lhs, const filter_iterator& rhs)
    SROOK_NOEXCEPT(lhs == rhs) { return !(lhs == rhs); }
private:
    detail::lambda_wrapper<Pred> pred_;
    iterator first_, last_;
};

#if SROOK_HAS_CONCEPTS
template <class Pred, srook::concepts::Iterator Iter>
#else
template <class Pred, class Iter, SROOK_REQUIRES(is_iterator<Iter>::value)>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR filter_iterator<SROOK_DEDUCED_TYPENAME decay<Pred>::type, Iter>
make_filter_iterator(Pred&& pred, Iter first, Iter last) 
SROOK_NOEXCEPT(filter_iterator<SROOK_DEDUCED_TYPENAME decay<Pred>::type, Iter>(first, last, srook::forward<Pred>(pred)))
{ 
    return filter_iterator<SROOK_DEDUCED_TYPENAME decay<Pred>::type, Iter>(first, last, srook::forward<Pred>(pred)); 
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, range, srook)

#endif
