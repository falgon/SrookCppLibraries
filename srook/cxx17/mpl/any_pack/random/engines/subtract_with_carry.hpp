// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CXX17_MPL_RANDOM_SUBTRACT_CARRY_ENGINE_HPP
#define INCLUDED_SROOK_CXX17_MPL_RANDOM_SUBTRACT_CARRY_ENGINE_HPP
#include<cstdint>
#include<type_traits>

namespace srook{
namespace vmpl {
inline namespace mpl{
namespace random{
inline namespace v1{

template<class UIntType,UIntType seed,UIntType w,UIntType s,UIntType r>
struct subtract_with_carry{
	using result_type = UIntType;
private:
	static_assert(std::is_unsigned_v<UIntType>);
	static constexpr result_type word_size = w;
	static constexpr result_type short_tag = s;
	static constexpr result_type long_tag = r;
public:
	static constexpr result_type min(){return 0;}
	static constexpr result_type max(){return M - 1u;}
	static constexpr result_type result = 0;
};

using ranlux24_base = subtract_with_carry<std::uint_fast32_t,24,10,24>;
using ranlux48_base = subtract_with_carry<std::uint_fast32_t,48,5,12>;

} // inline namespace v1
} // namespace random
} // inline namespace mpl
} // namespace vmpl
} // namespace srook

#endif
