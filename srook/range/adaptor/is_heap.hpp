#ifndef SROOK_INCLUDED_RANGE_ADAPTOR_IS_HEAP
#define SROOK_INCLUDED_RANGE_ADAPTOR_IS_HEAP
#include<srook/range/adaptor/adaptor_operator.hpp>
#if __has_include(<boost/range/algorithm/is_heap.hpp>)
#include<boost/range/algorithm/is_heap.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_ALGORITHM_IS_HEAP
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct is_heap_t{
	template<class Range>
	bool operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_ALGORITHM_IS_HEAP
		return boost::range::is_heap(std::forward<Range>(r));
#else
		return std::is_heap(r.cbegin(),r.cend());
#endif
	}
};

template<class Compare>
struct is_heap_compare_t{
	explicit constexpr is_heap_compare_t(Compare comp):comp_(std::move(comp)){}

	template<class Range>
	bool operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_ALGORITHM_IS_HEAP
		return boost::range::is_heap(std::forward<Range>(r),std::move(comp_));
#else
		return std::is_heap(r.cbegin(),r.cend(),std::move(comp_));
#endif
	}
private:
	Compare comp_;
};

constexpr is_heap_t is_heap()
{
	return is_heap_t();
}

template<class Compare>
constexpr is_heap_compare_t<std::decay_t<Compare>> is_heap(Compare&& comp)
{
	return is_heap_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline namesapce v1
} // namespace detail

using detail::is_heap;

} // namesapce adaptors
} // namespace srook

#endif
