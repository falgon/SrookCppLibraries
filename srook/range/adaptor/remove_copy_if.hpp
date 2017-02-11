#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_REMOVE_COPY_IF_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_REMOVE_COPY_IF_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#if __has_include(<boost/range/algorithm/remove_copy_if.hpp>)
#include<boost/range/algorithm/remove_copy_if.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_REMOVE_COPY_IF
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Iterator,class Predicate>
struct remove_copy_if_iterator{
	template<REQUIRES(!has_iterator_v<Iterator> && is_callable_v<Predicate>)>
	explicit constexpr remove_copy_if_iterator(Iterator iter,Predicate pred)
		:iter_(std::move(iter)),pred_(std::move(pred)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	Iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_REMOVE_COPY_IF
		boost::remove_copy_if(std::forward<Range>(r),std::move(iter_),std::move(pred_));
#else
		std::remove_copy_if(r.begin(),r.end(),std::move(iter_),std::move(pred_));
#endif
	}
private:
	Iterator iter_;
	Predicate pred_;
};

template<class Iterator,class Predicate,REQUIRES(!has_iterator_v<std::decay_t<Iterator>> && is_callable_v<std::decay_t<Predicate>>)>
constexpr remove_copy_if_iterator<std::decay_t<Iterator>,std::decay_t<Predicate>>
remove_copy_if(Iterator&& iter,Predicate&& pred)
{
	return remove_copy_if_iterator<std::decay_t<Iterator>,std::decay_t<Predicate>>(std::forward<Iterator>(iter),std::forward<Predicate>(pred));
}

template<
	class Range,
	class Predicate,
	REQUIRES((has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>) && is_callable_v<std::decay_t<Predicate>>)
>
constexpr remove_copy_if_iterator<typename std::decay_t<Range>::iterator,std::decay_t<Predicate>>
remove_copy_if(Range&& r,Predicate&& pred)
{
	return remove_copy_if_iterator<typename std::decay_t<Range>::iterator,std::decay_t<Predicate>>(r.begin(),std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::remove_copy_if;

} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_REMOVE_COPY_IF
#undef POSSIBLE_TO_INCLUDE_BOOST_REMOVE_COPY_IF
#endif
#endif
