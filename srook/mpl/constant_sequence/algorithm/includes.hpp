#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_INCLUDES_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_INCLUDES_HPP
#include<srook/mpl/constant_sequence/algorithm/binary_search.hpp>
#include<srook/mpl/constant_sequence/algorithm/first.hpp>
#include<srook/mpl/constant_sequence/algorithm/pop_front.hpp>

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<bool,class,class>
struct includes;

template<std::size_t head1,std::size_t... tail1,std::size_t head2,std::size_t... tail2>
struct includes<true,std::index_sequence<head1,tail1...>,std::index_sequence<head2,tail2...>>{
	static constexpr bool value=
		includes<
			binary_search_v<head2,std::index_sequence<head1,tail1...>>,
			std::index_sequence<tail1...>,
			std::index_sequence<tail2...>
		>::value;
};

template<std::size_t... seq1,std::size_t... seq2>
struct includes<false,std::index_sequence<seq1...>,std::index_sequence<seq2...>>:std::false_type{};

template<std::size_t... seq1>
struct includes<true,std::index_sequence<seq1...>,std::index_sequence<>>:std::true_type{};

template<std::size_t... seq2>
struct includes<true,std::index_sequence<>,std::index_sequence<seq2...>>:std::true_type{};

template<class Seq1,class Seq2>
constexpr bool includes_v=includes<binary_search_v<first_v<Seq2>,Seq1>,pop_front_t<Seq1>,pop_front_t<Seq2>>::value;

} // inline namespace v1
} // namespace constant_sequence
} // inline namespace mpl
} // namespace srook
#endif
