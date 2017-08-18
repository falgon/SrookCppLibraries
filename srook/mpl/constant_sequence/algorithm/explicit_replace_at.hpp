#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_EXPLICIT_REPLACE_AT_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_EXPLICIT_REPLACE_AT_HPP

#include <srook/mpl/constant_sequence/algorithm/explicit_concat.hpp>
#include <utility>

namespace srook {
inline namespace mpl {
namespace constant_sequence {
inline namespace v1 {

template <class T, std::size_t, T, class>
struct explicit_replace_at;

template <class T, std::size_t target_index, T replace_value, T head, T... tail>
struct explicit_replace_at<T, target_index, replace_value, std::integer_sequence<T, head, tail...>> {
    using type = explicit_concat_t<T, std::integer_sequence<T, head>, typename explicit_replace_at<T, target_index - 1, replace_value, std::integer_sequence<T, tail...>>::type>;
};

template <class T, T replace_value, T head, T... tail>
struct explicit_replace_at<T, 0, replace_value, std::integer_sequence<T, head, tail...>> {
    using type = explicit_concat_t<T, std::integer_sequence<T, replace_value>, std::integer_sequence<T, tail...>>;
};

template <class T, std::size_t target_index, T replace_value, class Seq>
using explicit_replace_at_t = typename explicit_replace_at<T, target_index, replace_value, Seq>::type;

} // namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook

#endif
