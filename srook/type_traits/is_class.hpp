// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_CLASS_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_CLASS_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature.hpp>
#include <srook/type_traits/bool_constant.hpp>

#define COMPILER_MAGIC_IS_CLASS                             \
    template <class T>                                      \
    struct is_class : public bool_constant<__is_class(T)> { \
    }

#if !defined(__GNUC__) && !defined(__clang__)
#    undef COMPILER_MAGIC_IS_CLASS
#    include <srook/type_traits.hpp>
#endif

#if defined(__clang__)
#    if !__has_feature(is_class)
#        undef COMPILER_MAGIC_IS_CLASS
#        include <srook/type_traits.hpp>
#    endif
#endif

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

#ifdef COMPILER_MAGIC_IS_CLASS
COMPILER_MAGIC_IS_CLASS;
#    undef COMPILER_MAGIC_IS_CLASS
#else

template <class T>
struct is_class
    : public bool_constant<bool,
        detail::Land<
            detail::Lnot<is_void<T> >,
            detail::Lnot<is_integral<T> >,
            detail::Lnot<is_floating_point<T> >,
            detail::Lnot<is_array<T> >,
            detail::Lnot<is_pointer<T> >,
            detail::Lnot<is_reference<T> >,
            detail::Lnot<is_member_pointer<T> >,
            detail::Lnot<is_union<T> >,
            detail::Lnot<is_enum<T> >,
            detail::Lnot<is_function<T> > >::value> {};

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_class;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_class_v = is_class<T>::value;
#endif

} // namespace srook

#endif
