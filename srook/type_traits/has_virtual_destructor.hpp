// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP

#if (defined(__GNUC__) && __GNUC__ >= 5 || __GNUC__ >= 4 && (__GNUC_MINOR__ >= 5 && __GNUC_PATCH_LEVEL__ >= 4)) || (defined(_MSC_VER) && _MSC_VER >= 1800)
#    define SROOK_HAS_BUILTIN_HAS_VIRTUAL_DESTRUCTOR
#elif defined(__has_builtin)
#    if __has_builtin(__has_virtual_destructor)
#        define SROOK_HAS_BUILTIN_HAS_VIRTUAL_DESTRUCTOR
#    endif
#elif defined(__has_feature)
#    if __has_feature(has_virtual_destructor)
#        define SROOK_HAS_BUILTIN_HAS_VIRTUAL_DESTRUCTOR
#    endif
#elif defined(__clang__)
#    if !(__clang_major__ >= 4 || (__clang_major__ >= 3 && __clang_minor__ >= 2))
#        undef SROOK_HAS_BUILTIN_HAS_VIRTUAL_DESTRUCTOR
#    endif
#endif

#ifdef SROOK_HAS_BUILTIN_HAS_VIRTUAL_DESTRUCTOR
#    include <srook/config/cpp_predefined.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class T>
struct has_virtual_destructor : public bool_constant<__has_virtual_destructor(T)> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::has_virtual_destructor;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool has_virtual_destructor_v = has_virtual_destructor<T>::value;
#    endif

} // namespace srook

#        undef SROOK_HAS_BUILTIN_HAS_VIRTUAL_DESTRUCTOR
#    else
#        error has_virtual_destructor: This environment is not supported.
#    endif

#endif
