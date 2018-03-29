// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_RANDOM_MERSENNE_TWISTER_HPP
#define INCLUDED_SROOK_CXX17_MPL_RANDOM_MERSENNE_TWISTER_HPP
#include<cstdint>
#include<type_traits>
#include<utility>
#include<srook/mpl/constant_sequence/algorithm/at.hpp>
#include<srook/cxx17/mpl/any_pack/random/engines/algorithm/discard.hpp>

namespace srook{
namespace vmpl {
inline namespace mpl{
namespace random{
inline namespace v1{

namespace detail{

template<class,std::size_t,std::size_t,class,class,std::size_t,class = std::nullptr_t> struct initialize;

template<class UIntType,std::size_t i,std::size_t until_max,UIntType... v,UIntType initialization_multiplier,UIntType seed,std::size_t word_size>
struct initialize<UIntType,i,until_max,std::integer_sequence<UIntType,v...>,std::integer_sequence<UIntType,initialization_multiplier,seed>,word_size,std::enable_if_t<(i < until_max),std::nullptr_t>>{
private:
	static constexpr UIntType value = (!i) ? seed : (initialization_multiplier * (seed ^ (seed >> (word_size - 2))) + i);
public:
	using type = 
		typename initialize<
			UIntType,
			i + 1,until_max,
			std::integer_sequence<UIntType,v...,value>,
			std::integer_sequence<UIntType,initialization_multiplier,value>,
			word_size
		>::type;
};

template<class UIntType,std::size_t i,std::size_t until_max,UIntType... v,UIntType initialization_multiplier,UIntType seed,std::size_t word_size>
struct initialize<UIntType,i,until_max,std::integer_sequence<UIntType,v...>,std::integer_sequence<UIntType,initialization_multiplier,seed>,word_size,std::enable_if_t<!(i < until_max),std::nullptr_t>>{
	using type = std::integer_sequence<UIntType,v...>;
};

template<class UIntType,std::size_t begin,std::size_t end,class Anypack,std::size_t word_size,class arg = std::integer_sequence<UIntType>>
using initialize_t = typename initialize<UIntType,begin,end,arg,Anypack,word_size>::type;

} // namespace detail

template<
	class UIntType,
	UIntType seed,
	std::size_t w,std::size_t n,std::size_t m,std::size_t r,
	UIntType a,std::size_t u,UIntType d,std::size_t s,
	UIntType b,std::size_t t,
	UIntType c,std::size_t l,UIntType f,
	UIntType next_index = 0
>
struct mersenne_twister{
private:
	static_assert(std::is_unsigned_v<UIntType>,"result_type must be an unsigned integral type");
	static_assert(1u <= m && m <= n,"template argument substituting m out of bounds");
	static_assert(r <= w, "template argument substituting r out of bound");
	static_assert(u <= w, "template argument substituting u out of bound");
	static_assert(s <= w, "template argument substituting s out of bound");
	static_assert(t <= w, "template argument substituting t out of bound");
	static_assert(l <= w, "template argument substituting l out of bound");
	static_assert(w <= std::numeric_limits<UIntType>::digits,"template argument substituting w out of bound");
public:
	using result_type = UIntType;
	static constexpr std::size_t word_size = w;
	static constexpr std::size_t state_size = n;
	static constexpr std::size_t shift_size = m;
	static constexpr std::size_t mask_bits = r;
	static constexpr result_type xor_mask = a;
	static constexpr std::size_t tempering_u = u;
	static constexpr result_type tempering_d = d;
	static constexpr std::size_t tempering_s = s;
	static constexpr result_type tempering_b = b;
	static constexpr std::size_t tempering_t = t;
	static constexpr result_type tempering_c = c;
	static constexpr std::size_t tempering_l = l;
	static constexpr result_type initialization_multiplier = f;

	static constexpr result_type min(){return 0;}
	static constexpr result_type max(){return (2 ^ word_size) - 1;}
private:
	static constexpr result_type mask_lower = (static_cast<UIntType>(1) << mask_bits) - 1;
	static constexpr result_type mask_upper = ~mask_lower;
	static constexpr result_type i = next_index;

	using init_array = detail::initialize_t<result_type,0,state_size,std::integer_sequence<result_type,initialization_multiplier,seed>,word_size>;

	template<std::size_t x_>
	static constexpr result_type mt = srook::constant_sequence::at_v<x_,init_array,result_type>;

	// twist
	struct twist{
		static constexpr result_type x = (mt<i> & mask_upper) + (mt<(i + 1) % state_size> & mask_lower);
		static constexpr result_type xA_ = x >> 1;
		static constexpr result_type xA = !(x & 0x1) ? xA_ : (xA_ ^ xor_mask);
		static constexpr result_type mt_0 = mt<(i + shift_size) % state_size> ^ xA;
	};

	// extract
	static constexpr result_type y = twist::mt_0;
	static constexpr result_type next_value = mt<i + 1>;
	static constexpr result_type y1 = y ^ (twist::mt_0 >> tempering_u) & tempering_d;
	static constexpr result_type y2 = y1 ^ (y1 << tempering_s) & tempering_b;
	static constexpr result_type y3 = y2 ^ (y2 << tempering_t) & tempering_c;
public:
	static constexpr result_type result = y3 ^ (y3 >> tempering_l);
	using next_type = 
		mersenne_twister<
			result_type,seed,
			word_size,state_size,shift_size,mask_bits,
			xor_mask,tempering_u,tempering_d,tempering_s,
			tempering_b,tempering_t,
			tempering_c,tempering_l,
			initialization_multiplier,
			i + 1
		>;

	template<unsigned long long z>
	using discard_type = 
		discard_t<
			z,
			mersenne_twister<
				result_type,seed,
				word_size,state_size,shift_size,mask_bits,
				xor_mask,tempering_u,tempering_d,tempering_s,
				tempering_b,tempering_t,
				tempering_c,tempering_l,
				initialization_multiplier,
				next_index
			>
		>;
};

template<auto seed = 5489u>
using mt11213b =
	mersenne_twister<
		std::uint_fast32_t,
		seed,
		32,351,175,19,
		0xccab8ee7,11,0xffffffff,7,
		0x31b6ab00,15,0xffe50000,17,1812433253UL
	>;

template<auto seed = 5489u>
using mt19937 = 
	mersenne_twister<
		std::uint_fast32_t,
		seed,
		32,624,397,31,
		0x9908b0dfUL,11,0xffffffffUL,7,
		0x9d2c5680UL,15,0xefc60000UL,18,1812433253UL
	>;

template<auto seed = 5489u>
using mt19937_64 = 
	mersenne_twister<
		std::uint_fast64_t,
		seed,
		64,312,156,31,
		0xb5026f5aa96619e9ULL,29,0x5555555555555555ULL,17,
		0x71d67fffeda60000ULL,37,0xfff7eee000000000ULL,43,6364136223846793005ULL
	>;	

} // inline namespace v1
} // namespace random
} // inline namespace mpl
} // namespace vmpl
} // namespace srook

#endif
