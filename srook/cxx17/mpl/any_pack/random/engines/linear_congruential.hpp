// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CXX17_MPL_RANDOM_LINEAR_CONGRUENTIAL_HPP
#define INCLUDED_SROOK_CXX17_MPL_RANDOM_LINEAR_CONGRUENTIAL_HPP
#include<cstdint>
#include<type_traits>
#include<srook/cxx17/mpl/any_pack/random/engines/algorithm/discard.hpp>

namespace srook{
inline namespace mpl{
namespace random{
inline namespace v1{

template<class UIntType,UIntType seed,UIntType A,UIntType C,UIntType M>
struct linear_congruential{
	using result_type = UIntType;
private:
	static_assert(std::is_unsigned_v<UIntType>);
	static_assert(M == 0 || A < M);
	static_assert(M == 0 || C < M);
public:
	static constexpr result_type multiplier = A;
	static constexpr result_type increment = C;
	static constexpr result_type modulus = M;
	static constexpr result_type min(){return C == 0u ? 1u : 0u;}
	static constexpr result_type max(){return M - 1u;}
	static constexpr result_type result = (seed * A + C) & M;
	using next_type = linear_congruential<UIntType,result,A,C,M>;
	template<unsigned long long z>
	using discard_type = discard_t<z,linear_congruential<UIntType,seed,A,C,M>>;
};

template<std::uint_fast32_t seed = 1>
using minstd_rand0 = linear_congruential<std::uint_fast32_t,seed,16807u,0,2147483647>;

template<std::uint_fast32_t seed = 1>
using minstd_rand = linear_congruential<std::uint_fast32_t,seed,48271u,0,2147483647>;

} // inline namespace v1
} // namespace random
} // inline namespace mpl
} // namespace srook

#endif
