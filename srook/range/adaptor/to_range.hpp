#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_TO_RANGE
#define INCLUDED_SROOK_RANGE_ADAPTOR_TO_RANGE
#include<srook/mpl/variadic_player.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/config/require.hpp>
#include<tuple>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<template<class...>class,std::size_t...>
struct to_range;

template<template<class...>class Container>
struct to_range<Container>{
	template<
		class Range,
		REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)
	>
	auto operator()(Range&& r) -> Container<typename std::decay_t<Range>::value_type>
	{
		return Container<typename std::decay_t<Range>::value_type>(r.begin(),r.end());
	}
};

template<std::size_t n>
struct to_range<std::tuple,n>{
	template<
		class Range,
		REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)
	>
	auto operator()(Range&& r)
	{
		return applyer(
				std::forward<Range>(r),
				std::integral_constant<std::size_t,n-1>(),
				std::integral_constant<std::size_t,n-1>()
		);
	}
private:
	template<class Range,std::size_t N,std::size_t Size,class... Args>
	static auto applyer(
			Range&& r,
			const std::integral_constant<std::size_t,N>& intconst,
			const std::integral_constant<std::size_t,Size>& intsize,
			Args&&... args)
	{
		return std::conditional<
			(sizeof...(args)>Size),
			invoke,
			unpack
		>::type::apply(std::forward<Range>(r),intconst,intsize,std::forward<Args>(args)...);
	}
	struct invoke final{
		template<class Range,std::size_t N,std::size_t Size,class... Args>
		static auto
		apply(
				Range&&,
				const std::integral_constant<std::size_t,N>&,
				const std::integral_constant<std::size_t,Size>&,
				Args&&... args
		)
		{
			return std::make_tuple(std::forward<Args>(args)...);
		}
	};
	struct unpack final{
		template<class Range,std::size_t N,std::size_t Size,class... Args>
		static auto apply(
				Range&& r,
				const std::integral_constant<std::size_t,N>&,
				const std::integral_constant<std::size_t,Size>& size,
				Args&&... args
		)
		{
			return applyer(
					std::forward<Range>(r),
					std::integral_constant<std::size_t,N-1>(),
					size,
					r[N],
					std::forward<Args>(args)...
			);
		}
	};
};

	
} // inline namespace v1
} // namespace detail

using detail::to_range;

} // namespace adaptors
} // namesapce srook

#endif
