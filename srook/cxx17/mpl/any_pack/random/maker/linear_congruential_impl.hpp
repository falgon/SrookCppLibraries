#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_RANDOM_MAKER_LINEAR_CONGRUENTIAL_IMPL_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_RANDOM_MAKER_LINEAR_CONGRUENTIAL_IMPL_HPP
#include<srook/cxx17/mpl/any_pack/random/maker/core/make_random_sequence_declare.h>

namespace srook{
inline namespace mpl{
namespace random{
inline namespace v1{

// Liniear
template<std::size_t N,class UIntType,UIntType seed,UIntType A,UIntType C,UIntType M,auto... v>
struct make_random_sequence_impl<N,linear_congruential<UIntType,seed,A,C,M>,any_pack<v...>>{
	using type = 
		typename make_random_sequence_impl<
			N - 1,
			linear_congruential<UIntType,linear_congruential<UIntType,seed,A,C,M>::result,A,C,M>,
			any_pack<v...,linear_congruential<UIntType,seed,A,C,M>::result>
		>::type;
};

template<class UIntType,UIntType seed,UIntType A,UIntType C,UIntType M,auto... v>
struct make_random_sequence_impl<0,linear_congruential<UIntType,seed,A,C,M>,any_pack<v...>>{
	using type = any_pack<v...>;
};

template<std::size_t N,class UIntType,UIntType seed,UIntType A,UIntType C,UIntType M,auto min,auto max,auto... v>
struct make_random_sequence_impl<N,uniform_int_distribution<linear_congruential<UIntType,seed,A,C,M>,min,max>,any_pack<v...>>{
private:
	static constexpr UIntType rnd = linear_congruential<UIntType,seed,A,C,M>::result;
	static constexpr UIntType r = uniform_int_distribution<linear_congruential<UIntType,seed,A,C,M>,min,max>::result;
public:
	using type =
		typename make_random_sequence_impl<
			N - 1,
			uniform_int_distribution<linear_congruential<UIntType,rnd,A,C,M>,min,max>,
			any_pack<v...,r>
		>::type;
};

template<class UIntType,UIntType seed,UIntType A,UIntType C,UIntType M,auto min,auto max,auto... v>
struct make_random_sequence_impl<0,uniform_int_distribution<linear_congruential<UIntType,seed,A,C,M>,min,max>,any_pack<v...>>{
	using type = any_pack<v...>;
};


} // namespace v1
} // namespace random
} // inline namespace mpl
} // namespace srook

#endif
