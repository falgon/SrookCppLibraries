// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_RANDOM_LINEAR_CONGRUENTIAL_HPP
#define INCLUDED_SROOK_CXX17_MPL_RANDOM_LINEAR_CONGRUENTIAL_HPP
#include<cstdint>
#include<climits>
#include<type_traits>
#include<srook/cxx17/mpl/any_pack/random/engines/algorithm/discard.hpp>
#include<srook/utility/lg.hpp>

namespace srook{
inline namespace mpl{
namespace random{
inline namespace v1{

namespace detail{
	
template<
	int s,
	int which = ((s <= CHAR_BIT * sizeof(int)) + (s <= CHAR_BIT * sizeof(long)) + (s <= CHAR_BIT * sizeof(long long)) + (s <= 128))
>
struct Select_uint_least_t{
	static_assert(which < 0);
};

template<int s>
struct Select_uint_least_t<s,4>{
	typedef unsigned int type;
};
template<int s>
struct Select_uint_least_t<s,3>{
	typedef unsigned long type;
};
template<int s>
struct Select_uint_least_t<s,2>{
	typedef unsigned long long type;
};

} // namespace detail


template<class UIntType,UIntType seed,UIntType A,UIntType C,UIntType M>
struct linear_congruential{
	using result_type = UIntType;
private:
	static_assert(std::is_unsigned_v<UIntType>,"result_type must be an unsigned integral type");
	static_assert(M == 0 || (A < M && C < M),"template argument substituting m out of bounds");
	using Value_tp = typename detail::Select_uint_least_t<srook::impl::lg(A) + srook::impl::lg(M) + 2>::type;
public:
	static constexpr result_type multiplier = A;
	static constexpr result_type increment = C;
	static constexpr result_type modulus = M;
	static constexpr result_type min(){return C == 0u ? 1u : 0u;}
	static constexpr result_type max(){return M - 1u;}
	static constexpr result_type result = static_cast<result_type>((seed * Value_tp(multiplier) + increment) & modulus);
	using next_type = linear_congruential<result_type,result,A,C,M>;
	template<unsigned long long z>
	using discard_type = discard_t<z,linear_congruential<result_type,seed,A,C,M>>;
};

template<std::uint_fast32_t seed = 1>
using minstd_rand0 = linear_congruential<std::uint_fast32_t,seed,16807UL,0UL,2147483647UL>;

template<std::uint_fast32_t seed = 1>
using minstd_rand = linear_congruential<std::uint_fast32_t,seed,48271UL,0UL,2147483647UL>;


} // inline namespace v1
} // namespace random
} // inline namespace mpl
} // namespace srook

#endif
