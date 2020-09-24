// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_THREAD_DETAIL_RECURSIVE_MUTEX_BASE_HPP
#define INCLUDED_SROOK_THREAD_DETAIL_RECURSIVE_MUTEX_BASE_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>

#if (!SROOK_HAS_INCLUDE(<system_error>)) && (!SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>))
#    error This environment is not supported.
#else
#    include <srook/config/attribute/deprecated.hpp>
#    include <srook/config/feature/default.hpp>
#    include <srook/config/feature/delete.hpp>
#    include <srook/config/feature/explicit.hpp>
#    include <srook/config/feature/inline_variable.hpp>
#    include <srook/config/feature/static_assert.hpp>
#    include <srook/thread/detail/support.hpp>
#    include <srook/utility/noncopyable.hpp>
#    if SROOK_HAS_INCLUDE(<system_error>)
#        include <system_error>
#    elif SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
#        include <boost/system/system_error.hpp>
#    endif

#    if SROOK_HAS_THREADS
#        if !SROOK_THREAD_SAFETY_ANNOTATION
#            if SROOK_HAS_THREAD_SAFETY_ANNOTATIONS
#                define SROOK_THREAD_SAFETY_ANNOTATION(x) __attribute__((x))
#            else
#                define SROOK_THREAD_SAFETY_ANNOTATION(x)
#            endif
#        endif

namespace srook {
namespace mutexes { 
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#	define SROOK_RECURSIVE_MUTEX_INIT = SROOK_RECURSIVE_MUTEX_INITIALIZER
#else
#	define SROOK_RECURSIVE_MUTEX_INIT
#endif

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT SROOK_THREAD_SAFETY_ANNOTATION(capability("mutex")) 
recursive_mutex_base : private noncopyable<recursive_mutex_base> {
protected:
    typedef threading::detail::recursive_mutex_type native_type;
    native_type m SROOK_RECURSIVE_MUTEX_INIT;
#undef SROOK_MUTEX_INIT
public:
    SROOK_ATTRIBUTE_INLINE_VISIBILITY recursive_mutex_base() 
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
		: m(SROOK_RECURSIVE_MUTEX_INITIALIZER)		
#endif
    {
        threading::detail::recursive_mutex_init(&m);
    }
	~recursive_mutex_base() SROOK_NOEXCEPT_TRUE
    {
        threading::detail::recursive_mutex_destroy(&m);
    }
};

SROOK_INLINE_NAMESPACE_END
} // namespace mutexes
} // namespace srook

#    else
#        error This environment is not supported.
#    endif
#endif
#endif
