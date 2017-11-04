// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_REMOVE_ALL_REFERENCES
#define INCLUDED_SROOK_TYPE_TRAITS_REMOVE_ALL_REFERENCES
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/mpl/variadic_types/algorithm/concat.hpp>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class...>
struct remove_all_reference;

template <class Head, class... Tail>
struct remove_all_reference<Head, Tail...> {
    using type = typename srook::mpl::Concat<std::remove_reference_t<Head>, typename remove_all_reference<Tail...>::type>::type;
};
template <class Tail>
struct remove_all_reference<Tail> {
    using type = std::remove_reference_t<Tail>;
};

template <class... Pack>
struct remove_all_reference<srook::mpl::pack<Pack...> > : remove_all_reference<Pack...> {
};

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

using type_traits::detail::remove_all_reference;

#if SROOK_CPP_ALIAS_TEMPLATES
template <class... Pack>
using remove_all_reference_t = typename type_traits::detail::remove_all_reference<Pack...>::type;
#endif

} // namespace srook
#endif
#endif
