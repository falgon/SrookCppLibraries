#ifndef SROOK_INCLUDE_VARIADIC_PLAYER_HPP
#define SROOK_INCLUDE_VARIADIC_PLAYER_HPP
#include<srook/mpl/variadic_tmp_player.hpp>
namespace srook{
namespace mpl{
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
} // namespace v1
} // namespace mpl
} // namespace srook
#endif 
