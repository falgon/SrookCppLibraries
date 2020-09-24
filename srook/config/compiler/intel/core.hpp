// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_COMPILER_INTEL_CORE_HPP
#define INCLUDED_SROOK_CONFIG_COMPILER_INTEL_CORE_HPP
#ifdef __INTEL_COMPILER
#    include <srook/config/cpp_predefined/feature_testing.hpp>
#    if SROOK_HAS_INCLUDE(<boost/config/compiler/intel.hpp>)
#        include <boost/config/compiler/intel.hpp>
#        define SROOK_HAS_BOOST_CONFIG_COMPILER_INTEL_HPP 1
#        ifdef BOOST_HAS_EXPM1
#            define SROOK_HAS_EXPM1 BOOST_HAS_EXPM1
#        endif
#        ifdef BOOST_HAS_LOG1P
#            define SROOK_HAS_LOG1P BOOST_HAS_LOG1P
#        endif
#        ifdef BOOST_INTEL_CXX_VERSION
#            define SROOK_INTEL_CXX_VERSION BOOST_INTEL_CXX_VERSION
#        endif
#        ifdef BOOST_INTEL_STDCXX0X
#            define SROOK_INTEL_STDCXX0X BOOST_INTEL_STDCXX0X
#        endif
#        ifdef BOOST_INTEL_GCC_VERSION
#            define SROOK_INTEL_GCC_VERSION BOOST_INTEL_GCC_VERSION
#        endif
#        ifdef BOOST_COMPILER
#            define SROOK_COMPILER
#            define BOOST_COMPILER BOOST_INTEL
#        endif
#        ifdef BOOST_INTEL_WIN
#            define SROOK_INTEL_WIN BOOST_INTEL_WIN
#        endif
#        ifdef BOOST_INTEL_LINUX
#            define SROOK_INTEL_LINUX BOOST_INTEL_LINUX
#        endif
#        ifdef BOOST_INTEL_STDCXX0X
#            define SROOK_INTEL_STDCXX0X BOOST_INTEL_STDCXX0X
#        endif
#        ifdef BOOST_NO_SWPRINTF
#            define SROOK_NO_SWPRINTF BOOST_NO_SWPRINTF
#        endif
#        ifdef BOOST_NO_VOID_RETURNS
#            define SROOK_NO_VOID_RETURNS BOOST_NO_VOID_RETURNS
#        endif
#        ifdef BOOST_NO_INTEGRAL_INT64_T
#            define SROOK_NO_INTEGRAL_INT64_T BOOST_NO_INTEGRAL_INT64_T
#        endif
#        ifdef BOOST_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS
#            define SROOK_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS \
                BOOST_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS
#        endif
#        ifdef BOOST_NO_INTRINSIC_WCHAR_T
#            define SROOK_NO_INTRINSIC_WCHAR_T BOOST_NO_INTRINSIC_WCHAR_T
#        endif
#        ifdef BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#            define SROOK_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL \
                BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#        endif
#        ifdef BOOST_NO_TWO_PHASE_NAME_LOOKUP
#            define SROOK_NO_TWO_PHASE_NAME_LOOKUP BOOST_NO_TWO_PHASE_NAME_LOOKUP
#        endif
#        ifdef BOOST_HAS_MS_INT64
#            define SROOK_HAS_MS_INT64 BOOST_HAS_MS_INT64
#        endif
#        ifdef BOOST_NO_TWO_PHASE_NAME_LOOKUP
#            define SROOK_NO_TWO_PHASE_NAME_LOOKUP BOOST_NO_TWO_PHASE_NAME_LOOKUP
#        endif
#        ifdef BOOST_DISABLE_WIN32
#            define SROOK_DISABLE_WIN32 BOOST_DISABLE_WIN32
#        endif
#        ifdef BOOST_HAS_NRVO
#            define SROOK_HAS_NRVO BOOST_HAS_NRVO
#        endif
#        ifdef BOOST_LIKELY
#            define SROOK_LIKELY(x) BOOST_LIKELY(x)
#        endif
#        ifdef BOOST_UNLIKELY(x)
#            define SROOK_UNLIKELY(x) BOOST_UNLIKELY(x)
#        endif
#        ifdef BOOST_NO_RTTI
#            define SROOK_NO_RTTI BOOST_NO_RTTI
#        endif
#        ifdef BOOST_NO_RTTI
#            define SROOK_NO_RTTI BOOST_NO_RTTI
#        endif
#        ifdef BOOST_NO_TYPEID
#            define SROOK_NO_TYPEID BOOST_NO_TYPEID
#        endif
#        ifdef BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#            define SROOK_NO_COMPLETE_VALUE_INITIALIZATION \
                BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#        endif
#        ifdef BOOST_SYMBOL_EXPORT __attribute__((visibility("default")))
#            define SROOK_SYMBOL_EXPORT                                    \
                __attribute__((visibility("default"))) BOOST_SYMBOL_EXPORT \
                    __attribute__((visibility("default")))
#        endif
#        ifdef BOOST_SYMBOL_IMPORT
#            define SROOK_SYMBOL_IMPORT BOOST_SYMBOL_IMPORT
#        endif
#        ifdef BOOST_SYMBOL_VISIBLE __attribute__((visibility("default")))
#            define SROOK_SYMBOL_VISIBLE                                    \
                __attribute__((visibility("default"))) BOOST_SYMBOL_VISIBLE \
                    __attribute__((visibility("default")))
#        endif
#        ifdef BOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#            define SROOK_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS \
                BOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#        endif
#        ifdef BOOST_NO_CXX11_HDR_FUTURE
#            define SROOK_NO_CXX11_HDR_FUTURE BOOST_NO_CXX11_HDR_FUTURE
#        endif
#        ifdef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#            define SROOK_NO_CXX11_HDR_INITIALIZER_LIST BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#        endif
#        ifdef BOOST_NO_CXX11_HDR_FUTURE
#            define SROOK_NO_CXX11_HDR_FUTURE BOOST_NO_CXX11_HDR_FUTURE
#        endif
#        ifdef BOOST_NO_CXX11_HDR_TUPLE
#            define SROOK_NO_CXX11_HDR_TUPLE BOOST_NO_CXX11_HDR_TUPLE
#        endif
#        ifdef BOOST_NO_FENV_H
#            define SROOK_NO_FENV_H BOOST_NO_FENV_H
#        endif
#        ifdef BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS
#            define SROOK_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS \
                BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS
#        endif
#        ifdef BOOST_HAS_STDINT_H
#            define SROOK_HAS_STDINT_H BOOST_HAS_STDINT_H
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
#    else
#        if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1500) && (defined(_MSC_VER) || defined(__GNUC__))
#            ifdef _MSC_VER
#                include <srook/config/compiler/msvc.hpp>
#                undef SROOK_MSVC
#                undef SROOK_MSVC_FULL_VER
#                if (__INTEL_COMPILER >= 1500) && (_MSC_VER >= 1900)
#                    define SROOK_HAS_EXPM1
#                    define SROOK_HAS_LOG1P
#                    undef SROOK_NO_CXX14_BINARY_LITERALS
#                    undef SROOK_NO_SFINAE_EXPR
#                endif
#                if (__INTEL_COMPILER <= 1600) && !defined(SROOK_NO_CXX14_VARIABLE_TEMPLATES)
#                    define SROOK_NO_CXX14_VARIABLE_TEMPLATES
#                endif
#            else
#                include <srook/config/compiler/gcc.hpp>
#                undef SROOK_GCC_VERSION
#                undef SROOK_GCC_CXX11
#                if (__INTEL_COMPILER <= 1700) && !defined(SROOK_NO_CXX14_CONSTEXPR)
#                    define SROOK_NO_CXX14_CONSTEXPR
#                endif
#            endif
#            undef SROOK_COMPILER
#            if defined(__INTEL_COMPILER)
#                if __INTEL_COMPILER == 9999
#                    define SROOK_INTEL_CXX_VERSION 1200
#                else
#                    define SROOK_INTEL_CXX_VERSION __INTEL_COMPILER
#                endif
#            elif defined(__ICL)
#                define SROOK_INTEL_CXX_VERSION __ICL
#            elif defined(__ICC)
#                define SROOK_INTEL_CXX_VERSION __ICC
#            elif defined(__ECC)
#                define SROOK_INTEL_CXX_VERSION __ECC
#            endif
#            if (!(defined(_WIN32) || defined(_WIN64)) && defined(__STDC_HOSTED__) && (__STDC_HOSTED__ && (SROOK_INTEL_CXX_VERSION <= 1200))) || defined(__GXX_EXPERIMENTAL_CPP0X__) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#                define SROOK_INTEL_STDCXX0X
#            endif
#            if defined(_MSC_VER) && (_MSC_VER >= 1600)
#                define SROOK_INTEL_STDCXX0X
#            endif
#            ifdef __GNUC__
#                define SROOK_INTEL_GCC_VERSION \
                    (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#            endif
#            if !defined(SROOK_COMPILER)
#                if defined(SROOK_INTEL_STDCXX0X)
#                    define SROOK_COMPILER "Intel C++ C++0x mode version " SROOK_INTEL_CXX_VERSION
#                else
#                    define SROOK_COMPILER "Intel C++ version " SROOK_INTEL_CXX_VERSION
#                endif
#            endif
#            define SROOK_INTEL SROOK_INTEL_CXX_VERSION
#            if defined(_WIN32) || defined(_WIN64)
#                define SROOK_INTEL_WIN SROOK_INTEL
#            else
#                define SROOK_INTEL_LINUX SROOK_INTEL
#            endif
#        else
#            include <srook/config/compiler/common_edg.hpp>
#            if defined(__INTEL_COMPILER)
#                if __INTEL_COMPILER == 9999
#                    define SROOK_INTEL_CXX_VERSION 1200 // Intel bug in 12.1.
#                else
#                    define SROOK_INTEL_CXX_VERSION __INTEL_COMPILER
#                endif
#            elif defined(__ICL)
#                define SROOK_INTEL_CXX_VERSION __ICL
#            elif defined(__ICC)
#                define SROOK_INTEL_CXX_VERSION __ICC
#            elif defined(__ECC)
#                define SROOK_INTEL_CXX_VERSION __ECC
#            endif
#            if (!(defined(_WIN32) || defined(_WIN64)) && defined(__STDC_HOSTED__) && (__STDC_HOSTED__ && (SROOK_INTEL_CXX_VERSION <= 1200))) || defined(__GXX_EXPERIMENTAL_CPP0X__) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#                define SROOK_INTEL_STDCXX0X
#            endif
#            if defined(_MSC_VER) && (_MSC_VER >= 1600)
#                define SROOK_INTEL_STDCXX0X
#            endif
#            ifdef __GNUC__
#                define SROOK_INTEL_GCC_VERSION \
                    (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#            endif
#            if !defined(SROOK_COMPILER)
#                if defined(SROOK_INTEL_STDCXX0X)
#                    define SROOK_COMPILER "Intel C++ C++0x mode version " SROOK_INTEL_CXX_VERSION
#                else
#                    define SROOK_COMPILER "Intel C++ version " SROOK_INTEL_CXX_VERSION
#                endif
#            endif
#            define SROOK_INTEL SROOK_INTEL_CXX_VERSION
#            if defined(_WIN32) || defined(_WIN64)
#                define SROOK_INTEL_WIN SROOK_INTEL
#            else
#                define SROOK_INTEL_LINUX SROOK_INTEL
#            endif
#            if (SROOK_INTEL_CXX_VERSION <= 600)
#                if defined(_MSC_VER) && (_MSC_VER <= 1300)
#                    define SROOK_NO_SWPRINTF
#                endif
#                if defined(_MSC_VER) && (_MSC_VER <= 1200)
#                    define SROOK_NO_VOID_RETURNS
#                    define SROOK_NO_INTEGRAL_INT64_T
#                endif
#            endif
#            if (SROOK_INTEL_CXX_VERSION <= 710) && defined(_WIN32)
#                define SROOK_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS
#            endif
#            if SROOK_INTEL_CXX_VERSION < 600
#                define SROOK_NO_INTRINSIC_WCHAR_T
#            else
#                if ((_WCHAR_T_DEFINED + 0) == 0) && ((_WCHAR_T + 0) == 0)
#                    define SROOK_NO_INTRINSIC_WCHAR_T
#                endif
#            endif
#            if defined(__GNUC__) && !defined(SROOK_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
#                if ((__GNUC__ == 3) && (__GNUC_MINOR__ <= 2)) || (SROOK_INTEL < 900) || (__INTEL_COMPILER_BUILD_DATE < 20050912)
#                    define SROOK_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#                endif
#            endif
#            if (defined(__GNUC__) && (__GNUC__ < 4)) || (defined(_WIN32) && (SROOK_INTEL_CXX_VERSION <= 1200)) || (SROOK_INTEL_CXX_VERSION <= 1200)
#                define SROOK_NO_TWO_PHASE_NAME_LOOKUP
#            endif
#        endif
#        ifdef __cplusplus
#            if defined(SROOK_NO_INTRINSIC_WCHAR_T)
#                include <cwchar>
template <typename T>
struct assert_no_intrinsic_wchar_t;
template <>
struct assert_no_intrinsic_wchar_t<wchar_t> {
    typedef void type;
};

typedef assert_no_intrinsic_wchar_t<unsigned short>::type
    assert_no_intrinsic_wchar_t_;
#            else
template <typename T>
struct assert_intrinsic_wchar_t;
template <>
struct assert_intrinsic_wchar_t<wchar_t> {
};
template <>
struct assert_intrinsic_wchar_t<unsigned short> {
};
#            endif
#        endif
#        if defined(_MSC_VER) && (_MSC_VER + 0 >= 1000)
#            if _MSC_VER >= 1200
#                define SROOK_HAS_MS_INT64
#            endif
#            define SROOK_NO_SWPRINTF
#            define SROOK_NO_TWO_PHASE_NAME_LOOKUP
#        elif defined(_WIN32)
#            define SROOK_DISABLE_WIN32
#        endif
#        if (SROOK_INTEL_CXX_VERSION >= 600)
#            define SROOK_HAS_NRVO
#        endif
#        if defined(__GNUC__) && SROOK_INTEL_CXX_VERSION >= 800
#            define SROOK_LIKELY(x) __builtin_expect(x, 1)
#            define SROOK_UNLIKELY(x) __builtin_expect(x, 0)
#        endif
#        if !defined(__RTTI) && !defined(__INTEL_RTTI__) && !defined(__GXX_RTTI) && !defined(_CPPRTTI)
#            if !defined(SROOK_NO_RTTI)
#                define SROOK_NO_RTTI
#            endif
#            if !defined(_MSC_VER) && !defined(SROOK_NO_TYPEID)
#                define SROOK_NO_TYPEID
#            endif
#        endif
#        if SROOK_INTEL_CXX_VERSION < 600
#            error "Compiler not supported or configured - please reconfigure"
#        endif
#        if defined(__APPLE__) && defined(__INTEL_COMPILER)
#            define SROOK_NO_TWO_PHASE_NAME_LOOKUP
#        endif
#        if defined(__itanium__) && defined(__INTEL_COMPILER)
#            define SROOK_NO_TWO_PHASE_NAME_LOOKUP
#        endif
#        if defined(__INTEL_COMPILER)
#            if (__INTEL_COMPILER <= 1110) || (__INTEL_COMPILER == 9999) || (defined(_WIN32) && (__INTEL_COMPILER < 1600))
#                define SROOK_NO_COMPLETE_VALUE_INITIALIZATION
#            endif
#        endif
#        if defined(__GNUC__) && (__GNUC__ >= 4)
#            define SROOK_SYMBOL_EXPORT __attribute__((visibility("default")))
#            define SROOK_SYMBOL_IMPORT
#            define SROOK_SYMBOL_VISIBLE __attribute__((visibility("default")))
#        endif
#        if defined(__GNUC__) && (SROOK_INTEL_CXX_VERSION >= 1300)
#            define SROOK_MAY_ALIAS __attribute__((__may_alias__))
#        endif
#        if defined(SROOK_INTEL_STDCXX0X)
#            if (SROOK_INTEL_CXX_VERSION >= 1500) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40600)) && !defined(_MSC_VER)
#                undef SROOK_NO_CXX11_CONSTEXPR
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1210) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40600)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#                undef SROOK_NO_CXX11_NULLPTR
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1210) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40700)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#                undef SROOK_NO_CXX11_TEMPLATE_ALIASES
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40300)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#                undef SROOK_NO_CXX11_DECLTYPE
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1500) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40800)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#                undef SROOK_NO_CXX11_DECLTYPE_N3276
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40300)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#                undef SROOK_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1300) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40300)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#                undef SROOK_NO_CXX11_RVALUE_REFERENCES
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1110) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40300)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#                undef SROOK_NO_CXX11_STATIC_ASSERT
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#                undef SROOK_NO_CXX11_VARIADIC_TEMPLATES
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40200)) && (!defined(_MSC_VER) || (_MSC_VER >= 1400))
#                undef SROOK_NO_CXX11_VARIADIC_MACROS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#                undef SROOK_NO_CXX11_AUTO_DECLARATIONS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#                undef SROOK_NO_CXX11_AUTO_MULTIDECLARATIONS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#                undef SROOK_NO_CXX11_CHAR16_T
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#                undef SROOK_NO_CXX11_CHAR32_T
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#                undef SROOK_NO_CXX11_DEFAULTED_FUNCTIONS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#                undef SROOK_NO_CXX11_DELETED_FUNCTIONS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_VER >= 1700))
#                undef SROOK_NO_CXX11_HDR_INITIALIZER_LIST
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40501)) && (!defined(_MSC_VER) || (_MSC_VER >= 1700))
#                undef SROOK_NO_CXX11_SCOPED_ENUMS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40500)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#                undef SROOK_NO_SFINAE_EXPR
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1500) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40800)) && !defined(_MSC_VER)
#                undef SROOK_NO_CXX11_SFINAE_EXPR
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1500) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40500)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#                undef SROOK_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40500)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#                undef SROOK_NO_CXX11_LAMBDAS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40500))
#                undef SROOK_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40600)) && (!defined(_MSC_VER) || (_MSC_VER >= 1700))
#                undef SROOK_NO_CXX11_RANGE_BASED_FOR
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40500)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#                undef SROOK_NO_CXX11_RAW_LITERALS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40500)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#                undef SROOK_NO_CXX11_UNICODE_LITERALS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1500) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40600)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#                undef SROOK_NO_CXX11_NOEXCEPT
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40600)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#                undef SROOK_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1500) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40700)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 190021730))
#                undef SROOK_NO_CXX11_USER_DEFINED_LITERALS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1500) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40800)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 190021730))
#                undef SROOK_NO_CXX11_ALIGNAS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1200) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#                undef SROOK_NO_CXX11_TRAILING_RESULT_TYPES
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 190021730))
#                undef SROOK_NO_CXX11_INLINE_NAMESPACES
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40800)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 190021730))
#                undef SROOK_NO_CXX11_REF_QUALIFIERS
#            endif
#            if (SROOK_INTEL_CXX_VERSION >= 1400) && (!defined(SROOK_INTEL_GCC_VERSION) || (SROOK_INTEL_GCC_VERSION >= 40700)) && (!defined(_MSC_VER) || (_MSC_VER >= 1700))
#                undef SROOK_NO_CXX11_FINAL
#            endif
#        endif
#        define SROOK_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#        if defined(SROOK_INTEL_STDCXX0X) && (SROOK_INTEL_CXX_VERSION <= 1310)
#            define SROOK_NO_CXX11_HDR_FUTURE
#            define SROOK_NO_CXX11_HDR_INITIALIZER_LIST
#        endif
#        if defined(SROOK_INTEL_STDCXX0X) && (SROOK_INTEL_CXX_VERSION == 1400)
#            define SROOK_NO_CXX11_HDR_FUTURE
#            define SROOK_NO_CXX11_HDR_TUPLE
#        endif
#        if (SROOK_INTEL_CXX_VERSION < 1200)
#            define SROOK_NO_FENV_H
#        endif
#        if (SROOK_INTEL_CXX_VERSION <= 1310)
#            define SROOK_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS
#        endif
#        if defined(_MSC_VER) && (_MSC_VER >= 1600)
#            define SROOK_HAS_STDINT_H
#        endif
#        if defined(__CUDACC__)
#            if defined(SROOK_GCC_CXX11)
#                define SROOK_NVCC_CXX11
#            else
#                define SROOK_NVCC_CXX03
#            endif
#        endif
#        if defined(__LP64__) && defined(__GNUC__) && (SROOK_INTEL_CXX_VERSION >= 1310) && !defined(SROOK_NVCC_CXX03)
#            define SROOK_HAS_INT128
#        endif
#    endif
#endif
#endif
