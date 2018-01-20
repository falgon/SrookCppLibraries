#ifndef INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_INPUT_ITERATOR_HPP
#define INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_INPUT_ITERATOR_HPP
#include <srook/cxx20/concepts/iterator/Iterator.hpp>
#include <srook/cxx20/concepts/EqualityComparable.hpp>
#if SROOK_HAS_CONCEPTS
namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template <class Iter>
SROOK_CONCEPT InputIterator = srook::concepts::Iterator<Iter> && srook::concepts::EqualityComparable<Iter> && 
requires (Iter i, Iter j) {
    { i != j } -> bool;
    { *i } -> SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::reference;
    { ++i } -> Iter&;
    { *i++ } -> SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type;
    { *i } -> SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type;
    (void)i++;
};

SROOK_INLINE_NAMESPACE_END

} // namespace concepts
} // namespace srook

#endif
#endif
