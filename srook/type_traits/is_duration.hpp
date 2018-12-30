// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_DURATION_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_DURATION_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_HAS_LIB_STD_CHRONO || SROOK_HAS_LIB_BOOST_CHRONO || (SROOK_HAS_INCLUDE(<chrono>) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) || SROOK_HAS_INCLUDE(<boost / chrono.hpp>) || SROOK_HAS_INCLUDE(<boost / chrono / include.hpp>)
#    include <srook/config/feature.hpp>
#    include <srook/config/user_config.hpp>
#    include <srook/type_traits/true_false_type.hpp>

#    if !defined(SROOK_HAS_LIB_STD_CHRONO) && (SROOK_HAS_INCLUDE(<chrono>) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT)
#        include <chrono>
#        define SROOK_HAS_LIB_STD_CHRONO 1
#    endif
#    if !SROOK_CONFIG_DISABLE_BOOST_CHRONO && !defined(SROOK_HAS_LIB_BOOST_CHRONO) && SROOK_HAS_INCLUDE(<boost/chrono.hpp>)
#        include <boost/chrono.hpp>
#        define SROOK_HAS_LIB_BOOST_CHRONO 1
#    elif !SROOK_CONFIG_DISABLE_BOOST_CHRONO && !defined(SROOK_HAS_LIB_BOOST_CHRONO) && SROOK_HAS_INCLUDE(<boost/chrono/include.hpp>)
#        include <boost/chrono/include.hpp>
#        define SROOK_HAS_LIB_BOOST_CHRONO 1
#    endif

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class>
struct is_duration : public SROOK_FALSE_TYPE {};

#    if SROOK_HAS_LIB_STD_CHRONO
template <class Rep, class Period>
struct is_duration<std::chrono::duration<Rep, Period> > : public SROOK_TRUE_TYPE {};
#    endif

#    if SROOK_HAS_LIB_BOOST_CHRONO
template <class Rep, class Period>
struct is_duration<boost::chrono::duration<Rep, Period> > : public SROOK_TRUE_TYPE {};
#    endif

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_duration;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_duration_v = is_duration<T>::value;
#    endif

} // namespace srook

#    else

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

template <class>
struct is_duration : public SROOK_FALSE_TYPE {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_duration;

#        if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR is_duration_v = is_duration<T>::value;
#        endif

} // namespace srook

#    endif
#endif
