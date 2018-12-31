// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_ALIGNMENT_OF_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_ALIGNMENT_OF_HPP

#include <srook/config/feature.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/utility/enable_copy_move.hpp>
#ifdef _MSC_VER
#    pragma warning(push)
#    pragma warning(disable : 4121 4512)
#endif
#if defined(__BORLANDC__) && (__BORLANDC__ < 0x600)
#    pragma option push -Vx- -Ve -
#endif

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)

#ifdef SROOK_ALIGN_OF
template <class T>
struct alignment_of 
    : public integral_constant<std::size_t, SROOK_ALIGN_OF(T)> {};
#else
#    ifdef _MSC_VER
#        pragma warning(push)
#        pragma warning(disable : 4324)
#    endif
namespace detail {

template <class T>
struct alignment_of_hack : 
	public disable_special_functions<alignment_of_hack<T> > {
    char c;
    T t;
};
#    ifdef _MSC_VER
#        pragma warning(pop)
#    endif

template <unsigned A, unsigned S>
struct alignment_logic 
    : public integral_constant <std::size_t, A < S ? A : S> {};

template <class T>
struct alignment_of_impl
    : public integral_constant<std::size_t,
	// This function always returns a multiple of alignment.
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
	alignment_logic<sizeof(alignment_of_hack<T>) - sizeof(T), __alignof(T)>::value  
#else
	alignment_logic<sizeof(alignment_of_hack<T>) - sizeof(T), sizeof(T)>::value
#endif	
	> {};

} // namespace detail

template <class T>
struct alignment_of 
    : public integral_constant<std::size_t, detail::alignment_of_impl<T>::value> {};

#endif

template <class T>
struct alignment_of<T&> : public alignment_of<T*> {};

#ifdef __BORLANDC__
struct long_doubler {
    long double ld;
};
template <>
struct alignment_of<long double> : public alignment_of<long_doubler> {};
#endif

template <> struct alignment_of<void> : public integral_constant<std::size_t, 0> {};
template <> struct alignment_of<const void> : public alignment_of<void> {};
template <> struct alignment_of<const volatile void> : public alignment_of<void> {};
template <> struct alignment_of<volatile void> : public alignment_of<void> {};

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::alignment_of;

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool alignment_of_v = alignment_of<T>::value;
#endif

} // namespace srook

#    if defined(__BORLANDC__) && (__BORLANDC__ < 0x600)
#        pragma option pop
#    endif
#    ifdef _MSC_VER
#        pragma warning(pop)
#    endif
#endif
