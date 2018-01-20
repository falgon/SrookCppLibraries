#ifndef INCLUDED_SROOK_CXX20_CONCEPT_EQUALITY_COMPARABLE_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_EQUALITY_COMPARABLE_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_convertible.hpp>
#include <srook/utility/declval.hpp>
#if SROOK_HAS_CONCEPTS

namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template<class T>
SROOK_CONCEPT EqualityComparable = is_convertible<SROOK_DECLTYPE(declval<T>() == declval<T>()), bool>::value;

SROOK_INLINE_NAMESPACE_END
} // namespace concepts
} // namespace srook

#endif
#endif
