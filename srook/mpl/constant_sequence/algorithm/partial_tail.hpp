// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONSTANT_SEQUENCE_PARTIAL_TAIL_HPP
#define INCLUDED_SROOK_CONSTANT_SEQUENCE_PARTIAL_TAIL_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/deduced_typename.hpp>
#include <srook/mpl/constant_sequence/algorithm/concat.hpp>
#include <srook/type_traits/detail/type_constant.hpp>
#include <utility>

#if defined(__GNUC__) && (__GNUC__ <= 7 && __GNUC_MINOR__ <= 3) // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=84785

namespace srook{
inline namespace mpl{
namespace constant_sequence{
inline namespace v1{

template<class>
struct partial_tail_impl;
template<std::size_t head,std::size_t... tail>
struct partial_tail_impl<std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<head>,typename partial_tail_impl<std::index_sequence<tail...>>::type>;
};
template<std::size_t tail>
struct partial_tail_impl<std::index_sequence<tail>>{
	using type=std::index_sequence<tail>;
};
template<>
struct partial_tail_impl<std::index_sequence<>>{
	using type=std::index_sequence<>;
};
template<std::size_t,class>
struct partial_tail;
template<std::size_t target,std::size_t head,std::size_t... tail>
struct partial_tail<target,std::index_sequence<head,tail...>>{
	using type=typename partial_tail<target-1,std::index_sequence<tail...>>::type;
};
template<std::size_t head,std::size_t... tail>
struct partial_tail<0,std::index_sequence<head,tail...>>{
	using type=concat_t<std::index_sequence<head>,typename partial_tail_impl<std::index_sequence<tail...>>::type>;
};
template<std::size_t target,class Sequence>
using partial_tail_t=typename partial_tail<target,Sequence>::type;

} // inline namespace v1
} // namespace constant_sequence
} // namespace mpl
} // namespace srook 

#else

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
namespace constant_sequence {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T, std::size_t>
struct pair_type : type_constant<T> {};

template <class> struct partial_tail_impl2;
template <std::size_t... idx>
struct partial_tail_impl2<std::index_sequence<idx...>> {
    template <SROOK_DEDUCED_TYPENAME pair_type<std::size_t, idx>::type..., std::size_t... xs>
    struct get : type_constant<std::index_sequence<xs...>> {};
};

template <std::size_t target, std::size_t... xs>
struct partial_tail_impl1
    : partial_tail_impl2<std::make_index_sequence<target>>::template get<xs...> {};

} // namespace detail

template <std::size_t, class>
struct partial_tail;

template <std::size_t target, std::size_t... xs>
struct partial_tail<target, std::index_sequence<xs...>>
    : detail::partial_tail_impl1<target, xs...> {};

#if SROOK_CPP_ALIAS_TEMPLATES
template <std::size_t n, class T>
using partial_tail_t = SROOK_DEDUCED_TYPENAME srook::constant_sequence::partial_tail<n, T>::type;
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace constant_sequence
SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif

#endif
#endif
