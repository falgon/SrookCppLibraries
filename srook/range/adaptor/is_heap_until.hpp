#ifndef INCLUDED_SROOK_RANGE_ADAPTORS_IS_HEAP_UNTIL_HPP
#define INCLUDED_SROOK_RANGE_ADAPTORS_IS_HEAP_UNTIL_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct is_heap_until_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::const_iterator operator()(Range&& r)
	{
		return
		std::is_heap_until(r.cbegin(),r.cend());
	}
};

template<class Compare>
struct is_heap_until_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr is_heap_until_compare_t(Compare comp):comp_(std::move(comp)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::iterator operator()(Range&& r)
	{
		return
		std::is_heap_until(r.cbegin(),r.cend(),std::move(comp_));
	}
private:
	Compare comp_;
};

constexpr is_heap_until_t is_heap_until()
{
	return is_heap_until_t();
}

template<class Compare>
constexpr is_heap_until_compare_t<std::decay_t<Compare>> is_heap_until(Compare&& comp)
{
	return is_heap_until_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::is_heap_until;

} // namespace adaptors
} // namesapce srook

#endif
