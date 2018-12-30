// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TUPLE_UTILITY_AMPERSAND_HPP
#define INCLUDED_SROOK_TUPLE_UTILITY_AMPERSAND_HPP

#include <srook/tuple/utility/detail/utils.hpp>
#include <srook/type_traits/is_tuple.hpp>
#include <srook/type_traits/is_rvalue_reference.hpp>
#include <srook/type_traits/is_nothrow_move_constructible.hpp>
#include <srook/type_traits/derivation_invoke_result.hpp>

SROOK_NESTED_NAMESPACE(srook, tuple, utility) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <bool>
struct tuple_type_impl {
    template <class... Ts>
    using type = std::tuple<Ts...>;
};

template <>
struct tuple_type_impl<false> {
    template <class L, class R>
    using type = std::pair<L, R>;
};

template <class... Fs>
struct tuple_type {
private:
    template <class T>
    struct cm_constructible
        : conditional<is_rvalue_reference<T>::value, is_nothrow_move_constructible<T>, is_nothrow_constructible<T&, T>> {};
        
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST bool tuple_select = sizeof...(Fs) > 2; 
    typedef srook::tmpl::vt::packer<
        SROOK_DEDUCED_TYPENAME srook::tmpl::vt::transfer<
            invoke_result, 
            SROOK_DEDUCED_TYPENAME srook::tmpl::vt::concat<Fs, SROOK_DEDUCED_TYPENAME arguments<Fs>::type>::type
        >::type::type...
    > result_types;
public:
    typedef SROOK_DEDUCED_TYPENAME srook::tmpl::vt::transfer<tuple_type_impl<tuple_select>::template type, result_types>::type type;
    
    template <class... Ts>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE static type make(Ts&&... ts) 
    SROOK_NOEXCEPT(type_traits::detail::Land<SROOK_DEDUCED_TYPENAME cm_constructible<Ts&&>::type...>)
    {
        return { srook::forward<Ts>(ts)... };
    }
};

template <class... Fs>
struct intrinsic_lambda_ampersand {
    template <class... Args, SROOK_REQUIRES(type_traits::detail::Land<is_same<Fs, SROOK_DEDUCED_TYPENAME decay<Args>::type>...>::value)>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE intrinsic_lambda_ampersand(Args&&... args)
    SROOK_NOEXCEPT(is_nothrow_invocable<std::tuple<Fs...>, Args&&...>::value)
        : fs(srook::forward<Args>(args)...) {}

    template <class T, SROOK_REQUIRES(type_traits::detail::Land<is_invocable<Fs, T&&>...>::value)>
    SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
    detail::tuple_type<Fs...>::type 
    operator()(T&& v) 
    SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_invocable<Fs, T&&>...>::value)
    {
        return srook::apply(apply_fns<SROOK_DEDUCED_TYPENAME decay<T>::type>(srook::forward<T>(v)), fs);
    }
private:
    const std::tuple<Fs...> fs;

    template <class T>
    struct apply_fns SROOK_FINAL {
        template <class U, SROOK_REQUIRES(is_same<SROOK_DEDUCED_TYPENAME decay<U>::type, T>::value)>
        SROOK_CONSTEXPR SROOK_FORCE_INLINE apply_fns (U&& u) 
        SROOK_NOEXCEPT(is_nothrow_constructible<T&, U&&>::value)
            : val(srook::forward<U>(u)) {}

        template <class... Fns>
        SROOK_CONSTEXPR SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME 
        detail::tuple_type<SROOK_DEDUCED_TYPENAME decay<Fns>::type...>::type
        operator()(Fns&&... fn)
        SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_invocable<Fns, T&&>...>::value)
        {
            return tuple_type<SROOK_DEDUCED_TYPENAME decay<Fns>::type...>::make(srook::invoke(srook::forward<Fns>(fn), val)...);
        }
    private:
        const T val;
    };
};

} // namespace detail

template <class... Fs,
SROOK_REQUIRES(
    type_traits::detail::Land<
        type_traits::detail::Lor<is_callable<SROOK_DEDUCED_TYPENAME decay<Fs>::type>, 
        is_function<SROOK_DEDUCED_TYPENAME remove_pointer<SROOK_DEDUCED_TYPENAME decay<Fs>::type>::type>>...
    >::value
)>
SROOK_FORCE_INLINE SROOK_CONSTEXPR 
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT    
auto
#else
detail::intrinsic_lambda_ampersand<SROOK_DEDUCED_TYPENAME decay<Fs>::type...>
#endif
ampersand(Fs&&... fs)
SROOK_NOEXCEPT(
    type_trait::detail::Land<
        SROOK_DEDUCED_TYPENAME srook::tmpl::vt::transfer<
            is_nothrow_invocable, 
            SROOK_DEDUCED_TYPENAME srook::tmpl::vt::concat<Fs, SROOK_DEDUCED_TYPENAME arguments<SROOK_DEDUCED_TYPENAME decay<Fs>::type>::type>::type
        >::type::type...
    >::value
)
{
#if SROOK_CPP_LAMBDAS && SROOK_CPLUSPLUS14_CONSTANT
    typedef SROOK_DEDUCED_TYPENAME detail::tuple_type<SROOK_DEDUCED_TYPENAME decay<Fs>::type...>::type result_type;
    return
        [t = std::forward_as_tuple(srook::forward<Fs>(fs)...)](auto&& v) -> result_type {
            return 
                srook::apply([val = srook::forward<SROOK_DECLTYPE(v)>(v)](auto&&... fns) -> result_type { 
                    return detail::tuple_type<SROOK_DEDUCED_TYPENAME decay<Fs>::type...>::make(srook::invoke(srook::forward<SROOK_DECLTYPE(fns)>(fns), val)...);
                }, t);
        };
#else
    return detail::intrinsic_lambda_ampersand<SROOK_DEDUCED_TYPENAME decay<Fs>::type...>(srook::forward<Fs>(fs)...);
#endif
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(utility, tuple, srook)
#endif
