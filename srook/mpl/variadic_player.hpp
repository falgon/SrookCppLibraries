// Copyright (C) 2017 roki
#ifndef SROOK_INCLUDE_VARIADIC_PLAYER_HPP
#define SROOK_INCLUDE_VARIADIC_PLAYER_HPP
#include<srook/mpl/variadic_tmp_player.hpp>
#include<type_traits>

namespace srook{
inline namespace mpl{
inline namespace v1{

// Tag to ***er.
// These tags have feautures that changing the mode(Single/All).
namespace variadic_tag{
	struct Single{};
	struct All{};
}

// Eraser
template<class,class,class...>
struct Eraser;
template<class Mode,class T,class Head,class... Tail>
struct Eraser<Mode,T,Head,Tail...>{
	using type=Concat_t<Head,typename Eraser<Mode,T,Tail...>::type>;
};
template<class T,class... Tail>
struct Eraser<variadic_tag::Single,T,T,Tail...>{
	using type=pack<Tail...>;
};
template<class T,class... Tail>
struct Eraser<variadic_tag::All,T,T,Tail...>{
	using type=typename Eraser<variadic_tag::All,Tail...>::type;
};
template<class Mode,class Tail>
struct Eraser<Mode,Tail>{
	using type=pack<>;
};
template<class Mode,class T,class Head,class... Tail>
struct Eraser<Mode,T,pack<Head,Tail...>>:Eraser<Mode,T,Head,Tail...>{};
template<class Mode,class T,class... Pack>
using Eraser_t=typename Eraser<Mode,T,Pack...>::type;

// Replacer
template<class,class,class,class... Pack>
struct Replacer;
template<class Mode,class T,class R,class Head,class... Pack>
struct Replacer<Mode,T,R,Head,Pack...>{
	using type=Concat_t<Head,typename Replacer<Mode,T,R,Pack...>::type>;
};
template<class T,class R,class... Pack>
struct Replacer<variadic_tag::Single,T,R,T,Pack...>{
	using type=pack<R,Pack...>;
};
template<class T,class R,class... Pack>
struct Replacer<variadic_tag::All,T,R,T,Pack...>{
	using type=Concat_t<R,typename Replacer<variadic_tag::All,T,R,Pack...>::type>;
};
template<class Mode,class T,class R>
struct Replacer<Mode,T,R>{
	using type=pack<>;
};
template<class Mode,class T,class R,class Head,class... Pack>
struct Replacer<Mode,T,R,pack<Head,Pack...>>:Replacer<Mode,T,R,Head,Pack...>{};
template<class Mode,class T,class R,class... Pack>
using Replacer_t=typename Replacer<Mode,T,R,Pack...>::type;

// make pack: automatic pack generater
template<class T,std::size_t size>
struct make_pack_impl{
	using type=Concat_t<T,typename make_pack_impl<T,size-1>::type>;
};
template<class T>
struct make_pack_impl<T,0>{
	using type=pack<>;
};
template<class T,std::size_t size>
using make_pack=typename make_pack_impl<T,size>::type;

// pack setting
template<class T,std::size_t s>
struct pack_setting{
	static constexpr std::size_t size=s;
	using type=T;
};

// make some pack: automatic multiple types pack generater
template<class... PackSetting>
struct make_someting_pack_impl{
private:
	using inner_type=make_pack<typename First_t<PackSetting...>::type,First_t<PackSetting...>::size>;
public:
	using type=Concat_t<inner_type,typename make_someting_pack_impl<PopFront_t<PackSetting...>>::type>;
};
template<>
struct make_someting_pack_impl<pack<>>{
		using type=pack<>;
};
template<class... PackSetting>
using make_some_pack=typename make_someting_pack_impl<PackSetting...>::type;

// erase_at
template<std::size_t,class...>
struct Erase_At;

template<std::size_t target,class Head,class... Tail>
struct Erase_At<target,Head,Tail...>{
	using type=Concat_t<Head,typename Erase_At<target-1,Tail...>::type>;
};

template<class Head,class... Tail>
struct Erase_At<0,Head,Tail...>{
	using type=pack<Tail...>;
};

template<std::size_t target,class... Args>
struct Erase_At<target,pack<Args...>>:Erase_At<target,Args...>{};

template<std::size_t n,class... Args>
using Erase_At_t=typename Erase_At<n,Args...>::type;

// erase_if
template<template<class>class,class...>
struct Erase_if;

template<template<class>class Pred,class Head,class... Tail>
struct Erase_if<Pred,Head,Tail...>{
	using type=Concat_t<typename std::conditional<Pred<Head>::value,Head,pack<>>::type,typename Erase_if<Pred,Tail...>::type>;
};

template<template<class>class Pred>
struct Erase_if<Pred>{
	using type=pack<>;
};

template<template<class>class Pred,class... Args>
struct Erase_if<Pred,pack<Args...>>:Erase_if<Pred,Args...>{};

template<template<class>class Pred,class... Args>
using Erase_if_t=typename Erase_if<Pred,Args...>::type;

} // namespace v1
} // namespace mpl
} // namespace srook
#endif 
