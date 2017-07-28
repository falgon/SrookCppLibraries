#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_RANDOM_ALGORITHM_DISCARD_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_RANDOM_ALGORITHM_DISCARD_HPP

namespace srook{
inline namespace mpl{
namespace random{
inline namespace v1{

template<unsigned long long z,class RandomEngine>
struct discard{
	using type = typename discard<z-1,typename RandomEngine::next_type>::type;
};
template<class RandomEngine>
struct discard<0,RandomEngine>{
	using type = RandomEngine;
};

template<unsigned long long z,class RandomEngine>
using discard_t = typename discard<z,RandomEngine>::type;

} // inline namespace v1
} // namespace random
} // inline namespace mpl
} // namespace srook

#endif
