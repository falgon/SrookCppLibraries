// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_LAUNDER_HPP
#define INCLUDED_SROOK_MEMORY_LAUNDER_HPP

#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature.hpp>

#if SROOK_CPP_LIB_LAUNDER
#    include <memory>
namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

using std::launder;

SROOK_INLINE_NAMESPACE_END
} // namespace memory

using memory::launder;

} // namespace srook
#else
#if __GNUC__ >= 7 
#    define SROOK_HAS_BUILTIN_LAUNDER 1
#elif defined(__has_builtin)
#    if __has_builtin(__builtin_launder)
#        define SROOK_HAS_BUILTIN_LAUNDER 1
#    endif
#endif

#if SROOK_HAS_BUILTIN_LAUNDER
#    define SROOK_APPLY_LAUNDER(p) p = __builtin_launder(p);
#    define SROOK_LAUNDER_DEPRECATED_MESSAGE
#    define SROOK_COND_CONSTEXPR SROOK_CONSTEXPR
#elif defined(__GNUC__)
#    define SROOK_APPLY_LAUNDER(p) __asm__ __volatile__ ("" : "+r"(p))
// The compiler has to assume that it has been changed inside the block
// because this inline assembler block effects that p is an input an an output.
#    define SROOK_LAUNDER_DEPRECATED_MESSAGE
#	 define SROOK_COND_CONSTEXPR
#elif defined(_MSC_VER)
#    include <srook/config/compiler/msvc/includes/intrin.h>
// reference of this hack:
// https://developer.mozilla.org/en-US/docs/Mozilla/Developer_guide/Build_Instructions/Intrin.h
#    define SROOK_APPLY_LAUNDER(p) _ReadWriteBarrier()
#    define SROOK_LAUNDER_DEPRECATED_MESSAGE
#    define SROOK_COND_CONSTEXPR
#else
#    define SROOK_APPLY_LAUNDER(p)
#    include <srook/config/attribute/deprecated.hpp>
#    define SROOK_LAUNDER_DEPRECATED_MESSAGE \
        SROOK_DEPRECATED_MESSAGE("launder srook::launder is not implemented for this environment")
#    define SROOK_COND_CONSTEXPR SROOK_CONSTEXPR 
#endif
#endif

#ifdef SROOK_APPLY_LAUNDER
#    include <srook/config/attribute/nodiscard.hpp>
#    include <srook/config/attribute/visibility.hpp>
#    include <srook/type_traits/detail/logical.hpp>
#    include <srook/type_traits/is_function.hpp>
#    include <srook/type_traits/is_void.hpp>

namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

template <class T> SROOK_LAUNDER_DEPRECATED_MESSAGE SROOK_ATTRIBUTE_NODISCARD SROOK_ATTRIBUTE_INLINE_VISIBILITY SROOK_COND_CONSTEXPR
T* launder(T*) SROOK_NOEXCEPT_TRUE;

template <class T>
SROOK_LAUNDER_DEPRECATED_MESSAGE 
SROOK_ATTRIBUTE_NODISCARD 
SROOK_ATTRIBUTE_INLINE_VISIBILITY
SROOK_COND_CONSTEXPR T*
launder(T* p) SROOK_NOEXCEPT_TRUE
{
    using namespace type_traits::detail;
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_STATIC_ASSERT((Land<Lnot<is_function<T> >, Lnot<is_void<T> > >::value), "T must not be function type or void")
#    else
    SROOK_STATIC_ASSERT((Land_2<Lnot<is_function<T> >, Lnot<is_void<T> > >::value), "T must not be function type or void")
#    endif
        ;
    SROOK_APPLY_LAUNDER(p);
    return p;
}

#    undef SROOK_APPLY_LAUNDER
#    undef SROOK_LAUNDER_DEPRECATED_MESSAGE
#    undef SROOK_COND_CONSTEXPR
SROOK_INLINE_NAMESPACE_END
} // namespace memory

using memory::launder;

} // namespace srook

#    endif
#endif
