// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_EXTENSION_IRQ_CONTROL_HPP
#define INCLUDED_SROOK_CONFIG_EXTENSION_IRQ_CONTROL_HPP

#ifdef __GNUC__
#include <srook/config/feature/decltype.hpp>
#include <srook/config/feature/static_assert.hpp>
#include <srook/type_traits/is_same.hpp>

#define SROOK_LOCAL_IRQ_DIABLE() __asm__ __volatile__ ("cli": : :"memory")
#define SROOK_LOCAL_IRQ_ENABLE() __asm__ __volatile__ ("sti": : :"memory")
#define SROOK_LOCAL_IRQ_SAVE(x) __asm__ __volatile__ ("pushfl ; popl %0 ; cli": "=g" (x) : : "memory")
#define SROOK_LOCAL_IRQ_RESTORE(x)\
   	do {\
	   	SROOK_ST_ASSERT((srook::is_same<SROOK_DECLTYPE(x), unsigned long>::value));\
		__asm__ __volatile__ ("pushl %0 ; popfl" : : "g" (x) : "memory", "cc");\
	} while(false)
#endif
#endif
