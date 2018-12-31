// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_INTEGRAL_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_INTEGRAL_HPP
#include <srook/cstdint.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/remove_cv.hpp>
#include <srook/type_traits/true_false_type.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

#define DEFINE_TRUE_INTEGRAL(TYPE)                           \
    template <>                                              \
    struct is_integral_impl<TYPE> : public SROOK_TRUE_TYPE {}

template <typename>
struct is_integral_impl : public SROOK_FALSE_TYPE {};

DEFINE_TRUE_INTEGRAL(bool);
DEFINE_TRUE_INTEGRAL(char);
DEFINE_TRUE_INTEGRAL(signed char);
DEFINE_TRUE_INTEGRAL(unsigned char);
DEFINE_TRUE_INTEGRAL(wchar_t);
DEFINE_TRUE_INTEGRAL(char16_t);
DEFINE_TRUE_INTEGRAL(char32_t);
DEFINE_TRUE_INTEGRAL(short);
DEFINE_TRUE_INTEGRAL(unsigned short);
DEFINE_TRUE_INTEGRAL(int);
DEFINE_TRUE_INTEGRAL(unsigned int);
DEFINE_TRUE_INTEGRAL(long);
DEFINE_TRUE_INTEGRAL(unsigned long);
DEFINE_TRUE_INTEGRAL(long long);
DEFINE_TRUE_INTEGRAL(unsigned long long);
#if (USHRT_MAX == 0xffffffff) && defined(__MTA__)
DEFINE_TRUE_INTEGRAL(srook::int16_t);
DEFINE_TRUE_INTEGRAL(srook::int_least16_t);
DEFINE_TRUE_INTEGRAL(srook::int_fast16_t);
DEFINE_TRUE_INTEGRAL(srook::uint16_t);
DEFINE_TRUE_INTEGRAL(srook::uint_least16_t);
DEFINE_TRUE_INTEGRAL(srook::uint_fast16_t);
DEFINE_TRUE_INTEGRAL(srook::int32_t);
DEFINE_TRUE_INTEGRAL(srook::int_least32_t);
DEFINE_TRUE_INTEGRAL(srook::int_fast32_t);
DEFINE_TRUE_INTEGRAL(srook::uint32_t);
DEFINE_TRUE_INTEGRAL(srook::uint_least32_t);
DEFINE_TRUE_INTEGRAL(srook::uint_fast32_t);
#endif
#if !defined(__STRICT_ANSI__) && defined(_GLIBCXX_USE_INT128)
DEFINE_TRUE_INTEGRAL(__int128);
DEFINE_TRUE_INTEGRAL(unsigned __int128);
#endif
#if defined(SROOK_HAS_MS_INT64) || defined(BOOST_HAS_MS_INT64)
DEFINE_TRUE_INTEGRAL(srook::int64_t);
DEFINE_TRUE_INTEGRAL(srook::int_least64_t);
DEFINE_TRUE_INTEGRAL(srook::int_fast64_t);
DEFINE_TRUE_INTEGRAL(srook::uint64_t);
DEFINE_TRUE_INTEGRAL(srook::uint_least64_t);
DEFINE_TRUE_INTEGRAL(srook::uint_fast64_t);
#endif
#undef DEFINE_TRUE_INTEGRAL

} // namespace detail

template <class T>
struct is_integral : public detail::is_integral_impl<typename remove_cv<T>::type>::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_integral;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_integral_v = is_integral<T>::value;
#endif

} // namespace srook

#endif
