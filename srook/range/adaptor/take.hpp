// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_TAKE_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_TAKE_HPP
#include <srook/range/adaptor/adaptor_operator.hpp>
#include <srook/iterator/range_iterators/range_iterator.hpp>
#include <srook/iterator/range_iterators/take_iterator.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/type_traits/is_range.hpp>

SROOK_NESTED_NAMESPACE(srook, range, adaptors) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

class range_take {
    template <class Range>
    struct deduce_iter : type_constant<SROOK_DEDUCED_TYPENAME decay<Range>::type::iterator> {};
public:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR explicit range_take(std::size_t s) SROOK_NOEXCEPT_TRUE
        : s_(srook::move(s)) {}

    template <class Range, SROOK_REQUIRES(is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>::value)>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::range::iterator::range_iterator<srook::range::iterator::take_iterator<SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>>
    operator()(Range&& range) 
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_constructible<
                srook::range::iterator::take_iterator<SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type
            >,
            is_nothrow_constructible<
                srook::range::iterator::range_iterator<take_iterator<SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>>, 
                take_iterator<SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>, 
                take_iterator<SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>
            >
        >::value
    )
    {
        using srook::range::iterator::make_range_iterator;
        using srook::range::iterator::make_take_iterator;
        return make_range_iterator(make_take_iterator(s_, srook::begin(range), srook::end(range)), make_take_iterator(s_, srook::end(range), srook::end(range)));
    }
private:
    std::size_t s_;
};

} // namespace detail

SROOK_FORCE_INLINE SROOK_CONSTEXPR detail::range_take take(std::size_t s) SROOK_NOEXCEPT_TRUE
{
    return detail::range_take(srook::move(s));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(adaptors, range, srook)

#endif
