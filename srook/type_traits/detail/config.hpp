// Copyright (C) 2011-2020 Roki. Distributed under the MIT License.
#ifndef INCLUDED_SROOK_TYPE_TRAITS_DETAIL_CONFIG_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_DETAIL_CONFIG_HPP

#ifndef INCLUDED_SROOK_CONFIG_HPP
#    include <srook/config.hpp>
#endif
#ifdef SROOK_HAS_PRAGMA_ONCE
#    pragma once
#endif
#if defined(BOOST_TT_CONFIG_HPP_INCLUDED) || !defined(SROOK_HAS_BOOST_TT_CONFIG_HPP)
#    define SROOK_HAS_BOOST_TT_CONFIG_HPP 1
#else
#    if SROOK_HAS_INCLUDE(<boost/type_traits/detail/config.hpp>)
#        include <boost/type_traits/detail/config.hpp>
#        define SROOK_HAS_BOOST_TT_CONFIG_HPP 1
#    endif
#endif
#ifdef SROOK_HAS_BOOST_TT_CONFIG_HPP
#    ifdef BOOST_TT_DECL
#        define SROOK_TT_DECL BOOST_TT_DECL
#    endif
#    ifdef BOOST_TT_NO_CONFORMING_IS_CLASS_IMPLEMENTATION
#        define SROOK_TT_NO_CONFORMING_IS_CLASS_IMPLEMENTATION BOOST_TT_NO_CONFORMING_IS_CLASS_IMPLEMENTATION
#    endif
#    ifdef BOOST_TT_HAS_CONFORMING_IS_CLASS_IMPLEMENTATION
#        define SROOK_TT_HAS_CONFORMING_IS_CLASS_IMPLEMENTATION BOOST_TT_HAS_CONFORMING_IS_CLASS_IMPLEMENTATION
#    endif
#    ifdef BOOST_TT_TEST_MS_FUNC_SIGS
#        define SROOK_TT_TEST_MS_FUNC_SIGS BOOST_TT_TEST_MS_FUNC_SIGS
#    endif
#    ifdef BOOST_TT_NO_CV_FUNC_TEST
#        define SROOK_TT_NO_CV_FUNC_TEST BOOST_TT_NO_CV_FUNC_TEST
#    endif
#else
#    if defined(SROOK_MSVC) || (defined(__BORLANDC__) && !defined(SROOK_DISABLE_WIN32))
#        define SROOK_TT_DECL __cdecl
#    else
#        define SROOK_TT_DECL
#    endif
#    if (defined(__MWERKS__) && __MWERKS__ < 0x3000)       \
        || (defined(__IBMCPP__) && __IBMCPP__ < 600)       \
        || (defined(__BORLANDC__) && __BORLANDC__ < 0x5A0) \
        || (defined(__ghs))                                \
        || (defined(__HP_aCC) && __HP_aCC < 60700)         \
        || (defined(MPW_CPLUS) && MPW_CPLUS == 0x890)      \
        || (defined(__SUNPRO_CC) && __SUNPRO_CC == 0x580)  \
               && defined(SROOK_NO_IS_ABSTRACT)
#        define SROOK_TT_NO_CONFORMING_IS_CLASS_IMPLEMENTATION 1
#    endif
#    ifndef SROOK_TT_NO_CONFORMING_IS_CLASS_IMPLEMENTATION
#        define SROOK_TT_HAS_CONFORMING_IS_CLASS_IMPLEMENTATION 1
#    endif
#    if defined(_MSC_EXTENSIONS) && !defined(__BORLANDC__)
#        define SROOK_TT_TEST_MS_FUNC_SIGS
#    endif
#    if (defined(__MWERKS__) && __MWERKS__ < 0x3000) || (defined(__IBMCPP__) && __IBMCPP__ <= 600)
#        define SROOK_TT_NO_CV_FUNC_TEST
#    endif
#endif
#endif
