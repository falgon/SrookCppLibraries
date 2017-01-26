#ifndef INCLUDED_SROOK_ADAPTOR_MAKE_HEAP
#define INCLUDED_SROOK_ADAPTOR_MAKE_HEAP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/range/algorithm/make_heap.hpp>)
#include<boost/range/algorithm/make_heap.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAKE_HEAP
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct make_heap_t{
	template<class Range>
	srook::range_iterator<typename std::decay_t<Range>::const_iterator> operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAKE_HEAP
		boost::range::make_heap(std::forward<Range>(r));
#else
		std::make_heap(r.begin(),r.end());
#endif
		return srook::make_range_iterator(r.cbegin(),r.cend());
	}
};

template<class Compare>
struct make_heap_compare_t{
	explicit constexpr make_heap_compare_t(Compare comp):comp_(std::move(comp)){}

	template<class Range>
	srook::range_iterator<typename std::decay_t<Range>::const_iterator> operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAKE_HEAP
		boost::range::make_heap(std::forward<Range>(r),std::move(comp_));
#else
		std::make_heap(r.begin(),r.end(),std::move(comp_));
#endif
		return srook::make_range_iterator(r.cbegin(),r.cend());
	}
private:
	Compare comp_;
};

constexpr make_heap_t make_heap()
{
	return make_heap_t();
}

template<class Comp>
constexpr make_heap_compare_t<std::decay_t<Comp>> make_heap(Comp&& comp)
{
	return make_heap_compare_t<std::decay_t<Comp>>(std::forward<Comp>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::make_heap;

} // namespace adaptors
} // namesapce srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAKE_HEAP
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MAKE_HEAP
#endif
#endif
