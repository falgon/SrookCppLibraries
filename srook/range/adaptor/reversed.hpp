// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REVERSED_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REVERSED_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

const struct reversed_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	constexpr range_iterator<std::reverse_iterator<typename std::decay_t<Range>::iterator>>
	operator()(Range&& r)const
	{
		return make_range_iterator(std::make_reverse_iterator(r.end()),std::make_reverse_iterator(r.begin()));
	}
}reversed={};

} // inline namespace v1
} // namespace detail

using detail::reversed;

} // namespace adaptors
} // namesapce srook

#endif
