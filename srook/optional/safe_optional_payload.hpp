// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_OPTIONAL_SAFE_OPTIONAL_PAYLOAD_HPP
#define INCLUDED_SROOK_OPTIONAL_SAFE_OPTIONAL_PAYLOAD_HPP

#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <cassert>
#    include <new>
#    include <srook/config/attribute.hpp>
#    include <srook/memory/addressof.hpp>
#    include <srook/utility.hpp>
#    include <type_traits>

namespace srook {
namespace optionally {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <class T, bool, bool>
struct safe_optional_payload {
private:
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type Stored_type;

public:
    SROOK_CONSTEXPR safe_optional_payload() : empty_() {}

#    define DEF_CONSTRUCTOR(LIB)                                                                \
        template <class... Args>                                                                \
        SROOK_CONSTEXPR safe_optional_payload(LIB::in_place_t, Args&&... args)                  \
            : payload_(srook::forward<Args>(args)...), payload_ptr_(srook::addressof(payload_)) {}

    DEF_CONSTRUCTOR(srook)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    undef DEF_CONSTRUCTOR

    template <class U, class... Args>
    SROOK_CONSTEXPR safe_optional_payload(std::initializer_list<U> li, Args&&... args)
        : payload_(li, srook::forward<Args>(args)...), payload_ptr_(srook::addressof(payload_)) {}

    template <class U>
    struct ctor_tag SROOK_FINAL : private enable_copy_move<false, false, false, false> {};

    SROOK_CONSTEXPR safe_optional_payload(ctor_tag<bool>, const T& other)
        : payload_(other), payload_ptr_(srook::addressof(payload_)) {}
    SROOK_CONSTEXPR safe_optional_payload(ctor_tag<void>)
        : empty_() {}
    SROOK_CONSTEXPR safe_optional_payload(ctor_tag<bool>, T&& other)
        : payload_(srook::move(other)), payload_ptr_(srook::addressof(payload_)) {}

    SROOK_CONSTEXPR safe_optional_payload(bool is_engaged, const safe_optional_payload& other)
        : safe_optional_payload(is_engaged ? safe_optional_payload(ctor_tag<bool>{}, other.payload_) : safe_optional_payload(ctor_tag<void>{})) {}
    SROOK_CONSTEXPR safe_optional_payload(bool is_engaged, safe_optional_payload&& other)
        : safe_optional_payload(is_engaged ? safe_optional_payload(ctor_tag<bool>{}, srook::move(other.payload_)) : safe_optional_payload(ctor_tag<void>{})) {}

public:
    ~safe_optional_payload() SROOK_MEMFN_NOEXCEPT(is_nothrow_destructible<Stored_type>::value)
    {
        if (payload_ptr_) payload_ptr_->~Stored_type();
    }
    template <class... Args>
    void construct(Args&&... args)
    SROOK_NOEXCEPT((is_nothrow_constructible<Stored_type, Args...>::value))
    {
        payload_ptr_ = ::new (static_cast<void*>(srook::addressof(payload_))) Stored_type(srook::forward<Args>(args)...);
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool load_engaged() const SROOK_NOEXCEPT_TRUE { return payload_ptr_; }
    SROOK_FORCE_INLINE void store_engaged(bool b) SROOK_NOEXCEPT_TRUE
    {
        if (!b)
            payload_ptr_ = SROOK_NULLPTR;
        else
            payload_ptr_ = srook::addressof(payload_);
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const Stored_type& load_payload() const SROOK_NOEXCEPT_TRUE
    {
        return *payload_ptr_;
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR Stored_type& load_payload() SROOK_NOEXCEPT_TRUE
    {
        return *payload_ptr_;
    }

protected:
    struct Empty_byte SROOK_FINAL {};
    union {
        Empty_byte empty_;
        Stored_type payload_;
    };
    // 3.8 Object lifetime [basic.life] cause UB if Stored_type has const or reference type member variable.
    // This pointer is neccessary in order to prevent the problem.
    Stored_type* payload_ptr_ = SROOK_NULLPTR;
};

template <class T>
struct safe_optional_payload<T, false, true> {
private:
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type Stored_type;

public:
    SROOK_CONSTEXPR safe_optional_payload() : empty_() {}
#    define DEF_CONSTRUCTOR(X)                                               \
        template <class... Args>                                             \
        SROOK_CONSTEXPR safe_optional_payload(X::in_place_t, Args&&... args) \
            : payload_(srook::forward<Args>(args)...), payload_ptr_(true) {}
    DEF_CONSTRUCTOR(srook)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    undef DEF_CONSTRUCTOR

    template <class U, class... Args>
    SROOK_CONSTEXPR safe_optional_payload(std::initializer_list<U> li, Args&&... args)
        : payload_(li, srook::forward<Args>(args)...), payload_ptr_(srook::addressof(payload_)) {}
    SROOK_CONSTEXPR safe_optional_payload(bool, const safe_optional_payload& other)
        : safe_optional_payload(other) {}
    SROOK_CONSTEXPR safe_optional_payload(bool, safe_optional_payload&& other)
        : safe_optional_payload(srook::move(other)) {}
    SROOK_CONSTEXPR safe_optional_payload(const safe_optional_payload& other)
    {
        if (other.load_engaged()) construct(other.payload_);
    }
    SROOK_CONSTEXPR safe_optional_payload(safe_optional_payload&& other)
    {
        if (other.load_engaged()) construct(srook::move(other.payload_));
    }

    // trivially destructible...

    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<Stored_type, Args...>::value))
    {
        payload_ptr_ = ::new (static_cast<void*>(srook::addressof(payload_))) Stored_type(srook::forward<Args>(args)...);
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool load_engaged() const SROOK_NOEXCEPT_TRUE { return payload_ptr_; }
    SROOK_FORCE_INLINE void store_engaged(bool b) SROOK_NOEXCEPT_TRUE
    {
        if (!b)
            payload_ptr_ = SROOK_NULLPTR;
        else
            payload_ptr_ = srook::addressof(payload_);
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const Stored_type& load_payload() const SROOK_NOEXCEPT_TRUE
    {
        return *payload_ptr_;
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR Stored_type& load_payload() SROOK_NOEXCEPT_TRUE
    {
        return *payload_ptr_;
    }

protected:
    struct Empty_byte SROOK_FINAL {};
    union {
        Empty_byte empty_;
        Stored_type payload_;
    };
    // 3.8 Object lifetime [basic.life] cause UB if Stored_type has const or reference type member variable.
    // This pointer is neccessary in order to prevent the problem.
    Stored_type* payload_ptr_ = SROOK_NULLPTR;
};

template <class T>
struct safe_optional_payload<T, false, false> {
private:
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type Stored_type;

public:
    SROOK_CONSTEXPR safe_optional_payload() : empty_() {}
#    define DEF_CONSTRUCTOR(X)                                                                    \
        template <class... Args>                                                                  \
        SROOK_CONSTEXPR safe_optional_payload(X::in_place_t, Args&&... args)                      \
            : payload_(srook::forward<Args>(args)...), payload_ptr_(srook::addressof(payload_)) {}
    DEF_CONSTRUCTOR(srook)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_CONSTRUCTOR(std)
#    endif
#    undef DEF_CONSTRUCTOR

    template <class U, class... Args>
    SROOK_CONSTEXPR safe_optional_payload(std::initializer_list<U> li, Args&&... args)
        : payload_(li, srook::forward<Args>(args)...), payload_ptr_(srook::addressof(payload_)) {}
    SROOK_CONSTEXPR safe_optional_payload(bool, const safe_optional_payload& other)
        : safe_optional_payload(other) {}
    SROOK_CONSTEXPR safe_optional_payload(bool, safe_optional_payload&& other)
        : safe_optional_payload(srook::move(other)) {}
    SROOK_CONSTEXPR safe_optional_payload(const safe_optional_payload& other)
    {
        if (other.load_engaged()) construct(other.payload_);
    }
    SROOK_CONSTEXPR safe_optional_payload(safe_optional_payload&& other)
    {
        if (other.load_engaged()) construct(srook::move(other.payload_));
    }

    ~safe_optional_payload() SROOK_MEMFN_NOEXCEPT(is_nothrow_destructible<Stored_type>::value)
    {
        if (payload_ptr_) payload_ptr_->~Stored_type();
    }

    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<Stored_type, Args...>::value))
    {
        payload_ptr_ = ::new (static_cast<void*>(srook::addressof(payload_))) Stored_type(srook::forward<Args>(args)...);
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool load_engaged() const SROOK_NOEXCEPT_TRUE { return payload_ptr_; }
    SROOK_FORCE_INLINE void store_engaged(bool b) SROOK_NOEXCEPT_TRUE
    {
        if (!b)
            payload_ptr_ = SROOK_NULLPTR;
        else
            payload_ptr_ = srook::addressof(payload_);
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR const Stored_type& load_payload() const SROOK_NOEXCEPT_TRUE
    {
        return *payload_ptr_;
    }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR Stored_type& load_payload() SROOK_NOEXCEPT_TRUE
    {
        return *payload_ptr_;
    }

protected:
    struct Empty_byte SROOK_FINAL {};
    union {
        Empty_byte empty_;
        Stored_type payload_;
    };
    // 3.8 Object lifetime [basic.life] cause UB if Stored_type has const or reference type member variable.
    // This pointer is neccessary in order to prevent the problem.
    Stored_type* payload_ptr_ = SROOK_NULLPTR;
};

} // namespace detail

using detail::safe_optional_payload;

SROOK_INLINE_NAMESPACE_END
} // namespace optionally
} // namespace srook
#    endif
#endif
