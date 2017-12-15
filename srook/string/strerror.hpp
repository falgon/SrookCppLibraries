// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_STRING_STRERROR_HPP
#define INCLUDED_SROOK_STRING_STRERROR_HPP

#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#include <string>
#include <utility>
#include <cstring>

namespace srook {
namespace string {
SROOK_INLINE_NAMESPACE(v1)

static std::string strerror()
{
    std::string s(80, '\0');
#ifdef _WIN32
    if (strerror_s(&s[0], s.size(), errno) != 0) {
        s = "Unknown error";
    }
#elif (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !_GNU_SOURCE || defined(__APPLE__) // ref: STRERROR man page
    if (strerror_r(errno, &s[0], s.size()) != 0) {
        s = "Unknown error";
    }
#else
    auto p = strerror_r(errno, &s[0], s.size());
    std::string(p, std::char_traits<SROOK_DEDUCED_TYPENAME remove_pointer<SROOK_DECLTYPE(p)>::type>::length(p)).swap(s);
#endif
    s.resize(s.find('\0'));
    return s;
}

SROOK_INLINE_NAMESPACE_END
} // namespace string
} // namespace srook

#endif
