#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_IS_SORTED_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_IS_SORTED_HPP
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/range/adaptor/adaptor_operator.hpp>
#if __has_include(<boost/range/algorithm_ext/is_sorted.hpp>)
#include<boost/range/algorithm_ext/is_sorted.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_IS_SORTED
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct is_sorted_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_IS_SORTED
		boost::range::is_sorted(std::forward<Range>(r));
#else
		std::is_sorted(r.cbegin(),r.cend());
#endif
	}
};

template<class Compare>
struct is_sorted_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr is_sorted_compare_t(const Compare& comp):comp_(comp){}
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr is_sorted_compare_t(Compare&& comp):comp_(std::move(comp)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return 
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_IS_SORTED
		boost::range::is_sorted(std::forward<Range>(r),std::move(comp_));
#else
		std::is_sorted(r.cbegin(),r.cend(),std::move(comp_));
#endif
	}
private:
	Compare comp_;
};

constexpr is_sorted_t is_sorted()
{
	return is_sorted_t();
}

template<class Compare>
constexpr is_sorted_compare_t<std::decay_t<Compare>> is_sorted(Compare&& comp)
{
	return is_sorted_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::is_sorted;

} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_IS_SORTED
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_IS_SORTED
#endif
#endif
