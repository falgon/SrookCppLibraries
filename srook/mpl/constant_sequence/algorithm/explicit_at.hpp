#ifndef INCLUDED_SROOK_MPL_CONSTANT_RANGE_EXPLICIT_AT_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_RANGE_EXPLICIT_AT_HPP
#include <utility>

namespace srook {
inline namespace mpl {
namespace constant_sequence {
inline namespace v1 {

template <class, std::size_t, class>
struct explicit_at;

template <class T, std::size_t target, T head, T... tail>
struct explicit_at<T, target, std::integer_sequence<T, head, tail...>> {
    static constexpr T value = explicit_at<T, target - 1, std::integer_sequence<T, tail...>>::value;
    constexpr operator T() const noexcept { return value; }
    constexpr T operator()() const noexcept { return value; }
};
template <class T, T target, T... tail>
struct explicit_at<T, 0, std::integer_sequence<T, target, tail...>> {
    static constexpr T value = target;
    constexpr operator T() const noexcept { return value; }
    constexpr T operator()() const noexcept { return value; }
};

template <class T, std::size_t target_index, class Seq>
static constexpr T explicit_at_v = explicit_at<T, target_index, Seq>::value;

} // namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook

#endif
