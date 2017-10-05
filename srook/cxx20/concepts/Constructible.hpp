#ifndef INCLUDED_SROOK_CXX20_CONCEPT_CONSTRUCTIBLE_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_CONSTRUCTIBLE_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_constructible.hpp>

namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template<class T>
SROOK_CONCEPT Constructible = type_traits::is_constructible<T>::value;

SROOK_INLINE_NAMESPACE_END
} // namespace concepts
} // namespace srook

#endif
