#ifndef INCLUDED_SROOK_CXX20_CONCEPT_SAME_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_SAME_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_same.hpp>

namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template<class T, class U>
SROOK_CONCEPT Same = type_traits::is_same<T, U>::value;

SROOK_INLINE_NAMESPACE_END
} // namespace concepts
} // namespace srook

#endif
