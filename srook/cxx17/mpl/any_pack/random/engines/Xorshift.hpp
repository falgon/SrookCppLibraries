#ifndef INCLUDED_SROOK_CXX17_MPL_RANDOM_XOR_SHIFT_HPP
#define INCLUDED_SROOK_CXX17_MPL_RANDOM_XOR_SHIFT_HPP
#include<cstdint>
#include<type_traits>
#include<limits>

namespace srook{
inline namespace mpl{
namespace random{
inline namespace v1{

template<class UIntType = std::uint_fast32_t,UIntType Y = 2463534242>
struct Xorshift32{
	using result_type = UIntType;
private:
	static_assert(std::is_unsigned_v<UIntType>);
	static constexpr result_type inner1 = Y ^ (Y << 13);
	static constexpr result_type inner2 = inner1 ^ (inner1 >> 17);
public:
	static constexpr result_type min(){return 0;}
	static constexpr result_type max(){return std::numeric_limits<UIntType>::max();}
	static constexpr result_type result = inner2 ^ (inner2 << 5);
};

template<class UIntType = std::uint_fast64_t,UIntType Y = 88172645463325252ULL>
struct Xorshift64{
	using result_type = UIntType;
private:
	static_assert(std::is_unsigned_v<UIntType>);
	static constexpr result_type inner1 = Y ^ (Y << 13);
	static constexpr result_type inner2 = inner1 ^ (inner1 >> 7);
public:
	static constexpr result_type min(){return 0;}
	static constexpr result_type max(){return std::numeric_limits<UIntType>::max();}
	static constexpr result_type result = inner2 ^ (inner2 << 17);
};

template<class UIntType = std::uint_fast32_t,UIntType X = 123456789,UIntType Y = 362436069,UIntType Z = 521288629>
struct Xorshift96{
private:
	static_assert(std::is_unsigned_v<UIntType>);
public:
	using result_type = UIntType;
	static constexpr result_type x = Y;
	static constexpr result_type y = Z;
	static constexpr result_type result = (X ^ (X << 3)) ^ (Y ^ (Y >> 19)) ^ (Z ^ (Z << 6));
	static constexpr result_type min(){return 0;}
	static constexpr result_type max(){return std::numeric_limits<UIntType>::max();}
};

template<class UIntType = std::uint_fast32_t,UIntType X = 123456789,UIntType Y = 362436069,UIntType Z = 521288629,UIntType W = 88675123>
struct Xorshift128{
private:
	static_assert(std::is_unsigned_v<UIntType>);
public:
	using result_type = UIntType;
	static constexpr result_type t = X ^ (X << 11);
	static constexpr result_type x = Y;
	static constexpr result_type y = Z;
	static constexpr result_type z = W;
	static constexpr result_type result = (W ^ (W >> 19)) ^ (t ^ (t >> 8));
	static constexpr result_type min(){return 0;}
	static constexpr result_type max(){return std::numeric_limits<UIntType>::max();}
};

} // inline namespace v1
} // namespace random
} // inline namespace mpl
} // namespace srook

#endif
