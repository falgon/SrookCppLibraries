// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_PROXY_NONCOPYABLE_HPP
#define INCLUDED_SROOK_PROXY_NONCOPYABLE_HPP

#include <srook/proxy/noncopyable.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/type_traits/enable_if.hpp>
#include <srook/type_traits/decay.hpp>
#include <srook/type_traits/detail/has_type_gen.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <srook/memory/pointer_traits.hpp>

namespace srook {
namespace proxy {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

SROOK_TT_DEF_HAS_TYPE_IMPL(value_type);
SROOK_TT_DEF_HAS_TYPE_IMPL(reference);
SROOK_TT_DEF_HAS_TYPE_IMPL(pointer);
SROOK_TT_DEF_HAS_TYPE_IMPL(const_reference);
SROOK_TT_DEF_HAS_TYPE_IMPL(const_pointer);
SROOK_TT_DEF_HAS_TYPE_IMPL(iterator);
SROOK_TT_DEF_HAS_TYPE_IMPL(const_iterator);
SROOK_TT_DEF_HAS_TYPE_IMPL(size_type);
SROOK_TT_DEF_HAS_TYPE_IMPL(difference_type);
SROOK_TT_DEF_HAS_TYPE(value_type);
SROOK_TT_DEF_HAS_TYPE(reference);
SROOK_TT_DEF_HAS_TYPE(pointer);
SROOK_TT_DEF_HAS_TYPE(const_reference);
SROOK_TT_DEF_HAS_TYPE(const_pointer);
SROOK_TT_DEF_HAS_TYPE(iterator);
SROOK_TT_DEF_HAS_TYPE(const_iterator);
SROOK_TT_DEF_HAS_TYPE(size_type);
SROOK_TT_DEF_HAS_TYPE(difference_type);

#define SROOK_DEF_ENABLE_IF_ELSE(TRUE_T)\
    template <class, class F, bool> struct enable_if_else_##TRUE_T : public type_constant<F> {};\
    template <class T, class F> struct enable_if_else_##TRUE_T<T, F, true> : public type_constant<SROOK_DEDUCED_TYPENAME T::TRUE_T> {}

SROOK_DEF_ENABLE_IF_ELSE(value_type);
SROOK_DEF_ENABLE_IF_ELSE(reference);
SROOK_DEF_ENABLE_IF_ELSE(pointer);
SROOK_DEF_ENABLE_IF_ELSE(const_reference);
SROOK_DEF_ENABLE_IF_ELSE(const_pointer);
SROOK_DEF_ENABLE_IF_ELSE(iterator);
SROOK_DEF_ENABLE_IF_ELSE(const_iterator);
SROOK_DEF_ENABLE_IF_ELSE(size_type);
SROOK_DEF_ENABLE_IF_ELSE(difference_type);

#undef SROOK_DEF_ENABLE_IF_ELSE

#define SROOK_DEF_ENABLE_IF_ELSE_BIND(TRUE_T)\
    template <class Wrapped, class F>\
    struct enable_ie_bind_##TRUE_T : public enable_if_else_##TRUE_T<Wrapped, F, has_##TRUE_T<Wrapped>::value> {}

SROOK_DEF_ENABLE_IF_ELSE_BIND(value_type);
SROOK_DEF_ENABLE_IF_ELSE_BIND(reference);
SROOK_DEF_ENABLE_IF_ELSE_BIND(pointer);
SROOK_DEF_ENABLE_IF_ELSE_BIND(const_reference);
SROOK_DEF_ENABLE_IF_ELSE_BIND(const_pointer);
SROOK_DEF_ENABLE_IF_ELSE_BIND(iterator);
SROOK_DEF_ENABLE_IF_ELSE_BIND(const_iterator);
SROOK_DEF_ENABLE_IF_ELSE_BIND(size_type);
SROOK_DEF_ENABLE_IF_ELSE_BIND(difference_type);

#undef SROOK_DEF_ENABLE_IF_ELSE_BIND

} // namespace detail

template <class T>
class noncopyable : private srook::utility::noncopyable<T>, public T {
public:
    typedef T wrapped_type;
    typedef SROOK_DEDUCED_TYPENAME 
        srook::proxy::detail::enable_ie_bind_value_type<wrapped_type, wrapped_type>::type 
        value_type;
    typedef SROOK_DEDUCED_TYPENAME 
        srook::proxy::detail::enable_ie_bind_reference<wrapped_type, SROOK_DEDUCED_TYPENAME add_lvalue_reference<wrapped_type>::type>::type 
        reference;
    typedef SROOK_DEDUCED_TYPENAME 
        srook::proxy::detail::enable_ie_bind_pointer<wrapped_type, SROOK_DEDUCED_TYPENAME pointer_traits<SROOK_DEDUCED_TYPENAME add_pointer<wrapped_type>::type>::pointer>::type 
        pointer;
    typedef SROOK_DEDUCED_TYPENAME 
        srook::proxy::detail::enable_ie_bind_const_reference<wrapped_type, const value_type&>::type 
        const_reference;
    typedef SROOK_DEDUCED_TYPENAME 
        srook::proxy::detail::enable_ie_bind_const_pointer<wrapped_type, const value_type*>::type 
        const_pointer;
    typedef SROOK_DEDUCED_TYPENAME
        srook::proxy::detail::enable_ie_bind_iterator<wrapped_type, pointer>::type
        iterator;
    typedef SROOK_DEDUCED_TYPENAME
        srook::proxy::detail::enable_ie_bind_const_iterator<wrapped_type, const_pointer>::type
        const_iterator;
    typedef SROOK_DEDUCED_TYPENAME
        srook::proxy::detail::enable_ie_bind_size_type<wrapped_type, std::size_t>::type
        size_type;
    typedef SROOK_DEDUCED_TYPENAME
        srook::proxy::detail::enable_ie_bind_difference_type<wrapped_type, std::ptrdiff_t>::type
        difference_type;

    using T::T;
    
    explicit SROOK_FORCE_INLINE SROOK_CONSTEXPR noncopyable(const T& val) SROOK_NOEXCEPT((is_nothrow_constructible<T, T&>::value))
        : T(val) {}
    
    template <class... Ts, SROOK_REQUIRES(is_constructible<T, Ts&&...>::value)>
    explicit SROOK_FORCE_INLINE SROOK_CONSTEXPR noncopyable(Ts&&... ts) SROOK_NOEXCEPT((is_nothrow_constructible<T, Ts&&...>::value))
        : T(srook::forward<Ts>(ts)...) {}
};

template <class T>
class noncopyable<std::reference_wrapper<T>> : private srook::utility::noncopyable<T>, public T {
public:
    typedef std::reference_wrapper<T> wrapped_type;
    typedef T value_type;
    typedef SROOK_DEDUCED_TYPENAME 
        srook::proxy::detail::enable_ie_bind_reference<value_type, SROOK_DEDUCED_TYPENAME add_lvalue_reference<value_type>::type>::type 
        reference;
    typedef SROOK_DEDUCED_TYPENAME 
        srook::proxy::detail::enable_ie_bind_pointer<value_type, SROOK_DEDUCED_TYPENAME pointer_traits<value_type*>::pointer>::type 
        pointer;
    typedef SROOK_DEDUCED_TYPENAME 
        srook::proxy::detail::enable_ie_bind_const_reference<value_type, const value_type&>::type 
        const_reference; 
    typedef SROOK_DEDUCED_TYPENAME 
        srook::proxy::detail::enable_ie_bind_const_pointer<value_type, const value_type*>::type 
        const_pointer;
    typedef SROOK_DEDUCED_TYPENAME
        srook::proxy::detail::enable_ie_bind_iterator<value_type, pointer>::type
        iterator;
    typedef SROOK_DEDUCED_TYPENAME
        srook::proxy::detail::enable_ie_bind_const_iterator<value_type, const_pointer>::type
        const_iterator;
    typedef SROOK_DEDUCED_TYPENAME
        srook::proxy::detail::enable_ie_bind_size_type<value_type, std::size_t>::type
        size_type;
    typedef SROOK_DEDUCED_TYPENAME
        srook::proxy::detail::enable_ie_bind_difference_type<value_type, std::ptrdiff_t>::type
        difference_type;

    using T::T;

    explicit SROOK_FORCE_INLINE SROOK_CONSTEXPR noncopyable(std::reference_wrapper<T> val) SROOK_NOEXCEPT((is_nothrow_constructible<T, T&>::value))
        : T(val.get()) {}
};

#if SROOK_CPP_DEDUCTION_GUIDES
template <class T>
explicit noncopyable(T&) -> noncopyable<T>;
#endif

template <class T>
SROOK_FORCE_INLINE SROOK_CONSTEXPR noncopyable<SROOK_DEDUCED_TYPENAME decay<T>::type> 
make_noncopyable(T&& v) SROOK_NOEXCEPT((is_nothrow_constructible<T, T&&>::value))
{
    return noncopyable<SROOK_DEDUCED_TYPENAME decay<T>::type>(srook::forward<T>(v));
}

SROOK_INLINE_NAMESPACE_END
} // namespace proxy
} // namespace srook

#endif
#endif
