#ifndef INCLUDED_SROOK_CXX20_CONCEPT_CHAR_TYPE
#define INCLUDED_SROOK_CXX20_CONCEPT_CHAR_TYPE
#include <string>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_character.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook{
namespace concepts{
SROOK_INLINE_NAMESPACE(v10

template<typename T>
SROOK_CONCEPT CharType = srook::type_traits::is_character<T>::value;

SROOK_INLINE_NAMESPACE_END
} // concepts
} // namespace srook

#endif
