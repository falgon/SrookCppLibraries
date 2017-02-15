#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_POP_HEAP_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_POP_HEAP_HPP
#include<algorithm>
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

struct pop_heap_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
		std::pop_heap(r.begin(),r.end());
		return srook::make_range_iterator(r.begin(),r.end());
	}
};

template<class Compare>
struct pop_heap_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr pop_heap_compare_t(Compare comp):comp_(std::move(comp)){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
		std::pop_heap(r.begin(),r.end(),std::move(comp_));
		return srook::make_range_iterator(r.begin(),r.end());
	}
private:
	Compare comp_;
};

constexpr pop_heap_t pop_heap()
{
	return pop_heap_t();
}

template<class Compare>
constexpr pop_heap_compare_t<std::decay_t<Compare>> pop_heap(Compare&& comp)
{
	return pop_heap_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}


} // inline namespace v1
} // namespace detail

using detail::pop_heap;

} // namespace adaptors
} // namespace srook

#endif
