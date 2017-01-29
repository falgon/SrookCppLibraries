#ifndef INCLUDED_SROOK_UTILITY_VOID_T_HPP
#define INCLUDED_SROOK_UTILITY_VOID_T_HPP
#include<cstddef>

namespace srook{
namespace detail{
inline namespace v1{

template<class T,class... Ts>
struct Empty_type{
	constexpr std::size_t size()const noexcept{return sizeof...(Ts);}
	using type=T;
};

template<class... Ts>
struct void_t_impl:Empty_type<void,Ts...>{};

}; // inline namespace v1
}; // namespace detail

template<class... Ts>
using void_t=typename detail::void_t_impl<Ts...>::type;

}; // namespace srook

#endif
