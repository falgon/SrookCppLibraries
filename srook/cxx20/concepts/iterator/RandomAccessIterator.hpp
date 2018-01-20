#ifndef INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP
#define INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_RANDOM_ACCESS_ITERATOR_HPP
#include <srook/cxx20/concepts/iterator/BidirectionalIterator.hpp>
#include <srook/cxx20/concepts/iterator/OutputIterator.hpp>
#if SROOK_HAS_CONCEPTS
namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template <class Iter>
SROOK_CONCEPT RandomAccessIterator = srook::concepts::BidirectionalIterator<Iter> && 
requires (Iter i, Iter a, Iter b, const Iter ci, const Iter ca, const Iter cb, Iter& r, SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::difference_type n) {
    { r += n } -> Iter&;
    { a + n } -> Iter;
    { ca + n } -> Iter;
    { n + a } -> Iter;
    { n + ca } -> Iter;
    { r -= n } -> Iter&;
    { ci - n } -> Iter;
    { i - n } -> Iter;
    { b - a } -> SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::difference_type;
    { cb - ca } -> SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::difference_type;
    { b - ca } -> SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::difference_type;
    { cb - a } -> SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::difference_type;
    { a < b } -> bool;
    { ca < cb } -> bool;
    { ca < b } -> bool;
    { a < cb } -> bool;
    { a > b } -> bool;
    { ca > cb } -> bool;
    { a > cb } -> bool;
    { ca > b } -> bool;
    { a >= b } -> bool;
    { ca >= cb } -> bool;
    { ca >= b } -> bool;
    { a >= cb } -> bool;
    { a <= b } -> bool;
    { ca <= cb } -> bool;
    { ca <= b } -> bool;
    { a <= cb } -> bool;
} && is_convertible<SROOK_DECLTYPE(declval<Iter>()[declval<SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::difference_type>()]), bool>::value
&& conditional<is_const<Iter>::value, bool_constant<OutputIterator<Iter>>, SROOK_TRUE_TYPE>::type::value;

SROOK_INLINE_NAMESPACE_END
} // namespace concepts
} // namespace srook

#endif
#endif
