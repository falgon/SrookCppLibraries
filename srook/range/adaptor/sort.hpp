#ifndef INCLUDED_SROOK_ADAPTOR_SORT_HPP
#define INCLUDED_SROOK_ADAPTOR_SORT_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/algorithm/sort.hpp>)
#define POSSIBLE_TO_BOOST_RANGE_SORT
#include<boost/range/algorithm/sort.hpp>
#elif
#include<algorithm>
#endif
namespace srook{
namespace adaptors{
inline namespace v1{

template<class Compare>
struct sort_t_comp{
	explicit constexpr sort_t_comp(const Compare& comp):comp_(comp){}
	explicit constexpr sort_t_comp(Compare&& comp):comp_(std::move(comp)){}
	template<class Range>
	srook::range_iterator<std::decay_t<Range>> operator()(Range&& r)
	{
#ifdef INCLUDED_SROOK_ADAPTOR_BINARY_SEARCH_HPP
		boost::sort(r,std::move(comp_));
#elif
		std::sort(r.cbegin(),r.cend(),std::move(comp_));
#endif
		return make_range_iterator(r.cbegin(),r.cend());
	}
private:
	Compare comp_;
};
template<class Compare>
constexpr sort_t_comp<std::decay_t<Compare>> sort(Compare&& comp)
{
	return sort_t_comp<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

struct sort_t{
	template<class Range>
	srook::range_iterator<typename std::decay_t<Range>::const_iterator> operator()(Range&& r)
	{
#ifdef INCLUDED_SROOK_ADAPTOR_BINARY_SEARCH_HPP
		boost::sort(r);
#elif
		std::sort(r.cbegin(),r.cend());
#endif
		return make_range_iterator(r.cbegin(),r.cend());
	}
};
constexpr sort_t sort()
{
	return sort_t();
}

} // inline namespace v1
} // namespace adaptors
} // namespace srook
#ifdef POSSIBLE_TO_BOOST_RANGE_BINARY_SEARCH
#undef POSSIBLE_TO_BOOST_RANGE_BINARY_SEARCH
#endif
#endif
