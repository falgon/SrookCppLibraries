// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_DETAIL_HAS_TYPE_GEN_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DETAIL_HAS_TYPE_GEN_HPP

#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature.hpp>
#include <srook/preprocessor.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/void_t.hpp>

#ifdef SROOK_CONFIG_SUPURESS_VARIADIC_MACROS_WARNING
#   pragma GCC system_header
#endif

/*
 *
 * @SROOK_TT_TYPE_TRAITS_DEF_HAS_TYPE_VARIABLE_TEMPLATES_XX
 *
 * It is defined when only __cpp_variable_templates is defined and has some values.
 *
 * 1st argument: TYPE
 * 2nd argument: NAMESPACE
 * otherwise: ignored
 *
 */

#if SROOK_CPP_VARIABLE_TEMPLATES
#define SROOK_TT_DEF_HAS_TYPE_VARIABLE_TEMPLATES_XX(...)\
    SROOK_PP_IF_ELSE(SROOK_PP_EQUAL(SROOK_PP_VA_COUNT(__VA_ARGS__), 2))\
    (template <class T>\
     SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool SROOK_PP_CONCAT(SROOK_PP_CONCAT(has_, SROOK_PP_AT_1(__VA_ARGS__)), _v) = \
     SROOK_PP_AT_2(__VA_ARGS__)::SROOK_PP_CONCAT(has_, SROOK_PP_AT_1(__VA_ARGS__))<T>::value)\
    (template <class T>\
     SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool SROOK_PP_CONCAT(SROOK_PP_CONCAT(has_, SROOK_PP_AT_1(__VA_ARGS__)), _v) = \
     SROOK_PP_CONCAT(has_, SROOK_PP_AT_1(__VA_ARGS__))<T>::value)
#else
#define SROOK_TT_TYPE_TRAITS_DEF_HAS_TYPE_VARIABLE_TEMPLATES_XX(...)
#endif

#define SROOK_TT_DEF_HAS_TYPE_IMPL(TYPE)\
    template <class, class>\
    struct SROOK_PP_CONCAT(SROOK_PP_CONCAT(has_, TYPE), _impl) : SROOK_FALSE_TYPE {};\
    template <class T>\
    struct SROOK_PP_CONCAT(SROOK_PP_CONCAT(has_, TYPE), _impl)<T, SROOK_DEDUCED_TYPENAME srook::voider<SROOK_DEDUCED_TYPENAME T::TYPE>::type> \
    : SROOK_TRUE_TYPE {}

#define SROOK_TT_DEF_HAS_TYPE(...)\
    template <class T>\
    SROOK_PP_IF_ELSE(SROOK_PP_EQUAL(SROOK_PP_VA_COUNT(__VA_ARGS__), 2))\
    (struct SROOK_PP_CONCAT(has_, SROOK_PP_AT_1(__VA_ARGS__)) :\
     SROOK_PP_AT_2(__VA_ARGS__)::SROOK_PP_CONCAT(SROOK_PP_CONCAT(has_, SROOK_PP_AT_1(__VA_ARGS__)), _impl)<T, SROOK_DEDUCED_TYPENAME srook::voider<void>::type> {})\
     (struct SROOK_PP_CONCAT(has_, SROOK_PP_AT_1(__VA_ARGS__)) :\
      SROOK_PP_CONCAT(SROOK_PP_CONCAT(has_, SROOK_PP_AT_1(__VA_ARGS__)), _impl)<T, SROOK_DEDUCED_TYPENAME srook::voider<void>::type> {})

#define SROOK_TT_DEF_HAS_TYPE_VARIABLE_TEMPLATES(...)\
    SROOK_TT_DEF_HAS_TYPE_VARIABLE_TEMPLATES_XX(__VA_ARGS__)

#define SROOK_TT_DEF_HAS_TYPE_ALL(...)\
    SROOK_TT_DEF_HAS_TYPE_IMPL(__VA_ARGS__);\
    SROOK_TT_DEF_HAS_TYPE(__VA_ARGS__);\
    SROOK_TT_DEF_HAS_TYPE_VARIABLE_TEMPLATES(__VA_ARGS__)
 
#endif
