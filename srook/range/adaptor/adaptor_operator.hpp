// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef SROOK_INCLUDED_ADAPTOR_OPERATOR
#define SROOK_INCLUDED_ADAPTOR_OPERATOR
#if 0
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
} // namespace roki
#else
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/is_range.hpp>

SROOK_NESTED_NAMESPACE(srook, range, adaptors) {
SROOK_INLINE_NAMESPACE(v1)

template <class F, class Range, SROOK_REQUIRES(is_range<SROOK_DEDUCED_TYPENAME decay<Range>::type>::value)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME srook::invoke_result<F, Range&&>::type
operator|(Range&& range, F&& f) SROOK_NOEXCEPT(is_nothrow_invocable<F, Range&&>::value)
{
    return srook::forward<F>(f)(srook::forward<Range>(range));
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(adaptors, range, srook)

#endif
#endif
