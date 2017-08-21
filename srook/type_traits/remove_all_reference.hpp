// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_REMOVE_ALL_REFERENCES
#define INCLUDED_SROOK_TYPE_TRAITS_REMOVE_ALL_REFERENCES
#include <srook/mpl/variadic_player.hpp>
namespace srook {
inline namespace v1 {

template <class...>
struct remove_all_reference;

template <class Head, class... Tail>
struct remove_all_reference<Head, Tail...> {
    using type = srook::mpl::Concat_t<std::remove_reference_t<Head>, typename remove_all_reference<Tail...>::type>;
};
template <class Tail>
struct remove_all_reference<Tail> {
    using type = std::remove_reference_t<Tail>;
};

template <class... Pack>
struct remove_all_reference<srook::mpl::pack<Pack...>> : remove_all_reference<Pack...> {
};

template <class... Pack>
using remove_all_reference_t = typename remove_all_reference<Pack...>::type;

} // namespace v1
} // namespace srook
#endif
