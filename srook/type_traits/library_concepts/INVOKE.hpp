// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_CONCEPT_CXX17_INVOKE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_CONCEPT_CXX17_INVOKE_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <functional>
#include <utility>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/is_base_of.hpp>
#include <srook/type_traits/is_function.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/utility/forward.hpp>
#include <type_traits>

namespace srook{
namespace type_traits {
namespace library_concepts{
namespace detail{

template<class> struct is_reference_wrapper : SROOK_FALSE_TYPE {};
template<class T> struct is_reference_wrapper<std::reference_wrapper<T>> : SROOK_TRUE_TYPE {};

} // namespace detail

template <class Base, class T, class Derived, class... Args>
auto INVOKE(T Base::*pmf, Derived&& ref, Args&&... args)
-> typename enable_if<
	is_function<T>::value && is_base_of<Base, typename decay<Derived>::type>::value,
	decltype((srook::forward<Derived>(ref).*pmf)(srook::forward<Args>(args)...))
>::type;

template <class Base, class T, class RefWrap, class... Args>
auto INVOKE(T Base::*pmf, RefWrap&& ref, Args&&... args)
-> typename enable_if<
	is_function<T>::value && detail::is_reference_wrapper<typename decay<RefWrap>::type>::value,
	decltype((ref.get().*pmf)(srook::forward<Args>(args)...))
>::type;

template <class Base, class T, class Pointer, class... Args>
auto INVOKE(T Base::*pmf, Pointer&& ptr, Args&&... args)
-> typename enable_if<
	is_function<T>::value && !detail::is_reference_wrapper<typename decay<Pointer>::type>::value && !is_base_of<Base, typename decay<Pointer>::type>::value,
	decltype(((*srook::forward<Pointer>(ptr)).*pmf)(srook::forward<Args>(args)...))
>::type;

template <class Base, class T, class Derived>
auto INVOKE(T Base::*pmd, Derived&& ref)
-> typename enable_if<
	!is_function<T>::value && is_base_of<Base, typename decay<Derived>::type>::value,
	decltype(srook::forward<Derived>(ref).*pmd)
>::type;

template <class Base, class T, class RefWrap>
auto INVOKE(T Base::*pmd, RefWrap&& ref)
-> typename enable_if<
	!is_function<T>::value && detail::is_reference_wrapper<typename decay<RefWrap>::type>::value,
	decltype(ref.get().*pmd)
>::type;

template <class Base, class T, class Pointer>
auto INVOKE(T Base::*pmd, Pointer&& ptr)
-> typename enable_if<
	!is_function<T>::value && !detail::is_reference_wrapper<typename decay<Pointer>::type>::value && !is_base_of<Base, typename decay<Pointer>::type>::value,
	decltype((*srook::forward<Pointer>(ptr)).*pmd)
>::type;

template <class F, class... Args>
auto INVOKE(F&& f, Args&&... args)
-> typename enable_if<
	!std::is_member_pointer<typename decay<F>::type>::value,
	decltype(srook::forward<F>(f)(srook::forward<Args>(args)...))
>::type;

template <class F, class... Args>
auto INVOKE(F&& f, Args&&... args)
-> typename enable_if<
    !std::is_member_pointer<typename decay<F>::type>::value,
    decltype(srook::forward<F>(f)()(srook::forward<Args>(args)...))
>::type;

} // namespace library_concept
} // namespace type_traits
} // namespace srook

#endif
#endif
