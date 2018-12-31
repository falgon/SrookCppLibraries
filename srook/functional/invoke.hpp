// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_FUNCTIONAL_INVOKE_HPP
#define INCLUDED_SROOK_FUNCTIONAL_INVOKE_HPP
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/type_traits/concepts/cxx17/invoke.hpp>
#include <srook/type_traits/invoke_result.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

namespace srook {
namespace functional {

template <class F, class... Args>
typename invoke_result<F, Args...>::type invoke(F&& f, Args&&... args) SROOK_NOEXCEPT_TRUE
{
    return cxx17::concepts::INVOKE(std::forward<F>(f), std::forward<Args>(args)...);
}

} // namespace functional

using functional::invoke;

} // namespace srook

#    endif
#endif
