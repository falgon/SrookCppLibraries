// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_FILTERD_ITERATOR_HPP
#define INCLUDED_FILTERD_ITERATOR_HPP
#if 0
#include <iterator>
#include <srook/config/require.hpp>
#include <srook/type_traits/has_iterator.hpp>
#include <srook/type_traits/is_callable.hpp>
#include <srook/utility/lambda_wrapper.hpp>
#include <type_traits>

namespace srook {
inline namespace v1 {

template <class Predicate, class Iterator>
struct filterd_iterator final {
    using iterator_category = std::forward_iterator_tag;
    using iterator = Iterator;
    using const_iterator = Iterator;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using pointer = typename std::iterator_traits<Iterator>::pointer;

    explicit filterd_iterator(const Predicate &predicate, Iterator first, Iterator last) noexcept
	: pred(predicate), first_(std::move(first)), last_(std::move(last))
    {
	skip();
    }
    explicit filterd_iterator(Predicate &&predicate, Iterator first, Iterator last) noexcept
	: pred(std::move(predicate)), first_(std::move(first)), last_(std::move(last))
    {
	skip();
    }

    filterd_iterator &operator++()
    {
	++first_;
	skip();
	return *this;
    }
    filterd_iterator operator++(int)
    {
	filterd_iterator tmp = *this;
	++first_;
	skip();
	return tmp;
    }

    filterd_iterator &operator=(const filterd_iterator &rhs)
    {
	pred.reset(rhs.pred);
	first_ = rhs.first_;
	last_ = rhs.last_;
	return *this;
    }

    reference operator*() { return *first_; }
    const reference operator*() const { return *first_; }
    constexpr bool operator==(const filterd_iterator &rhs) const { return first_ == rhs.first_; }
    constexpr bool operator!=(const filterd_iterator &rhs) const { return !operator==(rhs); }

private:
    void skip()
    {
	while (first_ != last_ && !pred(*first_)) ++first_;
    }
    lambda_wrapper<Predicate> pred;
    iterator first_, last_;
};
template <
    class Predicate,
    class Iterator,
    REQUIRES(
	is_callable_v<std::remove_cv_t<std::remove_reference_t<Predicate>>> &&
	!has_iterator<std::remove_cv_t<std::remove_reference_t<Iterator>>>::value)>
constexpr filterd_iterator<
    std::remove_cv_t<std::remove_reference_t<Predicate>>,
    std::remove_cv_t<std::remove_reference_t<Iterator>>>
make_filterd_iterator(Predicate &&pred, Iterator first, Iterator last)
{
    return filterd_iterator<
	std::remove_cv_t<std::remove_reference_t<Predicate>>,
	std::remove_cv_t<std::remove_reference_t<Iterator>>>(
	std::forward<Predicate>(pred), std::move(first), std::move(last));
}

} // namespace v1
} // namespace srook

#else

#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/type_traits/is_preincrementable.hpp>
#include <srook/iterator/iterator_traits.hpp>
#include <srook/iterator/range_iterators/detail/lambda_wrapper.hpp>

SROOK_NESTED_NAMESPACE(srook, range, iterator) {
SROOK_INLINE_NAMESPACE(v1)

template <class Pred, class Iter>
class filter_iterator : public srook::iterator_traits<Iter> {
    SROOK_STATIC_ASSERT(is_iterator<Iter>::value, "Type must be iterator");
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Iter iterator;
    typedef iterator const_iterator;

    SROOK_FORCE_INLINE filter_iterator(Iter first, Iter last, Pred pred)
        : first_(first), last_(last), pred_(pred)
    {
        static_cast<void>(skip());
    }

    SROOK_FORCE_INLINE filter_iterator& operator++() 
    SROOK_NOEXCEPT(is_nothrow_preincrementable<iterator>::value)
    {
        ++first_;
        return skip();
    }

    filter_iterator& operator++(int)
    SROOK_NOEXCEPT(is_nothrow_preincrementable<iterator>::value)
    {
        filter_iterator t = *this;
        ++first_;
        static_cast<void>(skip());
        return t;
    }

    filter_iterator& operator=(const filter_iterator& rhs)
    {
        pred_.reset(rhs.pred_);
        first_ = pred_.first_;
        last_ = pred_.last_;
        return *this;
    }

    SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference operator*() { return *first_; }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    const SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference operator*() const { return *first_; }
#endif
private:
    filter_iterator& skip() 
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_equality_comparable<iterator>, 
            is_nothrow_preincrementable<iterator>, 
            is_nothrow_dereferenceable<iterator>,
            is_nothrow_invocable<pred_, SROOK_DEDUCED_TYPENAME srook::iterator_traits<iterator>::reference>
        >::value
    )
    {
        while (first_ != last_ && !pred_(*first_)) ++first_;
        return *this;
    }
            
    detail::lambda_wrapper<Pred> pred_;
    iterator first_, last_;

    SROOK_FORCE_INLINE SROOK_CONSTEXPR friend bool operator==(const filter_iterator& lhs, const filter_iterator& rhs)
    SROOK_NOEXCEPT(is_nothrow_equality_comparable<SROOK_DEDUCED_TYPENAME filter_iterator::iterator>::value)
    {
        return lhs.first_ == rhs.first_;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR friend bool operator!=(const filter_iterator& lhs, const filter_iterator& rhs)
    SROOK_NOEXCEPT(lhs == rhs)
    {
        return !(lhs == rhs);
    }
};

#if SROOK_HAS_CONCEPTS
template <class Pred, srook::concepts::Iterator Iter>
#else
template <class Pred, class Iter, SROOK_REQUIRES(is_iterator<Iter>::value)>
#endif
SROOK_FORCE_INLINE SROOK_CONSTEXPR filter_iterator<SROOK_DEDUCED_TYPENAME decay<Pred>::type, Iter>
make_filter_iterator(Pred&& pred, Iter first, Iter last)
{
    return filter_iterator<SROOK_DEDUCED_TYPENAME decay<Pred>::type, Iter>(first, last, srook::forward<Pred>(pred));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, range, srook)

#endif
#endif
