// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_MEMORY_POINTER_TRAITS_HPP
#define INCLUDED_MEMORY_POINTER_TRAITS_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/config/attribute/force_inline.hpp>
#include <srook/config/feature.hpp>
#include <srook/memory/addressof.hpp>
#include <srook/memory/to_address.hpp>
#include <srook/tmpl/vt/first.hpp>
#include <srook/type_traits.hpp>

namespace srook {
namespace memory {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

struct invalid {};

template <class T>
struct get_first_arg : disable_special_functions<get_first_arg<T>>, type_constant<invalid> {};
template <template <class...> class Template, class... Ts>
struct get_first_arg<Template<Ts...>> : disable_special_functions<get_first_arg<Template<Ts...>>>, srook::tmpl::vt::first<Ts...> {};
template <class T> using get_first_arg_t = SROOK_DEDUCED_TYPENAME get_first_arg<T>::type;

template <class T, class U>
struct replace_first_arg : disable_special_functions<replace_first_arg<T, U>> {};
template <template <class, class> class Template, class U, class T, class... Ts>
struct replace_first_arg<Template<T, Ts...>, U> 
    : disable_special_functions<replace_first_arg<Template<T, Ts...>, U>>, type_constant<Template<U, Ts...>> {};
template <class T, class U> using replace_first_arg_t = SROOK_DEDUCED_TYPENAME replace_first_arg<T, U>::type;

template <class T>
struct make_not_void : bool_constant<type_traits::detail::Lnot<is_void<T>>::value> {};

} // namespace detail

template <class Ptr>
struct pointer_traits {
private:
    template <class T>
    using element_t = SROOK_DEDUCED_TYPENAME T::element_type;
    template <class T>
    using difference_t = SROOK_DEDUCED_TYPENAME T::difference_type;
    template <class T, class U, class = void_t<>>
    struct rebinder : detail::replace_first_arg<T, U> {};
    template <class T, class U>
    struct rebinder<T, U, void_t<SROOK_DEDUCED_TYPENAME T::template rebind<U>>> 
        : type_constant<SROOK_DEDUCED_TYPENAME T::template rebind<U>> {};
public:
    typedef Ptr pointer;
    typedef type_traits::detail::detector_or_t<detail::get_first_arg_t<Ptr>, element_t, Ptr> element_type;
    typedef type_traits::detail::detector_or_t<std::ptrdiff_t, difference_t, Ptr> difference_type;
    
    template <class U>
    using rebind = SROOK_DEDUCED_TYPENAME rebinder<Ptr, U>::type;
    
    SROOK_FORCE_INLINE static Ptr pointer_to(detail::make_not_void<element_type>& e) { return Ptr::pointer_to(e); }
    SROOK_FORCE_INLINE static element_type* to_address(pointer p) SROOK_NOEXCEPT_TRUE { return ::srook::to_address(p); }

    SROOK_STATIC_ASSERT((type_traits::detail::Lnot<is_same<element_type, detail::invalid>>::value), 
            "pointer type defines element_type or is like SomePointer<T, Args>");
};

template <class T>
struct pointer_traits<T*> {
    typedef T* pointer;
    typedef T element_type;
    typedef std::ptrdiff_t difference_type;
    template <class U>
    using rebind = U*;

    SROOK_FORCE_INLINE static pointer pointer_to(detail::make_not_void<element_type>& r) SROOK_NOEXCEPT_TRUE { return srook::addressof(r); }
    SROOK_FORCE_INLINE static element_type* to_address(pointer p) SROOK_NOEXCEPT_TRUE { return ::srook::to_address(p); }
};

SROOK_INLINE_NAMESPACE_END
} // namespace memory

using memory::pointer_traits;

} // namespace srook
#endif
#endif
