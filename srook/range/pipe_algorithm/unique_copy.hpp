// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_UNIQUE_COPY_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_UNIQUE_COPY_HPP
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class OutputIterator>
struct unique_copy_t{
	template<
		REQUIRES(
				!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
		)
	>
	explicit unique_copy_t(OutputIterator iter):oiter_(std::move(iter)){}


	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	OutputIterator operator()(Range&& r)
	{
		return std::unique_copy(r.begin(),r.end(),std::move(oiter_));
	}
private:
	OutputIterator oiter_;
};

template<class OutputIterator,class BinaryPredicate>
struct unique_copy_pred_t{
	template<
		REQUIRES(
				!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
				and
				is_callable_v<std::remove_reference_t<std::remove_cv_t<BinaryPredicate>>>
		)
	>
	explicit constexpr unique_copy_pred_t(OutputIterator oiter,BinaryPredicate pred)
		:oiter_(std::move(oiter)),pred_(std::move(pred)){}
	
	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	OutputIterator operator()(Range&& r)
	{
		return std::unique_copy(r.begin(),r.end(),std::move(oiter_),std::move(pred_));
	}
private:
	OutputIterator oiter_;
	BinaryPredicate pred_;
};

template<class OutputIterator,REQUIRES(!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>)>
constexpr unique_copy_t<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
unique_copy(OutputIterator&& oiter)
{
	return unique_copy_t<
		std::remove_reference_t<std::remove_cv_t<OutputIterator>>
	>(std::forward<OutputIterator>(oiter));
}

template<
	class OutputIterator,
	class BinaryPredicate,
	REQUIRES(
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
			and
			is_callable_v<std::remove_reference_t<std::remove_cv_t<BinaryPredicate>>>
	)
>
constexpr unique_copy_pred_t<
	std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
	std::remove_reference_t<std::remove_cv_t<BinaryPredicate>>
>
unique_copy(OutputIterator&& iter,BinaryPredicate&& pred)
{
	return unique_copy_pred_t<
		std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
		std::remove_reference_t<std::remove_cv_t<BinaryPredicate>>
	>(std::forward<OutputIterator>(iter),std::forward<BinaryPredicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::unique_copy;

} // namespace pipealgo
} // namespace srook

#endif
