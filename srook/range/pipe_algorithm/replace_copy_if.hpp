#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REPLACE_COPY_IF_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REPLACE_COPY_IF_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#if __has_include(<boost/range/algorithm/replace_copy_if.hpp>)
#include<boost/range/algorithm/replace_copy_if.hpp>
#define POSSIBLE_TO_BOOST_RANGE_ALGORITHM_REPLACE_COPY_IF
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class OutputIterator,class Predicate,class T>
struct replace_copy_if_t{
	template<REQUIRES(!has_iterator_v<OutputIterator> && is_callable_v<Predicate>)>
	explicit constexpr replace_copy_if_t(OutputIterator iter,Predicate pred,const T& new_value)
		:iter_(std::move(iter)),pred_(std::move(pred)),new_value_(new_value){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	OutputIterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_BOOST_RANGE_ALGORITHM_REPLACE_COPY_IF
		boost::range::replace_copy_if(std::forward<Range>(r),std::move(iter_),std::move(pred_),new_value_);
#else
		std::replace_copy_if(r.begin(),r.end(),std::move(iter_),std::move(pred_),new_value_);
#endif
	}
private:
	OutputIterator iter_;
	Predicate pred_;
	const T& new_value_;
};

template<class OutputIterator,class Predicate,class T,REQUIRES(!has_iterator_v<std::decay_t<OutputIterator>> && is_callable_v<std::decay_t<Predicate>>)>
constexpr replace_copy_if_t<std::decay_t<OutputIterator>,std::decay_t<Predicate>,std::decay_t<T>>
replace_copy_if(OutputIterator&& iter,Predicate&& pred,T&& new_value)
{
	return replace_copy_if_t<
		std::decay_t<OutputIterator>,
		std::decay_t<Predicate>,
		std::decay_t<T>
	>(std::forward<OutputIterator>(iter),std::forward<Predicate>(pred),std::forward<T>(new_value));
}

template<class Range,class Predicate,class T,REQUIRES(has_iterator_v<std::decay_t<Range>> && is_callable_v<std::decay_t<Predicate>>)>
constexpr replace_copy_if_t<typename std::decay_t<Range>::iterator,std::decay_t<Predicate>,std::decay_t<T>>
replace_copy_if(Range&& r,Predicate&& pred,T&& new_value)
{
	return replace_copy_if_t<
		typename std::decay_t<Range>::iterator,
		std::decay_t<Predicate>,
		std::decay_t<T>
	>(r.begin(),std::forward<Predicate>(pred),std::forward<T>(new_value));
}

} // inline namespace v1
} // namespace detail

using detail::replace_copy_if;

} // namesapce pipealgo
} // namespace srook

#endif
