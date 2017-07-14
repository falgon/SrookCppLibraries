// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_MINMAX_ELEMENT_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_MINMAX_ELEMENT_HPP
#include<algorithm>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

struct minmax_element_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	std::pair<typename std::decay_t<Range>::const_iterator,typename std::decay_t<Range>::const_iterator>
	operator()(Range&& r)
	{
		return std::minmax_element(r.cbegin(),r.cend());
	}
};

template<class Compare>
struct minmax_element_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr minmax_element_compare_t(Compare comp):comp_(std::move(comp)){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	std::pair<typename std::decay_t<Range>::const_iterator,typename std::decay_t<Range>::const_iterator>
	operator()(Range&& r)
	{
		return std::minmax_element(r.cbegin(),r.cend(),std::move(comp_));
	}
private:
	Compare comp_;
};

constexpr minmax_element_t minmax_element()
{
	return minmax_element_t();
}
template<class Compare>
constexpr minmax_element_compare_t<std::decay_t<Compare>> minmax_element(Compare&& comp)
{
	return minmax_element_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::minmax_element;

} // namespace pipealgo
} // namespace srook
#endif
