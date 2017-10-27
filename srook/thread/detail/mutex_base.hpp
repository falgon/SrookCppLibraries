// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_DETAIL_MUTEX_BASE_HPP
#define INCLUDED_SROOK_THREAD_DETAIL_MUTEX_BASE_HPP

#include <srook/config/cpp_predefined/feature_testing.hpp>

#if !SROOK_HAS_INCLUDE(<system_error>) && !SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
#    error This environment is not supported.
#else
#    include <srook/config/feature/default.hpp>
#    include <srook/config/feature/delete.hpp>
#    include <srook/config/feature/explicit.hpp>
#    include <srook/config/feature/inline_variable.hpp>
#    include <srook/config/feature/static_assert.hpp>
#    include <srook/thread/detail/support.hpp>
#    include <srook/type_traits/is_nothrow_default_constructible.hpp>
#    include <srook/utility/noncopyable.hpp>
#    if SROOK_HAS_INCLUDE(<system_error>)
#        include <system_error>
#    elif SROOK_HAS_INCLUDE(<boost/system/system_error.hpp>)
#        include <boost/system/system_error.hpp>
#    endif

SROOK_PUSH_MACROS
#    ifdef min
#        undef min
#    endif
#    ifdef max
#        undef max
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
namespace thread {
namespace mutex_collection {
SROOK_INLINE_NAMESPACE(v1)

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT SROOK_THREAD_SAFETY_ANNOTATION(capability("mutex")) 
mutex_base : private noncopyable<mutex_base> {
protected:
    typedef detail::mutex_type native_type;
    native_type m
#        if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        = SROOK_MUTEX_INITIALIZER
#        endif
        ;
public:
    SROOK_ATTRIBUTE_INLINE_VISIBILITY
#        if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    SROOK_CONSTEXPR mutex_base() SROOK_DEFAULT
#        else
    mutex_base() SROOK_NOEXCEPT_TRUE
    {
		pthread_mutex_init(&m, NULL);
	}
#        endif    
	~mutex_base() SROOK_NOEXCEPT_TRUE
    {
        detail::mutex_destroy(&m);
    }
};

SROOK_INLINE_NAMESPACE_END
} // namespace mutex_collection
} // namespace thread
} // namespace srook

SROOK_POP_MACROS
#    else
#        error This environment is not supported.
#    endif
#endif
#endif
