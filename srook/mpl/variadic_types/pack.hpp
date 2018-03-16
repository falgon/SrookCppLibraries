// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MPL_VARIADIC_TYPES_PACK_HPP
#define INCLUDED_SROOK_MPL_VARIADIC_TYPES_PACK_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <cstddef>
#include <srook/config/inline_variable.hpp>
#include <srook/config/feature/inline_variable.hpp>
#include <srook/config/feature/constexpr.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/feature/nested_namespace.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

template <class...> struct packer;

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

namespace srook {
SROOK_INLINE_NAMESPACE(mpl)
SROOK_INLINE_NAMESPACE(v1)
namespace detail {
template <class... T>
struct pack {
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR_OR_CONST std::size_t size = sizeof...(T);
    typedef srook::tmpl::vt::packer<T...> rebind_packer;
};
} // namespace detail

using detail::pack;

SROOK_INLINE_NAMESPACE_END
SROOK_INLINE_NAMESPACE_END
} // namespace srook

#endif
#endif
