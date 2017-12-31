// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_GENERATE_N
#define INCLUDED_SROOK_RANGE_ADAPTOR_GENERATE_N
#include<srook/range/adaptor/adaptor_operator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/config/compiler.hpp>
#include<srook/config/require.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<algorithm>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Size,class Generate>
struct generate_n_t{
	explicit constexpr generate_n_t(Size s,Generate gen)
		:s_(std::move(s)),gen_(std::move(gen)){}
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	auto operator()(Range&& r)
	{
#if (__has_include(<boost/config/compiler/gcc.hpp>) || __has_include(<boost/config/compiler/clang.hpp>)) && \
		(defined(BOOST_NO_CXX11_AUTO_DECLARATIONS) || defined(BOOST_GCC_CXX11))
		return std::generate_n(r.begin(),std::move(s_),std::move(gen_));
#elif defined(SROOK_NO_CXX11_AUTO_DECLARATIONS) || defined(SROOK_GCC_CXX11)
		return std::generate_n(r.begin(),std::move(s_),std::move(gen_));
#else
		std::generate_n(r.begin(),std::move(s_),std::move(gen_));
		return r.begin();
#endif
	}
private:
	Size s_;
	Generate gen_;
};

template<class Size,class Generate,REQUIRES(std::is_convertible<std::decay_t<Size>,std::size_t>{})>
constexpr generate_n_t<std::decay_t<Size>,std::decay_t<Generate>> generate_n(Size&& s,Generate&& gen)
{
	return generate_n_t<std::decay_t<Size>,std::decay_t<Generate>>(std::forward<Size>(s),std::forward<Generate>(gen));
}

} // inline namespace v1
} // namespace detail

using detail::generate_n;

} // namespace pipealgo
} // namespace srook

#ifdef POSSIBLE_TO_INCLUDE_BOOST_RANGE_GENERATE_N
#undef POSSIBLE_TO_INCLUDE_BOOST_RANGE_GENERATE_N
#endif

#endif
