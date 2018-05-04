// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_TRANSFORMED_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_TRANSFORMED_HPP
#include <srook/range/adaptor/adaptor_operator.hpp>
#include <srook/range/adaptor/detail/deduce_iter.hpp>
#include <srook/iterator/range_iterators/range_iterator.hpp>
#include <srook/iterator/range_iterators/transform_iterator.hpp>
#include <srook/iterator/range_access.hpp>
#include <srook/type_traits/is_range.hpp>

SROOK_NESTED_NAMESPACE(srook, range, adaptors) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class Pred>
class range_transform {
public:
    SROOK_FORCE_INLINE SROOK_CONSTEXPR explicit range_transform(Pred pred) SROOK_NOEXCEPT(is_nothrow_constructible<Pred>::value)
        : pred_(pred) {}

    template <class Range, SROOK_REQUIRES(is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>::value)>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::range::iterator::range_iterator<srook::range::iterator::transform_iterator<Pred, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>>
    operator()(Range&& range) const
    SROOK_NOEXCEPT(
        type_traits::detail::Land<
            is_nothrow_constructible<
                srook::range::iterator::transform_iterator<Pred, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>, Pred, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type
            >,
            is_nothrow_constructible<
                srook::range::iterator::range_iterator<transform_iterator<Pred, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>>, 
                transform_iterator<Pred, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>, 
                transform_iterator<Pred, SROOK_DEDUCED_TYPENAME deduce_iter<Range>::type>
            >
        >::value
    )
    {
        using srook::range::iterator::make_range_iterator;
        using srook::range::iterator::make_transform_iterator;
        return make_range_iterator(make_transform_iterator(pred_, srook::begin(range), srook::end(range)), make_transform_iterator(pred_, srook::end(range), srook::end(range)));
    }
private:
    Pred pred_;
};

} // namespace detail

template <class Pred>
SROOK_FORCE_INLINE SROOK_CONSTEXPR detail::range_transform<SROOK_DEDUCED_TYPENAME decay<Pred>::type> transformed(Pred&& pred)
SROOK_NOEXCEPT(is_nothrow_constructible<range_transform<SROOK_DEDUCED_TYPENAME decay<Pred>::type>, Pred&&>::value)
{
    return detail::range_transform<SROOK_DEDUCED_TYPENAME decay<Pred>::type>(srook::forward<Pred>(pred));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(adaptors, range, srook)

#endif