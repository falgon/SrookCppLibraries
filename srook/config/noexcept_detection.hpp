// for the issue : https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52869
#ifndef INCLUDED_SROOK_CONFIG_NOEXCEPT_DETECTION_HPP
#define INCLUDED_SROOK_CONFIG_NOEXCEPT_DETECTION_HPP

#if defined(__GNUC__) or defined(__GNUG__)
#define SROOK_NOEXCEPT(x) noexcept(false)
#else
#define SROOK_NOEXCEPT(...) noexcept(noexcept(__VA_ARGS__))
#endif

#endif
