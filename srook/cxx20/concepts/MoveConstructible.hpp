#ifndef INCLUDED_SROOK_CXX20_CONCEPT_MOVECONSTRUCTIBLE_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_MOVECONSTRUCTIBLE_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/cxx20/concepts/Constructible.hpp>
#include <srook/cxx20/concepts/ConvertibleTo.hpp>
#if SROOK_HAS_CONCEPTS

namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template<class T>
SROOK_CONCEPT MoveConstructible = Constructible<T, T> && ConvertibleTo<T, T>;

SROOK_INLINE_NAMESPACE_END
} // namespace concepts
} // namespace srook

#endif
#endif
