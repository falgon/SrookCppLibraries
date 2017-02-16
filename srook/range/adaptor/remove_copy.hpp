#ifndef INCLUDED_SROOK_RANGE_ADAPTORS_REMOVE_COPY_HPP
#define INCLUDED_SROOK_RANGE_ADAPTORS_REMOVE_COPY_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#if __has_include(<boost/range/algorithm/remove_copy.hpp>)
#include<boost/range/algorithm/remove_copy.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_RANGE_REMOVE_COPY
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class OutputIterator,class T>
struct remove_copy_iterator_t{
	template<REQUIRES(!has_iterator_v<OutputIterator>)>
	explicit constexpr remove_copy_iterator_t(OutputIterator iter,const T& t)
		:iter_(std::move(iter)),value_(t){}

	template<
		class Range,
		REQUIRES(
				(has_iterator_v<std::decay_t<Range>> or 
				 is_range_iterator_v<std::decay_t<Range>>)
		)
	>
	OutputIterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_REMOVE_COPY		
		boost::range::remove_copy(std::forward<Range>(r),std::move(iter_),value_);
#else
		std::remove_copy(std::begin(r),std::end(r),std::move(iter_),value_);
#endif
	}
private:
	OutputIterator iter_;
	const T& value_;
};

template<class Range,class T>
struct remove_copy_range_t{
	template<
		REQUIRES(has_iterator_v<Range> or is_range_iterator_v<Range>)
	>
	explicit constexpr remove_copy_range_t(Range& r,const T& t)
		:first_(std::begin(r)),value_(t){}

	template<
		class R,
		REQUIRES(
				has_iterator_v<std::decay_t<R>> || 
				is_range_iterator_v<std::decay_t<R>>
		)
	>
	typename std::remove_reference_t<Range>::iterator operator()(R&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_REMOVE_COPY
		boost::range::remove_copy(std::forward<R>(r),std::move(first_),value_);
#else
		std::remove_copy(std::begin(r),std::end(r),std::move(first_),value_);
#endif
	}
private:
	typename std::remove_reference_t<Range>::iterator first_;
	const T& value_;
};

template<
	class OutputIterator,
	class T,
	REQUIRES(!has_iterator_v<std::remove_cv_t<std::decay_t<OutputIterator>>>)
>
constexpr remove_copy_iterator_t<
	std::remove_cv_t<std::decay_t<OutputIterator>>,
	std::remove_cv_t<std::decay_t<T>>
>
remove_copy(OutputIterator&& iter,T&& value)
{
	return remove_copy_iterator_t<
		std::remove_cv_t<std::decay_t<OutputIterator>>,
		std::remove_cv_t<std::decay_t<T>>
	>(std::forward<OutputIterator>(iter),std::forward<T>(value));
}

template<
	class Range,
	class T,
	REQUIRES(
			has_iterator_v<std::decay_t<Range>> || 
			is_range_iterator_v<std::decay_t<Range>>
	)
>
constexpr remove_copy_range_t<
	std::remove_cv_t<std::decay_t<Range>>,
	std::remove_cv_t<std::decay_t<T>>
>
remove_copy(Range&& r,T&& value)
{
	return remove_copy_range_t<
		std::remove_cv_t<std::decay_t<Range>>,
		std::remove_cv_t<std::decay_t<T>>
	>(std::forward<Range>(r),std::forward<T>(value));
}


} // inline namesapce v1
} // namespace detail

using detail::remove_copy;

} // namespace adaptors
} // namespace srook

#endif
