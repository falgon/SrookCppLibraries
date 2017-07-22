// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_TRANSFORM_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_TRANSFORM_HPP
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class OutputIterator,class UnaryOperation>
struct transform_t{
	template<
		REQUIRES(
				!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>> and
				is_callable_v<std::remove_reference_t<std::remove_cv_t<UnaryOperation>>>
		)
	>
	explicit constexpr transform_t(OutputIterator iter,UnaryOperation op)
		:iter_(std::move(iter)),op_(std::move(op)){}

	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	OutputIterator operator()(Range&& r)
	{
		return std::transform(r.begin(),r.end(),std::move(iter_),std::move(op_));
	}
private:
	OutputIterator iter_;
	UnaryOperation op_;
};

template<class InputIterator,class OutputIterator,class BinaryOperation>
struct transform_binary_t{
	template<
		class Range,
		REQUIRES(
				(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
				and
				!has_iterator_v<std::remove_reference_t<std::remove_cv_t<InputIterator>>>
				and
				!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
				and
				is_callable_v<std::remove_reference_t<std::remove_cv_t<BinaryOperation>>>
		)
	>
	explicit constexpr transform_binary_t(Range&& r,OutputIterator oiter,BinaryOperation binary)
		:first_(std::begin(r)),oiter_(std::move(oiter)),binary_(std::move(binary)){}

	template<
		REQUIRES(
				!has_iterator_v<std::remove_reference_t<std::remove_cv_t<InputIterator>>>
				and
				!has_iterator_v<std::remove_reference_t<std::remove_cv_t<InputIterator>>>
				and
				is_callable_v<std::remove_reference_t<std::remove_cv_t<BinaryOperation>>>
		)
	>
	explicit constexpr transform_binary_t(InputIterator iter,OutputIterator oiter,BinaryOperation binary)
		:first_(std::move(iter)),oiter_(std::move(oiter)),binary_(std::move(binary)){}

	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	OutputIterator operator()(Range&& r)
	{
		return std::transform(std::begin(r),std::end(r),std::move(first_),std::move(oiter_),std::move(binary_));
	}
private:
	InputIterator first_;
	OutputIterator oiter_;
	BinaryOperation binary_;
};

template<
	class OutputIterator,
	class UnaryOperation,
	REQUIRES(
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>> and
			is_callable_v<std::remove_reference_t<std::remove_cv_t<UnaryOperation>>>
	)
>
constexpr transform_t<
	std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
	std::remove_reference_t<std::remove_cv_t<UnaryOperation>>
>
transform(OutputIterator&& iter,UnaryOperation&& op_)
{
	return transform_t<
		std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
		std::remove_reference_t<std::remove_cv_t<UnaryOperation>>
	>(std::forward<OutputIterator>(iter),std::forward<UnaryOperation>(op_));
}

template<
	class Range,
	class OutputIterator,
	class BinaryOperation,
	REQUIRES(
			(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
			is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>)
			and
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
			and
			is_callable_v<std::remove_reference_t<std::remove_cv_t<BinaryOperation>>>
	)
>
constexpr transform_binary_t<
	typename std::remove_reference_t<std::remove_cv_t<Range>>::const_iterator,
	std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
	std::remove_reference_t<std::remove_cv_t<BinaryOperation>>
>
transform(Range&& r,OutputIterator&& oiter,BinaryOperation&& binary)
{
	return transform_binary_t<
		typename std::remove_reference_t<std::remove_cv_t<Range>>::const_iterator,
		std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
		std::remove_reference_t<std::remove_cv_t<BinaryOperation>>
	>(std::forward<Range>(r),std::forward<OutputIterator>(oiter),std::forward<BinaryOperation>(binary));
}

template<
	class InputIterator,
	class OutputIterator,
	class BinaryOperation,
	REQUIRES(
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<InputIterator>>>
			and
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
			and
			is_callable_v<std::remove_reference_t<std::remove_cv_t<BinaryOperation>>>
	)
>
constexpr transform_binary_t<
	std::remove_reference_t<std::remove_cv_t<InputIterator>>,
	std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
	std::remove_reference_t<std::remove_cv_t<BinaryOperation>>
>
transform(InputIterator&& first,OutputIterator&& oiter,BinaryOperation&& binary)
{
	return transform_binary_t<
		std::remove_reference_t<std::remove_cv_t<InputIterator>>,
		std::remove_reference_t<std::remove_cv_t<OutputIterator>>,
		std::remove_reference_t<std::remove_cv_t<BinaryOperation>>
	>(std::forward<InputIterator>(first),std::forward<OutputIterator>(oiter),std::forward<BinaryOperation>(binary));
}

} // inline namespace v1
} // namespace detail

using detail::transform;

} // namespace pipealgo
} // namespace srook

#endif
