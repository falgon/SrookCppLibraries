#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_MIN_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_MIN_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/config/require.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<initializer_list>
#include<type_traits>
#include<srook/type_traits/is_callable.hpp>

#if __has_include(<boost/range/algorithm/min_element.hpp>)
#include<boost/range/algorithm/min_element.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_MIN_ELEMENT
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{


template<class T>
struct min_t{
	explicit constexpr min_t(T t):value(std::move(t)){}
	const T& operator()(const T& rhs)
	{
		return std::min(rhs,std::move(value));
	}
private:
	T value;
};

template<class T,class Compare>
struct min_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr min_compare_t(T t,Compare comp):value(std::move(t)),comp_(std::move(comp)){}
	
	const T& operator()(const T& rhs)
	{
		return std::min(rhs,std::move(value),std::move(comp_));
	}
private:
	T value;
	Compare comp_;
};

struct min_initializer_list_t{
	template<class T>
	T operator()(std::initializer_list<T> ilist)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MIN_ELEMENT
		*boost::range::min_element(std::move(ilist));
#else
		*std::min_element(ilist.begin(),ilist.end());
#endif
	}
	
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::value_type operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MIN_ELEMENT
		*boost::range::min_element(std::move(r));
#else
		*std::min_element(r.cbegin(),r.cend());
#endif
	}
};

template<class Compare>
struct min_initializer_list_compare_t{
	template<REQUIRES(is_callable_v<Compare>)>
	explicit constexpr min_initializer_list_compare_t(Compare comp):comp_(std::move(comp)){}
	
	template<class T>
	T operator()(std::initializer_list<T> ilist)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MIN_ELEMENT
		*boost::range::min_element(std::move(ilist),std::move(comp_));
#else
		*std::min_element(ilist.begin(),ilist.end(),std::move(comp_));
#endif
	}
	
	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	typename std::decay_t<Range>::value_type operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MIN_ELEMENT
		*boost::range::min_element(std::move(r),std::move(comp_));
#else
		*std::min_element(r.cbegin(),r.cend(),std::move(comp_));
#endif
	}
private:
	Compare comp_;
};

template<class T,REQUIRES(!srook::is_callable_v<std::decay_t<T>>)>
constexpr min_t<std::decay_t<T>> min(T&& t)
{
	return min_t<std::decay_t<T>>(std::forward<T>(t));
}

template<class T,class Compare,REQUIRES(srook::is_callable_v<std::decay_t<Compare>>)>
constexpr min_compare_t<std::decay_t<T>,std::decay_t<Compare>> min(T&& t,Compare&& comp)
{
	return min_compare_t<std::decay_t<T>,std::decay_t<Compare>>(std::forward<T>(t),std::forward<Compare>(comp));
}

constexpr min_initializer_list_t min()
{
	return min_initializer_list_t();
}

template<
	class Compare,
	REQUIRES( (std::is_function<std::decay_t<Compare>>::value && std::is_pointer<std::decay_t<Compare>>::value) || srook::is_callable_v<std::decay_t<Compare>> )
>
constexpr min_initializer_list_compare_t<std::decay_t<Compare>> min(Compare&& comp)
{
	return min_initializer_list_compare_t<std::decay_t<Compare>>(std::forward<Compare>(comp));
}

} // namespace v1
} // namesapce detail

using detail::min;

} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MIN_ELEMENT
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_MIN_ELEMENT
#endif
#endif
