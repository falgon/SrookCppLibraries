// Copyright (C) 2017 roki
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


#endif
