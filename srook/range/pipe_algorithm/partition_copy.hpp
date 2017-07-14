// Copyright (C) 2017 Roki
#ifndef INCLUDE_SROOK_RANGE_ADAPTOR_PARTITION_COPY
#define INCLUDE_SROOK_RANGE_ADAPTOR_PARTITION_COPY
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/mpl/has_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/config/require.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Outer1,class Outer2,class Predicate>
struct partition_copy_iter_iter_t{
	
	template<
		REQUIRES(!srook::mpl::has_iterator_v<Outer1> && !srook::mpl::has_iterator_v<Outer2> && srook::is_callable_v<Predicate>)
	>
	explicit constexpr partition_copy_iter_iter_t(Outer1 o_iter1,Outer2 o_iter2,Predicate pred)
		:out_true(std::move(o_iter1)),out_false(std::move(o_iter2)),pred_(std::move(pred)){}
	
	template<
		class Range1,
		REQUIRES(
				!srook::mpl::has_iterator_v<Outer1> && 
				(srook::mpl::has_iterator_v<std::decay_t<Range1>> || is_range_iterator_v<std::decay_t<Range1>>) && 
				srook::is_callable_v<Predicate>
		)
	>
	explicit constexpr partition_copy_iter_iter_t(Outer1 o_iter1,Range1&& o_range1,Predicate pred)
		:out_true(std::move(o_iter1)),out_false(o_range1.begin()),pred_(std::move(pred)){}

	template<
		class Range1,
		REQUIRES(
				(srook::mpl::has_iterator_v<std::decay_t<Range1>> || is_range_iterator_v<std::decay_t<Range1>>) && 
				!srook::mpl::has_iterator_v<Outer2> && 
				srook::is_callable_v<Predicate>
		)	
	>
	explicit constexpr partition_copy_iter_iter_t(Range1&& o_range1,Outer2 o_iter1,Predicate pred)
		:out_true(o_range1.begin()),out_false(std::move(o_iter1)),pred_(std::move(pred)){}

	template<
		class Range1,
		class Range2,
		REQUIRES(
				(srook::mpl::has_iterator_v<std::decay_t<Range1>> || is_range_iterator_v<std::decay_t<Range1>>) &&
				(srook::mpl::has_iterator_v<std::decay_t<Range2>> || is_range_iterator_v<std::decay_t<Range2>>) && 
				srook::is_callable_v<Predicate>
		)
	>
	explicit constexpr partition_copy_iter_iter_t(Range1&& o_range1,Range2&& o_range2,Predicate pred)
		:out_true(o_range1.begin()),out_false(o_range2.begin()),pred_(std::move(pred)){}


	template<class Range,REQUIRES(srook::mpl::has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	std::pair<Outer1,Outer2> operator()(Range&& r)
	{
		return std::partition_copy(r.cbegin(),r.cend(),std::move(out_true),std::move(out_false),std::move(pred_));
	}
private:
	Outer1 out_true;
	Outer2 out_false;
	Predicate pred_;
};


template<
	class Outer1,
	class Outer2,
	class Predicate,
	REQUIRES(
			!srook::mpl::has_iterator_v<std::decay_t<Outer1>> && 
			!srook::mpl::has_iterator_v<std::decay_t<Outer2>> && 
			srook::is_callable_v<std::decay_t<Predicate>>
	)
>
constexpr partition_copy_iter_iter_t<std::decay_t<Outer1>,std::decay_t<Outer2>,std::decay_t<Predicate>>
partition_copy(Outer1&& out1,Outer2&& out2,Predicate&& pred)
{
	return partition_copy_iter_iter_t<
		std::decay_t<Outer1>,
		std::decay_t<Outer2>,
		std::decay_t<Predicate>
	>(std::forward<Outer1>(out1),std::forward<Outer2>(out2),std::forward<Predicate>(pred));
}

template<
	class Outer1,
	class Outer2,
	class Predicate,
	REQUIRES(
			(srook::mpl::has_iterator_v<std::decay_t<Outer1>> || is_range_iterator_v<std::decay_t<Outer1>>) &&
			!srook::mpl::has_iterator_v<std::decay_t<Outer2>> &&
			srook::is_callable_v<std::decay_t<Predicate>>
	)
>
constexpr partition_copy_iter_iter_t<typename std::decay_t<Outer1>::iterator,std::decay_t<Outer2>,std::decay_t<Predicate>>
partition_copy(Outer1&& outer1,Outer2&& outer2,Predicate&& pred)
{
	return partition_copy_iter_iter_t<
		typename std::decay_t<Outer1>::iterator,
		std::decay_t<Outer2>,
		std::decay_t<Predicate>
	>(std::forward<Outer1>(outer1),std::forward<Outer2>(outer2),std::forward<Predicate>(pred));
}

template<
	class Outer1,
	class Outer2,
	class Predicate,
	REQUIRES(
			!srook::mpl::has_iterator_v<std::decay_t<Outer1>> &&
			(srook::mpl::has_iterator_v<std::decay_t<Outer2>> || is_range_iterator_v<std::decay_t<Outer2>>) &&
			srook::is_callable_v<std::decay_t<Predicate>>
	)
>
constexpr partition_copy_iter_iter_t<std::decay_t<Outer1>,typename std::decay_t<Outer2>::iterator,std::decay_t<Predicate>>
partition_copy(Outer1&& outer1,Outer2&& outer2,Predicate&& pred)
{
	return partition_copy_iter_iter_t<
			std::decay_t<Outer1>,
			typename std::decay_t<Outer2>::iterator,
			std::decay_t<Predicate>
	>(std::forward<Outer1>(outer1),std::forward<Outer2>(outer2),std::forward<Predicate>(pred));
}

template<
	class Outer1,
	class Outer2,
	class Predicate,
	REQUIRES(
			(srook::mpl::has_iterator_v<std::decay_t<Outer1>> || is_range_iterator_v<std::decay_t<Outer1>>) &&
			(srook::mpl::has_iterator_v<std::decay_t<Outer2>> || is_range_iterator_v<std::decay_t<Outer2>>) &&
			srook::is_callable_v<std::decay_t<Predicate>>
	)
>
constexpr partition_copy_iter_iter_t<typename std::decay_t<Outer1>::iterator,typename std::decay_t<Outer2>::iterator,std::decay_t<Predicate>>
partition_copy(Outer1&& outer1,Outer2&& outer2,Predicate&& pred)
{
	return partition_copy_iter_iter_t<
			typename std::decay_t<Outer1>::iterator,
			typename std::decay_t<Outer2>::iterator,
			std::decay_t<Predicate>
	>(std::forward<Outer1>(outer1),std::forward<Outer2>(outer2),std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::partition_copy;

} // namespace pipealgo
} // namespace srook

#endif
