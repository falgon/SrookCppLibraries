// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_THREAD_DETAIL_MUTEX_BASE_HPP
#define INCLUDED_SROOK_THREAD_DETAIL_MUTEX_BASE_HPP

#include <srook/config/attribute/deprecated.hpp>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/mutex/includes/lib.hpp>
#include <srook/utility/noncopyable.hpp>
#include <srook/type_traits/is_nothrow_default_constructible.hpp>

namespace srook {
namespace mutexes {
SROOK_INLINE_NAMESPACE(v1)

#        if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#            define SROOK_MUTEX_INIT = SROOK_MUTEX_INITIALIZER
#            define SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE
#            define SROOK_MUTEX_BASE_CONSTRUCTOR SROOK_CONSTEXPR mutex_base() SROOK_DEFAULT
#        else
#            define SROOK_MUTEX_INIT
#            define SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE                                    \
                SROOK_DEPRECATED_MESSAGE(                                                               \
                    "No constexpr until C++03 so mutex doesn't support static initialization.\n" \
                    "See also: http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#828 ")
#            define SROOK_MUTEX_BASE_CONSTRUCTOR                             \
                SROOK_MUTEX_DOES_NOT_SUPPORT_STATIC_INIT_MESSAGE             \
                mutex_base() SROOK_NOEXCEPT_TRUE                             \
                {                                                            \
                    m = (threading::detail::mutex_type)SROOK_MUTEX_INITIALIZER; \
                }
#        endif

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT SROOK_THREAD_SAFETY_ANNOTATION(capability("mutex"))
    mutex_base : private noncopyable<mutex_base> {
protected:
    typedef threading::detail::mutex_type native_type;
    native_type m SROOK_MUTEX_INIT;
#        undef SROOK_MUTEX_INIT
public:
    SROOK_ATTRIBUTE_INLINE_VISIBILITY SROOK_MUTEX_BASE_CONSTRUCTOR
#        undef SROOK_MUTEX_BASE_CONSTRUCTOR
        ~mutex_base() SROOK_NOEXCEPT_TRUE
    {
        threading::detail::mutex_destroy(&m);
    }
};

SROOK_INLINE_NAMESPACE_END
} // namespace mutexes
} // namespace srook

#endif
