// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_BINARY_SEARCH_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_BINARY_SEARCH_HPP
#include<srook/mpl/variadic_player.hpp>
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/algorithm/partial_head.hpp>
#include<srook/cxx17/mpl/any_pack/algorithm/partial_tail.hpp>

namespace srook{
inline namespace mpl{
inline namespace v1{
namespace detail{

template<auto,class> struct binary_search;
template<auto target,auto... v>
struct binary_search<target,any_pack<v...>>{
private:
	static constexpr At_t<sizeof...(v)/2,decltype(v)...> half_value=any_pack<v...>::template at<sizeof...(v)/2>();
	using head_inner=binary_search<target,typename any_pack<v...>::template partial_head_type<(sizeof...(v)/2)>>;
	using tail_inner=binary_search<target,typename any_pack<v...>::template partial_tail_type<(sizeof...(v)/2)>>;
public:
	static constexpr bool value = std::conditional_t<(target == half_value),std::true_type,std::conditional_t<(half_value > target),head_inner,tail_inner>>::value;
};
template<auto target,auto l1,auto l2>
struct binary_search<target,any_pack<l1,l2>>{
	static constexpr bool value = target==l1 or target==l2;
};
template<auto target,auto l>
struct binary_search<target,any_pack<l>>{
	static constexpr bool value = target==l;
};
template<auto target>
struct binary_search<target,any_pack<>>:std::false_type{};
template<auto target,auto... v>
constexpr bool binary_search_v = binary_search<target,any_pack<v...>>::value;

} // namespace detail
} // inline namespace v1
} // inlnie namespace mpl 
} // namespace srook

#endif
