// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_RANGE_ITERATORS_HPP
#define INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_RANGE_ITERATORS_HPP
#if 0
#include <iterator>
#include <type_traits>
#include <srook/utility/void_t.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/cpp_predefined.hpp>

namespace srook {
inline namespace v1 {

struct Srook_range_iterator_type_ {
    Srook_range_iterator_type_() = delete;
};

template <class Iterator>
struct range_iterator final {
private:
    struct OnlyHeadAndTail_Iterator_Tag {
	OnlyHeadAndTail_Iterator_Tag() = delete;
    };

public:
    using iterator_category = OnlyHeadAndTail_Iterator_Tag;
    using iterator = Iterator;
    using const_iterator = iterator;
    using value_type = typename std::iterator_traits<iterator>::value_type;
    using pointer = typename std::iterator_traits<iterator>::pointer;
    using difference_type = typename std::iterator_traits<iterator>::difference_type;
    using reference = typename std::iterator_traits<iterator>::reference;

    using SROOK_RANGE_ITERATOR_TYPE = Srook_range_iterator_type_;

    explicit SROOK_CONSTEXPR range_iterator(iterator &&first, iterator &&last) noexcept
	: first_(std::move(first)), last_(std::move(last)) {}
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_CONSTEXPR iterator begin() const noexcept { return first_; }
    SROOK_CONSTEXPR iterator end() const noexcept { return last_; }
#endif
    SROOK_CONSTEXPR const_iterator cbegin() const noexcept { return first_; }
    SROOK_CONSTEXPR const_iterator cend() const noexcept { return last_; }
    SROOK_CONSTEXPR iterator begin() noexcept { return first_; }
    SROOK_CONSTEXPR iterator end() noexcept { return last_; }

private:
    iterator first_, last_;
};

template <class, class = typename voider<>::type>
SROOK_CONSTEXPR bool is_range_iterator_v = std::false_type::value;
template <class T>
SROOK_CONSTEXPR bool is_range_iterator_v<T, typename voider<typename T::SROOK_RANGE_ITERATOR_TYPE>::type> = std::true_type::value;

template <class Iterator>
SROOK_CONSTEXPR range_iterator<Iterator> make_range_iterator(Iterator first, Iterator last)
{
    return range_iterator<Iterator>(std::move(first), std::move(last));
}

} // namespace v1
} // namespace srook

#else
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
#endif
