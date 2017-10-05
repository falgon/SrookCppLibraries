#ifndef INCLUDED_SROOK_CXX20_CONCEPT_CONVERTIBLETO_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_CONVERTIBLETO_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/type_traits/is_convertible.hpp>

namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template<class From, class To>
SROOK_CONCEPT ConvertibleTo = type_traits::is_convertible<From, To>::value &&
requires(From (&f)()) {
	static_cast<To>(f());
};

SROOK_INLINE_NAMESPACE_END
} // namespace concepts
} // namespace srook

#endif
