// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REVERSED_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REVERSED_HPP
#include <srook/config.hpp>
#include <srook/range/adaptor/adaptor_operator.hpp>
#include <srook/iterator/range_iterators/range_iterator.hpp>
#include <srook/type_traits/is_range.hpp>
#include <srook/type_traits/decay.hpp>
#include <iterator>

SROOK_NESTED_NAMESPACE(srook, range, adaptors) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

const struct reversed_t{
	template<class Range, SROOK_REQUIRES(is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>::value)>
	SROOK_FORCE_INLINE SROOK_CONSTEXPR srook::range::iterator::range_iterator<std::reverse_iterator<SROOK_DEDUCED_TYPENAME decay<Range>::type::iterator>>
	operator()(Range&& r) const SROOK_NOEXCEPT(make_range_iterator(std::make_reverse_iterator(r.end()), std::make_reverse_iterator(r.begin())))
	{
		return srook::range::iterator::make_range_iterator(std::make_reverse_iterator(r.end()), std::make_reverse_iterator(r.begin()));
	}
} reversed = {};

} // namespace detail

using detail::reversed;

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(adaptors, range, srook)
#endif
