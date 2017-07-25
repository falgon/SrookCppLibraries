// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_POP_FRONT_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_POP_FRONT_HPP
#include<srook/mpl/variadic_player.hpp>
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<optional>

namespace srook{
inline namespace mpl{
inline namespace v1{
namespace detail{

template<auto...>
struct pop_front;
template<auto head,auto... tail>
struct pop_front<head,tail...>{
	using type = any_pack<tail...>;
};
template<>
struct pop_front<>{
	using type = std::nullopt_t;
};
template<auto... v>
using pop_front_t=typename pop_front<v...>::type;

} // namespace detail
} // inline namespace v1
} // inlnie namespace mpl 
} // namespace srook

#endif
