#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_EXPLICIT_CONCAT_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_ALGORITHM_EXPLICIT_CONCAT_HPP

#include <utility>

namespace srook {
inline namespace mpl {
namespace constant_sequence {
inline namespace v1 {

template <class, class, class>
struct explicit_concat;

template <class T, T... l, T... r>
struct explicit_concat<T, std::integer_sequence<T, l...>, std::integer_sequence<T, r...>> {
    using type = std::integer_sequence<T, l..., r...>;
};

template <class T, class L, class R>
using explicit_concat_t = typename explicit_concat<T, L, R>::type;

} // namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook

#endif
