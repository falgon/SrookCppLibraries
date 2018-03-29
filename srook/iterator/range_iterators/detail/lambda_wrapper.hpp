// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_DETAIL_LAMBDA_WRAPPER_HPP
#define INCLUDED_SROOK_ITERATOR_RANGE_ITERATORS_DETAIL_LAMBDA_WRAPPER_HPP
#include <srook/config.hpp>
#include <srook/type_traits/is_function_object.hpp>
#include <srook/type_traits/is_function.hpp>
#include <srook/type_traits/invoke_result.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/memory/destroy/destroy_at.hpp>
#include <srook/memory/addressof.hpp>
#include <srook/functional/invoke.hpp>
#include <new>

#if SROOK_CPP_VARIADIC_TEMPLATES

SROOK_NESTED_NAMESPACE(srook, range, iterator) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class F>
class lambda_wrapper {
public:
    explicit SROOK_CONSTEXPR lambda_wrapper(const F& inv) SROOK_NOEXCEPT(is_nothrow_constructible<F&, F>::value) 
        : lambda_(inv), replaced_(false) {}

    template <class T>
    SROOK_FORCE_INLINE lambda_wrapper& operator=(const T& t) SROOK_MEMFN_NOEXCEPT(reset(t)) { return reset(t); }

    SROOK_FORCE_INLINE ~lambda_wrapper()
    SROOK_NOEXCEPT(is_nothrow_destructible<F>::value)
    {
        if (replaced_) srook::destroy_at(srook::addressof(lambda_));
    }

#if SROOK_CPP_RVALUE_REFERENCES
    template <class T>
    SROOK_FORCE_INLINE lambda_wrapper& reset(T&& t)
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_destructible<SROOK_DEDUCED_TYPENAME decay<F>::type>, is_nothrow_constructible<SROOK_DEDUCED_TYPENAME decay<F>::type>::value)
    {
        srook::destroy_at(srook::addressof(lambda_));
        ::new (srook::addressof(lambda_)) SROOK_DEDUCED_TYPENAME decay<T>::type(srook::forward<T>(t));
        replaced_ = true;
        return *this;
    }
#else
    template <class T>
    SROOK_FORCE_INLINE lambda_wrapper& reset(const T& t) 
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_destructible<F>, is_nothrow_constructible<F>>::value)
    {
        srook::destroy_at(srook::addressof(lambda_));
        ::new (srook::addressof(lambda_)) T(t);
        replaced_ = true;
        return *this;
    }
#endif

    template <class... Args>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME srook::invoke_result<F, Args&&...>::type
    operator()(Args&&... args) const SROOK_NOEXCEPT(is_nothrow_invocable<F, Args&&...>::value)
    {
        return srook::invoke(lambda_, srook::forward<Args>(args)...); //lambda_(srook::forward<Args>(args)...);
    }
private:
    F lambda_;
    bool replaced_;
};

template <class F>
SROOK_CONSTEXPR SROOK_FORCE_INLINE lambda_wrapper<SROOK_DEDUCED_TYPENAME decay<F>::type> make_lambda_wrapper(F&& f)
SROOK_NOEXCEPT(is_nothrow_constructible<lambda_wrapper<SROOK_DEDUCED_TYPENAME decay<F>::type>, F&&>::value)
{
    return lambda_wrapper<SROOK_DEDUCED_TYPENAME decay<F>::type>(srook::forward<F>(f));
}


} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, range, srook)
#else
#   error This feature needs variadic templates
#endif
#endif
