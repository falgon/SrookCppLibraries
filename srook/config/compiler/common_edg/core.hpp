// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_COMPILER_COMMON_EDG_CORE_HPP
#define INCLUDED_SROOK_CONFIG_COMPILER_COMMON_EDG_CORE_HPP

#ifdef __EDG_VERSION__
#    include <srook/config/cpp_predefined/feature_testing.hpp>
#    if SROOK_HAS_INCLUDE(<boost / config / compiler / common_edg.hpp>)
#        include <boost/config/compiler/common_edg.hpp>
#        define SROOK_HAS_INCLUDE_BOOST_CONFIG_COMPILER_COMMON_EDG_HPP 1
#        ifdef BOOST_NO_INTEGRAL_INT64_T
#            define SROOK_NO_INTEGRAL_INT64_T BOOST_NO_INTEGRAL_INT64_T
#        endif
#        ifdef BOOST_NO_SFINAE
#            define SROOK_NO_SFINAE BOOST_NO_SFINAE
#        endif
#        ifdef BOOST_NO_VOID_RETURNS
#            define SROOK_NO_VOID_RETURNS BOOST_NO_VOID_RETURNS
#        endif
#        ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#            define SROOK_NO_ARGUMENT_DEPENDENT_LOOKUP BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#        endif
#        ifdef BOOST_NO_TEMPLATE_TEMPLATES
#            define SROOK_NO_TEMPLATE_TEMPLATES BOOST_NO_TEMPLATE_TEMPLATES
#        endif
#        ifdef BOOST_NO_IS_ABSTRACT
#            define SROOK_NO_IS_ABSTRACT BOOST_NO_IS_ABSTRACT
#        endif
#        ifdef BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#            define SROOK_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
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
#        ifdef BOOST_HAS_PRAGMA_ONCE
#            define SROOK_HAS_PRAGMA_ONCE BOOST_HAS_PRAGMA_ONCE
#        endif
#        ifdef BOOST_NO_CXX11_EXTERN_TEMPLATE
#            define SROOK_NO_CXX11_EXTERN_TEMPLATE BOOST_NO_CXX11_EXTERN_TEMPLATE
#        endif
#        ifdef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#            define SROOK_NO_CXX11_HDR_INITIALIZER_LIST BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#        endif
#        ifdef BOOST_NO_CXX11_VARIADIC_MACROS
#            define SROOK_NO_CXX11_VARIADIC_MACROS BOOST_NO_CXX11_VARIADIC_MACROS
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
#        ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
#            define SROOK_NO_CXX11_RVALUE_REFERENCES BOOST_NO_CXX11_RVALUE_REFERENCES
#        endif
#        ifdef BOOST_NO_CXX11_SCOPED_ENUMS
#            define SROOK_NO_CXX11_SCOPED_ENUMS BOOST_NO_CXX11_SCOPED_ENUMS
#        endif
#        ifdef BOOST_NO_SFINAE_EXPR
#            define SROOK_NO_SFINAE_EXPR BOOST_NO_SFINAE_EXPR
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
#        ifdef BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#            define SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
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
#        ifdef BOOST_NO_CXX11_REF_QUALIFIERS
#            define SROOK_NO_CXX11_REF_QUALIFIERS BOOST_NO_CXX11_REF_QUALIFIERS
#        endif
#        ifdef BOOST_NO_CXX11_FINAL
#            define SROOK_NO_CXX11_FINAL BOOST_NO_CXX11_FINAL
#        endif
#        ifdef BOOST_NO_CXX14_AGGREGATE_NSDMI
#            define SROOK_NO_CXX14_AGGREGATE_NSDMI BOOST_NO_CXX14_AGGREGATE_NSDMI
#        endif
#        ifdef BOOST_NO_CXX14_BINARY_LITERALS
#            define SROOK_NO_CXX14_BINARY_LITERALS BOOST_NO_CXX14_BINARY_LITERALS
#        endif
#        ifdef BOOST_NO_CXX14_CONSTEXPR
#            define SROOK_NO_CXX14_CONSTEXPR BOOST_NO_CXX14_CONSTEXPR
#        endif
#        ifdef BOOST_NO_CXX14_DECLTYPE_AUTO
#            define SROOK_NO_CXX14_DECLTYPE_AUTO BOOST_NO_CXX14_DECLTYPE_AUTO
#        endif
#        ifdef BOOST_NO_CXX14_DIGIT_SEPARATORS
#            define SROOK_NO_CXX14_DIGIT_SEPARATORS BOOST_NO_CXX14_DIGIT_SEPARATORS
#        endif
#        ifdef BOOST_NO_CXX14_GENERIC_LAMBDAS
#            define SROOK_NO_CXX14_GENERIC_LAMBDAS BOOST_NO_CXX14_GENERIC_LAMBDAS
#        endif
#        ifdef BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#            define SROOK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#        endif
#        ifdef BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#            define SROOK_NO_CXX14_RETURN_TYPE_DEDUCTION BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#        endif
#        ifdef BOOST_NO_CXX14_VARIABLE_TEMPLATES
#            define SROOK_NO_CXX14_VARIABLE_TEMPLATES BOOST_NO_CXX14_VARIABLE_TEMPLATES
#        endif
#    else
#        if (__EDG_VERSION__ <= 238)
#            define SROOK_NO_INTEGRAL_INT64_T
#            define SROOK_NO_SFINAE
#        endif
#        if (__EDG_VERSION__ <= 240)
#            define SROOK_NO_VOID_RETURNS
#        endif
#        if (__EDG_VERSION__ <= 241) && !defined(SROOK_NO_ARGUMENT_DEPENDENT_LOOKUP)
#            define SROOK_NO_ARGUMENT_DEPENDENT_LOOKUP
#        endif
#        if (__EDG_VERSION__ <= 244) && !defined(SROOK_NO_TEMPLATE_TEMPLATES)
#            define SROOK_NO_TEMPLATE_TEMPLATES
#        endif
#        if (__EDG_VERSION__ < 300) && !defined(SROOK_NO_IS_ABSTRACT)
#            define SROOK_NO_IS_ABSTRACT
#        endif
#        if (__EDG_VERSION__ <= 303) && !defined(SROOK_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
#            define SROOK_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#        endif
#        if !defined(__KCC) && !defined(__EXCEPTIONS) && !defined(SROOK_NO_EXCEPTIONS)
#            define SROOK_NO_EXCEPTIONS
#        endif
#        if !defined(__NO_LONG_LONG)
#            define SROOK_HAS_LONG_LONG
#        else
#            define SROOK_NO_LONG_LONG
#        endif
#        define SROOK_HAS_PRAGMA_ONCE
#        if (__EDG_VERSION__ < 310)
#            define SROOK_NO_CXX11_EXTERN_TEMPLATE
#        endif
#        if (__EDG_VERSION__ <= 310)
#            define SROOK_NO_CXX11_HDR_INITIALIZER_LIST
#        endif
#        if (__EDG_VERSION__ < 400)
#            define SROOK_NO_CXX11_VARIADIC_MACROS
#        endif
#        define SROOK_NO_CXX11_AUTO_DECLARATIONS
#        define SROOK_NO_CXX11_AUTO_MULTIDECLARATIONS
#        define SROOK_NO_CXX11_CHAR16_T
#        define SROOK_NO_CXX11_CHAR32_T
#        define SROOK_NO_CXX11_CONSTEXPR
#        define SROOK_NO_CXX11_DECLTYPE
#        define SROOK_NO_CXX11_DECLTYPE_N3276
#        define SROOK_NO_CXX11_DEFAULTED_FUNCTIONS
#        define SROOK_NO_CXX11_DELETED_FUNCTIONS
#        define SROOK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#        define SROOK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#        define SROOK_NO_CXX11_LAMBDAS
#        define SROOK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#        define SROOK_NO_CXX11_NOEXCEPT
#        define SROOK_NO_CXX11_NULLPTR
#        define SROOK_NO_CXX11_RANGE_BASED_FOR
#        define SROOK_NO_CXX11_RAW_LITERALS
#        define SROOK_NO_CXX11_RVALUE_REFERENCES
#        define SROOK_NO_CXX11_SCOPED_ENUMS
#        define SROOK_NO_SFINAE_EXPR
#        define SROOK_NO_CXX11_STATIC_ASSERT
#        define SROOK_NO_CXX11_TEMPLATE_ALIASES
#        define SROOK_NO_CXX11_UNICODE_LITERALS
#        define SROOK_NO_CXX11_VARIADIC_TEMPLATES
#        define SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#        define SROOK_NO_CXX11_USER_DEFINED_LITERALS
#        define SROOK_NO_CXX11_ALIGNAS
#        define SROOK_NO_CXX11_TRAILING_RESULT_TYPES
#        define SROOK_NO_CXX11_INLINE_NAMESPACES
#        define SROOK_NO_CXX11_REF_QUALIFIERS
#        define SROOK_NO_CXX11_FINAL
#        if !defined(__cpp_aggregate_nsdmi) || (__cpp_aggregate_nsdmi < 201304)
#            define SROOK_NO_CXX14_AGGREGATE_NSDMI
#        endif
#        if !defined(__cpp_binary_literals) || (__cpp_binary_literals < 201304)
#            define SROOK_NO_CXX14_BINARY_LITERALS
#        endif
#        if !defined(__cpp_constexpr) || (__cpp_constexpr < 201304)
#            define SROOK_NO_CXX14_CONSTEXPR
#        endif
#        if !defined(__cpp_decltype_auto) || (__cpp_decltype_auto < 201304)
#            define SROOK_NO_CXX14_DECLTYPE_AUTO
#        endif
#        if (__cplusplus < 201304) // There's no SD6 check for this....
#            define SROOK_NO_CXX14_DIGIT_SEPARATORS
#        endif
#        if !defined(__cpp_generic_lambdas) || (__cpp_generic_lambdas < 201304)
#            define SROOK_NO_CXX14_GENERIC_LAMBDAS
#        endif
#        if !defined(__cpp_init_captures) || (__cpp_init_captures < 201304)
#            define SROOK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#        endif
#        if !defined(__cpp_return_type_deduction) || (__cpp_return_type_deduction < 201304)
#            define SROOK_NO_CXX14_RETURN_TYPE_DEDUCTION
#        endif
#        if !defined(__cpp_variable_templates) || (__cpp_variable_templates < 201304)
#            define SROOK_NO_CXX14_VARIABLE_TEMPLATES
#        endif
#        ifdef c_plusplus
#        endif
#    endif
#endif
#endif
