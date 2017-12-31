// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_COMPILER_ILE_HPP
#define INCLUDED_SROOK_CONFIG_COMPILER_ILE_HPP

#if defined(__IBMCPP__) && !defined(SROOK_COMPILER_IS_ILE)
#	define SROOK_COMPILER_IS_ILE 1
#elif !defined(__IBMCPP__) && !defined(SROOK_COMPILER_IS_ILE)
#	define SROOK_COMPILER_IS_ILE 0
#endif

#if defined(__ANSI__) && !defined(SROOK_ANSI)
#	define SROOK_ANSI __ANSI__
#endif

#if defined(__ASYNC_SIG__) && !defined(SROOK_ASYNC_SIG)
#	define SROOK_ASYNC_SIG __ASYNC_SIG__
#endif

#if defined(__BASE_FILE__) && !defined(SROOK_BASE_FILE)
#	define SROOK_BASE_FILE
#endif

// TASK: https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rzarf/ilcrpmcr_ile.htm

#endif
