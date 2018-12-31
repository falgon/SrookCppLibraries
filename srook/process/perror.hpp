// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_PROCESS_PERROR_HPP
#define INCLUDED_SROOK_PROCESS_PERROR_HPP

#include <srook/config/env.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/compiler/msvc/includes/windows.h>
#include <cerrno>
#include <iostream>

SROOK_NESTED_NAMESPACE(srook, process) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

SROOK_FORCE_INLINE std::ostream& fixedformat_out(std::ostream& os, const char* er, std::string s)
{
    return os << er << ": " << s;
}

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(process, srook)

#ifdef SROOK_CONFIG_USE_BOOST_SYSTEM_ERROR
#include <boost/system/system_error.hpp>

SROOK_NESTED_NAMESPACE(srook, process) {
SROOK_INLINE_NAMESPACE(v1)

inline void perror(const char* message)
{
#ifdef _MSC_VER
    detail::fixedformat_out(std::cerr, message, boost::system::error_code(::GetLastError(), boost::system::system_category()).message())
#else
    detail::fixedformat_out(std::cerr, message, boost::system::error_code(errno, boost::system::get_system_category()).message())
#endif
    << std::endl;
}

#else

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <system_error>

SROOK_NESTED_NAMESPACE(srook, process) {
SROOK_INLINE_NAMESPACE(v1)
    
inline void perror(const char* message)
{
#ifdef _MSC_VER
    detail::fixedformat_out(std::cerr, message, std::error_code(::GetLastError(), std::system_category()).message())
#else
    detail::fixedformat_out(std::cerr, message, std::error_code(errno, std::generic_category()).message())
#endif
    << std::endl;
}

#else
#include <cstdio>

SROOK_NESTED_NAMESPACE(srook, process) {
SROOK_INLINE_NAMESPACE(v1)

inline void perror(const char* message) SROOK_NOEXCEPT_TRUE
{
#if _MSC_VER
    LPVOID lp = SROOK_NULLPTR;
    if (::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, ::GetLastError(), LANG_USER_DEFAULT, static_cast<LPTSTR>(&lp), 0, NULL)) {
        detail::fixedformat_out(std::cerr, message, lp) << std::endl;
        ::LocalFree(lp);
        lp = SROOK_NULLPTR;
    }
#else
    detail::fixedformat_out(std::cerr, message, std::strerror(errno)) << std::endl;
#endif
}

#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(process, srook)

#endif
#endif
