#ifndef INCLUDED_SROOK_CXX17_MPL_ANY_PACK_RANDOM_MAKER_CORE_MAKE_RANDOM_SEQUENCE_DECLARE_HPP
#define INCLUDED_SROOK_CXX17_MPL_ANY_PACK_RANDOM_MAKER_CORE_MAKE_RANDOM_SEQUENCE_DECLARE_HPP
#include<srook/cxx17/mpl/any_pack/core/any_pack_declare.h>
#include<srook/cxx17/mpl/any_pack/random/engines/linear_congruential.hpp>
#include<srook/cxx17/mpl/any_pack/random/engines/Xorshift.hpp>
#include<srook/cxx17/mpl/any_pack/random/uniform_distribution/uniform_int_distribution.hpp>

namespace srook{
inline namespace mpl{
namespace random{
inline namespace v1{

template<std::size_t,class,class> struct make_random_sequence_impl;

} // namespace v1
} // namespace random
} // inline namespace mpl
} // namespace srook
#endif
