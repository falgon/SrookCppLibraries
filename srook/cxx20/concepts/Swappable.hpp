#ifndef INCLUDED_SROOK_CXX20_CONCEPT_SWAPPABLE_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_SWAPPABLE_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_swappable.hpp>
#if SROOK_HAS_CONCEPTS

namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template<class T>
SROOK_CONCEPT Swappable = type_traits::is_swappable<T>::value;

SROOK_INLINE_NAMESPACE_END
} // namespace concepts
} // namespace srook

#endif
#endif
