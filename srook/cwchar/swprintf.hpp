// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CWCHAR_SWPRINTF_HPP
#define INCLUDED_SROOK_CWCHAR_SWPRINTF_HPP

#include <cwchar>
#include <cstdarg>
#include <srook/config.hpp>

#ifdef __GNUC__
#   pragma GCC diagnostic ignored "-Wuninitialized"
#endif

namespace srook {
namespace cwchar {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

typedef int (*wide_printf)(wchar_t* SROOK_RESTRICT, std::size_t, const wchar_t* SROOK_RESTRICT, ...);

SROOK_FORCE_INLINE wide_printf get_swprintf()
{
    return
#ifndef SROOK_MSVCRT
    std::swprintf
#else
    static_cast<int (__cdecl*)(wchar_t* SROOK_RESTRICT, size_t, const wchar_t* SROOK_RESTRICT, ...)>(_snwprintf);
#endif
        ;
}

} // namespace detail

int swprintf(wchar_t* SROOK_RESTRICT buffer, std::size_t count, const wchar_t* SROOK_RESTRICT format, ...)
{
    va_list args;
    va_start(args, format);
    int res = detail::get_swprintf()(buffer, count, format, args);
    va_end(args);
    return res;
}

SROOK_INLINE_NAMESPACE_END
} // namespace cwchar

using cwchar::swprintf;

} // namespace srook

#endif
