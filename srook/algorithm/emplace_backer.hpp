// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_EMPLACE_BACKER_HPP
#define INCLUDED_SROOK_ALGORITHM_EMPLACE_BACKER_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/algorithm/back.hpp>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

#if SROOK_CPP_FOLD_EXPRESSIONS
template <class Container, class... Args>
SROOK_FORCE_INLINE 
SROOK_DEDUCED_TYPENAME enable_if<detail::has_emplace_back<Container, Args...>::value>::type
emplace_backer(Container&& v, Args&&... args)
{
    (v.emplace_back(srook::forward<Args>(args)), ...);
}

template <class Container, class... Args>
SROOK_FORCE_INLINE
SROOK_DEDUCED_TYPENAME enable_if<detail::has_push_back<Container, Args...>::value>::type
push_backer(Container&& v, Args&&... args)
{
    (v.push_back(srook::forward<Args>(args)), ...);
}
#else
template <class Container>
SROOK_FORCE_INLINE 
SROOK_DEDUCED_TYPENAME enable_if<detail::has_emplace_back<Container>::value>::type
emplace_backer(Container&&) {}

template <class Container, class Arg, class... Args>
SROOK_DEDUCED_TYPENAME enable_if<detail::has_emplace_back<Container, Arg, Args...>::value>::type
emplace_backer(Container&& v, Arg&& arg, Args&&... args)
{
    v.emplace_back(srook::forward<Arg>(arg));
    srook::algorithm::emplace_backer(srook::forward<Container>(v), srook::forward<Args>(args)...);
}

template <class Container>
SROOK_FORCE_INLINE void push_backer(Container&&) {}

template <class Container, class Arg, class... Args>
SROOK_DEDUCED_TYPENAME enable_if<detail::has_push_back<Container, Arg, Args...>::value>::type
push_backer(Container&& v, Arg&& arg, Args&&... args)
{
    v.push_back(srook::forward<Arg>(arg));
    srook::algorithm::emplace_backer(srook::forward<Container>(v), srook::forward<Args>(args)...);
}
#endif

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

namespace srook {

using srook::algorithm::emplace_backer;
using srook::algorithm::push_backer;

} // namespace srook

#endif

#endif
