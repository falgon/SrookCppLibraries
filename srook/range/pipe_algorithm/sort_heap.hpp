#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_SORT_HEAP_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_SORT_HEAP_HPP
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

struct sort_heap_t{
	template<
		class Range,
		REQUIRES(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	Range&& operator()(Range&& r)
	{
		std::sort_heap(r.begin(),r.end());
		return std::forward<Range>(r);
	}
};

template<class Compare>
struct sort_heap_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr sort_heap_compare_t(Compare comp):comp_(std::move(comp)){}
	template<
		class Range,
		REQUIRES(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	Range&& operator()(Range&& r)
	{
		std::sort_heap(r.begin(),r.end(),std::move(comp_));
		return std::forward<Range>(r);
	}
private:
	Compare comp_;
};

constexpr sort_heap_t sort_heap(){return sort_heap_t();}

template<class Compare,REQUIRES(is_callable_v<std::remove_reference_t<std::remove_cv_t<Compare>>>)>
constexpr sort_heap_compare_t<std::remove_reference_t<std::remove_cv_t<Compare>>>
sort_heap(Compare&& comp)
{
	return sort_heap_compare_t<std::remove_reference_t<std::remove_cv_t<Compare>>>(std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::sort_heap;

} // namespace pipealgo
} // namespace srook

#endif
