#ifndef INCLUDED_SROOK_CONFIG_COMPILER_PATHSCALE_CORE_HPP
#define INCLUDED_SROOK_CONFIG_COMPILER_PATHSCALE_CORE_HPP
#ifdef __PATHSCALE__
#    include <srook/config/cpp_predefined/feature_testing.hpp>
#    if SROOK_HAS_INCLUDE(<boost / config / compiler / pathscale.hpp>)
#        include <boost/config/compiler/pathscale.hpp>
#        define SROOK_HAS_BOOST_CONFIG_COMPILER_PATHSCALE_HPP 1
#        ifdef BOOST_MSVC6_MEMBER_TEMPLATES
#            define SROOK_MSVC6_MEMBER_TEMPLATES BOOST_MSVC6_MEMBER_TEMPLATES
#        endif
#        ifdef BOOST_HAS_UNISTD_H
#            define SROOK_HAS_UNISTD_H BOOST_HAS_UNISTD_H
#        endif
#        ifdef BOOST_HAS_STDINT_H
#            define SROOK_HAS_STDINT_H BOOST_HAS_STDINT_H
#        endif
#        ifdef BOOST_HAS_SIGACTION
#            define SROOK_HAS_SIGACTION BOOST_HAS_SIGACTION
#        endif
#        ifdef BOOST_HAS_SCHED_YIELD
#            define SROOK_HAS_SCHED_YIELD BOOST_HAS_SCHED_YIELD
#        endif
#        ifdef BOOST_HAS_THREADS
#            define SROOK_HAS_THREADS BOOST_HAS_THREADS
#        endif
#        ifdef BOOST_HAS_PTHREADS
#            define SROOK_HAS_PTHREADS BOOST_HAS_PTHREADS
#        endif
#        ifdef BOOST_HAS_PTHREAD_YIELD
#            define SROOK_HAS_PTHREAD_YIELD BOOST_HAS_PTHREAD_YIELD
#        endif
#        ifdef BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#            define SROOK_HAS_PTHREAD_MUTEXATTR_SETTYPE BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#        endif
#        ifdef BOOST_HAS_PARTIAL_STD_ALLOCATOR
#            define SROOK_HAS_PARTIAL_STD_ALLOCATOR BOOST_HAS_PARTIAL_STD_ALLOCATOR
#        endif
#        ifdef BOOST_HAS_NRVO
#            define SROOK_HAS_NRVO BOOST_HAS_NRVO
#        endif
#        ifdef BOOST_HAS_NL_TYPES_H
#            define SROOK_HAS_NL_TYPES_H BOOST_HAS_NL_TYPES_H
#        endif
#        ifdef BOOST_HAS_NANOSLEEP
#            define SROOK_HAS_NANOSLEEP BOOST_HAS_NANOSLEEP
#        endif
#        ifdef BOOST_HAS_LONG_LONG
#            define SROOK_HAS_LONG_LONG BOOST_HAS_LONG_LONG
#        endif
#        ifdef BOOST_HAS_LOG1P
#            define SROOK_HAS_LOG1P BOOST_HAS_LOG1P
#        endif
#        ifdef BOOST_HAS_GETTIMEOFDAY
#            define SROOK_HAS_GETTIMEOFDAY BOOST_HAS_GETTIMEOFDAY
#        endif
#        ifdef BOOST_HAS_EXPM1
#            define SROOK_HAS_EXPM1 BOOST_HAS_EXPM1
#        endif
#        ifdef BOOST_HAS_DIRENT_H
#            define SROOK_HAS_DIRENT_H BOOST_HAS_DIRENT_H
#        endif
#        ifdef BOOST_HAS_CLOCK_GETTIME
#            define SROOK_HAS_CLOCK_GETTIME BOOST_HAS_CLOCK_GETTIME
#        endif
#        ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#            define SROOK_NO_CXX11_VARIADIC_TEMPLATES BOOST_NO_CXX11_VARIADIC_TEMPLATES
#        endif
#        ifdef BOOST_NO_CXX11_UNICODE_LITERALS
#            define SROOK_NO_CXX11_UNICODE_LITERALS BOOST_NO_CXX11_UNICODE_LITERALS
#        endif
#        ifdef BOOST_NO_CXX11_TEMPLATE_ALIASES
#            define SROOK_NO_CXX11_TEMPLATE_ALIASES BOOST_NO_CXX11_TEMPLATE_ALIASES
#        endif
#        ifdef BOOST_NO_CXX11_STATIC_ASSERT
#            define SROOK_NO_CXX11_STATIC_ASSERT BOOST_NO_CXX11_STATIC_ASSERT
#        endif
#        ifdef BOOST_NO_SFINAE_EXPR
#            define SROOK_NO_SFINAE_EXPR BOOST_NO_SFINAE_EXPR
#        endif
#        ifdef BOOST_NO_CXX11_SFINAE_EXPR
#            define SROOK_NO_CXX11_SFINAE_EXPR BOOST_NO_CXX11_SFINAE_EXPR
#        endif
#        ifdef BOOST_NO_CXX11_SCOPED_ENUMS
#            define SROOK_NO_CXX11_SCOPED_ENUMS BOOST_NO_CXX11_SCOPED_ENUMS
#        endif
#        ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
#            define SROOK_NO_CXX11_RVALUE_REFERENCES BOOST_NO_CXX11_RVALUE_REFERENCES
#        endif
#        ifdef BOOST_NO_CXX11_RANGE_BASED_FOR
#            define SROOK_NO_CXX11_RANGE_BASED_FOR BOOST_NO_CXX11_RANGE_BASED_FOR
#        endif
#        ifdef BOOST_NO_CXX11_RAW_LITERALS
#            define SROOK_NO_CXX11_RAW_LITERALS BOOST_NO_CXX11_RAW_LITERALS
#        endif
#        ifdef BOOST_NO_CXX11_NULLPTR
#            define SROOK_NO_CXX11_NULLPTR BOOST_NO_CXX11_NULLPTR
#        endif
#        ifdef BOOST_NO_CXX11_NUMERIC_LIMITS
#            define SROOK_NO_CXX11_NUMERIC_LIMITS BOOST_NO_CXX11_NUMERIC_LIMITS
#        endif
#        ifdef BOOST_NO_CXX11_NOEXCEPT
#            define SROOK_NO_CXX11_NOEXCEPT BOOST_NO_CXX11_NOEXCEPT
#        endif
#        ifdef BOOST_NO_CXX11_LAMBDAS
#            define SROOK_NO_CXX11_LAMBDAS BOOST_NO_CXX11_LAMBDAS
#        endif
#        ifdef BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#            define SROOK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#        endif
#        ifdef BOOST_NO_MS_INT64_NUMERIC_LIMITS
#            define SROOK_NO_MS_INT64_NUMERIC_LIMITS BOOST_NO_MS_INT64_NUMERIC_LIMITS
#        endif
#        ifdef BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#            define SROOK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#        endif
#        ifdef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#            define SROOK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#        endif
#        ifdef BOOST_NO_CXX11_DELETED_FUNCTIONS
#            define SROOK_NO_CXX11_DELETED_FUNCTIONS BOOST_NO_CXX11_DELETED_FUNCTIONS
#        endif
#        ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#            define SROOK_NO_CXX11_DEFAULTED_FUNCTIONS BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#        endif
#        ifdef BOOST_NO_CXX11_DECLTYPE
#            define SROOK_NO_CXX11_DECLTYPE BOOST_NO_CXX11_DECLTYPE
#        endif
#        ifdef BOOST_NO_CXX11_DECLTYPE_N3276
#            define SROOK_NO_CXX11_DECLTYPE_N3276 BOOST_NO_CXX11_DECLTYPE_N3276
#        endif
#        ifdef BOOST_NO_CXX11_CONSTEXPR
#            define SROOK_NO_CXX11_CONSTEXPR BOOST_NO_CXX11_CONSTEXPR
#        endif
#        ifdef BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#            define SROOK_NO_COMPLETE_VALUE_INITIALIZATION BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#        endif
#        ifdef BOOST_NO_CXX11_CHAR32_T
#            define SROOK_NO_CXX11_CHAR32_T BOOST_NO_CXX11_CHAR32_T
#        endif
#        ifdef BOOST_NO_CXX11_CHAR16_T
#            define SROOK_NO_CXX11_CHAR16_T BOOST_NO_CXX11_CHAR16_T
#        endif
#        ifdef BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#            define SROOK_NO_CXX11_AUTO_MULTIDECLARATIONS BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#        endif
#        ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
#            define SROOK_NO_CXX11_AUTO_DECLARATIONS BOOST_NO_CXX11_AUTO_DECLARATIONS
#        endif
#        ifdef BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#            define SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#        endif
#        ifdef BOOST_NO_CXX11_HDR_UNORDERED_SET
#            define SROOK_NO_CXX11_HDR_UNORDERED_SET BOOST_NO_CXX11_HDR_UNORDERED_SET
#        endif
#        ifdef BOOST_NO_CXX11_HDR_UNORDERED_MAP
#            define SROOK_NO_CXX11_HDR_UNORDERED_MAP BOOST_NO_CXX11_HDR_UNORDERED_MAP
#        endif
#        ifdef BOOST_NO_CXX11_HDR_TYPEINDEX
#            define SROOK_NO_CXX11_HDR_TYPEINDEX BOOST_NO_CXX11_HDR_TYPEINDEX
#        endif
#        ifdef BOOST_NO_CXX11_HDR_TUPLE
#            define SROOK_NO_CXX11_HDR_TUPLE BOOST_NO_CXX11_HDR_TUPLE
#        endif
#        ifdef BOOST_NO_CXX11_HDR_THREAD
#            define SROOK_NO_CXX11_HDR_THREAD BOOST_NO_CXX11_HDR_THREAD
#        endif
#        ifdef BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#            define SROOK_NO_CXX11_HDR_SYSTEM_ERROR BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#        endif
#        ifdef BOOST_NO_CXX11_HDR_REGEX
#            define SROOK_NO_CXX11_HDR_REGEX BOOST_NO_CXX11_HDR_REGEX
#        endif
#        ifdef BOOST_NO_CXX11_HDR_RATIO
#            define SROOK_NO_CXX11_HDR_RATIO BOOST_NO_CXX11_HDR_RATIO
#        endif
#        ifdef BOOST_NO_CXX11_HDR_RANDOM
#            define SROOK_NO_CXX11_HDR_RANDOM BOOST_NO_CXX11_HDR_RANDOM
#        endif
#        ifdef BOOST_NO_CXX11_HDR_MUTEX
#            define SROOK_NO_CXX11_HDR_MUTEX BOOST_NO_CXX11_HDR_MUTEX
#        endif
#        ifdef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#            define SROOK_NO_CXX11_HDR_INITIALIZER_LIST BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#        endif
#        ifdef BOOST_NO_CXX11_HDR_FUTURE
#            define SROOK_NO_CXX11_HDR_FUTURE BOOST_NO_CXX11_HDR_FUTURE
#        endif
#        ifdef BOOST_NO_CXX11_HDR_FORWARD_LIST
#            define SROOK_NO_CXX11_HDR_FORWARD_LIST BOOST_NO_CXX11_HDR_FORWARD_LIST
#        endif
#        ifdef BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#            define SROOK_NO_CXX11_HDR_CONDITION_VARIABLE BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#        endif
#        ifdef BOOST_NO_CXX11_HDR_CODECVT
#            define SROOK_NO_CXX11_HDR_CODECVT BOOST_NO_CXX11_HDR_CODECVT
#        endif
#        ifdef BOOST_NO_CXX11_HDR_CHRONO
#            define SROOK_NO_CXX11_HDR_CHRONO BOOST_NO_CXX11_HDR_CHRONO
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
#        ifdef BOOST_NO_CXX11_THREAD_LOCAL
#            define SROOK_NO_CXX11_THREAD_LOCAL BOOST_NO_CXX11_THREAD_LOCAL
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
#        ifdef BOOST_NO_CXX17_STRUCTURED_BINDINGS
#            define SROOK_NO_CXX17_STRUCTURED_BINDINGS BOOST_NO_CXX17_STRUCTURED_BINDINGS
#        endif
#        ifdef BOOST_NO_CXX17_INLINE_VARIABLES
#            define SROOK_NO_CXX17_INLINE_VARIABLES BOOST_NO_CXX17_INLINE_VARIABLES
#        endif
#        ifdef BOOST_NO_CXX17_FOLD_EXPRESSIONS
#            define SROOK_NO_CXX17_FOLD_EXPRESSIONS BOOST_NO_CXX17_FOLD_EXPRESSIONS
#        endif
#    else
#        if __PATHCC__ >= 6
#            include <srook/config/compiler/gcc.hpp>
#        elif __PATHCC__ >= 4
#            define SROOK_MSVC6_MEMBER_TEMPLATES
#            define SROOK_HAS_UNISTD_H
#            define SROOK_HAS_STDINT_H
#            define SROOK_HAS_SIGACTION
#            define SROOK_HAS_SCHED_YIELD
#            define SROOK_HAS_THREADS
#            define SROOK_HAS_PTHREADS
#            define SROOK_HAS_PTHREAD_YIELD
#            define SROOK_HAS_PTHREAD_MUTEXATTR_SETTYPE
#            define SROOK_HAS_PARTIAL_STD_ALLOCATOR
#            define SROOK_HAS_NRVO
#            define SROOK_HAS_NL_TYPES_H
#            define SROOK_HAS_NANOSLEEP
#            define SROOK_HAS_LONG_LONG
#            define SROOK_HAS_LOG1P
#            define SROOK_HAS_GETTIMEOFDAY
#            define SROOK_HAS_EXPM1
#            define SROOK_HAS_DIRENT_H
#            define SROOK_HAS_CLOCK_GETTIME
#            define SROOK_NO_CXX11_VARIADIC_TEMPLATES
#            define SROOK_NO_CXX11_UNICODE_LITERALS
#            define SROOK_NO_CXX11_TEMPLATE_ALIASES
#            define SROOK_NO_CXX11_STATIC_ASSERT
#            define SROOK_NO_SFINAE_EXPR
#            define SROOK_NO_CXX11_SFINAE_EXPR
#            define SROOK_NO_CXX11_SCOPED_ENUMS
#            define SROOK_NO_CXX11_RVALUE_REFERENCES
#            define SROOK_NO_CXX11_RANGE_BASED_FOR
#            define SROOK_NO_CXX11_RAW_LITERALS
#            define SROOK_NO_CXX11_NULLPTR
#            define SROOK_NO_CXX11_NUMERIC_LIMITS
#            define SROOK_NO_CXX11_NOEXCEPT
#            define SROOK_NO_CXX11_LAMBDAS
#            define SROOK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#            define SROOK_NO_MS_INT64_NUMERIC_LIMITS
#            define SROOK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#            define SROOK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#            define SROOK_NO_CXX11_DELETED_FUNCTIONS
#            define SROOK_NO_CXX11_DEFAULTED_FUNCTIONS
#            define SROOK_NO_CXX11_DECLTYPE
#            define SROOK_NO_CXX11_DECLTYPE_N3276
#            define SROOK_NO_CXX11_CONSTEXPR
#            define SROOK_NO_COMPLETE_VALUE_INITIALIZATION
#            define SROOK_NO_CXX11_CHAR32_T
#            define SROOK_NO_CXX11_CHAR16_T
#            define SROOK_NO_CXX11_AUTO_MULTIDECLARATIONS
#            define SROOK_NO_CXX11_AUTO_DECLARATIONS
#            define SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#            define SROOK_NO_CXX11_HDR_UNORDERED_SET
#            define SROOK_NO_CXX11_HDR_UNORDERED_MAP
#            define SROOK_NO_CXX11_HDR_TYPEINDEX
#            define SROOK_NO_CXX11_HDR_TUPLE
#            define SROOK_NO_CXX11_HDR_THREAD
#            define SROOK_NO_CXX11_HDR_SYSTEM_ERROR
#            define SROOK_NO_CXX11_HDR_REGEX
#            define SROOK_NO_CXX11_HDR_RATIO
#            define SROOK_NO_CXX11_HDR_RANDOM
#            define SROOK_NO_CXX11_HDR_MUTEX
#            define SROOK_NO_CXX11_HDR_INITIALIZER_LIST
#            define SROOK_NO_CXX11_HDR_FUTURE
#            define SROOK_NO_CXX11_HDR_FORWARD_LIST
#            define SROOK_NO_CXX11_HDR_CONDITION_VARIABLE
#            define SROOK_NO_CXX11_HDR_CODECVT
#            define SROOK_NO_CXX11_HDR_CHRONO
#            define SROOK_NO_CXX11_USER_DEFINED_LITERALS
#            define SROOK_NO_CXX11_ALIGNAS
#            define SROOK_NO_CXX11_TRAILING_RESULT_TYPES
#            define SROOK_NO_CXX11_INLINE_NAMESPACES
#            define SROOK_NO_CXX11_REF_QUALIFIERS
#            define SROOK_NO_CXX11_FINAL
#            define SROOK_NO_CXX11_THREAD_LOCAL

// C++ 14:
#            if !defined(__cpp_aggregate_nsdmi) || (__cpp_aggregate_nsdmi < 201304)
#                define SROOK_NO_CXX14_AGGREGATE_NSDMI
#            endif
#            if !defined(__cpp_binary_literals) || (__cpp_binary_literals < 201304)
#                define SROOK_NO_CXX14_BINARY_LITERALS
#            endif
#            if !defined(__cpp_constexpr) || (__cpp_constexpr < 201304)
#                define SROOK_NO_CXX14_CONSTEXPR
#            endif
#            if !defined(__cpp_decltype_auto) || (__cpp_decltype_auto < 201304)
#                define SROOK_NO_CXX14_DECLTYPE_AUTO
#            endif
#            if (__cplusplus < 201304) // There's no SD6 check for this....
#                define SROOK_NO_CXX14_DIGIT_SEPARATORS
#            endif
#            if !defined(__cpp_generic_lambdas) || (__cpp_generic_lambdas < 201304)
#                define SROOK_NO_CXX14_GENERIC_LAMBDAS
#            endif
#            if !defined(__cpp_init_captures) || (__cpp_init_captures < 201304)
#                define SROOK_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#            endif
#            if !defined(__cpp_return_type_deduction) || (__cpp_return_type_deduction < 201304)
#                define SROOK_NO_CXX14_RETURN_TYPE_DEDUCTION
#            endif
#            if !defined(__cpp_variable_templates) || (__cpp_variable_templates < 201304)
#                define SROOK_NO_CXX14_VARIABLE_TEMPLATES
#            endif

// C++17
#            if !defined(__cpp_structured_bindings) || (__cpp_structured_bindings < 201606)
#                define SROOK_NO_CXX17_STRUCTURED_BINDINGS
#            endif
#            if !defined(__cpp_inline_variables) || (__cpp_inline_variables < 201606)
#                define SROOK_NO_CXX17_INLINE_VARIABLES
#            endif
#            if !defined(__cpp_fold_expressions) || (__cpp_fold_expressions < 201603)
#                define SROOK_NO_CXX17_FOLD_EXPRESSIONS
#            endif
#        endif
#    endif
#endif
#endif
