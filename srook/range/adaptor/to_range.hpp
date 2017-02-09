#ifndef INCLUDED_SROOK_RANGE_ADAPTOR_TO_RANGE
#define INCLUDED_SROOK_RANGE_ADAPTOR_TO_RANGE
#include<srook/mpl/variadic_player.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<srook/config/require.hpp>
#include<array>
#include<tuple>
#include<string>

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
					*std::next(r.begin(),N),
					std::forward<Args>(args)...
			);
		}
	};
};

template<>
struct to_range<std::basic_string>{
	template<class Range,REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)>
	std::string operator()(Range&& r)
	{
		return std::string(r.begin(),r.end());
	}
};


template<template<class,std::size_t>class Array,std::size_t n>
struct to_array{
	template<
		class Range,
		REQUIRES(has_iterator_v<std::decay_t<Range>> || is_range_iterator_v<std::decay_t<Range>>)
	>
	Array<typename std::decay_t<Range>::value_type,n> operator()(Range&& r)
	{
		return applyer(
				std::forward<Range>(r),
				std::integral_constant<int,n-1>(),
				std::integral_constant<std::size_t,n>()
		);
	}
private:
	template<class Range,int N,std::size_t Size,class... Args>
	static auto applyer(
			Range&& r,
			const std::integral_constant<int,N>& intconst,
			const std::integral_constant<std::size_t,Size>& intsize,
			Args&&... args)
	{
		return std::conditional<
			(N==-1),
			invoke,
			unpack
		>::type::apply(std::forward<Range>(r),intconst,intsize,std::forward<Args>(args)...);
	}
	struct invoke final{
		template<class Range,int N,std::size_t Size,class... Args>
		static auto apply(
				Range&&,
				const std::integral_constant<int,N>&,
				const std::integral_constant<std::size_t,Size>&,
				Args&&... args
		)
		{
			return std::array<typename std::decay_t<Range>::value_type,Size>{{std::forward<Args>(args)...}};
		}
	};
	struct unpack final{
		template<class Range,int N,std::size_t Size,class... Args>
		static auto apply(
				Range&& r,
				const std::integral_constant<int,N>&,
				const std::integral_constant<std::size_t,Size>& size,
				Args&&... args
		)
		{
			return applyer(
					std::forward<Range>(r),
					std::integral_constant<int,N-1>(),
					size,
					*std::next(r.begin(),N),
					std::forward<Args>(args)...
			);
		}
	};
};

	
} // inline namespace v1
} // namespace detail

using detail::to_range;
using detail::to_array;

} // namespace adaptors
} // namesapce srook

#endif
