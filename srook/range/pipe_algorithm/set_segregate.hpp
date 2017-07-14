// Copyright (C) 2017 Roki
// Inspired from 
// http://www.fluentcpp.com/2017/02/09/set-aggregate-set-seggregate-higher-level-algorithms-on-sets/
// https://github.com/joboccara/sets/blob/master/set_seggregate.hpp

#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_SET_SEGREGATE_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_SET_SEGREGATE_HPP
#include<algorithm>
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<tuple>
#include<map>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Outputer1,class Outputer2,class Outputer3,class Compare>
struct set_segregate_t{
	template<
		REQUIRES(
				!has_iterator_v<Outputer1> and 
				!has_iterator_v<Outputer2> and 
				!has_iterator_v<Outputer3> and
				is_callable_v<Compare>
		)
	>
	explicit constexpr set_segregate_t(
			Outputer1 iter1,
			Outputer2 iter2,
			Outputer3 iter3,
			Compare comp
	)
		:iter1_(std::move(iter1)),iter2_(std::move(iter2)),iter3_(std::move(iter3)),comp_(std::move(comp)){}

	template<
		class Range1,class Range2,class Range3,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range1>>> and
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range2>>> and
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range3>>> and
				is_callable_v<Compare>
		)
	>
	explicit constexpr set_segregate_t(
			Range1&& o1,
			Range2&& o2,
			Range3&& o3,
			Compare comp
	)
		:iter1_(std::begin(o1)),iter2_(std::begin(o2)),iter3_(std::begin(o3)),comp_(std::move(comp)){}

	template<
		class Range1,
		class Range2,
		class... trash,
		REQUIRES(
				(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range1>>> or
				 is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range1>>>)
				and
				(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range2>>> or
				 is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range2>>>)
		)
	>
	std::tuple<Outputer1,Outputer2,Outputer3>
	operator()(const std::tuple<Range1,Range2,trash...>& range_tuple)
	{
		return operator()(std::make_pair(std::get<0>(range_tuple),std::get<1>(range_tuple)));
	}

	template<
		class Range1,
		class Range2,
		REQUIRES(
				(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range1>>> or 
				 is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range1>>>)
				and
				(has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range2>>> or
				 is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range2>>>)
		)
	>
	std::tuple<Outputer1,Outputer2,Outputer3>	
	operator()(const std::pair<Range1,Range2>& range_pair)
	{
		const std::remove_reference_t<Range1>& leftRange = range_pair.first;
		const std::remove_reference_t<Range2>& rightRange = range_pair.second;

		typename std::remove_cv_t<std::remove_reference_t<Range1>>::const_iterator left_it = std::begin(leftRange);
		typename std::remove_cv_t<std::remove_reference_t<Range2>>::const_iterator right_it = std::begin(rightRange);

		while (left_it != std::end(leftRange)){
			if(right_it == std::end(rightRange)){
				std::copy(left_it,std::end(leftRange),iter1_);
				return std::make_tuple(iter1_,iter2_,iter3_);
			}

			if(comp_(*left_it, *right_it)){
				*iter1_++ = *left_it++;
			}else{
            	if(!comp_(*right_it, *left_it)){
					*iter2_++ = *left_it++;
					++right_it;
				}else{
					*iter3_++ = *right_it++;
				}
			}
		}
		std::copy(right_it,std::end(rightRange),iter3_);
		return std::make_tuple(iter1_,iter2_,iter3_);
	}
private:
	Outputer1 iter1_;
	Outputer2 iter2_;
	Outputer3 iter3_;
	Compare comp_;
};

template<
	class Outputer1,
	class Outputer2,
	class Outputer3,
	class Compare=std::less<>,
	REQUIRES(
			(has_iterator_v<std::remove_cv_t<std::remove_reference_t<Outputer1>>> or 
			 is_range_iterator_v<std::remove_cv_t<std::remove_reference_t<Outputer1>>>)
			and
			(has_iterator_v<std::remove_cv_t<std::remove_reference_t<Outputer2>>> or
			 is_range_iterator_v<std::remove_cv_t<std::remove_reference_t<Outputer2>>>)
			and
			(has_iterator_v<std::remove_cv_t<std::remove_reference_t<Outputer3>>> or
			 is_range_iterator_v<std::remove_cv_t<std::remove_reference_t<Outputer3>>>)
			and
			is_callable_v<std::remove_cv_t<std::remove_reference_t<Compare>>>
	)
>
constexpr set_segregate_t<
	typename std::remove_cv_t<std::remove_reference_t<Outputer1>>::iterator,
	typename std::remove_cv_t<std::remove_reference_t<Outputer2>>::iterator,
	typename std::remove_cv_t<std::remove_reference_t<Outputer3>>::iterator,
	std::remove_cv_t<std::remove_reference_t<Compare>>
>
set_segregate(Outputer1&& o1,Outputer2&& o2,Outputer3&& o3,Compare&& comp=std::less<>())
{
	return set_segregate_t<
		typename std::remove_cv_t<std::remove_reference_t<Outputer1>>::iterator,
		typename std::remove_cv_t<std::remove_reference_t<Outputer2>>::iterator,
		typename std::remove_cv_t<std::remove_reference_t<Outputer3>>::iterator,
		std::remove_cv_t<std::remove_reference_t<Compare>>
	>(
			std::forward<Outputer1>(o1),std::forward<Outputer2>(o2),
			std::forward<Outputer3>(o3),std::forward<Compare>(comp)
	);
}

template<
	class Outputer1,
	class Outputer2,
	class Outputer3,
	class Compare=std::less<>,
	REQUIRES(
			!has_iterator_v<std::remove_cv_t<std::remove_reference_t<Outputer1>>> and
			!has_iterator_v<std::remove_cv_t<std::remove_reference_t<Outputer2>>> and
			!has_iterator_v<std::remove_cv_t<std::remove_reference_t<Outputer3>>> and
			is_callable_v<std::remove_cv_t<std::remove_reference_t<Compare>>>
	)
>
constexpr set_segregate_t<
	std::remove_cv_t<std::remove_reference_t<Outputer1>>,
	std::remove_cv_t<std::remove_reference_t<Outputer2>>,
	std::remove_cv_t<std::remove_reference_t<Outputer3>>,
	std::remove_cv_t<std::remove_reference_t<Compare>>
>
set_segregate(Outputer1&& o1,Outputer2 o2,Outputer3 o3,Compare&& comp=std::less<>())
{
	return set_segregate_t<
		std::remove_cv_t<std::remove_reference_t<Outputer1>>,
		std::remove_cv_t<std::remove_reference_t<Outputer2>>,
		std::remove_cv_t<std::remove_reference_t<Outputer3>>,
		std::remove_cv_t<std::remove_reference_t<Compare>>
	>(
			std::forward<Outputer1>(o1),std::forward<Outputer2>(o2),
			std::forward<Outputer3>(o3),std::forward<Compare>(comp)
	);
}

} // inline namespace v1
} // namespace detail

using detail::set_segregate;

} // namespace pipealgo
} // namespace srook

#endif
