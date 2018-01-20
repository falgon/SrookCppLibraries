#ifndef INCLUDED_SROOK_CXX20_CONCEPT_CHAR_TYPE
#define INCLUDED_SROOK_CXX20_CONCEPT_CHAR_TYPE
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_character.hpp>
#include <string>
#if SROOK_HAS_CONCEPTS

namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template<typename T>
SROOK_CONCEPT CharType = srook::type_traits::is_character<T>::value;

SROOK_INLINE_NAMESPACE_END
} // namespace concepts
} // namespace srook

#endif
#endif
