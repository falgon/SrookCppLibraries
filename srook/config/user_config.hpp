// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_USER_CONFIG_HPP
#define INCLUDED_SROOK_CONFIG_USER_CONFIG_HPP

/* 
 * 
 * builtin features settings. 
 *
 */

// #define SROOK_CONFIG_DISABLE_BUILTIN_CMATH_FUNCTION 1
// #define SROOK_CONFIG_DISABLE_BUILTIN_STRING_FUNCTION 1
// #define SROOK_CONFIG_DISABLE_BUILTIN_ADDRESS_OF 1

/* 
 *
 * detecting to version of ARM thumb settings.
 * this starts to become fragile and cumbersome, and may be overkill; it depends on the level of activity of the old Debian arm port.
 * See also: https://wiki.ubuntu.com/ARM/Thumb2PortingHowto 
 * 
 */

// #define SROOK_ARCH_ARM_THUMB_CHECK_MORE_COMPREHENSIVE 1

/*
 *
 * thread settings.
 *
 */

// #define SROOK_CONFIG_NO_THREADS 1
// #define SROOK_CONFIG_DISABLE_THREAD_SAFETY_ANNOTATIONS 1
// #define SROOK_CONFIG_THREAD_ENABLE_PHYSICAL_CONCURRENCY 1
#define SROOK_CONFIG_USE_PTHREADS_NUM_PROCESSORS_NP 1

/*
 *
 * diagnostics settings.
 *
 */

// #define SROOK_CONFIG_DIABLE_ADDITIONAL_DIAGNOSTICS 1

/*
 *
 * attributes settings.
 *
 */

// #define SROOK_CONFIG_DISABLE_VISIBILITY_ANNOTATIONS 1
// #define SROOK_CONFIG_DISABLE_DEPRECATED_OF_ATTRIBUTE_MESSAGES 1

/*
 *
 * language version settings.
 *
 */

// #define SROOK_CONFIG_ENABLE_CPP03_IMPLICIT_MOVE_CONSTRUCTIBLE 1


/*
 *
 * Boost settings.
 *
 */

#define SROOK_CONFIG_DISABLE_BOOST 1
// #define SROOK_CONFIG_DISABLE_BOOST_CHRONO 1
#if SROOK_CONFIG_DISABLE_BOOST && !defined(SROOK_CONFIG_DISABLE_BOOST_CHRONO)
#    define SROOK_CONFIG_DISABLE_BOOST_CHRONO 1
#endif
// #define SROOK_CONFIG_PMR_BOOST_FLAT_MAP_INCLUDE 1
// #define SROOK_CONFIG_PMR_BOOST_FLAT_SET_INCLUDE 1
// #define SROOK_CONFIG_PMR_BOOST_SLIST_INCLUDE 1
// #define SROOK_CONFIG_PMR_BOOST_SMALL_VECTOR_INCLUDE 1
// #define SROOK_CONFIG_PMR_BOOST_STABLE_VECTOR_INCLUDE 1

/*
 *
 * srook/memory_resource/pmrlib.hpp include settings
 *
 */
#define SROOK_CONFIG_PMR_ALL_INCLUDE 1 // default
// #define SROOK_CONFIG_PMR_STD_BASIC_STRING_INCLUDE 1
// #define SROOK_CONFIG_PMR_STD_DEQUE_INCLUDE 1
// #define SROOK_CONFIG_PMR_STD_FORWARD_LIST_INCLUDE 1
// #define SROOK_CONFIG_PMR_STD_LIST_INCLUDE 1
// #define SROOK_CONFIG_PMR_STD_VECTOR_INCLUDE 1
// #define SROOK_CONFIG_PMR_STD_MAP_INCLUDE 1
// #define SROOK_CONFIG_PMR_STD_SET_INCLUDE 1
// #define SROOK_CONFIG_PMR_STD_UNORDERED_MAP_INCLUDE 1
// #define SROOK_CONFIG_PMR_STD_UNORDERED_SET_INCLUDE 1
// #define SROOK_CONFIG_PMR_STD_REGEX 1

/*
 *
 * memcpy configure.
 * When set, the library checks the memory space with a call to memcpy.
 *
 */
// #define SROOK_CONFIG_CHECK_MEMCPY 1
// #define SROOK_CONFIG_ENABLE_AVX_MEMCPY 1
// #define SROOK_CONFIG_ENABLE_AVX512_MEMCPY 1


/*
 *
 * srook/tmpl/vr/at.hpp limit settings.
 *
 */
#define SROOK_CONFIG_TMPL_AT_LIMIT 128

/*
 *
 * When compiling functions that receive Range, compile the Boost.Range library to take precedence. 
 *
 */
// #define SROOK_CONFIG_ENABLE_BOOST_RANGE_ITERATOR 1

/*
 *
 * By setting the flag, srook/memory_resource/polymorphic_allocator and srook::pmr::XX will be prioritized 
 * in the inclusion of polymorphic allocator components.
 *
 */
// #define SROOK_CONFIG_ENABLE_PMR_PRIORITY 1

#endif
