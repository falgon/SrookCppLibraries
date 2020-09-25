// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_MOVED
#define INCLUDED_SROOK_RANGE_ADAPTOR_MOVED
#include <srook/config.hpp>
#include <srook/range/adaptor/adaptor_operator.hpp>
#include <srook/type_traits/is_range.hpp>
#include <srook/type_traits/iterator/is_iterator.hpp>
#include <srook/type_traits/is_nothrow_constructible.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/iterator/range_access/begin_end.hpp>
#include <srook/utility/forward.hpp>
#include <iterator>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
SROOK_NESTED_NAMESPACE(srook, range, adaptors) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail{

template<class Iterator>
struct moved_t_impl {
    SROOK_ST_ASSERT(is_iterator<Iterator>::value);
	SROOK_CONSTEXPR moved_t_impl(Iterator first, Iterator last)
		:first_(std::move(first)), last_(std::move(last)){}
	
	template<class Range, SROOK_REQUIRES(is_range<Range>::value)>
	SROOK_FORCE_INLINE SROOK_CONSTEXPR operator Range() const
    SROOK_NOEXCEPT(is_nothrow_constructible<Range, std::move_iterator<Iterator>, std::move_iterator<Iterator>>::value)
	{
		return Range(std::make_move_iterator(first_), std::make_move_iterator(last_));
	}
private:
	Iterator first_, last_;
};

template<class Iterator>
SROOK_CONSTEXPR moved_t_impl<SROOK_DEDUCED_TYPENAME decay<Iterator>::type> 
make_moved(Iterator&& first,Iterator&& last)
SROOK_NOEXCEPT(moved_t_impl<SROOK_DEDUCED_TYPENAME decay<Iterator>::type>(srook::forward<Iterator>(first), srook::forward<Iterator>(last)))
{
	return moved_t_impl<SROOK_DEDUCED_TYPENAME decay<Iterator>::type>(srook::forward<Iterator>(first), srook::forward<Iterator>(last));
}

const struct moved_t {
    template <class Range, SROOK_REQUIRES(is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>::value)>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE moved_t_impl<SROOK_DEDUCED_TYPENAME decay<Range>::type::iterator> 
    operator()(Range&& range) const SROOK_NOEXCEPT(make_moved(srook::begin(range), srook::end(range)))
    {
        return make_moved(srook::begin(range), srook::end(range));
    }
} moved = {};

} // namespace detail

using detail::moved;

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(adaptors, range, srook)

#else
#   error This feature is only supported C++11 or later.
#endif
#endif
