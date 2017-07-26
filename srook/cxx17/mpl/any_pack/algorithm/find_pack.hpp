#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_FIND_PACK_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_ALGORITHM_FIND_PACK_HPP
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/algorithm/pop_front.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/size.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{
namespace detail{

template<class,class,class,class> struct find_pack;

template<auto... pattern,auto... pattern_lost,auto... v,auto... seq>
struct find_pack<any_pack<pattern...>,any_pack<pattern_lost...>,any_pack<v...>,any_pack<seq...>>{
	static constexpr long int value = find_pack<any_pack<pattern...>,any_pack<pattern...>,any_pack<v...>,pop_front_t<v...>>::value;
};

template<auto... pattern,auto pattern_match,auto... pattern_lost,auto... v,auto... tail>
struct find_pack<any_pack<pattern...>,any_pack<pattern_match,pattern_lost...>,any_pack<v...>,any_pack<pattern_match,tail...>>{
	static constexpr long int value = find_pack<any_pack<pattern...>,any_pack<pattern_lost...>,any_pack<v...>,any_pack<tail...>>::value;
};

template<auto... pattern,auto... v>
struct find_pack<any_pack<pattern...>,any_pack<>,any_pack<v...>,any_pack<>>{
	static constexpr long int value = 0;
};

template<auto... pattern,auto pattern_head,auto... pattern_lost,auto... v>
struct find_pack<any_pack<pattern...>,any_pack<pattern_head,pattern_lost...>,any_pack<v...>,any_pack<>>{
	static constexpr long int value = -sizeof...(v);
};

template<class Pattern,class AnyPack>
static constexpr long int find_pack_v = size<Pattern> <= size<AnyPack> ? find_pack<Pattern,Pattern,AnyPack,AnyPack>::value : -1;

} // namespace detail
} // inline namespace v1
} // inline namespace mpl
} // namespace srook
#endif
