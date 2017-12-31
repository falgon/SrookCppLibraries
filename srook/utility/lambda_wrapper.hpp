// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_UTILITY_LAMBDA_WRAPPER_HPP
#define INCLUDED_SROOK_UTILITY_LAMBDA_WRAPPER_HPP
#include <srook/config/cpp_predefined.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <srook/config/feature/inline_namespace.hpp>
#    include <srook/config/require.hpp>
#    include <srook/type_traits/decay.hpp>
#    include <srook/type_traits/is_callable.hpp>
#    include <srook/utility/declval.hpp>
#    include <srook/utility/forward.hpp>

namespace srook {
namespace utility {
SROOK_INLINE_NAMESPACE(v1)

template <class Lambda>
struct lambda_wrapper {
    lambda_wrapper(const Lambda& lambda) : lambda_(lambda) {}

    template <class Lambdas, REQUIRES(is_callable<typename decay<Lambdas>::type>::value)>
    lambda_wrapper& operator=(const Lambdas& lambda)
    {
        reset(lambda);
        return *this;
    }

    template <class Lambdas, REQUIRES(is_callable<typename decay<Lambdas>::type>::value)>
    void reset(const Lambdas& lambda)
    {
        lambda_.~Lambda();
        new (&lambda_) typename decay<Lambdas>::type(lambda);
    }

    template <class... Args>
    auto operator()(Args&&... value) const
        -> SROOK_DECLTYPE(Lambda()(declval<Args>()...))
    {
        return lambda_(srook::forward<Args>(value)...);
    }

private:
    Lambda lambda_;
};

template <class Lambda>
lambda_wrapper<typename decay<Lambda>::type> make_lambda_wrapper(Lambda&& lambda)
{
    return lambda_wrapper<typename decay<Lambda>::type>(srook::forward<Lambda>(lambda));
}

SROOK_INLINE_NAMESPACE_END
} // namespace utility

using utility::lambda_wrapper;
} // namespace srook
#    endif
#endif
