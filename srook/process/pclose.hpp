// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_PROCESS_PCLOSE_HPP
#define INCLUDED_SROOK_PROCESS_PCLOSE_HPP

#include <srook/config/env.hpp>

#if defined(__linux__) || defined(__unix__) || defined(__FreeBSD__) || defined(__unix) || defined(unix) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__APPLE__)
#    define SROOK_PCLOSE(s) ::pclose(s)
#elif defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#    define SROOK_PCLOSE(s) ::_pclose(s)
#else
#    error This environment is not supported pclose
#endif

#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace process {
SROOK_INLINE_NAMESPACE(v1)

SROOK_DEPRECATED SROOK_ALWAYS_INLINE int pclose(std::FILE* stream) SROOK_NOEXCEPT_TRUE
{
    return SROOK_PCLOSE(stream);
}

SROOK_INLINE_NAMESPACE_END
} // namespace process
} // namespace srook

#    undef SROOK_PCLOSE
#endif
