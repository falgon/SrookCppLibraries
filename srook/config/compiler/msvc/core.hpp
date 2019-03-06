// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_COMPILER_MSVC_CORE_HPP
#define INCLUDED_SROOK_CONFIG_COMPILER_MSVC_CORE_HPP
#ifdef _MSC_VER
#    include <srook/config/cpp_predefined/feature_testing.hpp>
#    if SROOK_HAS_INCLUDE(<boost / config / compiler / visualc.hpp>)
#        include <boost/config/compiler/visualc.hpp>
#        define SROOK_HAS_BOOST_CONFIG_COMPILER_VISUALC_HPP
#        ifdef BOOST_MSVC
#            define SROOK_MSVC BOOST_MSVC
#        endif
#        ifdef BOOST_MSVC_FULL_VER
#            define SROOK_MSVC_FULL_VER BOOST_MSVC_FULL_VER
#        endif
#        ifdef BOOST_HAS_PRAGMA_ONCE
#            define SROOK_HAS_PRAGMA_ONCE BOOST_HAS_PRAGMA_ONCE
#        endif
#        ifdef BOOST_NO_FENV_H
#            define SROOK_NO_FENV_H BOOST_NO_FENV_H
#        endif
#        ifdef BOOST_NO_SWPRINTF
#            define SROOK_NO_SWPRINTF BOOST_NO_SWPRINTF
#        endif
#        ifdef BOOST_NO_CXX11_EXTERN_TEMPLATE
#            define SROOK_NO_CXX11_EXTERN_TEMPLATE
#        endif
#        ifdef BOOST_NO_CXX11_VARIADIC_MACROS
#            define SROOK_NO_CXX11_VARIADIC_MACROS BOOST_NO_CXX11_VARIADIC_MACROS
#        endif
#        ifdef BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#            define SROOK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#        endif
#        ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#            define SROOK_NO_MEMBER_TEMPLATE_FRIENDS BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#        endif
#        ifdef BOOST_NO_ADL_BARRIER
#            define SROOK_NO_ADL_BARRIER BOOST_NO_ADL_BARRIER
#        endif
#        ifdef BOOST_NO_INTRINSIC_WCHAR_T
#            define SROOK_NO_INTRINSIC_WCHAR_T BOOST_NO_INTRINSIC_WCHAR_T
#        endif
#        ifdef BOOST_NO_EXCEPTIONS
#            define SROOK_NO_EXCEPTIONS BOOST_NO_EXCEPTIONS
#        endif
#        ifdef BOOST_HAS_LONG_LONG
#            define SROOK_HAS_LONG_LONG BOOST_HAS_LONG_LONG
#        endif
#        ifdef BOOST_NO_LONG_LONG
#            define SROOK_NO_LONG_LONG BOOST_NO_LONG_LONG
#        endif
#        ifdef BOOST_HAS_NRVO
#            define SROOK_HAS_NRVO BOOST_HAS_NRVO
#        endif
#        ifdef BOOST_HAS_PRAGMA_DETECT_MISMATCH
#            define SROOK_HAS_PRAGMA_DETECT_MISMATCH BOOST_HAS_PRAGMA_DETECT_MISMATCH
#        endif
#        ifdef BOOST_DISABLE_WIN32
#            define SROOK_DISABLE_WIN32 BOOST_DISABLE_WIN32
#        endif
#        ifdef BOOST_NO_RTTI
#            define SROOK_NO_RTTI BOOST_NO_RTTI
#        endif
#        ifdef BOOST_HAS_TR1_UNORDERED_MAP
#            define SROOK_HAS_TR1_UNORDERED_MAP BOOST_HAS_TR1_UNORDERED_MAP
#        endif
#        ifdef BOOST_HAS_TR1_UNORDERED_SET
#            define SROOK_HAS_TR1_UNORDERED_SET BOOST_HAS_TR1_UNORDERED_SET
#        endif
#        ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
#            define SROOK_NO_CXX11_AUTO_DECLARATIONS BOOST_NO_CXX11_AUTO_DECLARATIONS
#        endif
#        ifdef BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#            define SROOK_NO_CXX11_AUTO_MULTIDECLARATIONS BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#        endif
#        ifdef BOOST_NO_CXX11_LAMBDAS
#            define SROOK_NO_CXX11_LAMBDAS BOOST_NO_CXX11_LAMBDAS
#        endif
#        ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
#            define SROOK_NO_CXX11_RVALUE_REFERENCES BOOST_NO_CXX11_RVALUE_REFERENCES
#        endif
#        ifdef BOOST_NO_CXX11_STATIC_ASSERT
#            define SROOK_NO_CXX11_STATIC_ASSERT BOOST_NO_CXX11_STATIC_ASSERT
#        endif
#        ifdef BOOST_NO_CXX11_NULLPTR
#            define SROOK_NO_CXX11_NULLPTR BOOST_NO_CXX11_NULLPTR
#        endif
#        ifdef BOOST_NO_CXX11_DECLTYPE
#            define SROOK_NO_CXX11_DECLTYPE BOOST_NO_CXX11_DECLTYPE
#        endif
#        ifdef BOOST_NO_CXX11_FINAL
#            define SROOK_NO_CXX11_FINAL BOOST_NO_CXX11_FINAL
#        endif
#        ifdef BOOST_NO_CXX11_RANGE_BASED_FOR
#            define SROOK_NO_CXX11_RANGE_BASED_FOR BOOST_NO_CXX11_RANGE_BASED_FOR
#        endif
#        ifdef BOOST_NO_CXX11_SCOPED_ENUMS
#            define SROOK_NO_CXX11_SCOPED_ENUMS BOOST_NO_CXX11_SCOPED_ENUMS
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
#        ifdef BOOST_NO_CXX11_RAW_LITERALS
#            define SROOK_NO_CXX11_RAW_LITERALS BOOST_NO_CXX11_RAW_LITERALS
#        endif
#        ifdef BOOST_NO_CXX11_TEMPLATE_ALIASES
#            define SROOK_NO_CXX11_TEMPLATE_ALIASES BOOST_NO_CXX11_TEMPLATE_ALIASES
#        endif
#        ifdef BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#            define SROOK_NO_CXX11_TRAILING_RESULT_TYPES BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#        endif
#        ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#            define SROOK_NO_CXX11_VARIADIC_TEMPLATES BOOST_NO_CXX11_VARIADIC_TEMPLATES
#        endif
#        ifdef BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#            define SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#        endif
#        ifdef BOOST_NO_CXX11_DECLTYPE_N3276
#            define SROOK_NO_CXX11_DECLTYPE_N3276 BOOST_NO_CXX11_DECLTYPE_N3276
#        endif
#        ifdef BOOST_HAS_EXPM1
#            define SROOK_HAS_EXPM1 BOOST_HAS_EXPM1
#        endif
#        ifdef BOOST_HAS_LOG1P
#            define SROOK_HAS_LOG1P BOOST_HAS_LOG1P
#        endif
#        ifdef BOOST_NO_CXX11_NOEXCEPT
#            define SROOK_NO_CXX11_NOEXCEPT BOOST_NO_CXX11_NOEXCEPT
#        endif
#        ifdef BOOST_NO_CXX11_REF_QUALIFIERS
#            define SROOK_NO_CXX11_REF_QUALIFIERS BOOST_NO_CXX11_REF_QUALIFIERS
#        endif
#        ifdef BOOST_NO_CXX11_USER_DEFINED_LITERALS
#            define SROOK_NO_CXX11_USER_DEFINED_LITERALS BOOST_NO_CXX11_USER_DEFINED_LITERALS
#        endif
#        ifdef BOOST_NO_CXX11_ALIGNAS
#            define SROOK_NO_CXX11_ALIGNAS BOOST_NO_CXX11_ALIGNAS
#        endif
#        ifdef BOOST_NO_CXX11_INLINE_NAMESPACES
#            define SROOK_NO_CXX11_INLINE_NAMESPACES BOOST_NO_CXX11_INLINE_NAMESPACES
#        endif
#        ifdef BOOST_NO_CXX11_CHAR16_T
#            define SROOK_NO_CXX11_CHAR16_T BOOST_NO_CXX11_CHAR16_T
#        endif
#        ifdef BOOST_NO_CXX11_CHAR32_T
#            define SROOK_NO_CXX11_CHAR32_T BOOST_NO_CXX11_CHAR32_T
#        endif
#        ifdef BOOST_NO_CXX11_UNICODE_LITERALS
#            define SROOK_NO_CXX11_UNICODE_LITERALS BOOST_NO_CXX11_UNICODE_LITERALS
#        endif
#        ifdef BOOST_NO_CXX14_DECLTYPE_AUTO
#            define SROOK_NO_CXX14_DECLTYPE_AUTO BOOST_NO_CXX14_DECLTYPE_AUTO
#        endif
#        ifdef BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#            define SROOK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#        endif
#        ifdef BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#            define SROOK_NO_CXX14_RETURN_TYPE_DEDUCTION BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#        endif
#        ifdef BOOST_NO_CXX14_BINARY_LITERALS
#            define SROOK_NO_CXX14_BINARY_LITERALS BOOST_NO_CXX14_BINARY_LITERALS
#        endif
#        ifdef BOOST_NO_CXX14_GENERIC_LAMBDAS
#            define SROOK_NO_CXX14_GENERIC_LAMBDAS BOOST_NO_CXX14_GENERIC_LAMBDAS
#        endif
#        ifdef BOOST_NO_CXX14_DIGIT_SEPARATORS
#            define SROOK_NO_CXX14_DIGIT_SEPARATORS BOOST_NO_CXX14_DIGIT_SEPARATORS
#        endif
#        ifdef BOOST_NO_CXX11_THREAD_LOCAL
#            define SROOK_NO_CXX11_THREAD_LOCAL BOOST_NO_CXX11_THREAD_LOCAL
#        endif
#        ifdef BOOST_NO_CXX14_VARIABLE_TEMPLATES
#            define SROOK_NO_CXX14_VARIABLE_TEMPLATES BOOST_NO_CXX14_VARIABLE_TEMPLATES
#        endif
#        ifdef BOOST_NO_SFINAE_EXPR
#            define SROOK_NO_SFINAE_EXPR BOOST_NO_SFINAE_EXPR
#        endif
#        ifdef BOOST_NO_CXX11_CONSTEXPR
#            define SROOK_NO_CXX11_CONSTEXPR BOOST_NO_CXX11_CONSTEXPR
#        endif
#        ifdef BOOST_NO_CXX14_AGGREGATE_NSDMI
#            define SROOK_NO_CXX14_AGGREGATE_NSDMI BOOST_NO_CXX14_AGGREGATE_NSDMI
#        endif
#        ifdef BOOST_NO_CXX17_STRUCTURED_BINDINGS
#            define SROOK_NO_CXX17_STRUCTURED_BINDINGS BOOST_NO_CXX17_STRUCTURED_BINDINGS
#        endif
#        ifdef BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#            define SROOK_NO_COMPLETE_VALUE_INITIALIZATION BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#        endif
#        ifdef BOOST_NO_TWO_PHASE_NAME_LOOKUP
#            define SROOK_NO_TWO_PHASE_NAME_LOOKUP BOOST_NO_TWO_PHASE_NAME_LOOKUP
#        endif
#        ifdef BOOST_NO_CXX11_SFINAE_EXPR
#            define SROOK_NO_CXX11_SFINAE_EXPR BOOST_NO_CXX11_SFINAE_EXPR
#        endif
#        ifdef BOOST_NO_CXX14_CONSTEXPR
#            define SROOK_NO_CXX14_CONSTEXPR BOOST_NO_CXX14_CONSTEXPR
#        endif
#        ifdef BOOST_NO_CXX17_INLINE_VARIABLES
#            define SROOK_NO_CXX17_INLINE_VARIABLES BOOST_NO_CXX17_INLINE_VARIABLES
#        endif
#        ifdef BOOST_NO_CXX17_FOLD_EXPRESSIONS
#            define SROOK_NO_CXX17_FOLD_EXPRESSIONS BOOST_NO_CXX17_FOLD_EXPRESSIONS
#        endif
#        ifdef BOOST_NO_CXX11_THREAD_LOCAL
#            define SROOK_NO_CXX11_THREAD_LOCAL BOOST_NO_CXX11_THREAD_LOCAL
#        endif
#        ifdef BOOST_NO_SFINAE_EXPR
#            define SROOK_NO_SFINAE_EXPR BOOST_NO_SFINAE_EXPR
#        endif
#        ifdef BOOST_NO_CXX11_REF_QUALIFIERS
#            define SROOK_NO_CXX11_REF_QUALIFIERS BOOST_NO_CXX11_REF_QUALIFIERS
#        endif
#        ifdef BOOST_NO_CXX11_CONSTEXPR
#            define SROOK_NO_CXX11_CONSTEXPR BOOST_NO_CXX11_CONSTEXPR
#        endif
#        ifdef BOOST_COMPILER_VERSION
#            define SROOK_COMPILER_VERSION BOOST_COMPILER_VERSION
#        endif
#        ifdef BOOST_COMPILER
#            define SROOK_COMPILER BOOST_COMPILER
#        endif
#    else
#        define SROOK_MSVC _MSC_VER
#        if _MSC_FULL_VER > 100000000
#            define SROOK_MSVC_FULL_VER _MSC_FULL_VER
#        else
#            define SROOK_MSVC_FULL_VER (_MSC_FULL_VER * 10)
#        endif

#        pragma warning(disable : 4503)
#        define SROOK_HAS_PRAGMA_ONCE

#        if _MSC_VER < 1310
#            error "Compiler not supported or configured - please reconfigure"
#        endif

#        if _MSC_FULL_VER < 180020827
#            define SROOK_NO_FENV_H
#        endif

#        if _MSC_VER < 1400
#            define SROOK_NO_SWPRINTF
#            define SROOK_NO_CXX11_EXTERN_TEMPLATE
#            define SROOK_NO_CXX11_VARIADIC_MACROS
#            define SROOK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#        endif

#        if _MSC_VER < 1500
#            define SROOK_NO_MEMBER_TEMPLATE_FRIENDS
#        endif

#        if _MSC_VER < 1600
#            define SROOK_NO_ADL_BARRIER
#        endif
#        ifndef _NATIVE_WCHAR_T_DEFINED
#            define SROOK_NO_INTRINSIC_WCHAR_T
#        endif

#        if !defined(_CPPUNWIND) && !defined(SROOK_NO_EXCEPTIONS)
#            define SROOK_NO_EXCEPTIONS
#        endif

#        define SROOK_HAS_MS_INT64
#        if defined(_MSC_EXTENSIONS) || (_MSC_VER >= 1400)
#            define SROOK_HAS_LONG_LONG
#        else
#            define SROOK_NO_LONG_LONG
#        endif
#        if (_MSC_VER >= 1400) && !defined(_DEBUG)
#            define SROOK_HAS_NRVO
#        endif
#        if _MSC_VER >= 1600
#            define SROOK_HAS_PRAGMA_DETECT_MISMATCH
#        endif
#        if !defined(_MSC_EXTENSIONS) && !defined(SROOK_DISABLE_WIN32)
#            define SROOK_DISABLE_WIN32
#        endif
#        if !defined(_CPPRTTI) && !defined(SROOK_NO_RTTI)
#            define SROOK_NO_RTTI
#        endif

#        if (_MSC_VER >= 1700) && defined(_HAS_CXX17) && (_HAS_CXX17 > 0)
#            define SROOK_HAS_TR1_UNORDERED_MAP
#            define SROOK_HAS_TR1_UNORDERED_SET
#        endif

#        if _MSC_VER < 1600
#            define SROOK_NO_CXX11_AUTO_DECLARATIONS
#            define SROOK_NO_CXX11_AUTO_MULTIDECLARATIONS
#            define SROOK_NO_CXX11_LAMBDAS
#            define SROOK_NO_CXX11_RVALUE_REFERENCES
#            define SROOK_NO_CXX11_STATIC_ASSERT
#            define SROOK_NO_CXX11_NULLPTR
#            define SROOK_NO_CXX11_DECLTYPE
#        endif

#        if _MSC_VER >= 1600
#            define SROOK_HAS_STDINT_H
#        endif

#        if _MSC_VER < 1700
#            define SROOK_NO_CXX11_FINAL
#            define SROOK_NO_CXX11_RANGE_BASED_FOR
#            define SROOK_NO_CXX11_SCOPED_ENUMS
#        endif

#        if _MSC_FULL_VER < 180020827
#            define SROOK_NO_CXX11_DEFAULTED_FUNCTIONS
#            define SROOK_NO_CXX11_DELETED_FUNCTIONS
#            define SROOK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#            define SROOK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#            define SROOK_NO_CXX11_RAW_LITERALS
#            define SROOK_NO_CXX11_TEMPLATE_ALIASES
#            define SROOK_NO_CXX11_TRAILING_RESULT_TYPES
#            define SROOK_NO_CXX11_VARIADIC_TEMPLATES
#            define SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#            define SROOK_NO_CXX11_DECLTYPE_N3276
#        endif

#        if _MSC_FULL_VER >= 180020827
#            define SROOK_HAS_EXPM1
#            define SROOK_HAS_LOG1P
#        endif

#        if (_MSC_FULL_VER < 190023026)
#            define SROOK_NO_CXX11_NOEXCEPT
#            define SROOK_NO_CXX11_REF_QUALIFIERS
#            define SROOK_NO_CXX11_USER_DEFINED_LITERALS
#            define SROOK_NO_CXX11_ALIGNAS
#            define SROOK_NO_CXX11_INLINE_NAMESPACES
#            define SROOK_NO_CXX11_CHAR16_T
#            define SROOK_NO_CXX11_CHAR32_T
#            define SROOK_NO_CXX11_UNICODE_LITERALS
#            define SROOK_NO_CXX14_DECLTYPE_AUTO
#            define SROOK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#            define SROOK_NO_CXX14_RETURN_TYPE_DEDUCTION
#            define SROOK_NO_CXX14_BINARY_LITERALS
#            define SROOK_NO_CXX14_GENERIC_LAMBDAS
#            define SROOK_NO_CXX14_DIGIT_SEPARATORS
#            define SROOK_NO_CXX11_THREAD_LOCAL
#        endif

#        if (_MSC_FULL_VER < 190024210)
#            define SROOK_NO_CXX14_VARIABLE_TEMPLATES
#            define SROOK_NO_SFINAE_EXPR
#            define SROOK_NO_CXX11_CONSTEXPR
#        endif

#        if (_MSC_VER < 1910)
#            define SROOK_NO_CXX14_AGGREGATE_NSDMI
#        endif

#        if (_MSC_VER < 1911) || (_MSVC_LANG < 201703)
#            define SROOK_NO_CXX17_STRUCTURED_BINDINGS
#        endif

#        define SROOK_NO_COMPLETE_VALUE_INITIALIZATION
#        define SROOK_NO_TWO_PHASE_NAME_LOOKUP
#        define SROOK_NO_CXX11_SFINAE_EXPR
#        define SROOK_NO_CXX14_CONSTEXPR
#        define SROOK_NO_CXX17_INLINE_VARIABLES
#        define SROOK_NO_CXX17_FOLD_EXPRESSIONS
#        ifdef _M_CEE
#            ifndef SROOK_NO_CXX11_THREAD_LOCAL
#                define SROOK_NO_CXX11_THREAD_LOCAL
#            endif
#            ifndef SROOK_NO_SFINAE_EXPR
#                define SROOK_NO_SFINAE_EXPR
#            endif
#            ifndef SROOK_NO_CXX11_REF_QUALIFIERS
#                define SROOK_NO_CXX11_REF_QUALIFIERS
#            endif
#        endif
#        ifdef _M_CEE_PURE
#            ifndef SROOK_NO_CXX11_CONSTEXPR
#                define SROOK_NO_CXX11_CONSTEXPR
#            endif
#        endif
#        ifndef SROOK_COMPILER
#            if defined(UNDER_CE)
#                if _MSC_VER < 1400
#                    if defined(SROOK_ASSERT_CONFIG)
#                        error "Unknown EVC++ compiler version - please run the configure tests and report the results"
#                    else
#                        pragma message("Unknown EVC++ compiler version - please run the configure tests and report the results")
#                    endif
#                elif _MSC_VER < 1500
#                    define SROOK_COMPILER_VERSION evc8
#                elif _MSC_VER < 1600
#                    define SROOK_COMPILER_VERSION evc9
#                elif _MSC_VER < 1700
#                    define SROOK_COMPILER_VERSION evc10
#                elif _MSC_VER < 1800
#                    define SROOK_COMPILER_VERSION evc11
#                elif _MSC_VER < 1900
#                    define SROOK_COMPILER_VERSION evc12
#                elif _MSC_VER < 2000
#                    define SROOK_COMPILER_VERSION evc14
#                else
#                    if defined(SROOK_ASSERT_CONFIG)
#                        error "Unknown EVC++ compiler version - please run the configure tests and report the results"
#                    else
#                        pragma message("Unknown EVC++ compiler version - please run the configure tests and report the results")
#                    endif
#                endif
#            else
#                if _MSC_VER < 1200
#                    define SROOK_COMPILER_VERSION 5.0
#                elif _MSC_VER < 1300
#                    define SROOK_COMPILER_VERSION 6.0
#                elif _MSC_VER < 1310
#                    define SROOK_COMPILER_VERSION 7.0
#                elif _MSC_VER < 1400
#                    define SROOK_COMPILER_VERSION 7.1
#                elif _MSC_VER < 1500
#                    define SROOK_COMPILER_VERSION 8.0
#                elif _MSC_VER < 1600
#                    define SROOK_COMPILER_VERSION 9.0
#                elif _MSC_VER < 1700
#                    define SROOK_COMPILER_VERSION 10.0
#                elif _MSC_VER < 1800
#                    define SROOK_COMPILER_VERSION 11.0
#                elif _MSC_VER < 1900
#                    define SROOK_COMPILER_VERSION 12.0
#                elif _MSC_VER < 1910
#                    define SROOK_COMPILER_VERSION 14.0
#                elif _MSC_VER < 1920
#                    define SROOK_COMPILER_VERSION 14.1
#                else
#                    define SROOK_COMPILER_VERSION _MSC_VER
#                endif
#            endif
#            define SROOK_COMPILER "Microsoft Visual C++ version " SROOK_COMPILER_VERSION
#        endif
#    endif
#    define SROOK_FUNC_NAME __FUNCTION__
#    define SROOK_FUNCD_NAME __FUNCDNAME__
#    define SROOK_PRETTY_FUNCTION __FUNCSIG__
#endif
#endif
