#ifndef INCLUDED_SROOK_RANGE_ADAPTORS_PARTIALSORT_HPP
#define INCLUDED_SROOK_RANGE_ADAPTORS_PARTIALSORT_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Iterator>
struct partial_sort_t{
	template<REQUIRES(!srook::mpl::has_iterator_v<Iterator>)>
	explicit constexpr partial_sort_t(Iterator iter):iter_(std::move(iter)){}
	
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
		std::partial_sort(r.begin(),std::move(iter_),r.end());
		return srook::make_range_iterator(r.begin(),r.end());
	}
private:
	Iterator iter_;
};


template<class Iterator,class Compare>
struct partial_sort_compare_t{
	template<REQUIRES(!srook::mpl::has_iterator_v<Iterator> && srook::is_callable_v<Compare>)>
	explicit constexpr partial_sort_compare_t(Iterator iter,Compare comp):iter_(std::move(iter)),comp_(std::move(comp)){}

	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
		std::partial_sort(r.begin(),std::move(iter_),r.end(),std::move(comp_));
		return srook::make_range_iterator(r.begin(),r.end());
	}
private:
	Iterator iter_;
	Compare comp_;
};

template<class Iterator>
constexpr partial_sort_t<std::decay_t<Iterator>> partial_sort(Iterator&& iter)
{
	return partial_sort_t<std::decay_t<Iterator>>(std::forward<Iterator>(iter));
}

template<class Iterator,class Compare>
constexpr partial_sort_compare_t<std::decay_t<Iterator>,std::decay_t<Compare>> partial_sort(Iterator&& iter,Compare&& comp)
{
	return partial_sort_compare_t<std::decay_t<Iterator>,std::decay_t<Compare>>(std::forward<Iterator>(iter),std::forward<Compare>(comp));
}

} // inline namespace v1
} // namespace detail

using detail::partial_sort;

} // namespace adaptors
} // namespace srook

#endif
