// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TYPE_TRAITS_REMOVE_ALL_REFERENCES
#define INCLUDED_SROOK_TYPE_TRAITS_REMOVE_ALL_REFERENCES
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/deduced_typename.hpp>
#include <srook/config/attribute/deprecated.hpp>
#include <srook/type_traits/remove_reference.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class...>
struct SROOK_DEPRECATED remove_all_reference;

template <class Head, class... Tail>
struct SROOK_DEPRECATED remove_all_reference<Head, Tail...> {
    typedef SROOK_DEDUCED_TYPENAME srook::mpl::Concat<SROOK_DEDUCED_TYPENAME remove_reference<Head>::type, SROOK_DEDUCED_TYPENAME remove_all_reference<Tail...>::type>::type type;
};
template <class Tail>
struct SROOK_DEPRECATED remove_all_reference<Tail> {
    typedef SROOK_DEDUCED_TYPENAME remove_reference<Tail>::type type;
};

template <class... Pack>
struct SROOK_DEPRECATED remove_all_reference<srook::mpl::pack<Pack...> > : remove_all_reference<Pack...> {};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::remove_all_reference;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Pack>
using remove_all_reference_t = SROOK_DEDUCED_TYPENAME type_traits::detail::remove_all_reference<Pack...>::type;
#endif

} // namespace srook
#endif
#endif
