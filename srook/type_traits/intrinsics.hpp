// Copyright (C) 2011-2019 Roki. Distributed under the MIT License.
#ifndef SROOK_TYPE_TRAITS_INTRINSICS_HPP_INCLUDED
#define SROOK_TYPE_TRAITS_INTRINSICS_HPP_INCLUDED

#ifndef SROOK_TYPE_TRAITS_DISABLE_INTRINSICS
#    include <srook/config.hpp>
#    ifndef BOOST_TT_INTRINSICS_HPP_INCLUDED
#        if SROOK_HAS_INCLUDE(<boost / type_traits / intrinsics.hpp>)
#            define SROOK_HAS_BOOST_TT_INTRINSICS_HPP 1
#        endif
#    endif
#    if defined(BOOST_TT_INTRINSICS_HPP_INCLUDED) || !defined(SROOK_HAS_BOOST_TT_INTRINSICS_HPP)
#        define SROOK_HAS_BOOST_TT_INTRINSICS_HPP
#    endif
#    ifdef SROOK_HAS_BOOST_TT_INTRINSICS_HPP
#        ifdef BOOST_IS_UNION
#            define SROOK_IS_UNION(T) BOOST_IS_UNION(T)
#        endif
#        ifdef BOOST_IS_POD
#            define SROOK_IS_POD(T) BOOST_IS_POD(T)
#        endif
#        ifdef BOOST_IS_EMPTY
#            define SROOK_IS_EMPTY(T) BOOST_IS_EMPTY(T)
#        endif
#        ifdef BOOST_HAS_TRIVIAL_CONSTRUCTOR
#            define SROOK_HAS_TRIVIAL_CONSTRUCTOR(T) BOOST_HAS_TRIVIAL_CONSTRUCTOR(T)
#        endif
#        ifdef BOOST_HAS_TRIVIAL_COPY
#            define SROOK_HAS_TRIVIAL_COPY(T) BOOST_HAS_TRIVIAL_COPY(T)
#        endif
#        ifdef BOOST_HAS_TRIVIAL_MOVE_CONSTRUCTOR
#            define SROOK_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) BOOST_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T)
#        endif
#        ifdef BOOST_HAS_TRIVIAL_ASSIGN
#            define SROOK_HAS_TRIVIAL_ASSIGN(T) BOOST_HAS_TRIVIAL_ASSIGN(T)
#        endif
#        ifdef BOOST_HAS_TRIVIAL_MOVE_ASSIGN
#            define SROOK_HAS_TRIVIAL_MOVE_ASSIGN(T) BOOST_HAS_TRIVIAL_MOVE_ASSIGN(T)
#        endif
#        ifdef BOOST_HAS_TRIVIAL_DESTRUCTOR
#            define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) BOOST_HAS_TRIVIAL_DESTRUCTOR(T)
#        endif
#        ifdef BOOST_HAS_NOTHROW_CONSTRUCTOR
#            define SROOK_HAS_NOTHROW_CONSTRUCTOR(T) BOOST_HAS_NOTHROW_CONSTRUCTOR(T)
#        endif
#        ifdef BOOST_HAS_NOTHROW_COPY
#            define SROOK_HAS_NOTHROW_COPY(T) BOOST_HAS_NOTHROW_COPY(T)
#        endif
#        ifdef BOOST_HAS_NOTHROW_ASSIGN
#            define SROOK_HAS_NOTHROW_ASSIGN(T) BOOST_HAS_NOTHROW_ASSIGN(T)
#        endif
#        ifdef BOOST_HAS_VIRTUAL_DESTRUCTOR
#            define SROOK_HAS_VIRTUAL_DESTRUCTOR(T) BOOST_HAS_VIRTUAL_DESTRUCTOR(T)
#        endif
#        ifdef BOOST_IS_NOTHROW_MOVE_CONSTRUCT
#            define SROOK_IS_NOTHROW_MOVE_CONSTRUCT(T) BOOST_IS_NOTHROW_MOVE_CONSTRUCT(T)
#        endif
#        ifdef BOOST_IS_NOTHROW_MOVE_ASSIGN
#            define SROOK_IS_NOTHROW_MOVE_ASSIGN(T) BOOST_IS_NOTHROW_MOVE_ASSIGN(T)
#        endif
#        ifdef BOOST_IS_ABSTRACT
#            define SROOK_IS_ABSTRACT(T) BOOST_IS_ABSTRACT(T)
#        endif
#        ifdef BOOST_IS_BASE_OF
#            define SROOK_IS_BASE_OF(T, U) BOOST_IS_BASE_OF(T, U)
#        endif
#        ifdef BOOST_IS_CLASS
#            define SROOK_IS_CLASS(T) BOOST_IS_CLASS(T)
#        endif
#        ifdef BOOST_IS_CONVERTIBLE
#            define SROOK_IS_CONVERTIBLE(T, U) BOOST_IS_CONVERTIBLE(T, U)
#        endif
#        ifdef BOOST_IS_ENUM
#            define SROOK_IS_ENUM(T) BOOST_IS_ENUM(T)
#        endif
#        ifdef BOOST_IS_POLYMORPHIC
#            define SROOK_IS_POLYMORPHIC(T) BOOST_IS_POLYMORPHIC(T)
#        endif
#        ifdef BOOST_ALIGNMENT_OF
#            define SROOK_ALIGNMENT_OF(T) BOOST_ALIGNMENT_OF(T)
#        endif
#    else
#        ifndef SROOK_TT_CONFIG_HPP_INCLUDED
#            include <srook/type_traits/detail/config.hpp>
#        endif

#        ifdef SROOK_HAS_SGI_TYPE_TRAITS
#            include <srook/type_traits/is_same.hpp>
#            ifdef __NetBSD__
#                include <algorithm>
#            else
#                include <type_traits.h>
#            endif
#            define SROOK_IS_POD(T) ::srook::is_same<typename ::__type_traits<T>::is_POD_type, ::__true_type>::value
#            define SROOK_HAS_TRIVIAL_CONSTRUCTOR(T) ::srook::is_same<typename ::__type_traits<T>::has_trivial_default_constructor, ::__true_type>::value
#            define SROOK_HAS_TRIVIAL_COPY(T) ::srook::is_same<typename ::__type_traits<T>::has_trivial_copy_constructor, ::__true_type>::value
#            define SROOK_HAS_TRIVIAL_ASSIGN(T) ::srook::is_same<typename ::__type_traits<T>::has_trivial_assignment_operator, ::__true_type>::value
#            define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) ::srook::is_same<typename ::__type_traits<T>::has_trivial_destructor, ::__true_type>::value

#            ifdef __sgi
#                define SROOK_HAS_TYPE_TRAITS_INTRINSICS
#            endif
#        endif

#        if defined(__MSL_CPP__) && (__MSL_CPP__ >= 0x8000)
#            include <msl_utility>
#            define SROOK_IS_UNION(T) SROOK_STD_EXTENSION_NAMESPACE::is_union<T>::value
#            define SROOK_IS_POD(T) SROOK_STD_EXTENSION_NAMESPACE::is_POD<T>::value
#            define SROOK_HAS_TRIVIAL_CONSTRUCTOR(T) SROOK_STD_EXTENSION_NAMESPACE::has_trivial_default_ctor<T>::value
#            define SROOK_HAS_TRIVIAL_COPY(T) SROOK_STD_EXTENSION_NAMESPACE::has_trivial_copy_ctor<T>::value
#            define SROOK_HAS_TRIVIAL_ASSIGN(T) SROOK_STD_EXTENSION_NAMESPACE::has_trivial_assignment<T>::value
#            define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) SROOK_STD_EXTENSION_NAMESPACE::has_trivial_dtor<T>::value
#            define SROOK_HAS_TYPE_TRAITS_INTRINSICS
#        endif

#        if (defined(SROOK_MSVC) && defined(SROOK_MSVC_FULL_VER) && (SROOK_MSVC_FULL_VER >= 140050215)) \
            || (defined(SROOK_INTEL) && defined(_MSC_VER) && (_MSC_VER >= 1500))
#            define SROOK_IS_UNION(T) __is_union(T)
#            define SROOK_IS_POD(T) (__is_pod(T) && __has_trivial_constructor(T))
#            define SROOK_IS_EMPTY(T) __is_empty(T)
#            define SROOK_HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)
#            define SROOK_HAS_TRIVIAL_ASSIGN(T) (__has_trivial_assign(T) || (::srook::is_pod<T>::value && !::srook::is_const<T>::value && !::srook::is_volatile<T>::value))
#            define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) (__has_trivial_destructor(T) || ::srook::is_pod<T>::value)
#            define SROOK_HAS_NOTHROW_CONSTRUCTOR(T) (__has_nothrow_constructor(T) || ::srook::has_trivial_constructor<T>::value)
#            if !defined(SROOK_INTEL)
#                define SROOK_HAS_NOTHROW_COPY(T) ((__has_nothrow_copy(T) || ::srook::has_trivial_copy<T>::value) && !is_array<T>::value)
#                define SROOK_HAS_TRIVIAL_COPY(T) (__has_trivial_copy(T) || ::srook::is_pod<T>::value)
#            elif (_MSC_VER >= 1900)
#                define SROOK_HAS_NOTHROW_COPY(T) ((__is_nothrow_constructible(T, typename add_lvalue_reference<typename add_const<T>::type>::type)) && !is_array<T>::value)
#                define SROOK_HAS_TRIVIAL_COPY(T) (__is_trivially_constructible(T, typename add_lvalue_reference<typename add_const<T>::type>::type))
#            endif
#            define SROOK_HAS_NOTHROW_ASSIGN(T) (__has_nothrow_assign(T) || ::srook::has_trivial_assign<T>::value)
#            define SROOK_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)

#            define SROOK_IS_ABSTRACT(T) __is_abstract(T)
#            define SROOK_IS_BASE_OF(T, U) (__is_base_of(T, U) && !is_same<T, U>::value)
#            define SROOK_IS_CLASS(T) __is_class(T)
#            define SROOK_IS_CONVERTIBLE(T, U) ((__is_convertible_to(T, U) || (is_same<T, U>::value && !is_function<U>::value)) && !__is_abstract(U))
#            define SROOK_IS_ENUM(T) __is_enum(T)

#            if defined(_MSC_VER) && (_MSC_VER >= 1700)
#                define SROOK_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) ((__has_trivial_move_constructor(T) || srook::is_pod<T>::value) && !::srook::is_volatile<T>::value && !::srook::is_reference<T>::value)
#                define SROOK_HAS_TRIVIAL_MOVE_ASSIGN(T) ((__has_trivial_move_assign(T) || srook::is_pod<T>::value) && !::srook::is_const<T>::value && !::srook::is_volatile<T>::value && !::srook::is_reference<T>::value)
#            endif
#            ifndef SROOK_NO_CXX11_FINAL
#                define SROOK_IS_POLYMORPHIC(T) __is_polymorphic(T)
#            endif
#            if _MSC_FULL_VER >= 180020827
#                define SROOK_IS_NOTHROW_MOVE_ASSIGN(T) (__is_nothrow_assignable(T&, T &&))
#                define SROOK_IS_NOTHROW_MOVE_CONSTRUCT(T) (__is_nothrow_constructible(T, T &&))
#            endif
#            define SROOK_HAS_TYPE_TRAITS_INTRINSICS
#        endif

#        if defined(__DMC__) && (__DMC__ >= 0x848)
#            define SROOK_IS_UNION(T) (__typeinfo(T) & 0x400)
#            define SROOK_IS_POD(T) (__typeinfo(T) & 0x800)
#            define SROOK_IS_EMPTY(T) (__typeinfo(T) & 0x1000)
#            define SROOK_HAS_TRIVIAL_CONSTRUCTOR(T) (__typeinfo(T) & 0x10)
#            define SROOK_HAS_TRIVIAL_COPY(T) (__typeinfo(T) & 0x20)
#            define SROOK_HAS_TRIVIAL_ASSIGN(T) (__typeinfo(T) & 0x40)
#            define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) (__typeinfo(T) & 0x8)
#            define SROOK_HAS_NOTHROW_CONSTRUCTOR(T) (__typeinfo(T) & 0x80)
#            define SROOK_HAS_NOTHROW_COPY(T) (__typeinfo(T) & 0x100)
#            define SROOK_HAS_NOTHROW_ASSIGN(T) (__typeinfo(T) & 0x200)
#            define SROOK_HAS_VIRTUAL_DESTRUCTOR(T) (__typeinfo(T) & 0x4)
#            define SROOK_HAS_TYPE_TRAITS_INTRINSICS
#        endif

#        if defined(SROOK_CLANG) && defined(__has_feature) && !defined(__CUDACC__)
#            include <cstddef>

#            if __has_feature(is_union)
#                define SROOK_IS_UNION(T) __is_union(T)
#            endif
#            if (!defined(__GLIBCXX__) || (__GLIBCXX__ >= 20080306 && __GLIBCXX__ != 20080519)) && __has_feature(is_pod)
#                define SROOK_IS_POD(T) __is_pod(T)
#            endif
#            if (!defined(__GLIBCXX__) || (__GLIBCXX__ >= 20080306 && __GLIBCXX__ != 20080519)) && __has_feature(is_empty)
#                define SROOK_IS_EMPTY(T) __is_empty(T)
#            endif
#            if __has_feature(has_trivial_constructor)
#                define SROOK_HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)
#            endif
#            if __has_feature(has_trivial_copy)
#                define SROOK_HAS_TRIVIAL_COPY(T) (__has_trivial_copy(T) && !is_reference<T>::value)
#            endif
#            if __has_feature(has_trivial_assign)
#                define SROOK_HAS_TRIVIAL_ASSIGN(T) (__has_trivial_assign(T) && !is_volatile<T>::value && is_assignable<T&, const T&>::value)
#            endif
#            if __has_feature(has_trivial_destructor)
#                define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) (__has_trivial_destructor(T) && is_destructible<T>::value)
#            endif
#            if __has_feature(has_nothrow_constructor)
#                define SROOK_HAS_NOTHROW_CONSTRUCTOR(T) (__has_nothrow_constructor(T) && is_default_constructible<T>::value)
#            endif
#            if __has_feature(has_nothrow_copy)
#                define SROOK_HAS_NOTHROW_COPY(T) (__has_nothrow_copy(T) && !is_volatile<T>::value && !is_reference<T>::value && is_copy_constructible<T>::value)
#            endif
#            if __has_feature(has_nothrow_assign)
#                define SROOK_HAS_NOTHROW_ASSIGN(T) (__has_nothrow_assign(T) && !is_volatile<T>::value && is_assignable<T&, const T&>::value)
#            endif
#            if __has_feature(has_virtual_destructor)
#                define SROOK_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)
#            endif
#            if __has_feature(is_abstract)
#                define SROOK_IS_ABSTRACT(T) __is_abstract(T)
#            endif
#            if __has_feature(is_base_of)
#                define SROOK_IS_BASE_OF(T, U) (__is_base_of(T, U) && !is_same<T, U>::value)
#            endif
#            if __has_feature(is_class)
#                define SROOK_IS_CLASS(T) __is_class(T)
#            endif
#            if __has_feature(is_convertible_to)
#                define SROOK_IS_CONVERTIBLE(T, U) __is_convertible_to(T, U)
#            endif
#            if __has_feature(is_enum)
#                define SROOK_IS_ENUM(T) __is_enum(T)
#            endif
#            if __has_feature(is_polymorphic)
#                define SROOK_IS_POLYMORPHIC(T) __is_polymorphic(T)
#            endif
#            if __has_feature(has_trivial_move_constructor)
#                define SROOK_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) (__has_trivial_move_constructor(T) && is_constructible<T, T&&>::value && !::srook::is_volatile<T>::value)
#            endif
#            if __has_feature(has_trivial_move_assign)
#                define SROOK_HAS_TRIVIAL_MOVE_ASSIGN(T) (__has_trivial_move_assign(T) && is_assignable<T&, T&&>::value && !::srook::is_volatile<T>::value)
#            endif
#            if (!defined(unix) && !defined(__unix__)) || defined(__LP64__) || !defined(__GNUC__)
#                define SROOK_ALIGNMENT_OF(T) __alignof(T)
#            endif
#            if __has_feature(is_final)
#                define SROOK_IS_FINAL(T) __is_final(T)
#            endif

#            define SROOK_HAS_TYPE_TRAITS_INTRINSICS
#        endif

#        if defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3) && !defined(__GCCXML__))) && !defined(SROOK_CLANG)

#            ifdef SROOK_INTEL
#                define SROOK_INTEL_TT_OPTS || is_pod<T>::value
#            else
#                define SROOK_INTEL_TT_OPTS
#            endif

#            define SROOK_IS_UNION(T) __is_union(T)
#            define SROOK_IS_POD(T) __is_pod(T)
#            define SROOK_IS_EMPTY(T) __is_empty(T)
#            define SROOK_HAS_TRIVIAL_CONSTRUCTOR(T) ((__has_trivial_constructor(T) SROOK_INTEL_TT_OPTS) && !::srook::is_volatile<T>::value)
#            define SROOK_HAS_TRIVIAL_COPY(T) ((__has_trivial_copy(T) SROOK_INTEL_TT_OPTS) && !is_reference<T>::value)
#            if (__GNUC__ * 100 + __GNUC_MINOR__) >= 409
#                define SROOK_HAS_TRIVIAL_ASSIGN(T) ((__has_trivial_assign(T) SROOK_INTEL_TT_OPTS) && !::srook::is_volatile<T>::value && !::srook::is_const<T>::value && is_assignable<T&, const T&>::value)
#                define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) (__has_trivial_destructor(T) SROOK_INTEL_TT_OPTS && is_destructible<T>::value)
#                define SROOK_HAS_NOTHROW_CONSTRUCTOR(T) (__has_nothrow_constructor(T) && is_default_constructible<T>::value SROOK_INTEL_TT_OPTS)
#                define SROOK_HAS_NOTHROW_COPY(T) ((__has_nothrow_copy(T) SROOK_INTEL_TT_OPTS) && !is_volatile<T>::value && !is_reference<T>::value && is_copy_constructible<T>::value)
#                define SROOK_HAS_NOTHROW_ASSIGN(T) ((__has_nothrow_assign(T) SROOK_INTEL_TT_OPTS) && !is_volatile<T>::value && !is_const<T>::value && is_assignable<T&, const T&>::value)
#            else
#                define SROOK_HAS_TRIVIAL_ASSIGN(T) ((__has_trivial_assign(T) SROOK_INTEL_TT_OPTS) && !::srook::is_volatile<T>::value && !::srook::is_const<T>::value)
#                define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) (__has_trivial_destructor(T) SROOK_INTEL_TT_OPTS)
#                define SROOK_HAS_NOTHROW_CONSTRUCTOR(T) (__has_nothrow_constructor(T) SROOK_INTEL_TT_OPTS)
#                define SROOK_HAS_NOTHROW_COPY(T) ((__has_nothrow_copy(T) SROOK_INTEL_TT_OPTS) && !is_volatile<T>::value && !is_reference<T>::value && !is_array<T>::value)
#                define SROOK_HAS_NOTHROW_ASSIGN(T) ((__has_nothrow_assign(T) SROOK_INTEL_TT_OPTS) && !is_volatile<T>::value && !is_const<T>::value && !is_array<T>::value)
#            endif
#            define SROOK_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)

#            define SROOK_IS_ABSTRACT(T) __is_abstract(T)
#            define SROOK_IS_BASE_OF(T, U) (__is_base_of(T, U) && !is_same<T, U>::value)
#            define SROOK_IS_CLASS(T) __is_class(T)
#            define SROOK_IS_ENUM(T) __is_enum(T)
#            define SROOK_IS_POLYMORPHIC(T) __is_polymorphic(T)
#            if (!defined(unix) && !defined(__unix__)) || defined(__LP64__)
#                define SROOK_ALIGNMENT_OF(T) __alignof__(T)
#            endif
#            if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7))
#                define SROOK_IS_FINAL(T) __is_final(T)
#            endif

#            if (__GNUC__ >= 5) && (__cplusplus >= 201103)
#                define SROOK_HAS_TRIVIAL_MOVE_ASSIGN(T) (__is_trivially_assignable(T&, T &&) && is_assignable<T&, T&&>::value && !::srook::is_volatile<T>::value)
#                define SROOK_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) (__is_trivially_constructible(T, T &&) && is_constructible<T, T&&>::value && !::srook::is_volatile<T>::value)
#            endif

#            define SROOK_HAS_TYPE_TRAITS_INTRINSICS
#        endif

#        if defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x5130)
#            define SROOK_IS_UNION(T) __oracle_is_union(T)
#            define SROOK_IS_POD(T) (__oracle_is_pod(T) && !is_function<T>::value)
#            define SROOK_IS_EMPTY(T) __oracle_is_empty(T)
#            define SROOK_HAS_TRIVIAL_CONSTRUCTOR(T) (__oracle_has_trivial_constructor(T) && !::srook::is_volatile<T>::value)
#            define SROOK_HAS_TRIVIAL_COPY(T) (__oracle_has_trivial_copy(T) && !is_reference<T>::value)
#            define SROOK_HAS_TRIVIAL_ASSIGN(T) ((__oracle_has_trivial_assign(T) || __oracle_is_trivial(T)) && !::srook::is_volatile<T>::value && !::srook::is_const<T>::value && is_assignable<T&, const T&>::value)
#            define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) (__oracle_has_trivial_destructor(T) && is_destructible<T>::value)
#            define SROOK_HAS_NOTHROW_CONSTRUCTOR(T) ((__oracle_has_nothrow_constructor(T) || __oracle_has_trivial_constructor(T) || __oracle_is_trivial(T)) && is_default_constructible<T>::value)
#            define SROOK_HAS_NOTHROW_ASSIGN(T) ((__oracle_has_nothrow_assign(T) || __oracle_has_trivial_assign(T) || __oracle_is_trivial(T)) && !is_volatile<T>::value && !is_const<T>::value && is_assignable<T&, const T&>::value)
#            define SROOK_HAS_VIRTUAL_DESTRUCTOR(T) __oracle_has_virtual_destructor(T)

#            define SROOK_IS_ABSTRACT(T) __oracle_is_abstract(T)
#            define SROOK_IS_CLASS(T) __oracle_is_class(T)
#            define SROOK_IS_ENUM(T) __oracle_is_enum(T)
#            define SROOK_IS_POLYMORPHIC(T) __oracle_is_polymorphic(T)
#            define SROOK_ALIGNMENT_OF(T) __alignof__(T)
#            define SROOK_IS_FINAL(T) __oracle_is_final(T)

#            define SROOK_HAS_TYPE_TRAITS_INTRINSICS
#        endif

#        if defined(__ghs__) && (__GHS_VERSION_NUMBER >= 600)
#            include <srook/type_traits/is_reference.hpp>
#            include <srook/type_traits/is_same.hpp>
#            include <srook/type_traits/is_volatile.hpp>

#            define SROOK_IS_UNION(T) __is_union(T)
#            define SROOK_IS_POD(T) __is_pod(T)
#            define SROOK_IS_EMPTY(T) __is_empty(T)
#            define SROOK_HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)
#            define SROOK_HAS_TRIVIAL_COPY(T) (__has_trivial_copy(T) && !is_reference<T>::value)
#            define SROOK_HAS_TRIVIAL_ASSIGN(T) (__has_trivial_assign(T) && !is_volatile<T>::value)
#            define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#            define SROOK_HAS_NOTHROW_CONSTRUCTOR(T) __has_nothrow_constructor(T)
#            define SROOK_HAS_NOTHROW_COPY(T) (__has_nothrow_copy(T) && !is_volatile<T>::value && !is_reference<T>::value)
#            define SROOK_HAS_NOTHROW_ASSIGN(T) (__has_nothrow_assign(T) && !is_volatile<T>::value)
#            define SROOK_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)

#            define SROOK_IS_ABSTRACT(T) __is_abstract(T)
#            define SROOK_IS_BASE_OF(T, U) (__is_base_of(T, U) && !is_same<T, U>::value)
#            define SROOK_IS_CLASS(T) __is_class(T)
#            define SROOK_IS_ENUM(T) __is_enum(T)
#            define SROOK_IS_POLYMORPHIC(T) __is_polymorphic(T)
#            define SROOK_ALIGNMENT_OF(T) __alignof__(T)
#            define SROOK_HAS_TYPE_TRAITS_INTRINSICS
#        endif

#        if defined(__CODEGEARC__)
#            include <srook/type_traits/is_reference.hpp>
#            include <srook/type_traits/is_same.hpp>
#            include <srook/type_traits/is_void.hpp>
#            include <srook/type_traits/is_volatile.hpp>

#            define SROOK_IS_UNION(T) __is_union(T)
#            define SROOK_IS_POD(T) __is_pod(T)
#            define SROOK_IS_EMPTY(T) __is_empty(T)
#            define SROOK_HAS_TRIVIAL_CONSTRUCTOR(T) (__has_trivial_default_constructor(T))
#            define SROOK_HAS_TRIVIAL_COPY(T) (__has_trivial_copy_constructor(T) && !is_reference<T>::value)
#            define SROOK_HAS_TRIVIAL_ASSIGN(T) (__has_trivial_assign(T) && !is_volatile<T>::value)
#            define SROOK_HAS_TRIVIAL_DESTRUCTOR(T) (__has_trivial_destructor(T))
#            define SROOK_HAS_NOTHROW_CONSTRUCTOR(T) (__has_nothrow_default_constructor(T))
#            define SROOK_HAS_NOTHROW_COPY(T) (__has_nothrow_copy_constructor(T) && !is_volatile<T>::value && !is_reference<T>::value)
#            define SROOK_HAS_NOTHROW_ASSIGN(T) (__has_nothrow_assign(T) && !is_volatile<T>::value)
#            define SROOK_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)

#            define SROOK_IS_ABSTRACT(T) __is_abstract(T)
#            define SROOK_IS_BASE_OF(T, U) (__is_base_of(T, U) && !is_void<T>::value && !is_void<U>::value)
#            define SROOK_IS_CLASS(T) __is_class(T)
#            define SROOK_IS_CONVERTIBLE(T, U) (__is_convertible(T, U) || is_void<U>::value)
#            define SROOK_IS_ENUM(T) __is_enum(T)
#            define SROOK_IS_POLYMORPHIC(T) __is_polymorphic(T)
#            define SROOK_ALIGNMENT_OF(T) alignof(T)

#            define SROOK_HAS_TYPE_TRAITS_INTRINSICS
#        endif
#    endif
#endif // SROOK_TT_DISABLE_INTRINSICS
#endif // SROOK_TT_INTRINSICS_HPP_INCLUDED
