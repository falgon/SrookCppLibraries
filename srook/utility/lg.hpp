#ifndef INCLUDED_SROOK_UTILITY_LG_HPP
#define INCLUDED_SROOK_UTILITY_LG_HPP
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook{
namespace impl{
SROOK_INLINE_NAMESPACE(v1)

template<typename Size>
SROOK_CONSTEXPR_OR_CONST inline Size lg(Size n)
{
	return n ? 1 + lg(n >>= 1) : -1;
}

SROOK_INLINE_NAMESPACE_END
} // namespace impl
} // namespace srook 

#endif
