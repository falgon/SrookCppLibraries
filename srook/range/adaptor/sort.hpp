#ifndef INCLUDED_SROOK_ADAPTOR_SORT_HPP
#define INCLUDED_SROOK_ADAPTOR_SORT_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<list>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<algorithm>
namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Compare>
struct sort_t_comp{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr sort_t_comp(const Compare& comp):comp_(comp){}
	
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr sort_t_comp(Compare&& comp):comp_(std::move(comp)){}
	
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
		std::sort(r.begin(),r.end(),std::move(comp_));
		return srook::make_range_iterator(r.begin(),r.end());
	}
private:
	Compare comp_;
};
template<class Compare>
constexpr sort_t_comp<std::decay_t<Compare>> sort(Compare&& comp)
{
	return sort_t_comp<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

struct sort_t{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
		std::sort(r.begin(),r.end());
		return srook::make_range_iterator(r.begin(),r.end());
	}
	template<class T>
	srook::range_iterator<typename std::list<T>::iterator> operator()(const std::list<T>& r)
	{
		r.sort();
		return srook::make_range_iterator(r.begin(),r.end());
	}
};
constexpr sort_t sort()
{
	return sort_t();
}

} // inline namespace v1
} // namespace detail

using detail::sort;

} // namespace adaptors
} // namespace srook
#endif
