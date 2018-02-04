// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_DETAIL_CONFIG_HPP
#define INCLUDED_SROOK_TMPL_VT_DETAIL_CONFIG_HPP

#include <srook/config.hpp>
#if SROOK_CPP_VARIADIC_TEMPLATES 
#if SROOK_HAS_INCLUDE(<tuple>)
#   include <tuple>
#   ifndef SROOK_HAS_STD_TUPLE
#       define SROOK_HAS_STD_TUPLE 1
#   endif
#elif SROOK_HAS_INCLUDE(<boost/tuple/tuple.hpp>)
#   include <boost/tuple/tuple.hpp>
#   ifndef SROOK_HAS_BOOST_TUPLE
#       define SROOK_HAS_BOOST_TUPLE 1
#   endif
#endif
#if !defined(BOOST_TYPE_INDEX_HPP) && SROOK_HAS_INCLUDE(<boost/type_index.hpp>)
#   include <boost/type_index.hpp>
#   include <string>
#   define SROOK_HAS_BOOST_TYPE_INDEX 1
#endif
#if defined(BOOST_TYPE_INDEX_HPP) && !defined(SROOK_HAS_BOOST_TYPE_INDEX)
#   define SROOK_HAS_BOOST_TYPE_INDEX 1
#endif

#include <srook/mpl/variadic_types.hpp>
#include <srook/type_traits/type_constant.hpp>
#include <utility>

namespace srook {
namespace tmpl {
namespace vt {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

using srook::variadic_types::detail::At;
using srook::variadic_types::detail::Concat;
using srook::variadic_types::detail::Erase;
using srook::variadic_types::detail::EraseAll;
using srook::variadic_types::detail::First;
using srook::variadic_types::detail::IndexOf;
using srook::variadic_types::is_contained_in;
using srook::variadic_types::detail::Last;
using srook::variadic_types::detail::Length;
using srook::variadic_types::detail::NoDuplicate;
using srook::variadic_types::detail::PartialHead;
using srook::variadic_types::detail::PartialTail;
using srook::variadic_types::detail::PopBack;
using srook::variadic_types::detail::PopFront;
using srook::variadic_types::detail::Replace;
using srook::variadic_types::detail::ReplaceAll;
using srook::variadic_types::detail::Reverse;
using srook::variadic_types::detail::Size;
using srook::SwapAt_L_type;
using srook::SwapAt_R_type;
using srook::SwapAt_Specified_L_type;
using srook::SwapAt_Specified_R_type;
using srook::variadic_types::detail::Transfer;

} // namespace detail

// Inspired by N4115
template <class... Ts>
struct packer 
    : public srook::pack<Ts...>
#if SROOK_HAS_STD_TUPLE
    , public std::tuple<Ts...>
#elif SROOK_HAS_BOOST_TUPLE
    , public boost::tuple<Ts...>
#endif
{
#if SROOK_HAS_STD_TUPLE
    typedef std::tuple<Ts...> base_type;
    using base_type::base_type;
    using base_type::operator=;
    using base_type::swap;
#elif SROOK_HAS_BOOST_TUPLE
    typedef boost::tuple<Ts...> base_type;
    using base_type::base_type;
#else
    typedef void base_type;
#endif

#ifdef SROOK_HAS_BOOST_TYPE_INDEX
    SROOK_FORCE_INLINE static std::string& pretty_name()
    {
        static std::string name(boost::typeindex::type_id<packer<Ts...>>().pretty_name());
        return name;
    }
#endif
};

#if SROOK_CPP_DEDUCTION_GUIDES
template <class... Ts> packer(Ts...) -> packer<Ts...>;
template <class L, class R> packer(std::pair<L, R>) -> packer<L, R>;
template <class Alloc, class... Ts> packer(std::allocator_arg_t, Alloc, Ts...) -> packer<Ts...>;
template <class Alloc, class L, class R> packer(std::allocator_arg_t, Alloc, std::pair<L, R>) -> packer<L, R>;
template <class Alloc, class... Ts> packer(std::allocator_arg_t, Alloc, packer<Ts...>) -> packer<Ts...>;

#if SROOK_HAS_STD_TUPLE
template <class Alloc, class... Ts> packer(std::allocator_arg_t, Alloc, std::tuple<Ts...>) -> packer<Ts...>;
#elif SROOK_HAS_BOOST_TUPLE
template <class Alloc, class... Ts> packer(std::allocator_arg_t, Alloc, boost::tuple<Ts...>) -> packer<Ts...>;
#endif
#endif

SROOK_INLINE_NAMESPACE_END
} // namespace vt
} // namespace tmpl
} // namespace srook

#else
#   error This feature needs to support variadic templates
#endif
#endif
