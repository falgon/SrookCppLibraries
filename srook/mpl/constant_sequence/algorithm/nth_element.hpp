// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_NTH_ELEMENT_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_NTH_ELEMENT_HPP
#include<srook/mpl/constant_sequence/algorithm/concat.hpp>
#include<srook/mpl/constant_sequence/algorithm/at.hpp>
#include<srook/mpl/constant_sequence/algorithm/nth_min.hpp>
#include<srook/mpl/constant_sequence/algorithm/find_if.hpp>
#include<srook/mpl/constant_sequence/algorithm/erase_index.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

namespace{

template<std::size_t,class,std::size_t>
struct min_indexs;

template<std::size_t n,std::size_t head,std::size_t... tail,std::size_t counter>
struct min_indexs<n,std::index_sequence<head,tail...>,counter>{
private:
	template<std::size_t n_>
	using pred=std::integral_constant<bool,(n>=n_)>;
public:
	using type=
		concat_t<
			std::conditional_t<
				pred<head>::value,
				std::index_sequence<counter>,
				std::index_sequence<>
			>,
			typename min_indexs<n,std::index_sequence<tail...>,counter+1>::type
		>;
};

template<std::size_t n,std::size_t counter>
struct min_indexs<n,std::index_sequence<>,counter>{
	using type=std::index_sequence<>;
};

template<std::size_t n,class Seq>
using min_indexs_t=typename min_indexs<n,Seq,0>::type;

} // anonymouse namespace

template<class,class,class>
struct nth_element;

template<std::size_t... seq,std::size_t head,std::size_t... tail,std::size_t... ind>
struct nth_element<std::index_sequence<seq...>,std::index_sequence<head,tail...>,std::index_sequence<ind...>>{
	using type=
		concat_t<
			std::index_sequence<at_v<head,std::index_sequence<seq...>>>,
			typename nth_element<
				std::index_sequence<seq...>,
				std::index_sequence<tail...>,
				std::index_sequence<ind...>
			>::type
		>;
};

template<std::size_t... seq,std::size_t... ind>
struct nth_element<std::index_sequence<seq...>,std::index_sequence<>,std::index_sequence<ind...>>{
private:
	template<class,class>
	struct make_delseq;
	template<std::size_t head_,std::size_t... tail_,std::size_t... seq_>
	struct make_delseq<std::index_sequence<head_,tail_...>,std::index_sequence<seq_...>>{
		using type=
			concat_t<
				std::index_sequence<at_v<head_,std::index_sequence<seq_...>>>,
				typename make_delseq<std::index_sequence<tail_...>,std::index_sequence<seq_...>>::type
			>;		
	};
	template<std::size_t... seq_>
	struct make_delseq<std::index_sequence<>,std::index_sequence<seq_...>>{
		using type=std::index_sequence<>;
	};

	template<class delseq,class seq_>
	using del_sequence_t=typename make_delseq<delseq,seq_>::type;
public:
	using type=
		erase_index_t<
			del_sequence_t<std::index_sequence<ind...>,std::index_sequence<seq...>>,
			std::index_sequence<seq...>
		>;
};

template<std::size_t n,class Seq>
using nth_element_t=
	typename nth_element<
		Seq,
		min_indexs_t<nth_min_v<n,Seq>,Seq>,
		min_indexs_t<nth_min_v<n,Seq>,Seq>
	>::type;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
