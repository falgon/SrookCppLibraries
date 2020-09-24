// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ARRAY_ARRAY_TRAITS_HPP
#define INCLUDED_SROOK_ARRAY_ARRAY_TRAITS_HPP

#include <srook/config.hpp>
#include <srook/type_traits.hpp>

namespace srook {
namespace array_ns {
SROOK_INLINE_NAMESPACE(v1)

template <class T, std::size_t S>
struct array_traits {
    typedef T type[S];
    enum { 
        is_swappable = is_swappable<T>::value,
        is_nothrow_swappable = is_nothrow_swappable<T>::value
    };
    static SROOK_CONSTEXPR_OR_CONST T& ref(const type& t, std::size_t n) SROOK_NOEXCEPT_TRUE
    {
        return const_cast<T&>(t[n]);
    }
    static SROOK_CONSTEXPR_OR_CONST T* ptr(const type& t) SROOK_NOEXCEPT_TRUE
    {
        return const_cast<T*>(t);
    }
};

template <class T>
struct array_traits<T, 0> {
    struct type {};
    enum {
        is_swappable = SROOK_TRUE_TYPE::value,
        is_nothrow_swappable = SROOK_TRUE_TYPE::value
    };
    static SROOK_CONSTEXPR_OR_CONST T& ref(const T&, std::size_t) SROOK_NOEXCEPT_TRUE
    { 
        return *static_cast<T*>(SROOK_NULLPTR); 
    }
    static SROOK_CONSTEXPR_OR_CONST T* ptr(const T&) SROOK_NOEXCEPT_TRUE
    {
        return SROOK_NULLPTR;
    }
};

SROOK_INLINE_NAMESPACE_END
} // array_ns
} // srook


#endif
