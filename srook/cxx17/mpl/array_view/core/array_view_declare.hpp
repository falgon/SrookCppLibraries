#ifndef INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_DECLARE_HPP
#define INCLUDED_SROOK_CXX17_MPL_ARRAY_VIEW_DECLARE_HPP
#include <srook/config/feature/inline_namespace.hpp> 
#include <cstddef>

namespace srook {
namespace cxx17 {
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)

template <auto*, std::size_t = 0>
struct array_view;

SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
} // namespace cxx17

using cxx17::array_view;

} // namespace srook

#endif
