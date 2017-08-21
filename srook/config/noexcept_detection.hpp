#ifndef INCLUDED_SROOK_CONFIG_NOEXCEPT_DETECTION_HPP
#define INCLUDED_SROOK_CONFIG_NOEXCEPT_DETECTION_HPP
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if (SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)

#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 180021114)
#define SROOK_NOEXCEPT(...) noexcept(noexcept(__VA_ARGS__))
#else
// for this issue : https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52869
#if defined(__GNUC__) or defined(__GNUG__)
#define SROOK_NOEXCEPT(x) noexcept(false)
#else
#define SROOK_NOEXCEPT(...) noexcept(noexcept(__VA_ARGS__))
#endif
#define SROOK_NOEXCEPT_TRUE noexcept(true)
#endif

#else
#define SROOK_NOEXCEPT_TRUE throw()
#define SROOK_NOEXCEPT(...)
#endif

#endif
