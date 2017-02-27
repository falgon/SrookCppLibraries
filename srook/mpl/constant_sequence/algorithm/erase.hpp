#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_PLAYER_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_PLAYER_HPP
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<std::size_t,class>
struct erase;
template<std::size_t target,std::size_t head,std::size_t... tail>
struct erase<target,std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<head>,typename erase<target,std::index_sequence<tail...>>::type>;
};
template<std::size_t target,std::size_t... pack>
struct erase<target,std::index_sequence<target,pack...>>{
	using type=std::index_sequence<pack...>;
};
template<std::size_t target>
struct erase<target,std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<std::size_t target,class Sequence=std::index_sequence<>>
using erase_t=typename erase<target,Sequence>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#endif
