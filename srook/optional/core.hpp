// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_OPTIONAL_CORE_HPP
#define INCLUDED_SROOK_OPTIONAL_CORE_HPP
#include <srook/optional/optional.h>
#include <srook/optional/optional_base.hpp>
#include <srook/optional/applicative.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
namespace srook {
namespace optionally {
SROOK_INLINE_NAMESPACE(v1)

template <class T, template <class, bool, bool> class Payload>
class optional
    : private detail::optional_base<T, Payload>,
      private enable_copy_move<
          is_copy_constructible<T>::value,
          type_traits::detail::Land<is_copy_constructible<T>, is_copy_assignable<T> >::value,
          is_move_constructible<T>::value,
          type_traits::detail::Land<is_move_constructible<T>, is_move_assignable<T> >::value,
          optional<T> > {
    SROOK_ST_ASSERT((type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME remove_cv<T>::type, nullopt_t> >::value));
    SROOK_ST_ASSERT((type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME remove_cv<T>::type, in_place_t> >::value));
    SROOK_ST_ASSERT((type_traits::detail::Lnot<is_reference<T> >::value));

private:
    typedef detail::optional_base<T, Payload> Base_type;

public:
    typedef T value_type;
    struct srook_optional_tag {}; // exposition only

    SROOK_CONSTEXPR optional() SROOK_DEFAULT
#    define DEF_CONSTRUCTOR(X) \
        SROOK_CONSTEXPR optional(X::nullopt_t) SROOK_NOEXCEPT_TRUE : Base_type(X::nullopt) {}
    DEF_CONSTRUCTOR(optionally)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    undef DEF_CONSTRUCTOR
#    if SROOK_HAS_BOOST_OPTIONAL
    optional(boost::none_t) SROOK_NOEXCEPT_TRUE : Base_type(boost::none) {}
#    endif

    template <
        class U = T,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<optional<T>, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
                type_traits::detail::Lnot<is_same<in_place_t, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
                is_constructible<T, U&&>,
                is_convertible<U&&, T> >::value)>
    SROOK_CONSTEXPR optional(U&& t) : Base_type(in_place, srook::forward<U>(t)) {}

    template <
        class U = T,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<optional<T>, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
                type_traits::detail::Lnot<is_same<in_place_t, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
                is_constructible<T, U&&>,
                type_traits::detail::Lnot<is_convertible<U&&, T> > >::value)>
    explicit SROOK_CONSTEXPR optional(U&& t) : Base_type(in_place, srook::forward<U>(t)) {}

#    define DEF_CONSTRUCTOR(X)                                                                  \
        template <                                                                              \
            class U,                                                                            \
            SROOK_REQUIRES(                                                                     \
                type_traits::detail::Land<                                                      \
                    type_traits::detail::Lnot<is_same<T, U> >,                                  \
                    is_constructible<T, const U&>,                                              \
                    is_convertible<const U&, T>,                                                \
                    type_traits::detail::Lnot<detail::converts_from_optional<T, U> > >::value)> \
        SROOK_CONSTEXPR optional(const X::optional<U>& t)                                       \
        {                                                                                       \
            if (t) emplace(*t);                                                                 \
        }
    DEF_CONSTRUCTOR(optionally)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    if SROOK_HAS_BOOST_OPTIONAL
    DEF_CONSTRUCTOR(boost)
#    endif
#    undef DEF_CONSTRUCTOR

#    define DEF_CONSTRUCTOR(X)                                                                  \
        template <                                                                              \
            class U,                                                                            \
            SROOK_REQUIRES(                                                                     \
                type_traits::detail::Land<                                                      \
                    type_traits::detail::Lnot<is_same<T, U> >,                                  \
                    is_constructible<T, const U&>,                                              \
                    type_traits::detail::Lnot<is_convertible<const U&, T> >,                    \
                    type_traits::detail::Lnot<detail::converts_from_optional<T, U> > >::value)> \
        explicit SROOK_CONSTEXPR optional(const X::optional<U>& t)                              \
        {                                                                                       \
            if (t) emplace(*t);                                                                 \
        }
    DEF_CONSTRUCTOR(optionally)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    if SROOK_HAS_BOOST_OPTIONAL
    DEF_CONSTRUCTOR(boost)
#    endif
#    undef DEF_CONSTRUCTOR

#    define DEF_CONSTRUCTOR(X)                                                                  \
        template <                                                                              \
            class U,                                                                            \
            SROOK_REQUIRES(                                                                     \
                type_traits::detail::Land<                                                      \
                    type_traits::detail::Lnot<is_same<T, U> >,                                  \
                    is_constructible<T, U&&>,                                                   \
                    is_convertible<U&&, T>,                                                     \
                    type_traits::detail::Lnot<detail::converts_from_optional<T, U> > >::value)> \
        SROOK_CONSTEXPR optional(X::optional<U>&& t)                                            \
        {                                                                                       \
            if (t) emplace(srook::move(*t));                                                    \
        }
    DEF_CONSTRUCTOR(optionally)
#    ifdef SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    if defined(SROOK_HAS_BOOST_OPTIONAL)
    DEF_CONSTRUCTOR(boost)
#    endif
#    undef DEF_CONSTRUCTOR

#    define DEF_CONSTRUCTOR(X)                                                                  \
        template <                                                                              \
            class U,                                                                            \
            SROOK_REQUIRES(                                                                     \
                type_traits::detail::Land<                                                      \
                    type_traits::detail::Lnot<is_same<T, U> >,                                  \
                    is_constructible<T, U&&>,                                                   \
                    type_traits::detail::Lnot<is_convertible<U&&, T> >,                         \
                    type_traits::detail::Lnot<detail::converts_from_optional<T, U> > >::value)> \
        explicit SROOK_CONSTEXPR optional(X::optional<U>&& t)                                   \
        {                                                                                       \
            if (t) emplace(srook::move(*t));                                                    \
        }
    DEF_CONSTRUCTOR(optionally)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    if SROOK_HAS_BOOST_OPTIONAL
    DEF_CONSTRUCTOR(boost)
#    endif
#    undef DEF_CONSTRUCTOR

#    define DEF_CONSTRUCTOR(X)                                                                                                \
        template <class... Args, SROOK_REQUIRES(is_constructible<T, Args&&...>::value)>                                       \
        explicit SROOK_CONSTEXPR optional(X::in_place_t, Args&&... args)                                                      \
            : Base_type(X::in_place, srook::forward<Args>(args)...) {}                                                        \
        template <class U, class... Args, SROOK_REQUIRES((is_constructible<T, std::initializer_list<U>&, Args&&...>::value))> \
        explicit SROOK_CONSTEXPR optional(X::in_place_t, std::initializer_list<U> li, Args&&... args)                         \
            : Base_type(X::in_place, li, srook::forward<Args>(args)...) {}
    DEF_CONSTRUCTOR(srook)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    undef DEF_CONSTRUCTOR

#    define DEF_OPERATOR(X)                                               \
        optional<T, Payload>& operator=(X::nullopt_t) SROOK_NOEXCEPT_TRUE \
        {                                                                 \
            reset();                                                      \
            return *this;                                                 \
        }
    DEF_OPERATOR(optionally)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_OPERATOR(std)
#    endif
#    if SROOK_HAS_BOOST_OPTIONAL
    optional<T, Payload>& operator=(boost::none_t) SROOK_NOEXCEPT_TRUE
    {
        reset();
        return *this;
    }
#    endif
#    undef DEF_OPERATOR

    template <class U = T>
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<optional<T>, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
            is_constructible<T, U>,
            type_traits::detail::Lnot<type_traits::detail::Land<is_scalar<T>, is_same<T, SROOK_DEDUCED_TYPENAME decay<U>::type> > >,
            is_assignable<T&, U> >::value,
        optional<T, Payload>&>::type
    operator=(U&& u)
    {
        if (Base_type::is_engaged())
            Base_type::get() = srook::forward<U>(u);
        else
            Base_type::construct(srook::forward<U>(u));
        return *this;
    }

#    define DEF_OPERATOR(X)                                                              \
        template <class U>                                                               \
        SROOK_DEDUCED_TYPENAME enable_if<                                                \
            type_traits::detail::Land<                                                   \
                type_traits::detail::Lnot<is_same<T, U> >,                               \
                is_constructible<T, const U&>,                                           \
                is_assignable<T&, U>,                                                    \
                type_traits::detail::Lnot<detail::converts_from_optional<T, U> >,        \
                type_traits::detail::Lnot<detail::assign_from_optional<T, U> > >::value, \
            optional<T, Payload>&>::type                                                 \
        operator=(const X::optional<U>& u)                                               \
        {                                                                                \
            if (u) {                                                                     \
                if (Base_type::is_engaged())                                             \
                    Base_type::get() = *u;                                               \
                else                                                                     \
                    construct(*u);                                                       \
            } else {                                                                     \
                reset();                                                                 \
            }                                                                            \
            return *this;                                                                \
        }
    DEF_OPERATOR(optionally)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_OPERATOR(std)
#    endif
#    if SROOK_HAS_BOOST_OPTIONAL
    DEF_OPERATOR(boost)
#    endif
#    undef DEF_OPERATOR

#    define DEF_OPERATOR(X)                                                              \
        template <class U>                                                               \
        SROOK_DEDUCED_TYPENAME enable_if<                                                \
            type_traits::detail::Land<                                                   \
                type_traits::detail::Lnot<is_same<T, U> >,                               \
                is_constructible<T, U>,                                                  \
                is_assignable<T&, U>,                                                    \
                type_traits::detail::Lnot<detail::converts_from_optional<T, U> >,        \
                type_traits::detail::Lnot<detail::assign_from_optional<T, U> > >::value, \
            optional<T, Payload>&>::type                                                 \
        operator=(X::optional<U>&& u)                                                    \
        {                                                                                \
            if (u) {                                                                     \
                if (Base_type::is_engaged())                                             \
                    Base_type::get() = srook::move(*u);                                  \
                else                                                                     \
                    construct(srook::move(*u));                                          \
            } else {                                                                     \
                reset();                                                                 \
            }                                                                            \
            return *this;                                                                \
        }
    DEF_OPERATOR(optionally)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_OPERATOR(std)
#    endif
#    if SROOK_HAS_BOOST_OPTIONAL
    DEF_OPERATOR(boost)
#    endif
#    undef DEF_OPERATOR

    template <class... Args>
    SROOK_DEDUCED_TYPENAME enable_if<is_constructible<T, Args&&...>::value, T&>::type
    emplace(Args&&... args)
    {
        reset();
        Base_type::construct(srook::forward<Args>(args)...);
        return Base_type::get();
    }

    template <class U, class... Args>
    SROOK_DEDUCED_TYPENAME enable_if<is_constructible<T, std::initializer_list<U>&, Args&&...>::value, T&>::type
    emplace(std::initializer_list<U> li, Args&&... args)
    {
        reset();
        Base_type::construct(li, srook::forward<Args>(args)...);
        return Base_type::get();
    }

    void swap(optional<T, Payload>& other)
    SROOK_MEMFN_NOEXCEPT((type_traits::detail::Land<is_nothrow_move_constructible<T>, is_nothrow_swappable<T> >::value))
    {
        using std::swap;

        if (Base_type::is_engaged() && other.is_engaged()) {
            swap(Base_type::get(), other.get());
        } else if (Base_type::is_engaged()) {
            other.construct(srook::move(Base_type::get()));
            Base_type::destruct();
        } else if (other.is_engaged()) {
            Base_type::construct(srook::move(other.get()));
            other.destruct();
        }
    }

#define DEF_SWAP(NAMESPACE)                                     \
    void swap(NAMESPACE::optional<T>& other)                    \
    {                                                           \
        using std::swap;                                        \
        if (Base_type::is_engaged() && bool(other)) {           \
            swap(Base_type::get(), other.value());              \
        } else if (Base_type::is_engaged()) {                   \
            other.emplace(srook::move(Base_type::get()));       \
            Base_type::destruct();                              \
        } else if (other) {                                     \
            Base_type::construct(srook::move(other.value()));   \
            other.reset();                                      \
        }                                                       \
    }

#ifdef SROOK_HAS_STD_OPTIONAL
    DEF_SWAP(std)
#endif
#ifdef SROOK_HAS_BOOST_OPTIONAL
    DEF_SWAP(boost)
#endif
#undef DEF_SWAP

    SROOK_CONSTEXPR const T* operator->() const { return srook::addressof(Base_type::get()); }
    T* operator->() { return srook::addressof(Base_type::get()); }
    SROOK_CONSTEXPR T& operator*() & { return Base_type::get(); }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_CONSTEXPR const T& operator*() const& { return Base_type::get(); }
    SROOK_CONSTEXPR T&& operator*() && { return srook::move(Base_type::get()); }
    SROOK_CONSTEXPR T&& operator*() const&& { return srook::move(Base_type::get()); }
#endif
    SROOK_CONSTEXPR SROOK_EXPLICIT operator bool() const SROOK_NOEXCEPT_TRUE { return Base_type::is_engaged(); }
    SROOK_CONSTEXPR bool has_value() const SROOK_NOEXCEPT_TRUE { return Base_type::is_engaged(); }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_CONSTEXPR const T& value() const&
    {
        return Base_type::is_engaged() ? Base_type::get() : (detail::throw_bad_optional_access(), Base_type::get());
    }
#endif
    SROOK_CONSTEXPR T& value() &
    {
        return Base_type::is_engaged() ? Base_type::get() : (detail::throw_bad_optional_access(), Base_type::get());
    }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_CONSTEXPR T&& value() &&
    {
        return Base_type::is_engaged() ? srook::move(Base_type::get()) : (detail::throw_bad_optional_access(), srook::move(Base_type::get()));
    }
    SROOK_CONSTEXPR const T& value() const&&
    {
        return Base_type::is_engaged() ? srook::move(Base_type::get()) : (detail::throw_bad_optional_access(), srook::move(Base_type::get()));
    }
#endif
    template <class U>
    SROOK_CONSTEXPR T value_or(U&& u) const&
    {
        SROOK_ST_ASSERT((is_copy_constructible<T>::value));
        SROOK_ST_ASSERT((is_convertible<U&&, T>::value));

        return Base_type::is_engaged() ? Base_type::get() : static_cast<T>(srook::forward<U>(u));
    }
    template <class U>
    T value_or(U&& u) &&
    {
        SROOK_ST_ASSERT((is_move_constructible<T>::value));
        SROOK_ST_ASSERT((is_convertible<U&&, T>::value));

        return Base_type::is_engaged() ? srook::move(Base_type::get()) : static_cast<T>(srook::forward<U>(u));
    }
    void reset() SROOK_MEMFN_NOEXCEPT(true) { Base_type::reset(); }

#    if 0 && SROOK_HAS_INCLUDE(<compare>) // C++20 feature
#        define DEF_COMP(NAMESPACE, NULLOP)                                                       \
            template <class U, template <class, bool, bool> class Payload>                        \
            SROOK_CONSTEXPR auto operator<=>(const NAMESPACE::optional<U, Payload>& rhs) const    \
            -> std::common_comparison_category_t<value_type, U>                                   \
            {                                                                                     \
                if (has_value() && rhs.has_value()) {                                             \
                    return std::compare_3way(**this, *rhs);                                       \
                } else {                                                                          \
                    return has_value() <=> rhs.has_value();                                       \
                }                                                                                 \
            }                                                                                     \
            template <class U>                                                                    \
            SROOK_CONSTEXPR auto operator<=>(const U& rhs) const                                  \
                ->std::common_comparison_category_t<value_type, U>                                \
            {                                                                                     \
                if (has_value()) {                                                                \
                    return compare_3way(**this, rhs);                                             \
                } else {                                                                          \
                    return std::strong_ordering::less;                                            \
                }                                                                                 \
            }                                                                                     \
            SROOK_CONSTEXPR std::strong_ordering operator<=>(NAMESPACE::NULLOP) const             \
            {                                                                                     \
                return has_value() ? std::strong_ordering::greater : std::strong_ordering::equal; \
            }
    DEF_COMP(optionally, nullopt_t)
#        if SROOK_HAS_STD_OPTIONAL
    DEF_COMP(std, nullopt_t)
#        endif
#        if SROOK_HAS_BOOST_OPTIONAL
    DEF_COMP(boost, none_t)
#        endif
#        undef DEF_COMP
#    endif

private:
    // extension
    //
    // optional for monad semantics
    // see also: https://goo.gl/EcV2Tf
    template <class F, 
    SROOK_REQUIRES(type_traits::detail::Lor<is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type>, is_optional<SROOK_DEDUCED_TYPENAME invoke_result<F, value_type>::type>>::value)>
    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME invoke_result<F, value_type>::type
    operator>>=(const optional& this_, F&& f) SROOK_NOEXCEPT(f(declval<value_type>()))
    {
        return this_ ? srook::forward<F>(f)(*this_) : nullopt;
    }
    
    template <class F, 
    SROOK_REQUIRES(type_traits::detail::Lor<is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type&&>, is_optional<SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type&&>::type>>::value)>
    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type&&>::type
    operator>>=(optional&& this_, F&& f) SROOK_NOEXCEPT(f(declval<value_type&&>()))
    {
        return this_ ? srook::forward<F>(f)(srook::move(*this_)) : nullopt;
    }

    // =<<
    template <class F, 
    SROOK_REQUIRES(type_traits::detail::Lor<is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type>, is_optional<SROOK_DEDUCED_TYPENAME invoke_result<F, value_type>::type>>::value)>
    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME invoke_result<F, value_type>::type
    operator<<=(F&& f, const optional& this_) SROOK_NOEXCEPT(f(declval<value_type>()))
    {
        return this_ >>= f;
    }

    template <class F, 
    SROOK_REQUIRES(type_traits::detail::Lor<is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type&&>, is_optional<SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type&&>::type>>::value)>
    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type&&>::type
    operator<<=(F&& f, optional&& this_) SROOK_NOEXCEPT(f(declval<value_type&&>()))
    {
        return this_ >>= f;
    }
    
    // >>
    template <class F, SROOK_REQUIRES(type_traits::detail::Lor<is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type>, is_optional<SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type>::type>>::value)>
    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR SROOK_DEDUCED_TYPENAME invoke_result<SROOK_DEDUCED_TYPENAME decay<F>::type>::type
    operator>>(const optional& this_, F&& f) SROOK_NOEXCEPT(f(declval<value_type>()))
    {
        return this_ ? srook::forward<F>(f)() : nullopt;
    }

    // |
    template <class U, SROOK_REQUIRES(is_same<SROOK_DEDUCED_TYPENAME optional::value_type, SROOK_DEDUCED_TYPENAME decay<U>::type>::value)>
    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR optional
    operator|(const optional& this_, U&& u) SROOK_NOEXCEPT(make_optional(this_.value_or(srook::forward<U>(u))))
    {
        return make_optional(this_.value_or(srook::forward<U>(u)));
    }
};

#    if !SROOK_HAS_INCLUDE(<compare>)
#        define DEF_OPERATORS(Y, NULLOP)                                                                             \
            template <class T, template <class, bool, bool> class Payload, class R>                                  \
            SROOK_CONSTEXPR auto operator==(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)              \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() == declval<R>()))>                                \
            {                                                                                                        \
                return static_cast<bool>(lhs) == static_cast<bool>(rhs) && (!lhs || *lhs == *rhs);                   \
            }                                                                                                        \
            template <class L, class T, template <class, bool, bool> class Payload>                                  \
            SROOK_CONSTEXPR auto operator==(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)              \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() == declval<T>()))>                                \
            {                                                                                                        \
                return operator==(rhs, lhs);                                                                         \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload, class R>                                  \
            SROOK_CONSTEXPR auto operator!=(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)              \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() != declval<R>()))>                                \
            {                                                                                                        \
                return static_cast<bool>(lhs) != static_cast<bool>(rhs) || (static_cast<bool>(lhs) && *lhs != *rhs); \
            }                                                                                                        \
            template <class L, class T, template <class, bool, bool> class Payload>                                  \
            SROOK_CONSTEXPR auto operator!=(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)              \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() != declval<T>()))>                                \
            {                                                                                                        \
                return operator!=(rhs, lhs);                                                                         \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload, class R>                                  \
            SROOK_CONSTEXPR auto operator<(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)               \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() < declval<R>()))>                                 \
            {                                                                                                        \
                return static_cast<bool>(rhs) && (!lhs || *lhs < *rhs);                                              \
            }                                                                                                        \
            template <class L, class T, template <class, bool, bool> class Payload>                                  \
            SROOK_CONSTEXPR auto operator<(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)               \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() < declval<T>()))>                                 \
            {                                                                                                        \
                return !operator<(rhs, lhs);                                                                         \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload, class R>                                  \
            SROOK_CONSTEXPR auto operator>(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)               \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() > declval<R>()))>                                 \
            {                                                                                                        \
                return static_cast<bool>(lhs) && (!rhs || *lhs > *rhs);                                              \
            }                                                                                                        \
            template <class L, class T, template <class, bool, bool> class Payload>                                  \
            SROOK_CONSTEXPR auto operator>(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)               \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() > declval<T>()))>                                 \
            {                                                                                                        \
                return !operator>(rhs, lhs);                                                                         \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload, class R>                                  \
            SROOK_CONSTEXPR auto operator<=(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)              \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() <= declval<R>()))>                                \
            {                                                                                                        \
                return !lhs || (static_cast<bool>(rhs) && *lhs <= *rhs);                                             \
            }                                                                                                        \
            template <class L, class T, template <class, bool, bool> class Payload>                                  \
            SROOK_CONSTEXPR auto operator<=(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)              \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() <= declval<T>()))>                                \
            {                                                                                                        \
                return !operator<=(rhs, lhs);                                                                        \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload, class R>                                  \
            SROOK_CONSTEXPR auto operator>=(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)              \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() >= declval<R>()))>                                \
            {                                                                                                        \
                return !rhs || (static_cast<bool>(lhs) && *lhs >= *rhs);                                             \
            }                                                                                                        \
            template <class L, class T, template <class, bool, bool> class Payload>                                  \
            SROOK_CONSTEXPR auto operator>=(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)              \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() >= declval<L>()))>                                \
            {                                                                                                        \
                return !operator>=(rhs, lhs);                                                                        \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator==(const optional<T, Payload>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE          \
            {                                                                                                        \
                return !lhs;                                                                                         \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator==(Y::NULLOP, const optional<T, Payload>& rhs) SROOK_NOEXCEPT_TRUE          \
            {                                                                                                        \
                return !rhs;                                                                                         \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator!=(const optional<T, Payload>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE          \
            {                                                                                                        \
                return static_cast<bool>(lhs);                                                                       \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator!=(Y::NULLOP, const optional<T, Payload>& rhs) SROOK_NOEXCEPT_TRUE          \
            {                                                                                                        \
                return static_cast<bool>(rhs);                                                                       \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator<(const optional<T, Payload>&, Y::NULLOP) SROOK_NOEXCEPT_TRUE               \
            {                                                                                                        \
                return false;                                                                                        \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator<(Y::NULLOP, const optional<T, Payload>& rhs) SROOK_NOEXCEPT_TRUE           \
            {                                                                                                        \
                return static_cast<bool>(rhs);                                                                       \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator>(const optional<T, Payload>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE           \
            {                                                                                                        \
                return static_cast<bool>(lhs);                                                                       \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator>(Y::NULLOP, const optional<T, Payload>&) SROOK_NOEXCEPT_TRUE               \
            {                                                                                                        \
                return false;                                                                                        \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator<=(const optional<T, Payload>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE          \
            {                                                                                                        \
                return !lhs;                                                                                         \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator<=(Y::NULLOP, const optional<T, Payload>&) SROOK_NOEXCEPT_TRUE              \
            {                                                                                                        \
                return true;                                                                                         \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator>=(const optional<T, Payload>&, Y::NULLOP) SROOK_NOEXCEPT_TRUE              \
            {                                                                                                        \
                return true;                                                                                         \
            }                                                                                                        \
            template <class T, template <class, bool, bool> class Payload>                                           \
            SROOK_CONSTEXPR bool operator>=(Y::NULLOP, const optional<T, Payload>& rhs) SROOK_NOEXCEPT_TRUE          \
            {                                                                                                        \
                return !rhs;                                                                                         \
            }
DEF_OPERATORS(optionally, nullopt_t)
#        if SROOK_HAS_STD_OPTIONAL
DEF_OPERATORS(std, nullopt_t)
#        endif
#        if SROOK_HAS_BOOST_OPTIONAL
#            undef DEF_OPERATORS
#            define DEF_OPERATORS(Y, NULLOP)                                                                             \
                template <class T, template <class, bool, bool> class Payload, class R>                                  \
                auto operator==(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)                              \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() == declval<R>()))>                                \
                {                                                                                                        \
                    return static_cast<bool>(lhs) == static_cast<bool>(rhs) && (!lhs || *lhs == *rhs);                   \
                }                                                                                                        \
                template <class L, class T, template <class, bool, bool> class Payload>                                  \
                auto operator==(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)                              \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() == declval<T>()))>                                \
                {                                                                                                        \
                    return operator==(rhs, lhs);                                                                         \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload, class R>                                  \
                auto operator!=(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)                              \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() != declval<R>()))>                                \
                {                                                                                                        \
                    return static_cast<bool>(lhs) != static_cast<bool>(rhs) || (static_cast<bool>(lhs) && *lhs != *rhs); \
                }                                                                                                        \
                template <class L, class T, template <class, bool, bool> class Payload>                                  \
                auto operator!=(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)                              \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() != declval<T>()))>                                \
                {                                                                                                        \
                    return operator!=(rhs, lhs);                                                                         \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload, class R>                                  \
                auto operator<(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)                               \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() < declval<R>()))>                                 \
                {                                                                                                        \
                    return static_cast<bool>(rhs) && (!lhs || *lhs < *rhs);                                              \
                }                                                                                                        \
                template <class L, class T, template <class, bool, bool> class Payload>                                  \
                auto operator<(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)                               \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() < declval<T>()))>                                 \
                {                                                                                                        \
                    return !operator<(rhs, lhs);                                                                         \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload, class R>                                  \
                auto operator>(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)                               \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() > declval<R>()))>                                 \
                {                                                                                                        \
                    return static_cast<bool>(lhs) && (!rhs || *lhs > *rhs);                                              \
                }                                                                                                        \
                template <class L, class T, template <class, bool, bool> class Payload>                                  \
                auto operator>(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)                               \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() > declval<T>()))>                                 \
                {                                                                                                        \
                    return !operator>(rhs, lhs);                                                                         \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload, class R>                                  \
                auto operator<=(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)                              \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() <= declval<R>()))>                                \
                {                                                                                                        \
                    return !lhs || (static_cast<bool>(rhs) && *lhs <= *rhs);                                             \
                }                                                                                                        \
                template <class L, class T, template <class, bool, bool> class Payload>                                  \
                auto operator<=(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)                              \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() <= declval<T>()))>                                \
                {                                                                                                        \
                    return !operator<=(rhs, lhs);                                                                        \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload, class R>                                  \
                auto operator>=(const optional<T, Payload>& lhs, const Y::optional<R>& rhs)                              \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() >= declval<R>()))>                                \
                {                                                                                                        \
                    return !rhs || (static_cast<bool>(lhs) && *lhs >= *rhs);                                             \
                }                                                                                                        \
                template <class L, class T, template <class, bool, bool> class Payload>                                  \
                auto operator>=(const Y::optional<L>& lhs, const optional<T, Payload>& rhs)                              \
                -> detail::optional_relop<SROOK_DECLTYPE((declval<T>() >= declval<L>()))>                                \
                {                                                                                                        \
                    return !operator>=(rhs, lhs);                                                                        \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator==(const optional<T, Payload>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE                          \
                {                                                                                                        \
                    return !lhs;                                                                                         \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator==(Y::NULLOP, const optional<T, Payload>& rhs) SROOK_NOEXCEPT_TRUE                          \
                {                                                                                                        \
                    return !rhs;                                                                                         \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator!=(const optional<T, Payload>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE                          \
                {                                                                                                        \
                    return static_cast<bool>(lhs);                                                                       \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator!=(Y::NULLOP, const optional<T, Payload>& rhs) SROOK_NOEXCEPT_TRUE                          \
                {                                                                                                        \
                    return static_cast<bool>(rhs);                                                                       \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator<(const optional<T, Payload>&, Y::NULLOP) SROOK_NOEXCEPT_TRUE                               \
                {                                                                                                        \
                    return false;                                                                                        \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator<(Y::NULLOP, const optional<T, Payload>& rhs) SROOK_NOEXCEPT_TRUE                           \
                {                                                                                                        \
                    return static_cast<bool>(rhs);                                                                       \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator>(const optional<T, Payload>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE                           \
                {                                                                                                        \
                    return static_cast<bool>(lhs);                                                                       \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator>(Y::NULLOP, const optional<T, Payload>&) SROOK_NOEXCEPT_TRUE                               \
                {                                                                                                        \
                    return false;                                                                                        \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator<=(const optional<T, Payload>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE                          \
                {                                                                                                        \
                    return !lhs;                                                                                         \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator<=(Y::NULLOP, const optional<T, Payload>&) SROOK_NOEXCEPT_TRUE                              \
                {                                                                                                        \
                    return true;                                                                                         \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator>=(const optional<T, Payload>&, Y::NULLOP) SROOK_NOEXCEPT_TRUE                              \
                {                                                                                                        \
                    return true;                                                                                         \
                }                                                                                                        \
                template <class T, template <class, bool, bool> class Payload>                                           \
                bool operator>=(Y::NULLOP, const optional<T, Payload>& rhs) SROOK_NOEXCEPT_TRUE                          \
                {                                                                                                        \
                    return !rhs;                                                                                         \
                }
DEF_OPERATORS(boost, none_t)
#        endif
#        undef DEF_OPERATORS

template <class T, template <class, bool, bool> class Payload, class R>
SROOK_CONSTEXPR auto operator==(const optional<T, Payload>& lhs, const R& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<T>() == declval<R>()))>
{
    return lhs && *lhs == rhs;
}

template <class L, class T, template <class, bool, bool> class Payload>
SROOK_CONSTEXPR auto operator==(const L& lhs, const optional<T, Payload>& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<L>() == declval<T>()))>
{
    return rhs && lhs == *rhs;
}

template <class T, template <class, bool, bool> class Payload, class R>
SROOK_CONSTEXPR auto operator!=(const optional<T, Payload>& lhs, const R& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<T>() != declval<R>()))>
{
    return !lhs || *lhs != rhs;
}

template <class L, class T, template <class, bool, bool> class Payload>
SROOK_CONSTEXPR auto operator!=(const L& lhs, const optional<T, Payload>& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<L>() != declval<T>()))>
{
    return !rhs || lhs != *rhs;
}

template <class T, template <class, bool, bool> class Payload, class R>
SROOK_CONSTEXPR auto operator<(const optional<T, Payload>& lhs, const R& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<T>() < declval<R>()))>
{
    return !lhs || *lhs < rhs;
}

template <class L, class T, template <class, bool, bool> class Payload>
SROOK_CONSTEXPR auto operator<(const L& lhs, const optional<T, Payload>& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<L>() < declval<T>()))>
{
    return rhs && lhs < *rhs;
}

template <class T, template <class, bool, bool> class Payload, class R>
SROOK_CONSTEXPR auto operator>(const optional<T, Payload>& lhs, const R& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<T>() > declval<R>()))>
{
    return lhs && *lhs > rhs;
}

template <class L, class T, template <class, bool, bool> class Payload>
SROOK_CONSTEXPR auto operator>(const L& lhs, const optional<T, Payload>& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<L>() > declval<T>()))>
{
    return !rhs || lhs > *rhs;
}

template <class T, template <class, bool, bool> class Payload, class R>
SROOK_CONSTEXPR auto operator<=(const optional<T, Payload>& lhs, const R& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<T>() <= declval<R>()))>
{
    return !lhs || *lhs <= rhs;
}

template <class L, class T, template <class, bool, bool> class Payload>
SROOK_CONSTEXPR auto operator<=(const L& lhs, const optional<T, Payload>& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<L>() <= declval<T>()))>
{
    return rhs && lhs <= *rhs;
}

template <class T, template <class, bool, bool> class Payload, class R>
SROOK_CONSTEXPR auto operator>=(const optional<T, Payload>& lhs, const R& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<T>() >= declval<R>()))>
{
    return lhs && *lhs >= rhs;
}

template <class L, class T, template <class, bool, bool> class Payload>
SROOK_CONSTEXPR auto operator>=(const L& lhs, const optional<T, Payload>& rhs)
-> detail::optional_relop<SROOK_DECLTYPE((declval<L>() >= declval<T>()))>
{
    return !rhs || lhs >= *rhs;
}
#    endif

#    define DEF_SWAP(X)                                                                                                                              \
        template <class T, template <class, bool, bool> class Payload, class R>                                                                      \
        SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME                                                                                                    \
        enable_if<type_traits::detail::Land<is_move_constructible<T>, is_swappable<T>, is_move_constructible<R>, is_swappable<R> >::value>::type     \
        swap(optional<T, Payload>& lhs, X::optional<R>& rhs)                                                                                         \
        SROOK_NOEXCEPT(lhs.swap(rhs))                                                                                                                \
        {                                                                                                                                            \
            lhs.swap(rhs);                                                                                                                           \
        }                                                                                                                                            \
        template <class L, class T, template <class, bool, bool> class Payload>                                                                      \
        SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME                                                                                                    \
        enable_if<type_traits::detail::Land<is_move_constructible<T>, is_swappable<T>, is_move_constructible<L>, is_swappable<L> >::value>::type     \
        swap(X::optional<L>& lhs, optional<T, Payload>& rhs)                                                                                         \
        SROOK_NOEXCEPT(swap(rhs, lhs))                                                                                                               \
        {                                                                                                                                            \
            swap(rhs, lhs);                                                                                                                          \
        }                                                                                                                                            \
        template <class T, template <class, bool, bool> class Payload, class R>                                                                      \
        SROOK_DEDUCED_TYPENAME                                                                                                                       \
        enable_if<                                                                                                                                   \
            type_traits::detail::Lor<                                                                                                                \
                type_traits::detail::Lnot<type_traits::detail::Land<is_move_constructible<T>, is_swappable<T> > >,                                   \
                type_traits::detail::Lnot<type_traits::detail::Land<is_move_constructible<R>, is_swappable<R> > > >::value                           \
        >::type                                                                                                                                      \
        swap(optional<T, Payload>&, X::optional<R>&) SROOK_EQ_DELETE                                                                                 \
        template <class L, class T, template <class, bool, bool> class Payload>                                                                      \
        SROOK_DEDUCED_TYPENAME                                                                                                                       \
        enable_if<                                                                                                                                   \
            type_traits::detail::Lor<                                                                                                                \
                type_traits::detail::Lnot<type_traits::detail::Land<is_move_constructible<T>, is_swappable<T> > >,                                   \
                type_traits::detail::Lnot<type_traits::detail::Land<is_move_constructible<L>, is_swappable<L> > > >::value                           \
        >::type                                                                                                                                      \
        swap(X::optional<L>&, optional<T, Payload>&) SROOK_EQ_DELETE
DEF_SWAP(optionally)
#    if SROOK_HAS_STD_OPTIONAL
DEF_SWAP(std)
#    endif
#    undef DEF_SWAP

template <class T>
SROOK_CONSTEXPR optional<SROOK_DEDUCED_TYPENAME decay<T>::type> make_optional(T&& t)
SROOK_NOEXCEPT(is_nothrow_constructible<T>::value)
{
    return optional<SROOK_DEDUCED_TYPENAME decay<T>::type>(srook::forward<T>(t));
}

template <class T, class... Args>
SROOK_CONSTEXPR optional<T> make_optional(Args&&... args)
SROOK_NOEXCEPT((is_nothrow_constructible<T, SROOK_DEDUCED_TYPENAME decay<Args>::type...>::value))
{
    return optional<T>(in_place, srook::forward<Args>(args)...);
}

template <class T, class U, class... Args>
SROOK_CONSTEXPR optional<T> make_optional(std::initializer_list<U> li, Args&&... args)
SROOK_NOEXCEPT((is_nothrow_constructible<T, U, SROOK_DEDUCED_TYPENAME decay<Args>::type...>::value))
{
    return optional<T>(in_place, li, srook::forward<Args>(args)...);
}

template <class T>
SROOK_CONSTEXPR optional<SROOK_DEDUCED_TYPENAME decay<T>::type, safe_optional_payload> make_safe_optional(T&& t)
SROOK_NOEXCEPT(is_nothrow_constructible<T>::value)
{
    return optional<SROOK_DEDUCED_TYPENAME decay<T>::type, safe_optional_payload>(srook::forward<T>(t));
}

template <class T, class... Args>
SROOK_CONSTEXPR optional<T, safe_optional_payload> make_safe_optional(Args&&... args)
SROOK_NOEXCEPT((is_nothrow_constructibleMTm SROOK_DEDUCED_TYPENAME decay<Args>::type...>::value))
{
    return optional<T, safe_optional_payload>(in_place, srook::forward<Args>(args)...);
}

template <class T, class U, class... Args>
SROOK_CONSTEXPR optional<T, safe_optional_payload> make_safe_optional(std::initializer_list<U> li, Args&&... args)
SROOK_NOEXCEPT((is_nothrow_constructible<T, U, SROOK_DEDUCED_TYPENAME decay<Args>::type...>::value))
{
    return optional<T, safe_optional_payload>(in_place, li, srook::forward<Args>(args)...);
}

template <class... Ts>
SROOK_CONSTEXPR std::tuple<srook::optional<SROOK_DEDUCED_TYPENAME decay<Ts>::type>...> make_optionals(Ts&&... ts)
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_constructible<Ts>...>::value)
{
    return std::make_tuple(srook::optionally::make_optional(srook::forward<Ts>(ts))...);
}

template <class... Ts>
SROOK_CONSTEXPR std::tuple<srook::optional<SROOK_DEDUCED_TYPENAME decay<Ts>::type, safe_optional_payload>...> make_safe_optionals(Ts&&... ts)
SROOK_NOEXCEPT(type_traits::detail::Land<is_nothrow_constructible<Ts>...>::value)
{
    return std::make_tuple(srook::optionally::make_safe_optional(srook::forward<Ts>(ts))...);
}

// TASK: specialize hash

SROOK_INLINE_NAMESPACE_END
} // namespace optionally

using optionally::swap;
using optionally::make_optional;
using optionally::make_safe_optional;
using optionally::make_optionals;
using optionally::make_safe_optionals;

} // namespace srook
#endif
#endif
