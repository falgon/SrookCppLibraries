// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_PROCESS_POPEN_HPP
#define INCLUDED_SROOK_PROCESS_POPEN_HPP

#include <srook/config/env.hpp>

#if defined(__linux__) || defined(__unix__) || defined(__FreeBSD__) || defined(__unix) || defined(unix) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__APPLE__)
#	define SROOK_POPEN(cmd, type) ::popen(cmd, type)
#elif defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__CYGWIN32__)
#	define SROOK_POPEN(cmd, type) ::_popen(cmd, type)
#	if defined(_UNICODE)
#		define SROOK_WPOPEN ::_wpopen(cmd, type)
#	endif
#else
#	error This environment is not supported popen
#endif

#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/attribute/deprecated.hpp>

namespace srook {
namespace process {
SROOK_INLINE_NAMESPACE(v1)

SROOK_ALWAYS_INLINE
std::FILE* popen(const char* cmd, const char* type)
{
	return SROOK_POPEN(cmd, type);
}

#ifdef WPOPEN
SROOK_ALWAYS_INLINE
std::FILE* popen(const wchar_t* cmd, const wchar_t* type)
{
	return SROOK_WPOPEN(cmd, type);
}
#undef WPOPEN
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace process
} // namespace srook

#undef SROOK_POPEN
#endif
