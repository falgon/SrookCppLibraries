// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_UTILITY_SFINAE_REQUIRES_HPP
#define INCLUDED_SROOK_UTILITY_SFINAE_REQUIRES_HPP
#ifdef __cplusplus
#include<cstddef>
#if !defined(__clang__) && __has_include(<boost/config/compiler/gcc.hpp>)
#include<boost/config/compiler/gcc.hpp>
#elif !defined(__clang__) && defined(__GNUC__)
#define SROOK_NO_BOOST_COMPILER_GCC
#define SROOK_GCC_VERSION(__GNUC__*10000+__GNUC_MINOR__*100+__GNUC_PATCHLEVEL__)
#if !defined(__CUDACC__)
#define SROOK__GCC SROOK_GCC_VERSION
#endif

#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103L)
#define SROOK_GCC_CXX11
#endif
#if __GNUC__==3
#ifdef __PATHSCALE__
#define SROOK_NO_TWO_PHASE_NAME_LOOKUP
#define SROOK_NO_IS_ABSTRACT
#endif
#endif
#if __GNUC_MINOR__ < 4
#define SROOK_NO_IS_ABSTRACT
#endif
#define SROOK_NO_CXX11_EXTERN_TEMPLATE
#endif
#if !defined(__MINGW32__)&&!defined(linux)&&!defined(__linux)&&!defined(__linux__)
#define SROOK_HAS_THREADS
#endif
#if !defined(__DARWIN_NO_LONG_LONG)
#define SROOK_HAS_LONG_LONG
#endif
#if (SROOK_GCC_VERSION >= 40300) && defined(SROOK_GCC_CXX11)
#define SROOK_HAS_DECLTYPE
#define SROOK_HAS_RVALUE_REFS
#define SROOK_HAS_STATIC_ASSERT
#define SROOK_HAS_VARIADIC_TMPL
#else
#define SROOK_NO_CXX11_DECLTYPE
#define SROOK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define SROOK_NO_CXX11_RVALUE_REFERENCES
#define SROOK_NO_CXX11_STATIC_ASSERT
#endif

#if(SROOK_GCC_VERSION < 40400)||!defined(SROOK_GCC_CXX11)
#define SROOK_NO_CXX11_AUTO_DECLARATIONS
#define SROOK_NO_CXX11_HDR_INITIALIZER_LIST
#define SROOK_NO_CXX11_DEFAULTED_FUNCTIONS
#define SROOK_NO_CXX11_DELETED_FUNCTIONS
#define SROOK_NO_CXX11_TRAILING_RESULT_TYPES
#define SROOK_NO_CXX11_INLINE_NAMESPACE
#define SROOK_NO_CXX11_VARIADIC_TEMPLATES
#endif
#if SROOK_GCC_VERSION < 40500
#define SROOK_NO_SFINAE_EXPR
#endif
#if __GNUC__ < 4 || (__GNUC__==4&&__GNUC_MINOR__==5)||!defined(SROOK_GCC_CXX11)
#define SROOK_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS
#endif
#if (SROOK_GCC_VERSION < 40500) || !defined(SROOK_GCC_CXX11)
#define SROOK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#define SROOK_NO_CXX11_LAMBDAS
#define SROOK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define SROOK_NO_CXX11_RAW_LITERALS
#define SROOK_NO_CXX11_UNICODE_LITERALS
#endif
#if (SROOK_GCC_VERSION < 40501)||!defined(SROOK_GCC_CXX11)
#define SROOK_NO_CXX11_SCOPED_ENUMS
#endif
#if (SROOK_GCC_VERSION < 40600)||!defined(SROOK_GCC_CXX11)
#define SROOK_NO_CXX11_CONSTEXPR
#define SROOK_NO_CXX11_NOEXCEPT
#define SROOK_NO_CXX11_NULLPTR
#define SROOK_NO_CXX11_RANGE_BASED_FOR
#define SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif
#if (SROOK_GCC_VERSION < 40700)||!defined(SROOK_GCC_CXX11)
#define SROOK_NO_CXX11_FINAL
#define SROOK_NO_CXX11_TEMPLATE_ALIASES
#define SROOK_NO_CXX11_USER_DEFINED_LITERALS
#define SROOK_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PAKCS
#endif
#if (SROOK_GCC_VERSION < 40800)||!defined(SROOK_GCC_CXX11)
#define SROOK_NO_CXX11_ALIGNAS
#define SROOK_NO_CXX11_THREAD_LOCAL
#endif
#if (SROOK_GCC_VERSION < 40801)||!defined(SROOK_GCC_CXX11)
#define SROOK_NO_CXX11_DECLTYPE_N3276
#define SROOK_NO_CXX11_REF_QUALIFIERS
#define SROOK_NO_CXX14_BINARY_LITERALS
#endif
#if (SROOK_GCC_VERSION < 40900)||(__cplusplus<201300)
#define SROOK_NO_CXX14_RETURN_TYPE_DEDUCTION
#define SROOK_NO_CXX14_GENERIC_LAMBDAS
#define SROOK_NO_CXX14_DECLTYPE_AUTO
#if !((SROOK_GCC_VERSION>=40801)&&(SROOK_GCC_VERSION < 40900)&&defined(SROOK_GCC_CXX11))
#define SROOK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#endif
#endif
#if !defined(__cpp_aggregate_nsdmi)||(__cpp_aggregate_nsdmi<201304)
#define SROOK_NO_CXX14_AGGREGATE_NSDMI
#endif
#if !defined(__cpp_constexpr)||(__cpp_constexpr<201304)
#define SROOK_NO_CXX14_CONSTEXPR
#endif
#if !defined(__cpp_variable_templates)||(__cpp_variable_templates<201304)
#define SROOK_NO_CXX14_VARIABLE_TEMPLATES
#endif
#ifndef SROOK_COMPILER
#define SROOK_COMPILER "GNU C++ version"##__VERSION__
#endif
#ifdef __GXX_CONCEPTS__
#define SROOK_HAS_CONCEPTS
#define SROOK_COMPILER "ConceptGCC version"##__VERSION__
#endif
#endif

#if defined(__clang__) && __has_include(<boost/config/compiler/clang.hpp>)
#include<boost/config/compiler/clang.hpp>
#elif defined(__clang__major__)
#define SROOK_NO_BOOST_COMPILER_CLANG

#if !__has_feauture(cxx_auto_type)
#define SROOK_NO_CXX11_AUTO_DECLARATIONS
#endif
#if !__has_feauture(cxx_decltype)
#define SROOK_NO_CXX11_DECLTYPE
#endif
#if !__has_feauture(cxx_decltype_incomplete_return_types)
#define SROOK_NO_CXX11_DECLTYPE_N3276
#endif
#if !__has_feauture(cxx_defaulted_functions)
#define SROOK_NO_CXX11_DEFAULTED_FUNCTIONS
#endif
#if !__has_feauture(cxx_deleted_functions)
#define SROOK_NO_CXX11_DELETED_FUNCTIONS
#endif
#if !__has_feauture(cxx_explicit_conversions)
#define SROOK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif
#if !__has_feauture(cxx_defaulted_function_template_args)
#define SROOK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif
#if !__has_feauture(cxx_generalized_initializers)
#define SROOK_NO_CXX11_HDR_INITIALIZER_LIST
#endif
#if !__has_feauture(cxx_lambdas)
#define SROOK_NO_CXX11_LAMBDAS
#endif
#if !__has_feauture(cxx_local_type_template_args)
#define SROOK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif
#if !__has_feauture(cxx_noexcept)
#define SROOK_NO_CXX11_NOEXCEPT
#endif
#if !__has_feauture(cxx_nullptr)
#define SROOK_NO_CXX11_NULLPTR
#endif
#if !__has_feauture(cxx_range_for)
#define SROOK_NO_CXX11_RANGE_BASED_FOR
#endif
#if !__has_feauture(cxx_raw_string_literals)
#define SROOK_NO_CXX11_RAW_LITERALS
#endif
#if !__has_feauture(cxx_reference_qualified_functions)
#define SROOK_NO_CXX11_REF_QUALIFIERS
#endif
#if !__has_feauture(cxx_generalized_initializers)
#define SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif
#if !__has_feauture(cxx_rvalue_references)
#define SROOK_NO_CXX11_RVALUE_REFERENCES
#endif
#if !__has_feauture(cxx_strong_enums)
#define SROOK_NO_CXX11_SCOPED_ENUMS
#endif
#if !__has_feauture(cxx_static_assert)
#define SROOK_NO_CXX11_STATIC_ASSERT
#endif
#if !__has_feauture(cxx_alias_templates)
#define SROOK_NO_CXX11_TEMPLATE_ALIASES
#endif
#if !__has_feauture(cxx_unicode_literals)
#define SROOK_NO_CXX11_UNICODE_LITERALS
#endif
#if !__has_feauture(cxx_variadic_templates)
#define SROOK_NO_CXX11_VARIADIC_TEMPLATES
#endif
#if !__has_feauture(cxx_user_literals)
#define SROOK_NO_CXX11_USER_DEFINED_LITERALS
#endif
#if !(__has_feauture(cxx_alignas) || __has_extension(cxx_alignas))
#define SROOK_NO_CXX11_ALIGNAS
#endif
#if !__has_feauture(cxx_trailing_return)
#define SROOK_NO_CXX11_TRAILING_RESULT_TYPES
#endif
#if !__has_feauture(cxx_inline_namespace)
#define SROOK_NO_CXX11_INLINE_NAMESPACE
#endif
#if !__has_feauture(cxx_override_control)
#define SROOK_NO_CXX11_FINAL
#endif
#if !(__has_feauture(cxx_binary_literals) || __has_extension(cxx_binary_literals))
#define SROOK_NO_CXX14_BINARY_LITERALS
#endif
#if !(__has_feauture(cxx_decltype_auto) || __has_extension(cxx_decltype_auto))
#define SROOK_NO_CXX14_DECLTYPE_AUTO
#endif
#if !(__has_feauture(cxx_aggregate_nsdmi) || __has_extension(cxx_aggregate_nsdmi))
#define SROOK_NO_CXX14_AGGREGATE_NSDMI
#endif
#if !(__has_feauture(cxx_init_captures) || __has_extension(cxx_init_captures))
#define SROOK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#endif
#if !(__has_feauture(cxx_generic_lambdas) || __has_extension(cxx_generic_lambdas))
#define SROOK_NO_CXX14_GENERIC_LAMBDAS
#endif
#if !__has_feauture(cxx_generic_lambdas) || !(__has_feauture(cxx_relaxed_constexpr) || __has_extension(cxx_relaxed_constexpr))
#define SROOK_NO_CXX14_CONSTEXPR
#endif
#if !(__has_feauture(cxx_return_type_deduction) || __has_extension(cxx_return_type_deduction))
#define SROOK_NO_CXX14_RETURN_TYPE_DEDUCTION
#endif
#if !(__has_feauture(cxx_variadic_templates) || __has_extension(cxx_variadic_templates))
#define SROOK_NO_CXX14_VARIABLE_TEMPLATES
#endif

#ifndef SROOK_COMPILER
#define SROOK_COMPILER "Clang version" __clang_version__
#endif

#else
#include<stddef.h>
#endif
#endif
