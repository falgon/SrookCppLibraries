// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_DETAIL_LAMBDA_WRAPPER_HPP
#define INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_DETAIL_LAMBDA_WRAPPER_HPP
#include <srook/config.hpp>
#include <srook/type_traits/is_function_object.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/memory/destroy/destroy_at.hpp>
#include <srook/memory/addressof.hpp>

#if SROOK_CPP_VARIADIC_TEMPLATES

SROOK_NESTED_NAMESPACE(srook, range, iterator) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class FObj>
class lambda_wrapper {
public:
    explicit SROOK_CONSTEXPR lambda_wrapper(const FObj& inv) SROOK_NOEXCEPT(is_nothrow_constructible<FObj&, FObj>::value) 
        : lambda_(inv) {}

    template <class T, SROOK_REQUIRES(is_function_object<T>::value)>
    SROOK_FORCE_INLINE lambda_wrapper& operator=(const T& t) SROOK_NOEXCEPT(reset(t))
    {
        return reset(t);
    }

#if SROOK_CPP_RVALUE_REFERENCES
    template <class T, SROOK_REQUIRES(is_function_object<SROOK_DEDUCED_TYPENAME decay<T>::type>::value)>
    SROOK_FORCE_INLINE lambda_wrapper& reset(T&& t)
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_destructible<FObj>, is_nothrow_constructible<FObj>::value)
    {
        srook::destroy_at(lambda_);
        new (srook::addressof(lambda_)) T(srook::forward<T>(t));
        return *this;
    }
#else
    template <class T, SROOK_REQUIRES(is_function_object<T>::value)>
    SROOK_FORCE_INLINE lambda_wrapper& reset(const T& t) 
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_destructible<FObj>, is_nothrow_constructible<FObj>>::value)
    {
        srook::destroy_at(lambda_);
        new (srook::addressof(lambda_)) T(t);
        return *this;
    }
#endif

    template <class... Args>
    SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME srook::invoke_result<FObj, Args&&...>::type
    operator()(Args&&... args) const SROOK_NOEXCEPT(is_nothrow_invocable<FObj, Args&&...>::value)
    {
        return lambda_(srook::forward<Args>(args)...);
    }
private:
    FObj lambda_;
};

template <class FObj>
SROOK_CONSTEXPR SROOK_FORCE_INLINE lambda_wrapper<SROOK_DEDUCED_TYPENAME decay<FObj>::type> make_lambda_wrapper(FObj&& f)
SROOK_NOEXCEPT(is_nothrow_constructible<lambda_wrapper<SROOK_DEDUCED_TYPENAME decay<FObj>::type>, FObj&&>::value)
{
    return lambda_wrapper<SROOK_DEDUCED_TYPENAME decay<FObj>::type>(srook::forward<FObj>(f));
}


} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, range, srook)
#else
#   error This feature needs variadic templates
#endif
#endif
