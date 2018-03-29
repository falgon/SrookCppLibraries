// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ALGORITHM_REVERSED_COPIED_HPP
#define INCLUDED_SROOK_RANGE_ALGORITHM_REVERSED_COPIED_HPP
#include<srook/iterator/range_iterators/range_iterator.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<iterator>
#include<algorithm>

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
	template<class Range,REQUIRES(std::is_const<std::remove_reference_t<Range>>::value)>
	constexpr reversed_copied_range_t<typename std::remove_cv_t<std::decay_t<Range>>::const_iterator>
	operator()(Range&& r)const
	{
		return reversed_copied_range_t<
			typename std::remove_cv_t<std::decay_t<Range>>::const_iterator
		>(std::begin(r),std::end(r));
	}

	template<class Range,REQUIRES(!std::is_const<std::remove_reference_t<Range>>::value)>
	constexpr reversed_copied_range_t<typename std::remove_cv_t<std::remove_reference_t<Range>>::iterator>
	operator()(Range&& r)const
	{
		return reversed_copied_range_t<
			typename std::remove_cv_t<std::remove_reference_t<Range>>::iterator
		>(std::begin(r),std::end(r));
	}
}reversed_copied={};

} // inline namespace v1
} // namespace detail

using detail::reversed_copied;

} // namespace adaptors
} // namespace srook

#endif
