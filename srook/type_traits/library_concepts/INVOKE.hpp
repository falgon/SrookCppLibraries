#ifndef INCLUDED_SROOK_TYPE_TRAITS_CONCEPT_CXX17_INVOKE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_CONCEPT_CXX17_INVOKE_HPP

#include <functional>
#include <utility>
#include <srook/type_traits/true_false_type.hpp>

namespace srook{
namespace library_concepts{

namespace detail{

template<class T> struct is_reference_wrapper : SROOK_FALSE_TYPE {};
template<class T> struct is_reference_wrapper<std::reference_wrapper<T>> : SROOK_TRUE_TYPE {};

} // namespace detail

template <class Base, class T, class Derived, class... Args>
auto INVOKE(T Base::*pmf, Derived&& ref, Args&&... args)
-> typename std::enable_if<
	std::is_function<T>::value && std::is_base_of<Base, typename std::decay<Derived>::type>::value,
	decltype((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...))
>::type;

template <class Base, class T, class RefWrap, class... Args>
auto INVOKE(T Base::*pmf, RefWrap&& ref, Args&&... args)
-> typename std::enable_if<
	std::is_function<T>::value && detail::is_reference_wrapper<typename std::decay<RefWrap>::type>::value,
	decltype((ref.get().*pmf)(std::forward<Args>(args)...))
>::type;

template <class Base, class T, class Pointer, class... Args>
auto INVOKE(T Base::*pmf, Pointer&& ptr, Args&&... args)
-> typename std::enable_if<
	std::is_function<T>::value && !detail::is_reference_wrapper<typename std::decay<Pointer>::type>::value && !std::is_base_of<Base, typename std::decay<Pointer>::type>::value,
	decltype(((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...))
>::type;

template <class Base, class T, class Derived>
auto INVOKE(T Base::*pmd, Derived&& ref)
-> typename std::enable_if<
	!std::is_function<T>::value && std::is_base_of<Base, typename std::decay<Derived>::type>::value,
	decltype(std::forward<Derived>(ref).*pmd)
>::type;

template <class Base, class T, class RefWrap>
auto INVOKE(T Base::*pmd, RefWrap&& ref)
-> typename std::enable_if<
	!std::is_function<T>::value && detail::is_reference_wrapper<typename std::decay<RefWrap>::type>::value,
	decltype(ref.get().*pmd)
>::type;

template <class Base, class T, class Pointer>
auto INVOKE(T Base::*pmd, Pointer&& ptr)
-> typename std::enable_if<
	!std::is_function<T>::value && !detail::is_reference_wrapper<typename std::decay<Pointer>::type>::value && !std::is_base_of<Base, typename std::decay<Pointer>::type>::value,
	decltype((*std::forward<Pointer>(ptr)).*pmd)
>::type;

template <class F, class... Args>
auto INVOKE(F&& f, Args&&... args)
-> typename std::enable_if<
	!std::is_member_pointer<typename std::decay<F>::type>::value,
	decltype(std::forward<F>(f)(std::forward<Args>(args)...))
>::type;

} // library_concept
} // namespace srook

#endif
