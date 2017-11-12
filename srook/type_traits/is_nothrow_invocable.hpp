// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <functional>
#    include <srook/config/feature.hpp>
#    include <srook/type_traits/bool_constant.hpp>
#    include <srook/type_traits/conditional.hpp>
#    include <srook/type_traits/decay.hpp>
#    include <srook/type_traits/detail/logical.hpp>
#    include <srook/type_traits/enable_if.hpp>
#    include <srook/type_traits/is_base_of.hpp>
#    include <srook/type_traits/is_invocable.hpp>
#    include <srook/type_traits/is_member_function_pointer.hpp>
#    include <srook/type_traits/is_member_object_pointer.hpp>
#    include <srook/type_traits/is_same.hpp>
#    include <srook/utility/declval.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

struct invoke_memfn_ref {};
struct invoke_memfn_deref {};
struct invoke_memobj_ref {};
struct invoke_memobj_deref {};
struct invoke_other {};
struct failure_type {};

template <class T, class Tag>
struct result_of_success : enable_if<true, T> {
    typedef Tag invoke_type;
};

struct result_of_memfun_ref_impl {
    template <class F, class T, class... Ts>
    static result_of_success<SROOK_DECLTYPE((declval<T>().*declval<F>())(declval<Ts>()...)), invoke_memfn_ref>
    test(int);

    template <class...>
    static failure_type test(...);
};

template <class Memptr, class Arg, class... Args>
struct result_of_memfun_ref : private result_of_memfun_ref_impl {
    typedef SROOK_DECLTYPE((test<Memptr, Arg, Args...>(0))) type;
};

struct result_of_memfun_deref_impl {
    template <class F, class T, class... Ts>
    static result_of_success<SROOK_DECLTYPE(((*declval<T>()).*declval<F>())(declval<Ts>()...)), invoke_memfn_deref>
    test(int);

    template <class...>
    static failure_type test(...);
};

template <class Memptr, class Arg, class... Args>
struct result_of_memfun_deref : private result_of_memfun_deref_impl {
    typedef SROOK_DECLTYPE((test<Memptr, Arg, Args...>(0))) type;
};

struct result_of_memobj_ref_impl {
    template <class F, class T>
    static result_of_success<SROOK_DECLTYPE(declval<T>().*declval<F>()), invoke_memobj_ref>
    test(int);

    template <class, class>
    static failure_type test(...);
};

template <class Memptr, class Arg>
struct result_of_memobj_ref : private result_of_memobj_ref_impl {
    typedef SROOK_DECLTYPE((test<Memptr, Arg>(0))) type;
};

struct result_of_memobj_deref_impl {
    template <class F, class T>
    static result_of_success<SROOK_DECLTYPE((*declval<T>()).*declval<F>()), invoke_memobj_deref>
    test(int);

    template <class, class>
    static failure_type test(...);
};

template <class Memptr, class Arg>
struct result_of_memobj_deref : private result_of_memobj_deref_impl {
    typedef SROOK_DECLTYPE((test<Memptr, Arg>(0))) type;
};

template <class Memptr, class Arg>
struct result_of_memobj;

template <class Res, class Class, class Arg>
struct result_of_memobj<Res Class::*, Arg> {
    typedef SROOK_DEDUCED_TYPENAME remove_cv<SROOK_DEDUCED_TYPENAME remove_reference<Arg>::type>::type Argval;
    typedef Res Class::*Memptr;
    typedef SROOK_DEDUCED_TYPENAME conditional<
        Lor<is_same<Argval, Class>, is_base_of<Class, Argval> >::value,
        result_of_memobj_ref<Memptr, Arg>,
        result_of_memobj_deref<Memptr, Arg> >::type::type type;
};

template <class Memptr, class Arg, class... Args>
struct result_of_memfun;

template <class Res, class Class, class Arg, class... Args>
struct result_of_memfun<Res Class::*, Arg, Args...> {
    typedef SROOK_DEDUCED_TYPENAME remove_cv<SROOK_DEDUCED_TYPENAME remove_reference<Arg>::type>::type Argval;
    typedef Res Class::*Memptr;
    typedef SROOK_DEDUCED_TYPENAME conditional<
        Lor<is_same<Argval, Class>, is_base_of<Class, Argval> >::value,
        result_of_memfun_ref<Memptr, Arg, Args...>,
        result_of_memfun_deref<Memptr, Arg, Args...> >::type::type type;
};

template <class T, class U = SROOK_DEDUCED_TYPENAME decay<T>::type>
struct inv_unwrap {
    typedef T type;
};
template <class T, class U>
struct inv_unwrap<T, std::reference_wrapper<U> > {
    typedef T& type;
};

template <bool, bool, class F, class... Args>
struct result_of_impl {
    typedef failure_type type;
};

template <class Memptr, class Arg>
struct result_of_impl<true, false, Memptr, Arg>
    : public result_of_memobj<SROOK_DEDUCED_TYPENAME decay<Memptr>::type, SROOK_DEDUCED_TYPENAME inv_unwrap<Arg>::type> {
};

template <class Memptr, class Arg, class... Args>
struct result_of_impl<false, true, Memptr, Arg, Args...>
    : public result_of_memfun<SROOK_DEDUCED_TYPENAME decay<Memptr>::type, SROOK_DEDUCED_TYPENAME inv_unwrap<Arg>::type, Args...> {
};

struct result_of_other_impl {
    template <class F, class... Args>
    static result_of_success<SROOK_DECLTYPE(declval<F>()(declval<Args>()...)), invoke_other>
    test(int);

    template <class...>
    static failure_type test(...);
};

template <class F, class... Args>
struct result_of_impl<false, false, F, Args...> : private result_of_other_impl {
    typedef SROOK_DECLTYPE((test<F, Args...>(0))) type;
};

template <class F, class... Args>
struct invoke_resulter
    : public result_of_impl<
          is_member_object_pointer<SROOK_DEDUCED_TYPENAME remove_reference<F>::type>::value,
          is_member_function_pointer<SROOK_DEDUCED_TYPENAME remove_reference<F>::type>::value,
          F, Args...>::type {};

template <class F, class T, class... Args>
SROOK_CONSTEXPR bool call_is_nt(invoke_memfn_ref)
{
    typedef SROOK_DEDUCED_TYPENAME inv_unwrap<T>::type U;
    return noexcept((declval<U>().*declval<F>())(declval<Args>()...));
}

template <class F, class T, class... Args>
SROOK_CONSTEXPR bool call_is_nt(invoke_memfn_deref)
{
    return noexcept(((*declval<T>()).*declval<F>())(declval<Args>()...));
}

template <class F, class T>
SROOK_CONSTEXPR bool call_is_nt(invoke_memobj_ref)
{
    typedef SROOK_DEDUCED_TYPENAME inv_unwrap<T>::type U;
    return noexcept(declval<U>().*declval<F>());
}

template <class F, class T>
SROOK_CONSTEXPR bool call_is_nt(invoke_memobj_deref)
{
    return noexcept((*declval<T>()).*declval<F>());
}

template <class F, class... Args>
SROOK_CONSTEXPR bool call_is_nt(invoke_other)
{
    return noexcept(declval<F>()(declval<Args>()...));
}

template <class Result, class F, class... Args>
struct call_is_nothrow_impl
    : public bool_constant<call_is_nt<F, Args...>(SROOK_DEDUCED_TYPENAME Result::invoke_type{})> {};

template <class F, class... Args>
struct call_is_nothrow : call_is_nothrow_impl<invoke_resulter<F, Args...>, F, Args...> {};

} // namespace detail

template <class F, class... Args>
struct is_nothrow_invocable
    : detail::Land<is_invocable<F, Args...>, detail::call_is_nothrow<F, Args...> >::type {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::is_nothrow_invocable;

#    if SROOK_CPP_VARIABLE_TEMPLATES
template <class F, class... Args>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_nothrow_invocable_v = is_nothrow_invocable<F, Args...>::value;
#    endif

} // namespace srook

#    endif
#endif
