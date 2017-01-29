#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_LOWER_BOUND_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_LOWER_BOUND_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/config/require.hpp>
#if __has_include(<boost/range/algorithm/lower_bound.hpp>)
#include<boost/range/algorithm/lower_bound.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_LOWER_BOUND
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class T>
struct lower_bound_t{
	explicit constexpr lower_bound_t(T t):value(std::move(t)){}
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_LOWER_BOUND
		boost::range::lower_bound(std::forward<Range>(r),std::move(value));
#else
		std::lower_bound(r.cbegin(),r.cend(),std::move(value));
#endif
	}
private:
	T value;
};


template<class T,class Compare>
struct lower_bound_compare_t{
	explicit constexpr lower_bound_compare_t(T t,Compare comp):value(std::move(t)),comp_(std::move(comp)){}
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_LOWER_BOUND
		boost::range::lower_bound(std::forward<Range>(r),std::move(value),std::move(comp_));
#else
		std::lower_bound(r.cbegin(),r.cend(),std::move(value),std::move(comp_));
#endif
	}
private:
	T value;
	Compare comp_;
};

template<class T>
constexpr lower_bound_t<std::decay_t<T>> lower_bound(T&& t)
{
	return lower_bound_t<std::decay_t<T>>(std::forward<T>(t));
}

template<class T,class Compare>
constexpr lower_bound_compare_t<std::decay_t<T>,std::decay_t<Compare>> lower_bound(T&& t,Compare&& comp)
{
	return lower_bound_compare_t<std::decay_t<T>,std::decay_t<Compare>>(std::forward<T>(t),std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::lower_bound;

} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_LOWER_BOUND
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_LOWER_BOUND
#endif
#endif
