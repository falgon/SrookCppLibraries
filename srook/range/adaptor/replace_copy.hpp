#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REPLACE_COPY
#define INCLUDED_SROOK_RANGE_ADAPTOR_REPLACE_COPY
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#if __has_include(<boost/range/algorithm/replace_copy.hpp>)
#include<boost/range/algorithm/replace_copy.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_ALGORITHM_REPLACE_COPY
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class OutputIterator,class T>
struct replace_copy_t{
	template<REQUIRES(!has_iterator_v<OutputIterator>)>
	explicit constexpr replace_copy_t(OutputIterator iter,const T& old_value,const T& new_value)
		:iter_(std::move(iter)),old_value_(old_value),new_value_(new_value){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	OutputIterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_ALGORITHM_REPLACE_COPY
		boost::range::replace_copy(std::forward<Range>(r),std::move(iter_),old_value_,new_value_);
#else
		std::replace_copy(r.begin(),r.end(),std::move(iter_),old_value_,new_value_);
#endif
	}
private:
	OutputIterator iter_;
	const T& old_value_,new_value_;
};

template<class OutputIterator,class T,REQUIRES(!has_iterator_v<std::decay_t<OutputIterator>>)>
constexpr replace_copy_t<std::decay_t<OutputIterator>,std::decay_t<T>>
replace_copy(OutputIterator&& iter,T&& old_value,T&& new_value)
{
	return replace_copy_t<
		std::decay_t<OutputIterator>,
		std::decay_t<T>
	>(std::forward<OutputIterator>(iter),std::forward<T>(old_value),std::forward<T>(new_value));
}

template<class Range,class T,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
constexpr replace_copy_t<typename std::decay_t<Range>::iterator,std::decay_t<T>>
replace_copy(Range&& r,T&& old_value,T&& new_value)
{
	return replace_copy_t<
		typename std::decay_t<Range>::iterator,
		std::decay_t<T>
	>(r.begin(),std::forward<T>(old_value),std::forward<T>(new_value));
}

} // inline nameespace v1
} // namespace detail

using detail::replace_copy;

} // namespace adaptors
} // namespace srook 

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_ALGORITHM_REPLACE_COPY
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_ALGORITHM_REPLACE_COPY
#endif
#endif
