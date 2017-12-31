// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_ENUM_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_ENUM_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/true_false_type.hpp>

#define COMPILER_MAGIC_IS_ENUM                                      \
    template <class T>                                              \
    struct is_enum : public integral_constant<bool, __is_enum(T)> { \
    }

#if !defined(__GNUC__) && !defined(__clang__)
#    undef COMPILER_MAGIC_IS_ENUM
#    include <srook/type_traits/is_integral.hpp>
#    include <srook/type_traits/is_floating_point.hpp>
#    include <srook/type_traits/is_array.hpp>
#    include <srook/type_traits/is_void.hpp>
#    include <srook/type_traits/is_pointer.hpp>
#    include <srook/type_traits/is_reference.hpp>
#    include <srook/type_traits/is_member_pointer.hpp>
#    include <srook/type_traits/is_union.hpp>
#    include <srook/type_traits/is_class.hpp>
#    include <srook/type_traits/is_function.hpp>
#endif

#if defined(__clang__)
#    if !__has_feature(is_enum)
#        undef COMPILER_MAGIC_IS_ENUM
#    endif
#endif

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

#ifdef COMPILER_MAGIC_IS_ENUM
COMPILER_MAGIC_IS_ENUM;
#    undef COMPILER_MAGIC_IS_ENUM
#else

template <class T>
struct is_enum : public integral_constant<bool,
                                          !is_void<T>::value && !is_integral<T>::value && !is_floating_point<T>::value && !is_array<T>::value && !is_pointer<T>::value && !is_reference<T>::value && !is_member_pointer<T>::value && !is_union<T>::value && !is_class<T>::value && !is_function<T>::value> {
};

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_enum;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_enum_v = is_enum<T>::value;
#endif

} // namespace srook

#endif
