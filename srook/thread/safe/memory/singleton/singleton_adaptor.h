#ifndef INCLUDED_SROOK_THREAD_SAFE_MEMORY_SINGLETON_SINGLETON_ADAPTOR_H
#define INCLUDED_SROOK_THREAD_SAFE_MEMORY_SINGLETON_SINGLETON_ADAPTOR_H

#include <srook/config.hpp>

namespace srook {
namespace threading {
namespace safe {
SROOK_INLINE_NAMESPACE(v1)

template <class>
class singleton_adaptor;

SROOK_INLINE_NAMESPACE_END
} // namespace safe
} // threading

namespace thread_safe {
namespace memory {

using srook::threading::safe::singleton_adaptor;

} // namespace memory
} // namespace thread_safe

} // srook

#endif
