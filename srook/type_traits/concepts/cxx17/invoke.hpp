// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_TYPE_TRAITS_CONCEPT_INVOKE_CONCEPT_HPP
#define INCLUDED_SROOK_TYPE_TRAITS_CONCEPT_INVOKE_CONCEPT_HPP
#include <srook/config/feature/inline_namespace.hpp>
#include <utility>

namespace srook {
namespace cxx17 {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class F, class... Args>
inline auto INVOKE(F&& f, Args&&... args)
-> decltype(std::forward<F>(f)(std::forward<Args>(args)...))
{
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

template <class Base, class T, class Derived>
inline auto INVOKE(T Base::*pmd, Derived&& ref)
-> decltype(std::forward<Derived>(ref).*pmd)
{
    return std::forward<Derived>(ref).*pmd;
}

template <class Base, class T, class Derived, class... Args>
inline auto INVOKE(T Base::*pmf, Derived&& ref, Args&&... args)
-> decltype((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...))
{
    return (std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...);
}

template <class PMD, class Pointer>
inline auto INVOKE(PMD&& pmd, Pointer&& ptr)
    -> decltype((*std::forward<Pointer>(ptr)).*std::forward<PMD>(pmd))
{
    return (*std::forward<Pointer>(ptr)).*std::forward<PMD>(pmd);
}

template <class PMF, class Pointer, class... Args>
inline auto INVOKE(PMF&& pmf, Pointer&& ptr, Args&&... args)
-> decltype(((*std::forward<Pointer>(ptr)).*std::forward<PMF>(pmf))(std::forward<Args>(args)...))
{
    return ((*std::forward<Pointer>(ptr)).*std::forward<PMF>(pmf))(std::forward<Args>(args)...);
}

} // namespace detail
SROOK_INLINE_NAMESPACE_END

using detail::INVOKE;

} // namespace concepts
} // namespace cxx17
} // namespace srook

#endif
