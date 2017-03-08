#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_IS_PERMUTATION_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_IS_PERMUTATION_HPP
#include<srook/mpl/constant_sequence/algorithm/binary_search.hpp>
#include<srook/mpl/constant_sequence/algorithm/sort.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<bool,class,class>
struct is_permutation;

template<std::size_t head,std::size_t... last,std::size_t... seq>
struct is_permutation<true,std::index_sequence<head,last...>,std::index_sequence<seq...>>{
	static constexpr bool value=
		is_permutation<
			binary_search_v<head,std::index_sequence<seq...>>,
			std::index_sequence<last...>,
			std::index_sequence<seq...>
		>::value;
};

template<std::size_t last,std::size_t... seq>
struct is_permutation<true,std::index_sequence<last>,std::index_sequence<seq...>>{
	static constexpr bool value=binary_search_v<last,std::index_sequence<seq...>>;
};

template<std::size_t... preseq,std::size_t... seq>
struct is_permutation<false,std::index_sequence<preseq...>,std::index_sequence<seq...>>:std::false_type{};

template<class Seq1,class Seq2>
constexpr bool is_permutation_v=
	is_permutation<
		binary_search_v<
			(Seq1::size()<Seq2::size())?first_v<Seq1>:first_v<Seq2>,
			sort_t<std::conditional_t<(Seq1::size()<Seq2::size()),Seq2,Seq1>>
		>,
		pop_front_t<std::conditional_t<(Seq1::size()<Seq2::size()),Seq1,Seq2>>,
		sort_t<std::conditional_t<(Seq1::size()<Seq2::size()),Seq2,Seq1>>
	>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook

#endif
