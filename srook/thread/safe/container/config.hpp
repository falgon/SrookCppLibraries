// Copyright (C) 2011-2018 Roki. Distributed under the MIT License 
#ifndef INCLUDED_SROOK_THREAD_SAFE_CONTAINER_CONFIG_HPP
#define INCLUDED_SROOK_THREAD_SAFE_CONTAINER_CONFIG_HPP

#include <exception>
#include <srook/config/feature.hpp>

namespace srook {
namespace threading {
namespace safe {
SROOK_INLINE_NAMESPACE(v1)

struct aborted : public std::exception {
    aborted() SROOK_DEFAULT
    virtual const char* what() const SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE
    {
        return "srook::thread_safe: Aborted";
    }
    virtual ~aborted() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
};
SROOK_STRONG_ENUM_BEGIN(behavior) {
    wait_pushed,
    no_wait_pushed
};
SROOK_STRONG_ENUM_EPILOG(perform)

SROOK_INLINE_NAMESPACE_END
} // namespace safe
} // namespace threading

namespace thread_safe {
namespace container {
SROOK_INLINE_NAMESPACE(v1)

using srook::threading::safe::behavior;

SROOK_INLINE_NAMESPACE_END
} // container
} // namespace thread_safe

namespace exception {
SROOK_INLINE_NAMESPACE(v1)
	
using srook::threading::safe::aborted;

SROOK_INLINE_NAMESPACE_END
} // namespace exception

} // namespace srook


#endif
