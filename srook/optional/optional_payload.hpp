// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_OPTIONAL_OPTIONAL_PAYLOAD_HPP
#define INCLUDED_SROOK_OPTIONAL_OPTIONAL_PAYLOAD_HPP
#include <exception>
#include <initializer_list>
#include <srook/config/feature.hpp>
#include <srook/memory/addressof.hpp>
#include <srook/optional/nullopt.hpp>
#include <srook/optional/exception.hpp>
#include <srook/type_traits/is_swappable.hpp>
#include <srook/type_traits/is_nothrow_constructible.hpp>
#include <srook/type_traits/is_nothrow_destructible.hpp>
#include <srook/type_traits/is_copy_constructible.hpp>
#include <srook/type_traits/is_copy_assignable.hpp>
#include <srook/type_traits/is_convertible.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/utility/enable_copy_move.hpp>
#include <srook/utility/in_place.hpp>
#include <srook/utility/move.hpp>
#include <srook/utility/forward.hpp>
#include <type_traits>

namespace srook {
namespace optionally {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T, bool, bool>
struct optional_payload {
protected:
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type Stored_type;

public:
    SROOK_CONSTEXPR optional_payload() : empty_() {}

#    define DEF_CONSTRUCTOR(LIB)                                          \
        template <class... Args>                                          \
        SROOK_CONSTEXPR optional_payload(LIB::in_place_t, Args&&... args) \
            : payload_(srook::forward<Args>(args)...), engaged_(true) {}

    DEF_CONSTRUCTOR(srook)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    undef DEF_CONSTRUCTOR

    template <class U, class... Args>
    SROOK_CONSTEXPR optional_payload(std::initializer_list<U> li, Args&&... args)
        : payload_(li, srook::forward<Args>(args)...), engaged_(true) {}

    template <class U>
    struct ctor_tag SROOK_FINAL : private enable_copy_move<false, false, false, false> {};

    SROOK_CONSTEXPR optional_payload(ctor_tag<bool>, const T& other)
        : payload_(other), engaged_(true) {}
    SROOK_CONSTEXPR optional_payload(ctor_tag<void>)
        : empty_() {}
    SROOK_CONSTEXPR optional_payload(ctor_tag<bool>, T&& other)
        : payload_(srook::move(other)), engaged_(true) {}

    SROOK_CONSTEXPR optional_payload(bool is_engaged, const optional_payload& other)
        : optional_payload(is_engaged ? optional_payload(ctor_tag<bool>{}, other.payload_) : optional_payload(ctor_tag<void>{})) {}
    SROOK_CONSTEXPR optional_payload(bool is_engaged, optional_payload&& other)
        : optional_payload(is_engaged ? optional_payload(ctor_tag<bool>{}, srook::move(other.payload_)) : optional_payload(ctor_tag<void>{})) {}

    ~optional_payload() SROOK_MEMFN_NOEXCEPT(is_nothrow_destructible<Stored_type>::value)
    {
        if (engaged_) payload_.~Stored_type();
    }

    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<Stored_type, Args...>::value))
    {
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        ::new (static_cast<void*>(srook::addressof(payload_))) Stored_type(srook::forward<Args>(args)...);
        engaged_ = true;
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool load_engaged() const SROOK_NOEXCEPT_TRUE
    {
        return engaged_;
    }
    SROOK_FORCE_INLINE void store_engaged(bool b) SROOK_NOEXCEPT_TRUE
    {
        engaged_ = srook::move(b);
    }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const Stored_type& load_payload() const SROOK_NOEXCEPT_TRUE
    {
        return payload_;
    }
#endif
    SROOK_FORCE_INLINE SROOK_CONSTEXPR Stored_type& load_payload() SROOK_NOEXCEPT_TRUE
    {
        return payload_;
    }

protected:
    struct Empty_byte SROOK_FINAL {};
    union {
        Empty_byte empty_;
        Stored_type payload_;
    };
    bool engaged_ = false;
};

template <class T>
struct optional_payload<T, false, true> {
protected:
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type Stored_type;

public:
    SROOK_CONSTEXPR optional_payload() : empty_() {}
#    define DEF_CONSTRUCTOR(X)                                          \
        template <class... Args>                                        \
        SROOK_CONSTEXPR optional_payload(X::in_place_t, Args&&... args) \
            : payload_(srook::forward<Args>(args)...), engaged_(true) {}
    DEF_CONSTRUCTOR(srook)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    undef DEF_CONSTRUCTOR

    template <class U, class... Args>
    SROOK_CONSTEXPR optional_payload(std::initializer_list<U> li, Args&&... args)
        : payload_(li, srook::forward<Args>(args)...), engaged_(true) {}
    SROOK_CONSTEXPR optional_payload(bool, const optional_payload& other)
        : optional_payload(other) {}
    SROOK_CONSTEXPR optional_payload(bool, optional_payload&& other)
        : optional_payload(srook::move(other)) {}
    SROOK_CXX14_CONSTEXPR optional_payload(const optional_payload& other)
    {
        if (other.engaged_) construct(other.payload_);
    }
    SROOK_CXX14_CONSTEXPR optional_payload(optional_payload&& other)
    {
        if (other.engaged_) construct(srook::move(other.payload_));
    }

    // trivially destructible...

    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<Stored_type, Args...>::value))
    {
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        ::new (static_cast<void*>(srook::addressof(payload_))) Stored_type(srook::forward<Args>(args)...);
        engaged_ = true;
    }

    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool load_engaged() const SROOK_NOEXCEPT_TRUE
    {
        return engaged_;
    }
    SROOK_FORCE_INLINE void store_engaged(bool b) SROOK_NOEXCEPT_TRUE
    {
        engaged_ = srook::move(b);
    }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const Stored_type& load_payload() const SROOK_NOEXCEPT_TRUE
    {
        return payload_;
    }
#endif
    SROOK_FORCE_INLINE SROOK_CONSTEXPR Stored_type& load_payload() SROOK_NOEXCEPT_TRUE
    {
        return payload_;
    }

protected:
    bool engaged_ = false;
    struct Empty_byte SROOK_FINAL {};
    union {
        Empty_byte empty_;
        Stored_type payload_;
    };
};

template <class T>
struct optional_payload<T, false, false> {
protected:
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type Stored_type;

public:
    SROOK_CONSTEXPR optional_payload() : empty_() {}
#    define DEF_CONSTRUCTOR(X)                                          \
        template <class... Args>                                        \
        SROOK_CONSTEXPR optional_payload(X::in_place_t, Args&&... args) \
            : payload_(srook::forward<Args>(args)...), engaged_(true) {}
    DEF_CONSTRUCTOR(srook)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    undef DEF_CONSTRUCTOR

    template <class U, class... Args>
    SROOK_CONSTEXPR optional_payload(std::initializer_list<U> li, Args&&... args)
        : payload_(li, srook::forward<Args>(args)...), engaged_(true) {}
    SROOK_CONSTEXPR optional_payload(bool, const optional_payload& other)
        : optional_payload(other) {}
    SROOK_CONSTEXPR optional_payload(bool, optional_payload&& other)
        : optional_payload(srook::move(other)) {}
    SROOK_CXX14_CONSTEXPR optional_payload(const optional_payload& other)
    {
        if (other.engaged_) construct(other.payload_);
    }
    SROOK_CXX14_CONSTEXPR optional_payload(optional_payload&& other)
    {
        if (other.engaged_) construct(srook::move(other.payload_));
    }

    ~optional_payload() SROOK_MEMFN_NOEXCEPT(is_nothrow_destructible<Stored_type>::value)
    {
        if (engaged_) payload_.~Stored_type();
    }
    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<Stored_type, Args...>::value))
    {
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        ::new (static_cast<void*>(srook::addressof(payload_))) Stored_type(srook::forward<Args>(args)...);
        engaged_ = true;
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool load_engaged() const SROOK_NOEXCEPT_TRUE
    {
        return engaged_;
    }
    SROOK_FORCE_INLINE void store_engaged(bool b) SROOK_NOEXCEPT_TRUE
    {
        engaged_ = srook::move(b);
    }
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const Stored_type& load_payload() const SROOK_NOEXCEPT_TRUE
    {
        return payload_;
    }
#endif
    SROOK_FORCE_INLINE SROOK_CONSTEXPR Stored_type& load_payload() SROOK_NOEXCEPT_TRUE
    {
        return payload_;
    }

protected:
    struct Empty_byte SROOK_FINAL {};
    union {
        Empty_byte empty_;
        Stored_type payload_;
    };
    bool engaged_ = false;
};

} // namespace detail

using detail::optional_payload;

SROOK_INLINE_NAMESPACE_END
} // namespace optionally
} // namespace srook
#endif
