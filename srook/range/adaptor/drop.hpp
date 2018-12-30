// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_DROP_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_DROP_HPP
#include <srook/range/adaptor/adaptor_operator.hpp>
#include <srook/range/adaptor/detail/deduce_iter.hpp>
#include <srook/iterator/range_iterators/range_iterator.hpp>
#include <srook/iterator/range_iterators/drop_iterator.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/type_traits/is_range.hpp>

SROOK_NESTED_NAMESPACE(srook, range, adaptors) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

class range_drop {
public:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR explicit range_drop(std::size_t s) SROOK_NOEXCEPT_TRUE
        : s_(srook::move(s)) {}

    template <class Range, SROOK_REQUIRES(is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>::value)>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::range::iterator::range_iterator<srook::range::iterator::drop_iterator<SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>>
    operator()(Range&& range) const
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_constructible<
                srook::range::iterator::drop_iterator<SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type
            >,
            is_nothrow_constructible<
                srook::range::iterator::range_iterator<drop_iterator<SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>>, 
                drop_iterator<SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>, 
                drop_iterator<SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>
            >
        >::value
    )
    {
        using srook::range::iterator::make_range_iterator;
        using srook::range::iterator::make_drop_iterator;
        return make_range_iterator(make_drop_iterator(s_, srook::begin(range), srook::end(range)), make_drop_iterator(s_, srook::end(range), srook::end(range)));
    }
private:
    std::size_t s_;
};

} // namespace detail

SROOK_FORCE_INLINE SROOK_CONSTEXPR detail::range_drop drop(std::size_t s) SROOK_NOEXCEPT_TRUE
{
    return detail::range_drop(srook::move(s));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(adaptors, range, srook)

#endif
