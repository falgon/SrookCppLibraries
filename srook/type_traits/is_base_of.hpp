// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_BASE_OF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_BASE_OF_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/true_false_type.hpp>

#define COMPILER_MAGIC_IS_BASE_OF                                            \
    template <class B, class D>                                              \
    struct is_base_of : public integral_constant<bool, __is_base_of(B, D)> { \
    }

#if !defined(__GNUC__) && !defined(__clang__)
#    undef COMPILER_MAGIC_IS_BASE_OF
#    include <srook/type_traits/detail/sfinae_types.hpp>
#endif

#if defined(__clang__)
#    if !__has_feature(is_base_of)
#        undef COMPILER_MAGIC_IS_BASE_OF
#    endif
#endif

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

#ifdef COMPILER_MAGIC_IS_BASE_OF
COMPILER_MAGIC_IS_BASE_OF;
#    undef COMPILER_MAGIC_IS_BASE_OF
#else

namespace detail {

template <class B, class D>
struct is_base_of_impl : public sfinae_types {
    struct Child : D {
    };
    static one test(B*);
    static two test(...);

    static SROOK_CONSTEXPR bool value = (sizeof(test(static_cast<Child*>(0))) == sizeof(one));
};

} // namespace detail

template <class B, D>
struct is_base_of : public detail::is_base_of_impl<typename remove_cv<B>::type, typename remove_cv<D>::type> {
};

#endif

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_base_of;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T, class U>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_base_of_v = is_base_of<T, U>::value;
#endif

} // namespace srook

#endif
