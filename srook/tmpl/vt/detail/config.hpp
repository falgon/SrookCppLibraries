// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_DETAIL_CONFIG_HPP
#define INCLUDED_SROOK_TMPL_VT_DETAIL_CONFIG_HPP

#include <srook/config.hpp>
#ifdef SROOK_CPP_VARIADIC_TEMPLATES 
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
#include <srook/utility/index_sequence.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/iterator/ostream_joiner.hpp>
#include <utility>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT && SROOK_CPP_TEMPLATE_AUTO
#   include <srook/cxx17/mpl/any_pack.hpp>
#endif
#if !SROOK_CPP_FOLD_EXPRESSIONS
#   include <srook/mpl/constant_sequence/algorithm/reverse.hpp>
#endif

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
template <class T>
struct packer_base {
protected:
#ifdef SROOK_HAS_BOOST_TYPE_INDEX
    SROOK_FORCE_INLINE static std::string& pretty_name()
    {
        static std::string name(boost::typeindex::type_id<T>().pretty_name());
        return name;
    }
#endif
};

template <class... Ts>
struct packer 
    : public srook::pack<Ts...>
    , protected packer_base<packer<Ts...>>
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
    using packer_base<packer<Ts...>>::pretty_name;
#endif
};

template <class Integral, Integral x>
struct packer<srook::integral_constant<Integral, x>>
    : protected packer_base<packer<srook::integral_constant<Integral, x>>> {
        typedef srook::integral_constant<Integral, x> pack_type;
#ifdef SROOK_HAS_BOOST_TYPE_INDEX
        using packer_base<packer<srook::integral_constant<Integral, x>>>::pretty_name;
#endif
        SROOK_FORCE_INLINE friend std::ostream& operator<<(std::ostream& os, const packer<srook::integral_constant<Integral, x>>&)
        {
            return os << x;
        }
};
    
#if !SROOK_CPP_FOLD_EXPRESSIONS
template <class T, class Integral, Integral... val>
SROOK_FORCE_INLINE void output_impl(srook::ostream_joiner<T>& os, const std::integer_sequence<Integral, val...>&)
{
#if SROOK_CPP_LAMBDAS
    [](...){}([](srook::ostream_joiner<T>& j, Integral v) -> srook::ostream_joiner<T>& { return j = v; }(os, val)...);
#else
    struct jt {
        SROOK_FORCE_INLINE jt(srook::ostream_joiner<char*>& oi, Integral x) { oi = x; }
    };
    struct nothingtodo { SROOK_CONSTEXPR SROOK_FORCE_INLINE nothingtodo(...) {} } ntd(jt(os, val)...);
#endif
}
#endif

#if SROOK_CPP_FOLD_EXPRESSIONS
#define SROOK_DEF_OUTPUT_SHIFT(NAMESPACE)\
    template <class Integral, Integral... val>\
    SROOK_FORCE_INLINE std::ostream& operator<<(std::ostream& os, const packer<NAMESPACE::integer_sequence<Integral, val...>>&)\
    {\
        srook::ostream_joiner<char*> joiner(os, ",");\
        ((joiner = val), ...);\
        return os;\
    }
#else
#define SROOK_DEF_OUTPUT_SHIFT(NAMESPACE)\
    template <class Integral, Integral... val>\
    SROOK_FORCE_INLINE std::ostream& operator<<(std::ostream& os, const packer<NAMESPACE::integer_sequence<Integral, val...>>&)\
    {\
        srook::ostream_joiner<char*> joiner(os, ",");\
        typedef SROOK_DEDUCED_TYPENAME srook::constant_sequence::reverse<std::integer_sequence<Integral, val...>>::type revtype;\
        output_impl(joiner, revtype());\
        return os;\
    }
#endif

SROOK_DEF_OUTPUT_SHIFT(srook::utility)
SROOK_DEF_OUTPUT_SHIFT(std)
#undef SROOK_DEF_OUTPUT_SHIFT

template <class Integral, Integral... val>
struct packer<srook::utility::integer_sequence<Integral, val...>> 
    : protected packer_base<packer<srook::utility::integer_sequence<Integral, val...>>> {
    typedef srook::utility::integer_sequence<Integral, val...> pack_type;
#ifdef SROOK_HAS_BOOST_TYPE_INDEX
    using packer_base<packer<srook::utility::integer_sequence<Integral, val...>>>::pretty_name;
#endif
};

template <class Integral, Integral... val>
struct packer<std::integer_sequence<Integral, val...>>
    : protected packer_base<packer<std::integer_sequence<Integral, val...>>> {
    typedef std::integer_sequence<Integral, val...> pack_type;
#ifdef SROOK_HAS_BOOST_TYPE_INDEX
    using packer_base<packer<std::integer_sequence<Integral, val...>>>::pretty_name;
#endif
};

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT && SROOK_CPP_TEMPLATE_AUTO
template <auto... vals>
struct packer<srook::vmpl::any_pack<vals...>> 
    : protected packer_base<packer<srook::vmpl::any_pack<vals...>>> {
    typedef srook::vmpl::any_pack<vals...> pack_type;
#ifdef SROOK_HAS_BOOST_TYPE_INDEX
    using packer_base<packer<srook::vmpl::any_pack<vals...>>>::pretty_name;
#endif
};
#if !SROOK_CPP_FOLD_EXPRESSIONS 
struct nofold_lambda {
    template <class CharType, class T, class... Ts>
    SROOK_FORCE_INLINE static void dojoin(srook::ostream_joiner<CharType>& os, T&& x, Ts&&... val)
    {
        dojoin(os = x, srook::forward<Ts>(val)...);
    }
    template <class CharType>
    SROOK_FORCE_INLINE static void dojoin(srook::ostream_joiner<CharType>&) {}
};  
#endif

template <auto... val>
SROOK_FORCE_INLINE std::ostream& operator<<(std::ostream& os, const packer<srook::vmpl::any_pack<val...>>&)
{
    srook::ostream_joiner<char*> joiner(os, ",");
#if SROOK_CPP_FOLD_EXPRESSIONS
    ((joiner = val), ...);
    return os;
#else
    nofold::dojoin(joiner, val...);
    return os;
#endif
}
#endif

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
