#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_NTH_ELEMENT_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_NTH_ELEMENT_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Iterator>
struct nth_element_t{
	template<REQUIRES(!srook::mpl::has_iterator_v<Iterator>)>
	explicit constexpr nth_element_t(Iterator iter):iter_(std::move(iter)){}
	
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
		std::nth_element(r.begin(),std::move(iter_),r.end());
		return srook::make_range_iterator(r.begin(),r.end());
	}
private:
	Iterator iter_;
};

template<class Iterator,class Compare>
struct nth_element_compare_t{
	template<REQUIRES(!srook::mpl::has_iterator_v<Iterator> && srook::is_callable_v<Compare>)>
	explicit constexpr nth_element_compare_t(Iterator iter,Compare comp):iter_(std::move(iter)),comp_(std::move(comp)){}
	
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
		std::nth_element(r.begin(),std::move(iter_),r.end());
		return srook::make_range_iterator(r.begin(),r.end());
	}
private:
	Iterator iter_;
	Compare comp_;
};


template<class Iterator>
constexpr nth_element_t<std::decay_t<Iterator>> nth_element(Iterator&& iter)
{
	return nth_element_t<std::decay_t<Iterator>>(std::forward<Iterator>(iter));
}

template<class Iterator,class Compare>
constexpr nth_element_compare_t<std::decay_t<Iterator>,std::decay_t<Compare>> nth_element(Iterator iter,Compare comp)
{
	return nth_element_compare_t<std::decay_t<Iterator>,std::decay_t<Compare>>(std::forward<Iterator>(iter),std::forward<Compare>(comp));
}


} // inline namespace v1
} // namespace detail

using detail::nth_element;

} // namespace adaptors
} // namespace srook

#endif
