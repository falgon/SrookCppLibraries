// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_OPTIONAL_BASE_HPP
#define INCLUDED_SROOK_OPTIONAL_BASE_HPP
#include <srook/optional/optional.h>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <initializer_list>
#include <srook/type_traits.hpp>
#include <srook/optional/safe_optional_payload.hpp>
#include <srook/optional/optional_payload.hpp>

namespace srook {
namespace optionally {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T, template <class, bool, bool> class Payload>
class optional_base {
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type Stored_type;
    typedef Payload<
        T,
        type_traits::detail::Land<
            std::is_trivially_copy_constructible<T>,
            std::is_trivially_move_constructible<T> >::value,
        std::is_trivially_destructible<T>::value>
        payload_type;

public:
    SROOK_CONSTEXPR optional_base() SROOK_NOEXCEPT_TRUE {}
    SROOK_CONSTEXPR optional_base(nullopt_t) SROOK_NOEXCEPT_TRUE {}

#    define DEF_CONSTRUCTOR(X)                                                                                              \
        template <class... Args, SROOK_REQUIRES(is_constructible<T, Args&&...>::value)>                                     \
        SROOK_CONSTEXPR explicit optional_base(X::in_place_t, Args&&... args)                                               \
            : payload_(X::in_place, srook::forward<Args>(args)...) {}                                                       \
        template <class U, class... Args, SROOK_REQUIRES(is_constructible<T, std::initializer_list<U>&, Args&&...>::value)> \
        SROOK_CONSTEXPR explicit optional_base(X::in_place_t, std::initializer_list<U> li, Args&&... args)                  \
            : payload_(X::in_place, li, srook::forward<Args>(args)...) {}

    DEF_CONSTRUCTOR(srook)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    undef DEF_CONSTRUCTOR

    SROOK_CONSTEXPR optional_base(const optional_base& other)
        : payload_(other.payload_.load_engaged(), other.payload_) {}
    SROOK_CONSTEXPR optional_base(optional_base&& other)
        SROOK_NOEXCEPT(is_nothrow_constructible<T>::value)
        : payload_(other.payload_.load_engaged(), srook::move(other.payload_)) {}
    optional_base& operator=(const optional_base& other)
    {
        if (payload_.load_engaged() && other.payload_.load_engaged()) {
            get() = other.get();
        } else {
            if (other.payload_.load_engaged()) {
                construct(other.get());
            } else {
                reset();
            }
        }
        return *this;
    }
    optional_base& operator=(optional_base&& other)
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_move_constructible<T>, is_nothrow_assignable<T> >::value))
    {
        if (payload_.load_engaged() && other.payload_.load_engaged()) {
            get() = srook::move(other.get());
        } else {
            if (other.payload_.load_engaged()) {
                construct(srook::move(other.get()));
            } else {
                reset();
            }
        }
        return *this;
    }

protected:
    SROOK_CONSTEXPR bool is_engaged() const SROOK_NOEXCEPT_TRUE
    {
        return payload_.load_engaged();
    }
    SROOK_CONSTEXPR T& get() SROOK_NOEXCEPT_TRUE
    {
        assert(is_engaged());
        return payload_.load_payload();
    }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_CONSTEXPR const T& get() const SROOK_NOEXCEPT_TRUE
    {
        assert(is_engaged());
        return payload_.load_payload();
    }
#endif
    template <class... Args>
    void construct(Args&&... args)
    SROOK_NOEXCEPT((is_nothrow_constructible<Stored_type, Args...>::value))
    {
        payload_.construct(srook::forward<Args>(args)...);
    }
    void destruct()
    SROOK_NOEXCEPT((is_nothrow_destructible<Stored_type>::value))
    {
        payload_.store_engaged(false);
        payload_.load_payload().~Stored_type();
    }
    void reset()
    SROOK_NOEXCEPT(is_nothrow_destructible<Stored_type>::value)
    {
        if (payload_.load_engaged()) destruct();
    }

private:
    payload_type payload_;
};

template <class T, class U>
using converts_from_optional = type_traits::detail::Lor<
    is_constructible<T, const optional<U>&>,
    is_constructible<T, optional<U>&>,
    is_constructible<T, const optional<U>&&>,
    is_constructible<T, optional<U>&&>,
    is_convertible<const optional<U>&, T>,
    is_convertible<optional<U>&, T>,
    is_convertible<const optional<U>&&, T>,
    is_convertible<optional<U>&&, T> >;

template <class T, class U>
using assign_from_optional = type_traits::detail::Lor<
    is_assignable<T&, const optional<U>&>,
    is_assignable<T&, optional<U>&>,
    is_assignable<T&, const optional<U>&&>,
    is_assignable<T&, optional<U>&&> >;

template <class T>
using optional_relop = SROOK_DEDUCED_TYPENAME enable_if<is_convertible<T, bool>::value, bool>::type;

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace optionally
} // namespace srook
#endif
#endif
