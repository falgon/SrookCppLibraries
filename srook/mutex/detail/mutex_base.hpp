// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_THREAD_DETAIL_MUTEX_BASE_HPP
#define INCLUDED_SROOK_THREAD_DETAIL_MUTEX_BASE_HPP

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
namespace mutexes { 
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#	define SROOK_MUTEX_INIT = SROOK_MUTEX_INITIALIZER
#	define SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE
#	define SROOK_MUTEX_BASE_CONSTRUCTOR SROOK_CONSTEXPR mutex_base() SROOK_DEFAULT
#else
#	define SROOK_MUTEX_INIT
#	define SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE\
   	SROOK_DEPRECATED_MESSAGE(\
			"No constexpr until C++03 so srook::mutex doesn't support static initialization.\n"\
			"See also: http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#828 "\
	)
#	define SROOK_MUTEX_BASE_CONSTRUCTOR\
	SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE\
	mutex_base() SROOK_NOEXCEPT_TRUE\
	{\
		pthread_mutex_init(&m, NULL);\
	}
#	endif

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT SROOK_THREAD_SAFETY_ANNOTATION(capability("mutex")) 
mutex_base : private noncopyable<mutex_base> {
protected:
    typedef thread::detail::mutex_type native_type;
    native_type m SROOK_MUTEX_INIT;
#undef SROOK_MUTEX_INIT
public:
    SROOK_ATTRIBUTE_INLINE_VISIBILITY SROOK_MUTEX_BASE_CONSTRUCTOR
#undef SROOK_MUTEX_BASE_CONSTRUCTOR
	~mutex_base() SROOK_NOEXCEPT_TRUE
    {
		thread::detail::mutex_destroy(&m);
    }
};

SROOK_INLINE_NAMESPACE_END
} // namespace mutexes
} // namespace srook

SROOK_POP_MACROS
#    else
#        error This environment is not supported.
#    endif
#endif
#endif
