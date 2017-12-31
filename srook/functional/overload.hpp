// Inspired by p0051
// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_FUNCTIONAL_OVERLOAD_HPP
#define INCLUDED_SROOK_FUNCTIONAL_OVERLOAD_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <srook/config/attribute.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/config/require.hpp>
#    include <srook/functional/invoke.hpp>
#    include <srook/mpl/variadic_types/pack.hpp>
#    include <srook/type_traits.hpp>
#    include <srook/utility/forward.hpp>
#    include <srook/utility/move.hpp>

namespace srook {
namespace functional {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class F>
struct wrap_caller {
    typedef F type;
    type f_;

    template <
        class U,
        SROOK_REQUIRES(
            type_traits::detail::Land<
            type_traits::detail::Lnot<is_base_of<wrap_caller, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
            is_constructible<F, U> >::value)
    >
    SROOK_CONSTEXPR wrap_caller(U&& f) : f_(srook::forward<U>(f))
    {}
#    define DECL_CALLOP_L(X)                                                                    \
        template <class... Ts>                                                                  \
        SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME invoke_result<F, Ts...>::type \
        operator()(Ts&&... ts)                                                                  \
        X SROOK_MEMFN_NOEXCEPT((is_nothrow_invocable<F, Ts...>::value))                         \
        {                                                                                       \
            return invoke(f_, srook::forward<Ts>(ts)...);                                       \
        }

    DECL_CALLOP_L(const&)
    DECL_CALLOP_L(&)
#    undef DECL_CALLOP_L
#    define DECL_CALLOP_R(X)                                                                    \
        template <class... Ts>                                                                  \
        SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME invoke_result<F, Ts...>::type \
        operator()(Ts&&... ts)                                                                  \
        X SROOK_MEMFN_NOEXCEPT((is_nothrow_invocable<F&&, Ts...>::value))                       \
        {                                                                                       \
            return invoke(srook::move(f_), srook::forward<Ts>(ts)...);                          \
        }

    DECL_CALLOP_R(const&&)
    DECL_CALLOP_R(&&)
#    undef DECL_CALLOP_R
};

#    define DEF_SPECIALS(X)                                                                                                          \
        template <class R, class... Args>                                                                                            \
        struct wrap_caller<X> {                                                                                                      \
            using type = X;                                                                                                          \
            type f_;                                                                                                                 \
            SROOK_CONSTEXPR wrap_caller(type f) : f_(f) {}                                                                           \
            template <class... Ts, SROOK_REQUIRES(is_equal<pack<Args...>, pack<SROOK_DEDUCED_TYPENAME decay<Ts>::type...> >::value)> \
            SROOK_FORCE_INLINE SROOK_CONSTEXPR R operator()(Ts&&... ts) const                                                        \
            SROOK_MEMFN_NOEXCEPT((is_nothrow_invocable<type, Ts...>::value))                                                         \
            {                                                                                                                        \
                return invoke(f_, srook::forward<Ts>(ts)...);                                                                        \
            }                                                                                                                        \
        }

DEF_SPECIALS(R (*)(Args...));
DEF_SPECIALS(R (&)(Args...));
#    undef DEF_SPECIALS

template <class Memptr, class Class, class R, class... Args>
struct function_member_wrapper {
private:
    template <class... Ts>
    using is_args_equal = is_equal<pack<SROOK_DEDUCED_TYPENAME decay<Ts>::type...>, pack<Args...> >;

public:
    typedef Memptr type;
    type f_;

    SROOK_CONSTEXPR function_member_wrapper(type f) : f_(f) {}
    template <
        class U, class... Ts,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                is_base_of<Class, SROOK_DEDUCED_TYPENAME decay<U>::type>,
                is_convertible<SROOK_DECLTYPE(((declval<U>().*f_)(declval<Ts>()...))), R>,
                is_args_equal<Ts...> >::value
        )
    >
    SROOK_FORCE_INLINE SROOK_CONSTEXPR R operator()(U&& obj, Ts&&... ts)
    const SROOK_MEMFN_NOEXCEPT((is_nothrow_invocable<U, Ts...>::value))
    {
        return (srook::forward<U>(obj).*f_)(srook::forward<Ts>(ts)...);
    }
    template <
        class U, class... Ts,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                is_convertible<SROOK_DECLTYPE(((declval<U&>().*f_)(declval<Ts>()...))), R>,
                is_args_equal<Ts...> >::value
        )
    >
    SROOK_FORCE_INLINE SROOK_CONSTEXPR R operator()(std::reference_wrapper<U> ref, Ts&&... ts)
    const SROOK_MEMFN_NOEXCEPT((is_nothrow_invocable<SROOK_DECLTYPE((ref.get())), Ts...>::value))
    {
        return (ref.get().*f_)(srook::forward<Ts>(ts)...);
    }
    template <
        class U, class... Ts,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_base_of<Class, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
                is_convertible<SROOK_DECLTYPE((((*declval<U>()).*f_)(declval<Ts>()...))), R>,
                is_args_equal<Ts...> >::value
        )
    >
    SROOK_FORCE_INLINE SROOK_CONSTEXPR R operator()(U&& ptr, Ts&&... ts)
    const SROOK_MEMFN_NOEXCEPT((is_nothrow_invocable<U, Ts...>::value))
    {
        return ((*srook::forward<U>(ptr)).*f_)(srook::forward<Ts>(ts)...);
    }
};

#    define WRAP_CALL_FOR_MEMFN(CV_REF_QUAL)                                                    \
        template <class C, class R, class... Args>                                              \
        struct wrap_caller<R (C::*)(Args...) CV_REF_QUAL>                                       \
            : function_member_wrapper<R (C::*)(Args...) CV_REF_QUAL, C, R, Args...> {           \
            typedef function_member_wrapper<R (C::*)(Args...) CV_REF_QUAL, C, R, Args...> base; \
            using base::base;                                                                   \
        }
WRAP_CALL_FOR_MEMFN();
WRAP_CALL_FOR_MEMFN(const);
WRAP_CALL_FOR_MEMFN(volatile);
WRAP_CALL_FOR_MEMFN(const volatile);
WRAP_CALL_FOR_MEMFN(&);
WRAP_CALL_FOR_MEMFN(const&);
WRAP_CALL_FOR_MEMFN(volatile&);
WRAP_CALL_FOR_MEMFN(const volatile&);
WRAP_CALL_FOR_MEMFN(&&);
WRAP_CALL_FOR_MEMFN(const&&);
WRAP_CALL_FOR_MEMFN(volatile&&);
WRAP_CALL_FOR_MEMFN(const volatile&&);
#    undef WRAP_CALL_FOR_MEMFN

template <class, class = SROOK_DEDUCED_TYPENAME voider<void>::type>
struct is_accesable_type
    : public SROOK_FALSE_TYPE {};
template <class T>
struct is_accesable_type<T, SROOK_DEDUCED_TYPENAME voider<SROOK_DEDUCED_TYPENAME T::type>::type>
    : public SROOK_TRUE_TYPE {};

template <class F>
struct overload_storage
    : public conditional<
          type_traits::detail::Land<is_accesable_type<F>, is_class<F>, type_traits::detail::Lnot<is_final<F> > >::value,
          F, wrap_caller<F> >::type {};

template <class, class...>
class overloader;
template <class F>
class overloader<F> : public overload_storage<F>::type {
    typedef SROOK_DEDUCED_TYPENAME overload_storage<F>::type base;

public:
    template <class U>
    SROOK_CONSTEXPR explicit overloader(U&& f) : base(srook::forward<U>(f)) {}
    using base::operator();
};
template <class F1, class F2, class... Fs>
class overloader<F1, F2, Fs...> : public overload_storage<F1>::type, public overloader<F2, Fs...> {
    typedef SROOK_DEDUCED_TYPENAME overload_storage<F1>::type base;
    typedef overloader<F2, Fs...> bases;

public:
    template <class U1, class U2, class... Us>
    SROOK_CONSTEXPR explicit overloader(U1&& u1, U2&& u2, Us&&... us)
        : base(srook::forward<U1>(u1)), bases(srook::forward<U2>(u2), srook::forward<Us>(us)...)
    {}
    using base::operator();
    using bases::operator();
};
template <class R, class... Fs>
struct explicit_overloader : public overloader<Fs...> {
    typedef R result_type;
    using overloader<Fs...>::operator();
    template <class... Ts>
    SROOK_CONSTEXPR explicit_overloader(Ts&&... ts) 
        : overloader<Ts...>(srook::forward<Ts>(ts)...)
    {}
};

} // namespace detail

template <class F, class... Fs>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
detail::overloader<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Fs>::type...>
overload(F&& f, Fs&&... fs)
SROOK_NOEXCEPT((is_nothrow_constructible<detail::overloader<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Fs>::type...>, F, Fs...>::value))
{
    return detail::overloader<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Fs>::type...>(
        srook::forward<F>(f), srook::forward<Fs>(fs)...);
}

template <class R, class F, class... Fs>
SROOK_FORCE_INLINE SROOK_CONSTEXPR
detail::explicit_overloader<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Fs>::type...>
overload(F&& f, Fs&&... fs)
SROOK_NOEXCEPT((is_nothrow_constructible<detail::explicit_overloader<SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Fs>::type...>, F, Fs...>::value))
{
    return detail::explicit_overloader<R, SROOK_DEDUCED_TYPENAME decay<F>::type, SROOK_DEDUCED_TYPENAME decay<Fs>::type...>(
        srook::forward<F>(f), srook::forward<Fs>(fs)...);
}

SROOK_INLINE_NAMESPACE_END
} // namespace functional

using functional::overload;

} // namespace srook

#    endif
#endif
