// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_STRING_TO_STRING_HPP
#define INCLUDED_SROOK_STRING_TO_STRING_HPP

#include <cstdio>
#include <string>
#include <srook/cwchar/swprintf.hpp>
#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#include <srook/limits/numeric_limits.hpp>

namespace srook {
namespace string {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class S, class SP, class V>
inline S as_string(SP, S, const SROOK_DEDUCED_TYPENAME S::value_type*) SROOK_ATTRIBUTE_FORMAT(printf, 3, 4);

template <class S, class SP, class V>
S as_string(SP sprintf, S s, const SROOK_DEDUCED_TYPENAME S::value_type* fmt, V a)
{
    typedef SROOK_DEDUCED_TYPENAME S::size_type size_type;
    size_type available = s.size();

    while (true) {
        const int st = sprintf(&s[0], available + 1, fmt, a);
        if (st >= 0) {
            const size_type used = static_cast<size_type>(st);
            if (used <= available) {
                s.resize(used);
                break;
            }
            available = used;
        } else {
            available = available * 2 + 1;
        }
        s.resize(available);
    }
    return s;
}

template <class S, class V, bool = is_floating_point<V>::value> struct init_string;
template <class V, bool b>
struct init_string<std::string, V, b> {
    std::string operator()() const
    {
        std::string s;
        s.resize(s.capacity());
        return s;
    }
};

template <class V>
struct init_string<std::wstring, V, false> {
    std::wstring operator()() const
    {
        const std::size_t n = (numeric_limits<unsigned long long>::digits / 3) + ((numeric_limits<unsigned long long>::digits % 3) != 0) + 1;
        std::wstring s(n, SROOK_DEDUCED_TYPENAME std::wstring::value_type());
        s.resize(s.capacity());
        return s;
    }
};

template <class V>
struct init_string<std::wstring, V, true> {
    std::wstring operator()() const
    {
        std::wstring s(20, SROOK_DEDUCED_TYPENAME std::wstring::value_type());
        s.resize(s.capacity());
        return s;
    }
};

} // namespace detail

#define DEF_TO_STRING(TYPE, F)\
    std::string to_string(TYPE val)\
    {\
        return detail::as_string(std::snprintf, detail::init_string<std::string, TYPE>()(), F, val);\
    }\
    std::wstring to_wstring(TYPE val)\
    {\
        return detail::as_string(srook::swprintf, detail::init_string<std::wstring, TYPE>()(), L##F, val);\
    }

DEF_TO_STRING(int, "%d")
DEF_TO_STRING(unsigned, "%u")
DEF_TO_STRING(long, "%ld")
DEF_TO_STRING(unsigned long, "%lu")
DEF_TO_STRING(long long, "%lld")
DEF_TO_STRING(unsigned long long, "%llu")
DEF_TO_STRING(float, "%f")
DEF_TO_STRING(double, "%f")
DEF_TO_STRING(long double, "%Lf")

SROOK_INLINE_NAMESPACE_END
} // namespace string

using string::to_string;

} // namespace srook

#endif
