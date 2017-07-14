// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_GENERATE
#define INCLUDED_SROOK_RANGE_ADAPTOR_GENERATE
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/config/require.hpp>


#if __has_include(<boost/range/algorithm/generate.hpp>)
#include<boost/range/algorithm/generate.hpp>
#define POSSIBLE_TO_BOOST_RANGE_ALGORITHM_GENERATE
#else
#include<algorithm>
#endif

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Generator>
struct generate_t{
	template<REQUIRES(is_callable_v<Generator>)>
	explicit constexpr generate_t(Generator gen):gen_(std::move(gen)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	srook::range_iterator<typename std::decay_t<Range>::iterator> operator()(Range&& r)
	{
#ifdef POSSIBLE_TO_BOOST_RANGE_ALGORITHM_GENERATE
		boost::range::generate(std::forward<Range>(r),std::move(gen_));
#else
		std::generate(r.begin(),r.end(),std::move(gen_));
#endif
		return srook::make_range_iterator(r.begin(),r.end());
	}
private:
	Generator gen_;
};

template<class Generator>
constexpr generate_t<std::decay_t<Generator>> generate(Generator&& gen)
{
	return generate_t<std::decay_t<Generator>>(std::forward<Generator>(gen));
}

} // inline namespace v1
} // namesapce detail

using detail::generate;

} // namespace pipealgo
} // namespace srook

#ifdef POSSIBLE_TO_BOOST_RANGE_ALGORITHM_GENERATE
#undef POSSIBLE_TO_BOOST_RANGE_ALGORITHM_GENERATE
#endif
#endif
