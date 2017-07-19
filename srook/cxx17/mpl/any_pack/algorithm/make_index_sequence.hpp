// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_MAKE_INDEX_SEQUENCE_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_MAKE_INDEX_SEQUENCE_HPP
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>

namespace srook{
inline namespace mpl{
inline namespace v1{
namespace detail{

template<std::size_t,class> struct make_index_sequence_impl;
template<std::size_t n,std::size_t... v>
struct make_index_sequence_impl<n,any_pack<v...>>{
	using type = typename make_index_sequence_impl<n-1,any_pack<n-1,v...>>::type;
};
template<std::size_t... v>
struct make_index_sequence_impl<0,any_pack<v...>>{
	using type = any_pack<v...>;
};
template<std::size_t n,class Seq = any_pack<>>
using make_index_sequence = typename make_index_sequence_impl<n,Seq>::type;

} // namespace detail
} // inline namespace v1
} // inlnie namespace mpl 
} // namespace srook

#ifdef NULLOPT
#undef NULLOPT
#endif
#endif