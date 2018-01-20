#ifndef INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_BIDIRECTIONAL_ITERATOR_HPP
#define INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_BIDIRECTIONAL_ITERATOR_HPP
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>

#if SROOK_HAS_CONCEPTS
namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template <class Iter>
SROOK_CONCEPT BidirectionalIterator = srook::concepts::ForwardIterator<Iter> && requires (Iter a) {
    { --a } -> Iter&;
    { *a-- } -> SROOK_DEDUCED_TYPENAME std::iterator_traits<Iter>::reference;
} && is_convertible<SROOK_DECLTYPE(declval<Iter>()--), const Iter&>::value;

SROOK_INLINE_NAMESPACE_END
} // namespace concepts
} // namespace srook

#endif
#endif
