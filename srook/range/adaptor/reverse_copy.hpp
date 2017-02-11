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
struct reversed_copied_range_t{
	explicit constexpr reversed_copied_range_t(Iterator first,Iterator last)
		:first_(std::move(first)),last_(std::move(last)){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	operator Range()
	{
		return Range(std::make_reverse_iterator(std::move(last_)),std::make_reverse_iterator(std::move(first_)));
	}
private:
	Iterator first_,last_;
};

template<class Iterator>
constexpr reversed_copied_range_t<std::decay_t<Iterator>> make_reversed_copied_t(Iterator&& first,Iterator&& last)
{
	return reversed_copied_range_t<std::decay_t<Iterator>>(std::forward<Iterator>(first),std::forward<Iterator>(last));
}

const struct reversed_copied_t{
	template<class Range>
	constexpr reversed_copied_range_t<typename std::decay_t<Range>::iterator> operator()(Range&& r)const
	{
		return reversed_copied_range_t<typename std::decay_t<Range>::iterator>(r.begin(),r.end());
	}
}reversed_copied={};

template<class Iterator>
struct reverse_copy_t{
	template<REQUIRES(!has_iterator_v<Iterator>)>
	explicit constexpr reverse_copy_t(Iterator iter):iter_(std::move(iter)){}

	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	Iterator operator()(Range&& r)
	{
		return
#ifdef POSSIBLE_TO_INCLUDE_BOOST_REVERSE_COPY
		boost::range::reverse_copy(std::forward<Range>(r),std::move(iter_));
#else
		std::reverse_copy(r.begin(),r.end(),std::move(iter_));
#endif
	}
private:
	Iterator iter_;
};

template<class Iterator,REQUIRES(!has_iterator_v<std::decay_t<Iterator>>)>
constexpr reverse_copy_t<std::decay_t<Iterator>> reverse_copy(Iterator&& iter)
{
	return reverse_copy_t<std::decay_t<Iterator>>(std::forward<Iterator>(iter));
}

template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>>)>
constexpr reverse_copy_t<typename std::decay_t<Range>::iterator> reverse_copy(Range&& r)
{
	return reverse_copy_t<typename std::decay_t<Range>::iterator>(r.begin());
}

} // inline namespace v1
} // namespace detail

using detail::reversed_copied;
using detail::reverse_copy;

} // namespace adaptors
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_REVERSE_COPY
#undef POSSIBLE_TO_INCLUDE_BOOST_REVERSE_COPY
#endif
#endif
