#ifndef INCLUDED_SROOK_CXX20_CONCEPT_CHAR_TYPE
#define INCLUDED_SROOK_CXX20_CONCEPT_CHAR_TYPE
#include <string>
#include <srook/cxx20/concepts/workaround/workaround.hpp>

namespace srook{
namespace concepts{

template<typename T>
SROOK_CONCEPT CharType = requires { typename std::char_traits<T>::char_type; };

} // concepts
} // namespace srook

#endif
