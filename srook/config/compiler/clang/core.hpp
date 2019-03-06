#ifndef SROOK_CONFIG_COMPILER_CLANG_CORE_HPP
#define SROOK_CONFIG_COMPILER_CLANG_CORE_HPP
#ifdef __clang_version__
#    include <srook/config/cpp_predefined/feature_testing.hpp>
#    if SROOK_HAS_INCLUDE(<boost / config / compiler / clang.hpp>)
#        include <boost/config/compiler/clang.hpp>
#        ifdef BOOST_LIKELY
#            define SROOK_LIKELY(x) BOOST_LIKELY(x)
#            define SROOK_UNLIKELY(x) BOOST_UNLIKELY(x)
#        endif
#        define SROOK_HAS_INCLUDE_BOOST_CONFIG_COMPILER_CLANG_HPP
#        ifdef BOOST_NO_EXCEPTIONS
#            define SROOK_NO_EXCEPTIONS BOOST_NO_EXCEPTIONS
#        endif
#        ifdef BOOST_NO_RTTI
#            define SROOK_NO_RTTI BOOST_NO_RTTI
#        endif
#        ifdef BOOST_NO_TYPEID
#            define SROOK_NO_TYPEID BOOST_NO_TYPEID
#        endif
#        ifdef BOOST_NO_CXX11_THREAD_LOCAL
#            define SROOK_NO_CXX11_THREAD_LOCAL BOOST_NO_CXX11_THREAD_LOCAL
#        endif
#        ifdef BOOST_HAS_MS_INT64
#            define SROOK_HAS_MS_INT64 BOOST_HAS_MS_INT64
#        endif
#        ifdef BOOST_HAS_STDINT_H
#            define SROOK_HAS_STDINT_H BOOST_HAS_STDINT_H
#        endif
#        ifdef BOOST_HAS_NRVO
#            define SROOK_HAS_NRVO BOOST_HAS_NRVO
#        endif
#        ifdef BOOST_HAS_LONG_LONG
#            define SROOK_HAS_LONG_LONG BOOST_HAS_LONG_LONG
#        endif
#        ifdef BOOST_NVCC_CXX11
#            define SROOK_NVCC_CXX11 BOOST_NVCC_CXX11
#        endif
#        ifdef BOOST_NVCC_CXX03
#            define SROOK_NVCC_CXX03 BOOST_NVCC_CXX03
#        endif
#        ifdef BOOST_HAS_INT128
#            define SROOK_HAS_INT128 BOOST_HAS_INT128
#        endif
#        ifdef BOOST_SYMBOL_EXPORT
#            define SROOK_SYMBOL_EXPORT BOOST_SYMBOL_EXPORT
#        endif
#        ifdef BOOST_SYMBOL_IMPORT
#            define SROOK_SYMBOL_IMPORT BOOST_SYMBOL_IMPORT
#        endif
#        ifdef BOOST_SYMBOL_VISIBLE
#            define SROOK_SYMBOL_VISIBLE BOOST_SYMBOL_VISIBLE
#        endif
#        ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
#            define SROOK_NO_CXX11_AUTO_DECLARATIONS BOOST_NO_CXX11_AUTO_DECLARATIONS
#        endif
#        ifdef BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#            define SROOK_NO_CXX11_AUTO_MULTIDECLARATIONS BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#        endif
#        ifdef BOOST_NO_CXX11_CHAR16_T
#            define SROOK_NO_CXX11_CHAR16_T BOOST_NO_CXX11_CHAR16_T
#        endif
#        ifdef BOOST_NO_CXX11_CHAR32_T
#            define SROOK_NO_CXX11_CHAR32_T BOOST_NO_CXX11_CHAR32_T
#        endif
#        ifdef BOOST_HAS_EXPM1
#            define SROOK_HAS_EXPM1 BOOST_HAS_EXPM1
#        endif
#        ifdef BOOST_HAS_LOG1P
#            define SROOK_HAS_LOG1P BOOST_HAS_LOG1P
#        endif
#        ifdef BOOST_NO_CXX11_CONSTEXPR
#            define SROOK_NO_CXX11_CONSTEXPR BOOST_NO_CXX11_CONSTEXPR
#        endif
#        ifdef BOOST_NO_CXX11_DECLTYPE
#            define SROOK_NO_CXX11_DECLTYPE BOOST_NO_CXX11_DECLTYPE
#        endif
#        ifdef BOOST_NO_CXX11_DECLTYPE_N3276
#            define SROOK_NO_CXX11_DECLTYPE_N3276 BOOST_NO_CXX11_DECLTYPE_N3276
#        endif
#        ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#            define SROOK_NO_CXX11_DEFAULTED_FUNCTIONS BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#        endif
#        ifdef BOOST_NO_CXX11_DELETED_FUNCTIONS
#            define SROOK_NO_CXX11_DELETED_FUNCTIONS BOOST_NO_CXX11_DELETED_FUNCTIONS
#        endif
#        ifdef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#            define SROOK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#        endif
#        ifdef BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#            define SROOK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#        endif
#        ifdef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#            define SROOK_NO_CXX11_HDR_INITIALIZER_LIST BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#        endif
#        ifdef BOOST_NO_CXX11_LAMBDAS
#            define SROOK_NO_CXX11_LAMBDAS BOOST_NO_CXX11_LAMBDAS
#        endif
#        ifdef BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#            define SROOK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#        endif
#        ifdef BOOST_NO_CXX11_NOEXCEPT
#            define SROOK_NO_CXX11_NOEXCEPT BOOST_NO_CXX11_NOEXCEPT
#        endif
#        ifdef BOOST_NO_CXX11_NULLPTR
#            define SROOK_NO_CXX11_NULLPTR BOOST_NO_CXX11_NULLPTR
#        endif
#        ifdef BOOST_NO_CXX11_RANGE_BASED_FOR
#            define SROOK_NO_CXX11_RANGE_BASED_FOR BOOST_NO_CXX11_RANGE_BASED_FOR
#        endif
#        ifdef BOOST_NO_CXX11_RAW_LITERALS
#            define SROOK_NO_CXX11_RAW_LITERALS BOOST_NO_CXX11_RAW_LITERALS
#        endif
#        ifdef BOOST_NO_CXX11_REF_QUALIFIERS
#            define SROOK_NO_CXX11_REF_QUALIFIERS BOOST_NO_CXX11_REF_QUALIFIERS
#        endif
#        ifdef BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#            define SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#        endif
#        ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
#            define SROOK_NO_CXX11_RVALUE_REFERENCES BOOST_NO_CXX11_RVALUE_REFERENCES
#        endif
#        ifdef BOOST_NO_CXX11_SCOPED_ENUMS
#            define SROOK_NO_CXX11_SCOPED_ENUMS BOOST_NO_CXX11_SCOPED_ENUMS
#        endif
#        ifdef BOOST_NO_CXX11_STATIC_ASSERT
#            define SROOK_NO_CXX11_STATIC_ASSERT BOOST_NO_CXX11_STATIC_ASSERT
#        endif
#        ifdef BOOST_NO_CXX11_TEMPLATE_ALIASES
#            define SROOK_NO_CXX11_TEMPLATE_ALIASES BOOST_NO_CXX11_TEMPLATE_ALIASES
#        endif
#        ifdef BOOST_NO_CXX11_UNICODE_LITERALS
#            define SROOK_NO_CXX11_UNICODE_LITERALS BOOST_NO_CXX11_UNICODE_LITERALS
#        endif
#        ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#            define SROOK_NO_CXX11_VARIADIC_TEMPLATES BOOST_NO_CXX11_VARIADIC_TEMPLATES
#        endif
#        ifdef BOOST_NO_CXX11_USER_DEFINED_LITERALS
#            define SROOK_NO_CXX11_USER_DEFINED_LITERALS BOOST_NO_CXX11_USER_DEFINED_LITERALS
#        endif
#        ifdef BOOST_NO_CXX11_ALIGNAS
#            define SROOK_NO_CXX11_ALIGNAS BOOST_NO_CXX11_ALIGNAS
#        endif
#        ifdef BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#            define SROOK_NO_CXX11_TRAILING_RESULT_TYPES BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#        endif
#        ifdef BOOST_NO_CXX11_INLINE_NAMESPACES
#            define SROOK_NO_CXX11_INLINE_NAMESPACES BOOST_NO_CXX11_INLINE_NAMESPACES
#        endif
#        ifdef BOOST_NO_CXX11_FINAL
#            define SROOK_NO_CXX11_FINAL BOOST_NO_CXX11_FINAL
#        endif
#        ifdef BOOST_NO_CXX14_BINARY_LITERALS
#            define SROOK_NO_CXX14_BINARY_LITERALS BOOST_NO_CXX14_BINARY_LITERALS
#        endif
#        ifdef BOOST_NO_CXX14_DECLTYPE_AUTO
#            define SROOK_NO_CXX14_DECLTYPE_AUTO BOOST_NO_CXX14_DECLTYPE_AUTO
#        endif
#        ifdef BOOST_NO_CXX14_AGGREGATE_NSDMI
#            define SROOK_NO_CXX14_AGGREGATE_NSDMI BOOST_NO_CXX14_AGGREGATE_NSDMI
#        endif
#        ifdef BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#            define SROOK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#        endif
#        ifdef BOOST_NO_CXX14_GENERIC_LAMBDAS
#            define SROOK_NO_CXX14_GENERIC_LAMBDAS BOOST_NO_CXX14_GENERIC_LAMBDAS
#        endif
#        define SROOK_CLANG 1
#    else
#        ifndef SROOK_HAS_PRAGMA_ONCE
#            define SROOK_HAS_PRAGMA_ONCE
#        endif
#        if defined(_MSC_VER) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 4))
#            define SROOK_HAS_PRAGMA_DETECT_MISMATCH
#        endif
#        ifndef __has_extension
#            define __has_extension __has_feature
#        endif
#        ifndef __has_attribute
#            define __has_attribute(x) 0
#        endif
#        ifndef __has_cpp_attribute
#            define __has_cpp_attribute(x) 0
#        endif
#        if !__has_feature(cxx_exceptions) && !defined(SROOK_NO_EXCEPTIONS)
#            define SROOK_NO_EXCEPTIONS
#        endif
#        if !__has_feature(cxx_rtti) && !defined(SROOK_NO_RTTI)
#            define SROOK_NO_RTTI
#        endif
#        if !__has_feature(cxx_rtti) && !defined(SROOK_NO_TYPEID)
#            define SROOK_NO_TYPEID
#        endif
#        if !__has_feature(cxx_thread_local)
#            define SROOK_NO_CXX11_THREAD_LOCAL
#        endif
#        ifdef __is_identifier
#            if !__is_identifier(__int64) && !defined(__GNUC__)
#                define SROOK_HAS_MS_INT64
#            endif
#        endif
#        if __has_include(<stdint.h>)
#            define SROOK_HAS_STDINT_H
#        endif
#        ifndef SROOK_HAS_NRVO
#            define SROOK_HAS_NRVO
#        endif
#        if !defined(__c2__) && defined(__has_builtin)
#            if __has_builtin(__builtin_expect)
#                ifdef SROOK_LIKELY
#                    undef SROOK_LIKELY
#                endif
#                ifdef SROOK_UNLIKELY
#                    undef SROOK_UNLIKELY
#                endif
#                define SROOK_LIKELY(x) __builtin_expect(x, 1)
#                define SROOK_UNLIKELY(x) __builtin_expect(x, 0)
#            endif
#        endif
#        define SROOK_HAS_LONG_LONG
#        if defined(__CUDACC__)
#            if defined(SROOK_GCC_CXX11)
#                define SROOK_NVCC_CXX11
#            else
#                define SROOK_NVCC_CXX03
#            endif
#        endif
#        if defined(__SIZEOF_INT128__) && !defined(SROOK_NVCC_CXX03) && !defined(_MSC_VER)
#            ifndef SROOK_HAS_INT128
#                define SROOK_HAS_INT128
#            endif
#        endif
#        if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)
#            ifndef SROOK_SYMBOL_EXPORT
#               define SROOK_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#            endif
#            ifndef SROOK_SYMBOL_IMPORT
#               define SROOK_SYMBOL_IMPORT
#            endif
#            ifndef SROOK_SYMBOL_VISIBLE
#               define SROOK_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#            endif
#        endif
#        if __cplusplus >= 201103L && defined(__has_warning)
#            if __has_feature(cxx_attributes) && __has_warning("-Wimplicit-fallthrough")
#                define SROOK_FALLTHROUGH [[clang::fallthrough]]
#            endif
#        endif
#        if !__has_feature(cxx_auto_type)
#            define SROOK_NO_CXX11_AUTO_DECLARATIONS
#            define SROOK_NO_CXX11_AUTO_MULTIDECLARATIONS
#        endif
#        if (defined(_MSC_VER) && (_MSC_VER < 1900)) || !(defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)
#            define SROOK_NO_CXX11_CHAR16_T
#            define SROOK_NO_CXX11_CHAR32_T
#        endif
#        if defined(_MSC_VER) && (_MSC_VER >= 1800) && !defined(__GNUC__)
#            define SROOK_HAS_EXPM1
#            define SROOK_HAS_LOG1P
#        endif
#        if !__has_feature(cxx_constexpr)
#            define SROOK_NO_CXX11_CONSTEXPR
#        endif
#        if !__has_feature(cxx_decltype)
#            define SROOK_NO_CXX11_DECLTYPE
#        endif
#        if !__has_feature(cxx_decltype_incomplete_return_types)
#            define SROOK_NO_CXX11_DECLTYPE_N3276
#        endif
#        if !__has_feature(cxx_defaulted_functions)
#            define SROOK_NO_CXX11_DEFAULTED_FUNCTIONS
#        endif
#        if !__has_feature(cxx_deleted_functions)
#            define SROOK_NO_CXX11_DELETED_FUNCTIONS
#        endif
#        if !__has_feature(cxx_explicit_conversions)
#            define SROOK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#        endif
#        if !__has_feature(cxx_default_function_template_args)
#            define SROOK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#        endif
#        if !__has_feature(cxx_generalized_initializers)
#            define SROOK_NO_CXX11_HDR_INITIALIZER_LIST
#        endif
#        if !__has_feature(cxx_lambdas)
#            define SROOK_NO_CXX11_LAMBDAS
#        endif
#        if !__has_feature(cxx_local_type_template_args)
#            define SROOK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#        endif
#        if !__has_feature(cxx_noexcept)
#            define SROOK_NO_CXX11_NOEXCEPT
#        endif
#        if !__has_feature(cxx_nullptr)
#            define SROOK_NO_CXX11_NULLPTR
#        endif
#        if !__has_feature(cxx_range_for)
#            define SROOK_NO_CXX11_RANGE_BASED_FOR
#        endif
#        if !__has_feature(cxx_raw_string_literals)
#            define SROOK_NO_CXX11_RAW_LITERALS
#        endif
#        if !__has_feature(cxx_reference_qualified_functions)
#            define SROOK_NO_CXX11_REF_QUALIFIERS
#        endif
#        if !__has_feature(cxx_generalized_initializers)
#            define SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#        endif
#        if !__has_feature(cxx_rvalue_references)
#            define SROOK_NO_CXX11_RVALUE_REFERENCES
#        endif
#        if !__has_feature(cxx_strong_enums)
#            define SROOK_NO_CXX11_SCOPED_ENUMS
#        endif
#        if !__has_feature(cxx_static_assert)
#            define SROOK_NO_CXX11_STATIC_ASSERT
#        endif
#        if !__has_feature(cxx_alias_templates)
#            define SROOK_NO_CXX11_TEMPLATE_ALIASES
#        endif
#        if !__has_feature(cxx_unicode_literals)
#            define SROOK_NO_CXX11_UNICODE_LITERALS
#        endif
#        if !__has_feature(cxx_variadic_templates)
#            define SROOK_NO_CXX11_VARIADIC_TEMPLATES
#        endif
#        if !__has_feature(cxx_user_literals)
#            define SROOK_NO_CXX11_USER_DEFINED_LITERALS
#        endif
#        if !__has_feature(cxx_alignas)
#            define SROOK_NO_CXX11_ALIGNAS
#        endif
#        if !__has_feature(cxx_trailing_return)
#            define SROOK_NO_CXX11_TRAILING_RESULT_TYPES
#        endif
#        if !__has_feature(cxx_inline_namespaces)
#            define SROOK_NO_CXX11_INLINE_NAMESPACES
#        endif
#        if !__has_feature(cxx_override_control)
#            define SROOK_NO_CXX11_FINAL
#        endif
#        if !(__has_feature(__cxx_binary_literals__) || __has_extension(__cxx_binary_literals__))
#            define SROOK_NO_CXX14_BINARY_LITERALS
#        endif
#        if !__has_feature(__cxx_decltype_auto__)
#            define SROOK_NO_CXX14_DECLTYPE_AUTO
#        endif
#        if !__has_feature(__cxx_aggregate_nsdmi__)
#            define SROOK_NO_CXX14_AGGREGATE_NSDMI
#        endif
#        if !__has_feature(__cxx_init_captures__)
#            define SROOK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#        endif
#        if !__has_feature(__cxx_generic_lambdas__)
#            define SROOK_NO_CXX14_GENERIC_LAMBDAS
#        endif
#        if !__has_feature(__cxx_generic_lambdas__) || !__has_feature(__cxx_relaxed_constexpr__)
#            define SROOK_NO_CXX14_CONSTEXPR
#        endif
#        if !__has_feature(__cxx_return_type_deduction__)
#            define SROOK_NO_CXX14_RETURN_TYPE_DEDUCTION
#        endif
#        if !__has_feature(__cxx_variable_templates__)
#            define SROOK_NO_CXX14_VARIABLE_TEMPLATES
#        endif
#        if !defined(__cpp_structured_bindings) || (__cpp_structured_bindings < 201606)
#            define SROOK_NO_CXX17_STRUCTURED_BINDINGS
#        endif
#        if !__has_cpp_attribute(fallthrough) || __cplusplus < 201406L
#            define SROOK_NO_CXX17_INLINE_VARIABLES
#            define SROOK_NO_CXX17_FOLD_EXPRESSIONS
#        endif
#        if __cplusplus < 201103L
#            define SROOK_NO_CXX11_SFINAE_EXPR
#        endif
#        if __cplusplus < 201400
#            define SROOK_NO_CXX14_DIGIT_SEPARATORS
#        endif
#        if defined(__has_builtin) && __has_builtin(__builtin_unreachable)
#            define SROOK_UNREACHABLE_RETURN(x) __builtin_unreachable();
#        endif
#        if (__clang_major__ == 3) && (__clang_minor__ == 0)
#            define SROOK_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#        endif
#        ifndef SROOK_ATTRIBUTE_UNUSED
#            define SROOK_ATTRIBUTE_UNUSED __attribute__((__unused__))
#        endif
#        if __has_attribute(__may_alias__)
#            define SROOK_MAY_ALIAS __attribute__((__may_alias__))
#        endif
#        ifndef SROOK_COMPILER
#            define SROOK_COMPILER "Clang version " __clang_version__
#        endif
#        define SROOK_CLANG 1
#    endif
#endif
#endif
