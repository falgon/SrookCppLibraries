#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_DETAIL_DOUBLE_CONVERT_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_DETAIL_DOUBLE_CONVERT_HPP

#include<cstdint>
#include<srook/config/attribute/deprecated.hpp>

namespace srook {
inline namespace mpl {
namespace constant_sequence {
namespace math {
inline namespace v1 {
namespace detail {

constexpr std::int64_t to_integer = 10000000000000000;

struct Realvalue {
    explicit constexpr Realvalue() = default;
    template <class T>
    constexpr double operator()(T &&v) const
    {
	return double(v) / to_integer;
    }
};

} // namespace detail
} // namespace v1
} // namespace math

using namespace math::detail;

} // namespace constant_sequence
} // namespace mpl
} // namespace srook
#endif
