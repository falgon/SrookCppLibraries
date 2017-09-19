#ifndef INCLUDED_SROOK_CXX20_CONCEPT_CHAR_TYPE
#define INCLUDED_SROOK_CXX20_CONCEPT_CHAR_TYPE
#include <string>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_character.hpp>

namespace srook{
namespace concepts{

template<typename T>
SROOK_CONCEPT CharType = srook::type_traits::is_character<T>::value;

} // concepts
} // namespace srook

#endif
