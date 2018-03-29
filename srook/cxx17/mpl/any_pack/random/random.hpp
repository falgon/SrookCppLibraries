#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_RANDOM_RANDOM_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_RANDOM_RANDOM_HPP

#include<srook/cxx17/mpl/any_pack/random/maker/make_random_sequence.hpp>
#include<srook/cxx17/mpl/any_pack/random/engines/linear_congruential.hpp>
#include<srook/cxx17/mpl/any_pack/random/engines/Xorshift.hpp>
#include<srook/cxx17/mpl/any_pack/random/engines/mersenne_twister.hpp>
#include<srook/cxx17/mpl/any_pack/random/uniform_distribution/uniform_int_distribution.hpp>

namespace srook{
namespace vmpl {
inline namespace mpl{
namespace random{
inline namespace v1{

typedef minstd_rand0<> default_random_engine;

} // inline namespace v1
} // namespace random 
} // inline namespace mpl
} // namespace vmpl
} // namespace srook
#endif
