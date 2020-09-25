// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_FINAL_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_FINAL_HPP

#include <srook/config/feature.hpp>
#include <srook/config/cpp_predefined.hpp>
#include <srook/type_traits/bool_constant.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7))
template <class T>
struct is_final : bool_constant<__is_final(T)> {};
#define SROOK_HAS_IS_FINAL
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x5130)
template <class T>
struct is_final : bool_constant<__oracle_is_final(T)> {};
#define SROOK_HAS_IS_FINAL
#elif defined(__has_feature) 
#    if __has_feature(is_final) && !defined(__CUDACC__)
template <class T>
struct is_final : bool_constant<__is_final(T)> {};
#    endif
#else
#	error is_final: This environment was not supported.
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_final;

#if SROOK_CPP_VARIABLE_TEMPLATES && defined(SROOK_HAS_IS_FINAL)
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_final_v = is_final<T>::value;
#undef SROOK_HAS_IS_FINAL
#endif

} // namespace srook

#endif
