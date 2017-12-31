// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef SROOK_INCLUDED_ADAPTOR_OPERATOR
#define SROOK_INCLUDED_ADAPTOR_OPERATOR
#include <type_traits>
#include <utility>
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/type_traits/invoke_result.hpp>

namespace srook{
namespace adaptors{
namespace detail{
inline namespace v1{

template<class Range,class Function>
constexpr typename srook::invoke_result<Function,Range>::type operator|(Range&& r,Function&& f) SROOK_NOEXCEPT(f(std::declval<Range>()))
{
	return std::forward<Function>(f)(std::forward<Range>(r));
}

} // inline namespace
} // namespace detail
} // namespace adaptors

namespace pipealgo{
namespace detail{
inline namespace v1{

template<class Range,class Function>
constexpr typename srook::invoke_result<Function,Range>::type operator|(Range&& r,Function&& f) SROOK_NOEXCEPT(f(std::declval<Range>()))
{
	return std::forward<Function>(f)(std::forward<Range>(r));
}

} // inline namespace v1
} // namespace algo
} // namespace detail

} // namespace roki
#endif
