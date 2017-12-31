// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_TYPELIST_TYPELIST_HPP
#define INCLUDED_SROOK_MPL_TYPELIST_TYPELIST_HPP
#include<srook/mpl/variadic_player.hpp>

#if __has_include(<optional>)
#include<optional>
#define POSSIBLE_TO_USE_STD_OPTIONAL
#elif __has_include(<boost/optional.hpp>)
#include<boost/optional.hpp>
#define POSSIBLE_TO_USE_BOOST_OPTIONAL
#else
#include<srook/optional.hpp>
#endif

namespace srook{
inline namespace mpl{
inline namespace v1{

using NullType=
#ifdef POSSIBLE_TO_USE_STD_OPTIONAL
	std::nullopt_t;
#elif defined(POSSIBLE_TO_USE_BOOST_OPTIONAL)
	boost::none_t;
#else
	srook::nullopt_t;
#endif

template<class L,class R>
struct typelist{
	using Head=L;
	using Tail=R;
};

template<class...Pack>
struct make_typelist;

template<class L,class... R>
struct make_typelist<L,R...>{
	using type=typelist<L,typename make_typelist<R...>::type>;
};
template<class Tail>
struct make_typelist<Tail>{
	using type=NullType;
};

template<class... Pack>
struct make_typelist<pack<Pack...>>:make_typelist<Pack...>{};

template<class... Pack>
using make_typelist_t=typename make_typelist<Pack...>::type;


} // namesapce v1
} // namespace mpl
} // namespace srook

#ifdef POSSIBLE_TO_USE_STD_OPTIONAL
#undef POSSIBLE_TO_USE_STD_OPTIONAL
#endif
#ifdef POSSIBLE_TO_USE_BOOST_OPTIONAL
#undef POSSIBLE_TO_USE_BOOST_OPTIONAL
#endif
#endif
