// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_FUNCTION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_FUNCTION_HPP
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/true_false_type.hpp>

#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wambiguous-ellipsis"
#endif

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class>
struct is_function : public SROOK_FALSE_TYPE {
};
template <class R, class... Arg>
struct is_function<R(Arg...)> : public SROOK_TRUE_TYPE {
};
template <class R, class... Arg>
struct is_function<R(Arg......)> : public SROOK_TRUE_TYPE {
};
template <class R, class... Arg>
struct is_function<R(Arg...) const> : public SROOK_TRUE_TYPE {
};
template <class R, class... Arg>
struct is_function<R(Arg......) const> : public SROOK_TRUE_TYPE {
};
template <class R, class... Arg>
struct is_function<R(Arg...) volatile> : public SROOK_TRUE_TYPE {
};
template <class R, class... Arg>
struct is_function<R(Arg......) volatile> : public SROOK_TRUE_TYPE {
};
template <class R, class... Arg>
struct is_function<R(Arg...) const volatile> : public SROOK_TRUE_TYPE {
};
template <class R, class... Arg>
struct is_function<R(Arg......) const volatile> : public SROOK_TRUE_TYPE {
};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_function;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_function_v = is_function<T>::value;
#endif

} // namespace srook
#ifdef __clang__
#   pragma clang diagnostic pop
#endif

#endif
