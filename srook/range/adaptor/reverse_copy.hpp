#ifndef INCLUDED_SROOK_RANGE_ALGORITHM_REVERSE_COPY_HPP
#define INCLUDED_SROOK_RANGE_ALGORITHM_REVERSE_COPY_HPP
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>
#if __has_include(<boost/range/algorithm/reverse_copy.hpp>)
#include<boost/range/algorithm/reverse_copy.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_REVERSE_COPY
#else
#include<algorithm>
#endif

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Iterator>
struct reverse_copy_t{
	template<REQUIRES(!has_iterator_v<Iterator>)>
	explicit constexpr reverse_copy_t(Iterator iter):iter_(std::move(iter)){}

	template<
		class Range,
		REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)
	>
	Iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_REVERSE_COPY
		boost::range::reverse_copy(std::forward<Range>(r),std::move(iter_));
#else
		std::reverse_copy(std::begin(r),std::end(r),std::move(iter_));
#endif
	}
private:
	Iterator iter_;
};

template<
	class Iterator,
	REQUIRES(!has_iterator_v<std::decay_t<Iterator>>)
>
constexpr reverse_copy_t<std::decay_t<Iterator>> reverse_copy(Iterator&& iter)
{
	return reverse_copy_t<std::decay_t<Iterator>>(std::forward<Iterator>(iter));
}

template<
	class Range,
	REQUIRES(
			(has_iterator_v<std::remove_cv_t<std::decay_t<Range>>> or 
			 is_range_iterator_v<std::remove_cv_t<Range>>) and
			!std::is_const<std::remove_reference_t<Range>>::value
	)
>
constexpr reverse_copy_t<
	typename std::remove_cv_t<std::decay_t<Range>>::iterator
> reverse_copy(Range&& r)
{
	return reverse_copy_t<
		typename std::remove_cv_t<std::decay_t<Range>>::iterator
	>(std::begin(r));
}

} // inline namespace v1
} // namespace detail

using detail::reverse_copy;

} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_REVERSE_COPY
#undef POSSIBLE_TO_INCLUDE_BOOST_REVERSE_COPY
#endif
#endif
