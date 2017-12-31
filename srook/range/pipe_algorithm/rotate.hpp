// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_HPP
#include<srook/config/require.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class ForwardIterator>
struct rotate_t{
	template<REQUIRES(!has_iterator_v<ForwardIterator>)>
	explicit constexpr rotate_t(ForwardIterator iter):middle(std::move(iter)){}
	
	template<
		class Range,
		REQUIRES(
				!has_iterator_v<ForwardIterator>
				and
				(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				 is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
		)
	>
	ForwardIterator operator()(Range&& r)
	{
		return std::rotate(r.begin(),std::move(middle),r.end());
	}
private:
	ForwardIterator middle;
};

template<
	class ForwardIterator,
	REQUIRES(!has_iterator_v<std::remove_reference_t<std::remove_cv_t<ForwardIterator>>>)
>
constexpr rotate_t<std::remove_reference_t<std::remove_cv_t<ForwardIterator>>>
rotate(ForwardIterator&& iter)
{
	return rotate_t<
		std::remove_reference_t<std::remove_cv_t<ForwardIterator>>
	>(std::forward<ForwardIterator>(iter));
}

} // inline namespace v1
} // namespace detail

using detail::rotate;

} // namespace pipealgo
} // namespace srook

#endif
