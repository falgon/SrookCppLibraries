#ifndef INCLUDED_SROOK_MAKE_SAME_TYPE_SEQUENCE_HPP
#define INCLUDED_SROOK_MAKE_SAME_TYPE_SEQUENCE_HPP

#include<srook/mpl/variadic_player.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{

template<bool,std::size_t,class...>
struct make_same_type_sequence_impl;

template<std::size_t n,class Head,class... Ts>
struct make_same_type_sequence_impl<true,n,pack<Head,Ts...>>{
	using type = typename make_same_type_sequence_impl<bool(n-1),n-1,pack<Head,Head,Ts...>>::type;
};

template<class... Ts>
struct make_same_type_sequence_impl<false,0,pack<Ts...>>{
	using type = PopBack_t<Ts...>;
};

template<std::size_t n,class T>
using make_same_type_sequence = typename make_same_type_sequence_impl<bool(n),n,pack<T>>::type;

} // inline namespace v1
} // inline namespace mpl
} // namespace srook

#endif
