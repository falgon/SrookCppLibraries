#ifndef INCLUDED_SROOK_ADAPTOR_SORT_HPP
#define INCLUDED_SROOK_ADAPTOR_SORT_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<list>
#if __has_include(<boost/range/algorithm/sort.hpp>)
#define POSSIBLE_TO_BOOST_RANGE_SORT
#include<boost/range/algorithm/sort.hpp>
#else
#include<algorithm>
#endif
namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Compare>
struct sort_t_comp{
	explicit constexpr sort_t_comp(const Compare& comp):comp_(comp){}
	explicit constexpr sort_t_comp(Compare&& comp):comp_(std::move(comp)){}
	template<class Range>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
#ifdef INCLUDED_SROOK_ADAPTOR_BINARY_SEARCH_HPP
		boost::sort(r,std::move(comp_));
#else
		std::sort(r.begin(),r.end(),std::move(comp_));
#endif
		return srook::make_range_iterator(r.begin(),r.end());
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
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
#ifdef INCLUDED_SROOK_ADAPTOR_BINARY_SEARCH_HPP
		boost::sort(r);
#else
		std::sort(r.begin(),r.end());
#endif
		return srook::make_range_iterator(r.begin(),r.end());
	}
	template<class T>
	srook::range_iterator<typename std::list<T>::iterator> operator()(const std::list<T>& r)
	{
		r.sort();
		return srook::make_range_iterator(r.begin(),r.end());
	}
};
constexpr sort_t sort()
{
	return sort_t();
}

} // inline namespace v1
} // namespace detail

using detail::sort;

} // namespace adaptors
} // namespace srook
#ifdef POSSIBLE_TO_BOOST_RANGE_BINARY_SEARCH
#undef POSSIBLE_TO_BOOST_RANGE_BINARY_SEARCH
#endif
#endif
