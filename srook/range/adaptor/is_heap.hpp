#ifndef SROOK_INCLUDED_RANGE_ADAPTOR_IS_HEAP
#define SROOK_INCLUDED_RANGE_ADAPTOR_IS_HEAP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct is_heap_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return std::is_heap(r.cbegin(),r.cend());
	}
};

template<class Compare>
struct is_heap_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr is_heap_compare_t(Compare comp):comp_(std::move(comp)){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
		return std::is_heap(r.cbegin(),r.cend(),std::move(comp_));
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
