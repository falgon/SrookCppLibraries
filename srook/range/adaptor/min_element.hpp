#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_MIN_ELEMENT_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_MIN_ELEMENT_HPP
#include<srook/mpl/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/adaptor/min_element.hpp>)
#include<boost/range/adaptor/min_element.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_MIN_ELEMENT
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct min_element_t{
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_MIN_ELEMENT
		boost::range::min_element(std::forward<Range>(r));
#else
		std::min_element(r.cbegin(),r.cend());
#endif
	}
};

template<class Compare>
struct min_element_compare_t{
	template<REQUIRES(srook::is_callable_v<Compare>)>
	explicit constexpr min_element_compare_t(Compare comp):comp_(std::move(comp)){}

	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_MIN_ELEMENT
		boost::range::min_element(std::forward<Range>(r),std::move(comp_));
#else
		std::min_element(r.cbegin(),r.cend(),std::move(comp_));
#endif
	}
private:
	Compare comp_;
};

constexpr min_element_t min_element()
{
	return min_element_t();
}
template<class Compare>
constexpr min_element_compare_t<std::decay_t<Compare>> min_element(Compare&& comp)
{
	return min_element_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline nmaespace v1
} // namesapce detail

using detail::min_element;

} // namesapce adaptors
} // namesapce srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_MIN_ELEMENT
#undef POSSIBLE_TO_INCLUDE_BOOST_MIN_ELEMENT
#endif
#endif
