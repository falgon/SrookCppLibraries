// Copyright (C) 2017 roki
#ifndef INCLUDED_FILTERD_ITERATOR_HPP
#define INCLUDED_FILTERD_ITERATOR_HPP
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
	!has_iterator_v<std::remove_cv_t<std::remove_reference_t<Iterator>>>)>
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
#endif
