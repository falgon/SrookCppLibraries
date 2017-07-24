#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_RANDOM_MAKER_XORSHIFT_IMPL_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_RANDOM_MAKER_XORSHIFT_IMPL_HPP
#include<srook/cxx17/mpl/any_pack/random/maker/core/make_random_sequence_declare.h>

namespace srook{
inline namespace mpl{
namespace random{
inline namespace v1{

// Xorshift32
template<std::size_t N,class UIntType,UIntType Y,auto... v>
struct make_random_sequence_impl<N,Xorshift32<UIntType,Y>,any_pack<v...>>{
	using type = 
		typename make_random_sequence_impl<
			N - 1,
			Xorshift32<UIntType,Xorshift32<UIntType,Y>::result>,
			any_pack<v...,Xorshift32<UIntType,Y>::result>
		>::type;
};

template<class UIntType,UIntType Y,auto... v>
struct make_random_sequence_impl<0,Xorshift32<UIntType,Y>,any_pack<v...>>{
	using type = any_pack<v...>;
};

template<std::size_t N,class UIntType,UIntType Y,auto min,auto max,auto... v>
struct make_random_sequence_impl<N,uniform_int_distribution<Xorshift32<UIntType,Y>,min,max>,any_pack<v...>>{
private:
	static constexpr UIntType rnd = Xorshift32<UIntType,Y>::result;
	static constexpr UIntType r = uniform_int_distribution<Xorshift32<UIntType,Y>,min,max>::result;
public:
	using type =
		typename make_random_sequence_impl<
			N - 1,
			uniform_int_distribution<Xorshift32<UIntType,rnd>,min,max>,
			any_pack<v...,r>
		>::type;
};

template<class UIntType,UIntType Y,auto min,auto max,auto... v>
struct make_random_sequence_impl<0,uniform_int_distribution<Xorshift32<UIntType,Y>,min,max>,any_pack<v...>>{
	using type = any_pack<v...>;
};

// Xorshift64
template<std::size_t N,class UIntType,UIntType Y,auto... v>
struct make_random_sequence_impl<N,Xorshift64<UIntType,Y>,any_pack<v...>>{
	using type =
		typename make_random_sequence_impl<
			N - 1,
			Xorshift64<UIntType,Xorshift64<UIntType,Y>::result>,
			any_pack<v...,Xorshift64<UIntType,Y>::result>
		>::type;
};

template<class UIntType,UIntType Y,auto... v>
struct make_random_sequence_impl<0,Xorshift64<UIntType,Y>,any_pack<v...>>{
	using type = any_pack<v...>;
};

template<std::size_t N,class UIntType,UIntType Y,auto min,auto max,auto... v>
struct make_random_sequence_impl<N,uniform_int_distribution<Xorshift64<UIntType,Y>,min,max>,any_pack<v...>>{
private:
	static constexpr UIntType rnd = Xorshift64<UIntType,Y>::result;
	static constexpr UIntType r = uniform_int_distribution<Xorshift64<UIntType,Y>,min,max>::result;
public:
	using type = 
		typename make_random_sequence_impl<
			N - 1,
			uniform_int_distribution<Xorshift64<UIntType,rnd>,min,max>,
			any_pack<v...,r>
		>::type;
};

template<class UIntType,UIntType Y,auto min,auto max,auto... v>
struct make_random_sequence_impl<0,uniform_int_distribution<Xorshift64<UIntType,Y>,min,max>,any_pack<v...>>{
	using type = any_pack<v...>;
};


// Xorshift96
template<std::size_t N,class UIntType,UIntType X,UIntType Y,UIntType Z,auto... v>
struct make_random_sequence_impl<N,Xorshift96<UIntType,X,Y,Z>,any_pack<v...>>{
	using type = 
		typename make_random_sequence_impl<
			N - 1,
			Xorshift96<UIntType,Xorshift96<UIntType,X,Y,Z>::x,Xorshift96<UIntType,X,Y,Z>::y,Xorshift96<UIntType,X,Y,Z>::result>,
			any_pack<v...,Xorshift96<UIntType,X,Y,Z>::result>
		>::type;
};

template<class UIntType,UIntType X,UIntType Y,UIntType Z,auto... v>
struct make_random_sequence_impl<0,Xorshift96<UIntType,X,Y,Z>,any_pack<v...>>{
	using type = any_pack<v...>;
};

template<std::size_t N,class UIntType,UIntType X,UIntType Y,UIntType Z,auto min,auto max,auto... v>
struct make_random_sequence_impl<N,uniform_int_distribution<Xorshift96<UIntType,X,Y,Z>,min,max>,any_pack<v...>>{
private:
	static constexpr UIntType x = Xorshift96<UIntType,X,Y,Z>::x;
	static constexpr UIntType y = Xorshift96<UIntType,X,Y,Z>::y;
	static constexpr UIntType z = Xorshift96<UIntType,X,Y,Z>::result;
	static constexpr UIntType r = uniform_int_distribution<Xorshift96<UIntType,X,Y,Z>,min,max>::result;
public:
	using type = 
		typename make_random_sequence_impl<
			N - 1,
			uniform_int_distribution<Xorshift96<UIntType,x,y,z>,min,max>,
			any_pack<v...,r>
		>::type;
};

template<class UIntType,UIntType X,UIntType Y,UIntType Z,auto min,auto max,auto... v>
struct make_random_sequence_impl<0,uniform_int_distribution<Xorshift96<UIntType,X,Y,Z>,min,max>,any_pack<v...>>{
	using type = any_pack<v...>;
};

// Xorshift128
template<std::size_t N,class UIntType,UIntType X,UIntType Y,UIntType Z,UIntType W,auto... v>
struct make_random_sequence_impl<N,Xorshift128<UIntType,X,Y,Z,W>,any_pack<v...>>{
	using type = 
		typename make_random_sequence_impl<
			N - 1,
			Xorshift128<UIntType,Xorshift128<UIntType,X,Y,Z,W>::x,Xorshift128<UIntType,X,Y,Z,W>::y,Xorshift128<UIntType,X,Y,Z,W>::z,Xorshift128<UIntType,X,Y,Z,W>::result>,
			any_pack<v...,Xorshift128<UIntType,X,Y,Z,W>::result>
		>::type;
};

template<class UIntType,UIntType X,UIntType Y,UIntType Z,UIntType W,auto... v>
struct make_random_sequence_impl<0,Xorshift128<UIntType,X,Y,Z,W>,any_pack<v...>>{
	using type = any_pack<v...>;
};

template<std::size_t N,class UIntType,UIntType X,UIntType Y,UIntType Z,UIntType W,auto min,auto max,auto... v>
struct make_random_sequence_impl<N,uniform_int_distribution<Xorshift128<UIntType,X,Y,Z,W>,min,max>,any_pack<v...>>{
private:
	static constexpr UIntType x = Xorshift128<UIntType,X,Y,Z>::x;
	static constexpr UIntType y = Xorshift128<UIntType,X,Y,Z>::y;
	static constexpr UIntType z = Xorshift128<UIntType,X,Y,Z>::z;
	static constexpr UIntType w = Xorshift128<UIntType,X,Y,Z>::result;
	static constexpr UIntType r = uniform_int_distribution<Xorshift128<UIntType,X,Y,Z,W>,min,max>::result;
public:
	using type = 
		typename make_random_sequence_impl<
			N - 1,
			uniform_int_distribution<Xorshift128<UIntType,x,y,z,w>,min,max>,
			any_pack<v...,r>
		>::type;
};

template<class UIntType,UIntType X,UIntType Y,UIntType Z,UIntType W,auto min,auto max,auto... v>
struct make_random_sequence_impl<0,uniform_int_distribution<Xorshift128<UIntType,X,Y,Z,W>,min,max>,any_pack<v...>>{
	using type = any_pack<v...>;
};

// Main Invoker
template<std::size_t N,class RandomEngine,class AnyPack = any_pack<>>
using make_random_sequence = typename make_random_sequence_impl<N,RandomEngine,AnyPack>::type;


} // namespace v1
} // namespace random
} // inline namespace mpl
} // namespace srook

#endif
