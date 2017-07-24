#ifndef INCLUDED_SROOK_CXX17_ANY_PACK_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP
#define INCLUDED_SROOK_CXX17_ANY_PACK_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP
#include<srook/cxx17/mpl/any_pack/random/engines/linear_congruential.hpp>

namespace srook{
inline namespace mpl{
namespace random{
inline namespace v1{

template<class RandomEngine,auto min,auto max>
struct uniform_int_distribution{
	static_assert(std::is_integral_v<decltype(min)> and std::is_integral_v<decltype(max)>);
	static_assert(max < RandomEngine::max());
	static_assert(min < RandomEngine::max());
	static_assert(min <= max);
	using result_type = typename RandomEngine::result_type;
private:
	static constexpr result_type r = RandomEngine::result;
public:
	static constexpr result_type result = r % (max - min + 1) + min;
};

} // inline namespace v1
} // namespace random
} // inline namespace mpl
} // namespace srook

#endif
