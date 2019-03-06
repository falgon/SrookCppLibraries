// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
// N4660 19.8 Predefined macro names [cpp.predefined]
#ifndef INCLUDED_SROOK_CONFIG_CPP_PREDEFINED_MACRO_NAMES_HPP
#define INCLUDED_SROOK_CONFIG_CPP_PREDEFINED_MACRO_NAMES_HPP

#ifdef __cplusplus
#define SROOK_CPLUSPLUS __cplusplus
#define SROOK_DATE __DATE__
#define SROOK_FILE __FILE__
#define SROOK_LINE __LINE__
#define SROOK_STDC_HOSTED __STDC_HOSTED__
#define SROOK_TIME __TIME__

#ifdef __STDC__
#define SROOK_STDC __STDC__
#else
#define SROOK_STDC 0
#endif

#ifdef __STDC_MB_MIGHT_NEQ_WC__
#define SROOK_STDC_MB_MIGHT_NEQ_WC _STDC_MB_MIGHT_NEQ_WC__
#else
#define SROOK_STDC_MB_MIGHT_NEQ_WC 0
#endif

#ifdef __STDC_VERSION__
#define SROOK_STDC_VERSION __STDC_VERSION__
#else
#define SROOK_STDC_VERSION 0
#endif

#ifdef __STDC_ISO_10646__
#define SROOK_STDC_ISO_10646 __STDC_ISO_10646__
#else
#define SROOK_STDC_ISO_10646 0
#endif

#ifdef __STDCPP_STRICT_POINTER_SAFETY__
#define SROOK_STDCPP_STRICT_POINTER_SAFETY __STDCPP_STRICT_POINTER_SAFETY__
#else
#define SROOK_STDCPP_STRICT_POINTER_SAFETY
#endif

#ifdef __STDCPP_THREADS__
#define SROOK_STDCPP_THREADS __STDCPP_THREADS__
#else
#define SROOK_STDCPP_THREADS
#endif
#endif

#endif
