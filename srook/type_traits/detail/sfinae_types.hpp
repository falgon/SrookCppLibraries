#ifndef INCLUDED_SROOK_TYPE_TRAITS_DETAIL_SFINAE_TYPES_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DETAIL_SFINAE_TYPES_HPP
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {
struct sfinae_types {
	typedef char one;
	typedef struct { char c[2]; } two;
};
} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits
} // namespace srook

#endif
