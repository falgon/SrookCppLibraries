// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_ALL_OF_HPP
#define INCLUDED_SROOK_RANGE_ADAPTOR_ALL_OF_HPP
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>
#include<srook/iterator/range_iterator.hpp>
#if __has_include(<boost/algorithm/cxx11/all_of.hpp>)
#define POSSIBLE_TO_BOOST_ALGORITHM_CXX11_ALL_OF
#include<boost/algorithm/cxx11/all_of.hpp>
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{
template<class Predicate>
struct all_of_t{
	explicit constexpr all_of_t(const Predicate& pred):pred_(pred){}
	explicit constexpr all_of_t(Predicate&& pred):pred_(std::move(pred)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	bool operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_ALGORITHM_CXX11_ALL_OF
		return boost::algorithm::all_of(std::forward<Range>(r),std::move(pred_));
#else
		return std::all_of(r.cbegin(),r.cend(),std::move(pred_));
#endif
	}
private:
	Predicate pred_;
};
template<class Predicate>
constexpr all_of_t<std::decay_t<Predicate>> all_of(Predicate&& pred)
{
	return all_of_t<std::decay_t<Predicate>>(std::forward<Predicate>(pred));
}

} // inline namespace v1
} // namespace detail

using detail::all_of;

} // namespace pipealgo
} // namespace srook
#ifdef POSSIBLE_TO_BOOST_ALGORITHM_CXX11_ALL_OF
#undef POSSIBLE_TO_BOOST_ALGORITHM_CXX11_ALL_OF
#endif
#endif
