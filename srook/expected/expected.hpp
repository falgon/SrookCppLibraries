// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_EXPECTED_EXPECTED_HPP
#define INCLUDED_SROOK_EXPECTED_EXPECTED_HPP

#include <srook/optional/optional_payload.hpp>
#include <srook/optional/safe_optional_payload.hpp>
#include <srook/functional/invoke.hpp>
#include <srook/expected/unexpected.hpp>
#include <stdexcept>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

namespace srook {
namespace exception {
SROOK_INLINE_NAMESPACE(v1)

class bad_expected_access : public std::exception {
public:
    bad_expected_access() SROOK_DEFAULT

    virtual const char* what() const
    SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE
    {
        return "bad expected access";
    }
    virtual ~bad_expected_access() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
};

struct set_error_t SROOK_FINAL { SROOK_CONSTEXPR set_error_t() SROOK_DEFAULT };
struct set_value_t SROOK_FINAL { SROOK_CONSTEXPR set_value_t() SROOK_DEFAULT };
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR set_error_t set_error{};
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR set_value_t set_value{};

namespace detail {

SROOK_FORCE_INLINE SROOK_NORETURN void throw_bad_expected_access() { SROOK_THROW bad_expected_access(); }

template <class ErrType>
SROOK_FORCE_INLINE SROOK_NORETURN SROOK_DEDUCED_TYPENAME 
enable_if<type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME decay<ErrType>::type, std::exception_ptr>>::value>::type
throw_expected_error(ErrType&& err) { SROOK_THROW err; }

SROOK_FORCE_INLINE SROOK_NORETURN void throw_expected_error(std::exception_ptr eptr) { std::rethrow_exception(eptr); }

template <class, class, bool, bool, template <class, bool, bool> class> 
class expected_payload;

template <class T, class ErrType, bool is_tcc, bool is_tmc>
class expected_payload<T, ErrType, is_tcc, is_tmc, srook::optionally::optional_payload> 
    : public srook::optionally::optional_payload<T, is_tcc, is_tmc> {
    typedef SROOK_DEDUCED_TYPENAME srook::optionally::optional_payload<T, is_tcc, is_tmc> base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::Stored_type stored_value_type;
    typedef SROOK_DEDUCED_TYPENAME remove_const<ErrType>::type error_type;
    template <class U>
    struct ctor_tag {};

    SROOK_CONSTEXPR expected_payload(ctor_tag<bool>, const expected_payload& other)
        : base_type(other), exempty_() {}
    SROOK_CONSTEXPR expected_payload(ctor_tag<bool>, expected_payload&& other)
        : base_type(srook::move(other)), exempty_() {}

    SROOK_CONSTEXPR expected_payload(ctor_tag<char>, const expected_payload& other)
        : err_(other.err_), error_engaged_(true) {}
    SROOK_CONSTEXPR expected_payload(ctor_tag<char>, expected_payload&& other)
        : err_(srook::move(other.err_)), error_engaged_(true) {}

    SROOK_CONSTEXPR expected_payload(ctor_tag<void>)
        : exempty_() {}

    template <class... Ts>
    using stored_constructible = type_traits::detail::Land<is_constructible<stored_value_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using error_constructible = type_traits::detail::Land<is_constructible<error_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using not_tags = 
        type_traits::detail::Land<
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_value_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_error_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>
         >;
public:
    SROOK_CONSTEXPR expected_payload() : exempty_() {}

    ~expected_payload()
    SROOK_MEMFN_NOEXCEPT((type_traits::detail::Land<is_nothrow_destructible<stored_value_type>, is_nothrow_destructible<error_type>>::value))
    {
        if (load_error_engaged()) err_.~error_type();
    }

    template <class... Ts, SROOK_REQUIRES(stored_constructible<Ts...>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, srook::exception::set_value_t, Ts&&... ts) 
        : base_type(srook::in_place, srook::forward<Ts>(ts)...), exempty_() {}

    template <class... Us, SROOK_REQUIRES(error_constructible<Us...>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, srook::exception::set_error_t, Us&&... us)
        : base_type(), err_(srook::forward<Us>(us)...), error_engaged_(true) {}
        
    template <class... Ts, SROOK_REQUIRES(type_traits::detail::Land<stored_constructible<Ts...>, type_traits::detail::Lnot<error_constructible<Ts...>>, not_tags<Ts...>>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, Ts&&... ts)
        : base_type(srook::in_place, srook::forward<Ts>(ts)...), exempty_() {}
    
    template <class... Us, SROOK_REQUIRES(type_traits::detail::Land<error_constructible<Us...>, type_traits::detail::Lnot<stored_constructible<Us...>>, not_tags<Us...>>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, Us&&... us)
        : base_type(), err_(srook::forward<Us>(us)...), error_engaged_(true) {}

    template <
        class U, 
        class... Ts, 
        SROOK_REQUIRES(
            type_traits::detail::Land<
                is_constructible<stored_value_type, std::initializer_list<U>, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>,
                type_traits::detail::Lnot<error_constructible<Ts...>>,
                not_tags<U, Ts...>
            >::value
        )
    >
    SROOK_CONSTEXPR expected_payload(std::initializer_list<U> li, Ts&&... ts)
        : base_type(li, srook::forward<Ts>(ts)...), exempty_() {}

    template <
        class U,
        class... Ts,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                is_constructible<error_type, std::initializer_list<U>, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>,
                type_traits::detail::Lnot<stored_constructible<Ts...>>,
                not_tags<U, Ts...>
            >::value
        )
    >
    SROOK_CONSTEXPR expected_payload(std::initializer_list<U> li, Ts&&... ts)
        : base_type(), err_(li, srook::forward<Ts>(ts)...) {}

    SROOK_CONSTEXPR expected_payload(bool is_engaged, bool is_error_engaged, const expected_payload& other)
        : expected_payload(is_engaged ? expected_payload(ctor_tag<bool>{}, other) : is_error_engaged ? expected_payload(ctor_tag<char>{}, other) : expected_payload(ctor_tag<void>{})) {}

    SROOK_CONSTEXPR expected_payload(bool is_engaged, bool is_error_engaged, expected_payload&& other)
        : expected_payload(is_engaged ? expected_payload(ctor_tag<bool>{}, srook::move(other)) : is_error_engaged ? expected_payload(ctor_tag<char>{}, srook::move(other)) : expected_payload(ctor_tag<void>{})) {}
    
    void reset() 
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_destructible<stored_value_type>, is_nothrow_destructible<error_type>>::value))
    {
        if (this->load_engaged()) {
            this->payload_.~stored_value_type();
            this->store_engaged(false);
        } else if (load_error()) {
            err_.~error_type();
            store_error_engaged(false);
        }
    }

    template <class... Args>
    void construct_err(Args&&... args) 
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<error_type, Args...>::value))
    {
        if (this->load_engaged()) {
            this->payload_.~stored_value_type();
            this->engaged_ = false;
        }
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        :: new (static_cast<void*>(srook::addressof(err_))) error_type(srook::forward<Args>(args)...);
        error_engaged_ = true;
    }

    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<stored_value_type, Args...>::value))
    {
        if (error_engaged_) {
            err_.~error_type();
            error_engaged_ = false;
        }
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        base_type::construct(srook::forward<Args>(args)...);
    }

    const error_type& load_error() const SROOK_NOEXCEPT_TRUE { return err_; }
    error_type& load_error() SROOK_NOEXCEPT_TRUE { return err_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool load_error_engaged() const { return error_engaged_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR void store_error_engaged(bool x) { error_engaged_ = srook::move(x); }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool any_engaged() const { return this->engaged_ || error_engaged_; }
private:
    union {
        SROOK_DEDUCED_TYPENAME base_type::Empty_byte exempty_;
        error_type err_;
    };
    bool error_engaged_ = false;
};

template <class T, class ErrType>
class expected_payload<T, ErrType, false, true, srook::optionally::optional_payload>
    : public srook::optionally::optional_payload<T, false, true> {
    typedef SROOK_DEDUCED_TYPENAME srook::optionally::optional_payload<T, false, true> base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::Stored_type stored_value_type;
    typedef SROOK_DEDUCED_TYPENAME remove_const<ErrType>::type error_type;

    template <class... Ts>
    using stored_constructible = type_traits::detail::Land<is_constructible<stored_value_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using error_constructible = type_traits::detail::Land<is_constructible<error_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using not_tags = 
        type_traits::detail::Land<
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_value_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_error_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>
         >;
public:
    SROOK_CONSTEXPR expected_payload() : exempty_() {}
    
    template <class... Ts, SROOK_REQUIRES(stored_constructible<Ts...>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, srook::exception::set_value_t, Ts&&... ts) 
        : base_type(srook::in_place, srook::forward<Ts>(ts)...), exempty_() {}

    template <class... Us, SROOK_REQUIRES(error_constructible<Us...>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, srook::exception::set_error_t, Us&&... us)
        : base_type(), err_(srook::forward<Us>(us)...), error_engaged_(true) {}
        
    template <class... Ts, SROOK_REQUIRES(type_traits::detail::Land<stored_constructible<Ts...>, type_traits::detail::Lnot<error_constructible<Ts...>>, not_tags<Ts...>>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, Ts&&... ts)
        : base_type(srook::in_place, srook::forward<Ts>(ts)...), exempty_() {}
    
    template <class... Us, SROOK_REQUIRES(type_traits::detail::Land<error_constructible<Us...>, type_traits::detail::Lnot<stored_constructible<Us...>>, not_tags<Us...>>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, Us&&... us)
        : base_type(), err_(srook::forward<Us>(us)...), error_engaged_(true) {}

    template <
        class U, 
        class... Ts, 
        SROOK_REQUIRES(
            type_traits::detail::Land<
                is_constructible<stored_value_type, std::initializer_list<U>, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>,
                type_traits::detail::Lnot<error_constructible<Ts...>>,
                not_tags<U, Ts...>
            >::value
        )
    >
    SROOK_CONSTEXPR expected_payload(std::initializer_list<U> li, Ts&&... ts)
        : base_type(li, srook::forward<Ts>(ts)...), exempty_() {}

    template <
        class U,
        class... Ts,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                is_constructible<error_type, std::initializer_list<U>, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>,
                type_traits::detail::Lnot<stored_constructible<Ts...>>,
                not_tags<U, Ts...>
            >::value
        )
    >
    SROOK_CONSTEXPR expected_payload(std::initializer_list<U> li, Ts&&... ts)
        : base_type(), err_(li, srook::forward<Ts>(ts)...) {}

    SROOK_CONSTEXPR expected_payload(bool, bool, const expected_payload& other)
        : expected_payload(other) {}

    SROOK_CONSTEXPR expected_payload(bool, bool, const expected_payload&& other)
        : expected_payload(srook::move(other)) {}

    SROOK_CONSTEXPR expected_payload(const expected_payload& other)
    {
        if (other.load_engaged()) {
            construct(other.payload_);
        } else if (other.load_error()) {
            construct_err(other.err_);
        } else {
            reset();
        }
    }

    SROOK_CONSTEXPR expected_payload(expected_payload&& other)
    {
        if (other.load_payload()) {
            construct(srook::move(other.payload_));
        } else if (other.load_error()) {
            construct_err(srook::move(other.err_));
        } else {
            reset();
        }
    }

    void reset() 
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_destructible<stored_value_type>, is_nothrow_destructible<error_type>>::value))
    {
        if (this->load_engaged()) {
            this->payload_.~stored_value_type();
            this->store_engaged(false);
        } else if (load_error()) {
            ~error_type();
            store_error_engaged(false);
        }
    }

    template <class... Args>
    void construct_err(Args&&... args) 
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<error_type, Args...>::value))
    {
        if (this->load_engaged()) {
            this->payload_.~stored_value_type();
            this->engaged_ = false;
        }
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        :: new (static_cast<void*>(srook::addressof(err_))) error_type(srook::forward<Args>(args)...);
        error_engaged_ = true;
    }

    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<stored_value_type, Args...>::value))
    {
        if (error_engaged_) {
            err_.~error_type();
            error_engaged_ = false;
        }
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        base_type::construct(srook::forward<Args>(args)...);
    }

    const error_type& load_error() const SROOK_NOEXCEPT_TRUE { return err_; }
    error_type& load_error() SROOK_NOEXCEPT_TRUE { return err_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool load_error_engaged() const { return error_engaged_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR void store_error_engaged(bool x) { error_engaged_ = srook::move(x); }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool any_engaged() const { return this->engaged_ || error_engaged_; }
private:
    union {
        SROOK_DEDUCED_TYPENAME base_type::Empty_byte exempty_;
        error_type err_;
    };
    bool error_engaged_ = false;

};

template <class T, class ErrType>
class expected_payload<T, ErrType, false, false, srook::optionally::optional_payload> 
    : public srook::optionally::optional_payload<T, false, false> {
    typedef SROOK_DEDUCED_TYPENAME srook::optionally::optional_payload<T, false, false> base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::Stored_type stored_value_type;
    typedef SROOK_DEDUCED_TYPENAME remove_const<ErrType>::type error_type;
    template <class U>
    struct ctor_tag : public enable_copy_move<false, false, false, false> {};

    template <class... Ts>
    using stored_constructible = type_traits::detail::Land<is_constructible<stored_value_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using error_constructible = type_traits::detail::Land<is_constructible<error_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using not_tags = 
        type_traits::detail::Land<
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_value_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_error_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>
         >;
public:
    SROOK_CONSTEXPR expected_payload() : exempty_() {}

    ~expected_payload()
    SROOK_MEMFN_NOEXCEPT((type_traits::detail::Land<is_nothrow_destructible<stored_value_type>, is_nothrow_destructible<error_type>>::value))
    {
        if (load_error_engaged()) err_.~error_type();
    }

    template <class... Ts, SROOK_REQUIRES(stored_constructible<Ts...>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, srook::exception::set_value_t, Ts&&... ts) 
        : base_type(srook::in_place, srook::forward<Ts>(ts)...), exempty_() {}

    template <class... Us, SROOK_REQUIRES(error_constructible<Us...>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, srook::exception::set_error_t, Us&&... us)
        : base_type(), err_(srook::forward<Us>(us)...), error_engaged_(true) {}
        
    template <class... Ts, SROOK_REQUIRES(type_traits::detail::Land<stored_constructible<Ts...>, type_traits::detail::Lnot<error_constructible<Ts...>>, not_tags<Ts...>>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, Ts&&... ts)
        : base_type(srook::in_place, srook::forward<Ts>(ts)...), exempty_() {}
    
    template <class... Us, SROOK_REQUIRES(type_traits::detail::Land<error_constructible<Us...>, type_traits::detail::Lnot<stored_constructible<Us...>>, not_tags<Us...>>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, Us&&... us)
        : base_type(), err_(srook::forward<Us>(us)...), error_engaged_(true) {}

    template <
        class U, 
        class... Ts, 
        SROOK_REQUIRES(
            type_traits::detail::Land<
                is_constructible<stored_value_type, std::initializer_list<U>, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>,
                type_traits::detail::Lnot<error_constructible<Ts...>>,
                not_tags<U, Ts...>
            >::value
        )
    >
    SROOK_CONSTEXPR expected_payload(std::initializer_list<U> li, Ts&&... ts)
        : base_type(li, srook::forward<Ts>(ts)...), exempty_() {}

    template <
        class U,
        class... Ts,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                is_constructible<error_type, std::initializer_list<U>, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>,
                type_traits::detail::Lnot<stored_constructible<Ts...>>,
                not_tags<U, Ts...>
            >::value
        )
    >
    SROOK_CONSTEXPR expected_payload(std::initializer_list<U> li, Ts&&... ts)
        : base_type(), err_(li, srook::forward<Ts>(ts)...) {}

    SROOK_CONSTEXPR expected_payload(bool, bool, const expected_payload& other)
        : expected_payload(other) {}

    SROOK_CONSTEXPR expected_payload(bool, bool, expected_payload&& other)
        : expected_payload(srook::move(other)) {}
    
    SROOK_CONSTEXPR expected_payload(const expected_payload& other)
    {
        if (other.load_engaged()) {
            construct(other.payload_);
        } else if (other.load_error()) {
            construct_err(other.err_);
        } else {
            reset();
        }
    }

    SROOK_CONSTEXPR expected_payload(expected_payload&& other)
    {
        if (other.load_payload()) {
            construct(srook::move(other.payload_));
        } else if (other.load_error()) {
            construct_err(srook::move(other.err_));
        } else {
            reset();
        }
    }
    
    void reset() 
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_destructible<stored_value_type>, is_nothrow_destructible<error_type>>::value))
    {
        if (this->load_engaged()) {
            this->payload_.~stored_value_type();
            this->store_engaged(false);
        } else if (load_error()) {
            err_.~error_type();
            store_error_engaged(false);
        }
    }

    template <class... Args>
    void construct_err(Args&&... args) 
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<error_type, Args...>::value))
    {
        if (this->load_engaged()) {
            this->payload_.~stored_value_type();
            this->engaged_ = false;
        }
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        :: new (static_cast<void*>(srook::addressof(err_))) error_type(srook::forward<Args>(args)...);
        error_engaged_ = true;
    }

    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<stored_value_type, Args...>::value))
    {
        if (error_engaged_) {
            err_.~error_type();
            error_engaged_ = false;
        }
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        base_type::construct(srook::forward<Args>(args)...);
    }

    const error_type& load_error() const SROOK_NOEXCEPT_TRUE { return err_; }
    error_type& load_error() SROOK_NOEXCEPT_TRUE { return err_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool load_error_engaged() const { return error_engaged_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR void store_error_engaged(bool x) { error_engaged_ = srook::move(x); }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool any_engaged() const { return this->engaged_ || error_engaged_; }
private:
    union {
        SROOK_DEDUCED_TYPENAME base_type::Empty_byte exempty_;
        error_type err_;
    };
    bool error_engaged_ = false;
};

template <class T, bool is_tcc, bool is_tmc>
class expected_payload<T, T, is_tcc, is_tmc, srook::optionally::optional_payload> 
    : public srook::optionally::optional_payload<T, is_tcc, is_tmc> {
    typedef SROOK_DEDUCED_TYPENAME srook::optionally::optional_payload<T, is_tcc, is_tmc> base_type;
    typedef SROOK_DEDUCED_TYPENAME base_type::Stored_type stored_value_type;
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type error_type;
    template <class U>
    struct ctor_tag : public enable_copy_move<false, false, false, false> {};

    SROOK_CONSTEXPR expected_payload(ctor_tag<bool>, const expected_payload& other)
        : exempty_(), base_type(other) {}
    SROOK_CONSTEXPR expected_payload(ctor_tag<bool>, expected_payload&& other)
        : exempty_(), base_type(srook::move(other)) {}

    SROOK_CONSTEXPR expected_payload(ctor_tag<char>, const expected_payload& other)
        : err_(other.err_), error_engaged_(true) {}
    SROOK_CONSTEXPR expected_payload(ctor_tag<char>, expected_payload&& other)
        : err_(srook::move(other.err_)), error_engaged_(true) {}

    SROOK_CONSTEXPR expected_payload(ctor_tag<void>, const expected_payload&)
        : exempty_(), base_type() {}

    template <class... Ts>
    using stored_constructible = SROOK_DEDUCED_TYPENAME type_traits::detail::Land<is_constructible<stored_value_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using error_constructible = SROOK_DEDUCED_TYPENAME type_traits::detail::Land<is_constructible<error_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using not_tags = 
        SROOK_DEDUCED_TYPENAME type_traits::detail::Land<
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_value_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_error_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<in_place_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>
         >;
public:
    SROOK_CONSTEXPR expected_payload() : exempty_() {}
    
    template <class... Ts, SROOK_REQUIRES(stored_constructible<Ts...>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, srook::exception::set_value_t, Ts&&... ts) 
        : base_type(srook::in_place, srook::forward<Ts>(ts)...), exempty_() {}

    template <class... Us, SROOK_REQUIRES(error_constructible<Us...>::value)>
    SROOK_CONSTEXPR expected_payload(srook::in_place_t, srook::exception::set_error_t, Us&&... us)
        : base_type(), err_(srook::in_place, srook::forward<Us>(us)...) {}
        
    template <
        class U, 
        class... Ts, 
        SROOK_REQUIRES(type_traits::detail::Land<is_constructible<stored_value_type, std::initializer_list<U>, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>, not_tags<U, Ts...>>::value)
    >
    SROOK_CONSTEXPR expected_payload(srook::exception::set_value_t, std::initializer_list<U> li, Ts&&... ts)
        : base_type(li, srook::forward<Ts>(ts)...), exempty_() {}

    template <
        class U,
        class... Ts,
        SROOK_REQUIRES(type_traits::detail::Land<is_constructible<error_type, std::initializer_list<U>, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>, not_tags<U, Ts...>>::value)
    >
    SROOK_CONSTEXPR expected_payload(srook::exception::set_error_t, std::initializer_list<U> li, Ts&&... ts)
        : base_type(), err_(li, srook::forward<Ts>(ts)...) {}

    SROOK_CONSTEXPR expected_payload(bool is_engaged, bool is_error_engaged, const expected_payload& other)
        : expected_payload(is_engaged ? ctor_tag<bool>{} : is_error_engaged ? ctor_tag<char>{} : ctor_tag<void>{}, other) {}

    SROOK_CONSTEXPR expected_payload(bool is_engaged, bool is_error_engaged, expected_payload&& other)
        : expected_payload(is_engaged ? ctor_tag<bool>{} : is_error_engaged ? ctor_tag<char>{} : ctor_tag<void>{}, srook::move(other)) {}
    
    void reset() 
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_destructible<stored_value_type>, is_nothrow_destructible<error_type>>::value))
    {
        if (this->load_engaged()) {
            this->payload_.~stored_value_type();
            this->store_engaged(false);
        } else if (load_error()) {
            ~error_type();
            store_error_engaged(false);
        }
    }

    template <class... Args>
    void construct_err(Args&&... args) 
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<error_type, Args...>::value))
    {
        if (this->load_engaged()) {
            this->payload_.~stored_value_type();
            this->engaged_ = false;
        }
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        :: new (static_cast<void*>(srook::addressof(err_))) error_type(srook::forward<Args>(args)...);
        error_engaged_ = true;
    }

    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<stored_value_type, Args...>::value))
    {
        if (error_engaged_) {
            err_.~error_type();
            error_engaged_ = false;
        }
        // NOTE: NOT laundered. Use safe_optional_payload if Stored_type has const or reference type member.
        base_type::construct(srook::forward<Args>(args)...);
    }

    const error_type& load_error() const SROOK_NOEXCEPT_TRUE { return err_; }
    error_type& load_error() SROOK_NOEXCEPT_TRUE { return err_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool load_error_engaged() const { return error_engaged_; }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR void store_error_engaged(bool x) { error_engaged_ = srook::move(x); }
    SROOK_FORCE_INLINE SROOK_CONSTEXPR bool any_engaged() const { return this->engaged_ || error_engaged_; }
private:
    union {
        SROOK_DEDUCED_TYPENAME base_type::Empty_byte exempty_;
        error_type err_;
    };
    bool error_engaged_ = false;
};

} // namespace detail

template <class T, class ErrType, template <class, class, bool, bool, template <class, bool, bool> class> class Payload>
class expected_base {
    typedef Payload<
        T, ErrType,
        type_traits::detail::Land<
            std::is_trivially_copy_constructible<T>, 
            std::is_trivially_move_constructible<T> 
        >::value,
        std::is_trivially_destructible<T>::value,
        srook::optionally::optional_payload
    > payload_type;
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type stored_value_type;
    typedef SROOK_DEDUCED_TYPENAME remove_const<ErrType>::type error_type;
    
    template <class... Ts>
    using stored_constructible = type_traits::detail::Land<is_constructible<stored_value_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using error_constructible = type_traits::detail::Land<is_constructible<error_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using not_tags = 
        type_traits::detail::Land<
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_value_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_error_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<in_place_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>
         >;
public:
    SROOK_CONSTEXPR expected_base() SROOK_NOEXCEPT_TRUE {}

    template <class... Ts, SROOK_REQUIRES(type_traits::detail::Land<stored_constructible<Ts&&...>, type_traits::detail::Lnot<error_constructible<Ts&&...>>, not_tags<Ts...>>::value)>
    SROOK_CONSTEXPR expected_base(srook::in_place_t, Ts&&... args)
        : payload_(srook::in_place, srook::exception::set_value, srook::forward<Ts>(args)...) {}

    template <class... Us, SROOK_REQUIRES(type_traits::detail::Land<type_traits::detail::Lnot<stored_constructible<Us&&...>>, error_constructible<Us&&...>, not_tags<Us...>>::value)>
    SROOK_CONSTEXPR expected_base(srook::in_place_t, Us&&... args)
        : payload_(srook::in_place, srook::exception::set_error, srook::forward<Us>(args)...) {}
    
    template <class... Ts, SROOK_REQUIRES(type_traits::detail::Land<stored_constructible<Ts&&...>, type_traits::detail::Lnot<error_constructible<Ts&&...>>, not_tags<Ts...>>::value)>
    SROOK_CONSTEXPR expected_base(srook::in_place_t, srook::exception::set_value_t, Ts&&... args)
        : payload_(srook::in_place, srook::exception::set_value, srook::forward<Ts>(args)...) {}

    template <class... Us, SROOK_REQUIRES(type_traits::detail::Land<type_traits::detail::Lnot<stored_constructible<Us&&...>>, error_constructible<Us&&...>, not_tags<Us...>>::value)>
    SROOK_CONSTEXPR expected_base(srook::in_place_t, srook::exception::set_error_t, Us&&... args)
        : payload_(srook::in_place, srook::exception::set_error, srook::forward<Us>(args)...) {}

    template <
        class U,
        class... Args,
        SROOK_REQUIRES(type_traits::detail::Land<stored_constructible<U, Args...>, not_tags<U, Args...>>::value)
    >
    SROOK_CONSTEXPR expected_base(srook::in_place_t, srook::exception::set_value_t, std::initializer_list<U> li, Args&&... args)
        : payload_(srook::in_place, srook::exception::set_value, li, srook::forward<Args>(args)...) {}

    template <
        class U,
        class... Args,
        SROOK_REQUIRES(type_traits::detail::Land<error_constructible<U, Args...>, not_tags<U, Args...>>::value)
    >
    SROOK_CONSTEXPR expected_base(srook::in_place_t, srook::exception::set_error_t, std::initializer_list<U> li, Args&&... args)
        : payload_(srook::in_place, srook::exception::set_error, li, srook::forward<Args>(args)...) {}

    template <
        class U,
        class... Args,
        SROOK_REQUIRES(type_traits::detail::Land<stored_constructible<U, Args...>, not_tags<U, Args...>>::value)
    >
    SROOK_CONSTEXPR expected_base(srook::in_place_t, std::initializer_list<U> li, Args&&... args)
        : payload_(srook::in_place, srook::exception::set_value, li, srook::forward<Args>(args)...) {}

    template <
        class U,
        class... Args,
        SROOK_REQUIRES(type_traits::detail::Land<error_constructible<U, Args...>, not_tags<U, Args...>>::value)
    >
    SROOK_CONSTEXPR expected_base(srook::in_place_t, std::initializer_list<U> li, Args&&... args)
        : payload_(srook::in_place, srook::exception::set_error, li, srook::forward<Args>(args)...) {}

    SROOK_CONSTEXPR expected_base(const expected_base& other)
        : payload_(other.payload_.load_engaged(), other.payload_.load_error_engaged(), other.payload_) {}

    SROOK_CONSTEXPR expected_base(expected_base&& other)
        : payload_(other.payload_.load_engaged(), other.payload_.load_error_engaged(), srook::move(other.payload_)) {}

    expected_base& operator=(const expected_base& other)
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_copyable<stored_value_type>, is_nothrow_copyable<error_type>>::value))
    {
        if (other.is_engaged()) {
            if (is_engaged()) {
                get() = other.get();
            } else {
                construct(other.get()); // include destruction
            }
        } else if (other.is_error_engaged()) {
            if (is_error_engaged()) {
                get_error() = other.get_error();
            } else {
                construct_err(other.get_error()); // ditto
            }
        } else {
            reset();
        }

        return *this;
    }

    expected_base& operator=(expected_base&& other)
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_movable<stored_value_type>, is_nothrow_movable<error_type>>::value))
    {
        if (other.is_engaged()) {
            if (is_engaged()) {
                get() = srook::move(other.get());
            } else {
                construct(srook::move(other.get())); // include destruction
            }
        } else if (other.is_error_engaged()) {
            if (is_error_engaged()) {
                get_error() = srook::move(other.get_error());
            } else {
                construct_err(srook::move(other.get_error())); // ditto
            }
        } else {
            reset();
        }
        return *this;
    }
protected:
    SROOK_CONSTEXPR bool is_engaged() const SROOK_NOEXCEPT_TRUE
    {
        return payload_.load_engaged();
    }

    SROOK_CONSTEXPR bool is_error_engaged() const SROOK_NOEXCEPT_TRUE
    {
        return payload_.load_error_engaged();
    }

    SROOK_CONSTEXPR bool is_any_engaged() const SROOK_NOEXCEPT_TRUE
    {
        return payload_.any_engaged();
    }

    SROOK_CONSTEXPR const stored_value_type& get() const SROOK_NOEXCEPT_TRUE
    {
        assert(is_engaged());
        return payload_.load_payload();
    }

    SROOK_CONSTEXPR stored_value_type& get() SROOK_NOEXCEPT_TRUE
    {
        assert(is_engaged());
        return payload_.load_payload();
    }

    SROOK_CONSTEXPR const error_type& get_error() const SROOK_NOEXCEPT_TRUE
    {
        assert(is_error_engaged());
        return payload_.load_error();
    }

    SROOK_CONSTEXPR error_type& get_error() SROOK_NOEXCEPT_TRUE
    {
        assert(is_error_engaged());
        return payload_.load_error();
    }

    template <class... Args>
    void construct(Args&&... args)
    SROOK_NOEXCEPT((is_nothrow_constructible<stored_value_type, Args...>::value))
    {
        payload_.construct(srook::forward<Args>(args)...);
    }

    template <class... Args>
    void construct_err(Args&&... args)
    SROOK_NOEXCEPT((is_nothrow_constructible<error_type, Args...>::value))
    {
        payload_.construct_err(srook::forward<Args>(args)...);
    }

    void destruct()
    SROOK_NOEXCEPT(is_nothrow_destructible<stored_value_type>::value)
    {
        payload_.load_payload().~stored_value_type();
        payload_.store_engaged(false);
    }

    void destruct_err()
    SROOK_NOEXCEPT(is_nothrow_destructible<error_type>::value)
    {
        payload_.load_error().~error_type();
        payload_.store_error_engaged(false);
    }

    void reset() 
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_destructible<stored_value_type>, is_nothrow_destructible<error_type>>::value))
    {
        payload_.reset();
    }
private:
    payload_type payload_;
};


template <class T, template <class, class, bool, bool, template <class, bool, bool> class> class Payload>
class expected_base<T, T, Payload> {
    typedef Payload<
        T, T,
        type_traits::detail::Land<
            std::is_trivially_copy_constructible<T>, 
            std::is_trivially_move_constructible<T> 
        >::value,
        std::is_trivially_destructible<T>::value,
        srook::optionally::optional_payload
    > payload_type;
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type stored_value_type;
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type error_type;
    
    template <class... Ts>
    using stored_constructible = type_traits::detail::Land<is_constructible<stored_value_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using error_constructible = type_traits::detail::Land<is_constructible<error_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>>;

    template <class... Ts>
    using not_tags = 
        type_traits::detail::Land<
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_value_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_error_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<in_place_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>
         >;
public:
    SROOK_CONSTEXPR expected_base() SROOK_NOEXCEPT_TRUE {}

    template <class... Ts, SROOK_REQUIRES(stored_constructible<Ts...>::value)>
    SROOK_CONSTEXPR expected_base(srook::in_place_t, srook::exception::set_value_t, Ts&&... args)
        : payload_(srook::in_place, srook::exception::set_value, srook::forward<Ts>(args)...) {}

    template <class... Us, SROOK_REQUIRES(error_constructible<Us...>::value)>
    SROOK_CONSTEXPR expected_base(srook::in_place_t, srook::exception::set_error_t, Us&&... args)
        : payload_(srook::in_place, srook::exception::set_error, srook::forward<Us>(args)...) {}

    template <
        class U,
        class... Args,
        SROOK_REQUIRES(type_traits::detail::Land<stored_constructible<U, Args...>, not_tags<U, Args...>>::value)
    >
    SROOK_CONSTEXPR expected_base(srook::in_place_t, srook::exception::set_value_t, std::initializer_list<U> li, Args&&... args)
        : payload_(srook::in_place, srook::exception::set_value, li, srook::forward<Args>(args)...) {}

    template <
        class U,
        class... Args,
        SROOK_REQUIRES(type_traits::detail::Land<error_constructible<U, Args...>, not_tags<U, Args...>>::value)
    >
    SROOK_CONSTEXPR expected_base(srook::in_place_t, srook::exception::set_error_t, std::initializer_list<U> li, Args&&... args)
        : payload_(srook::in_place, srook::exception::set_value, li, srook::forward<Args>(args)...) {}


    SROOK_CONSTEXPR expected_base(const expected_base& other)
        : payload_(other.payload_.load_engaged(), other.payload_.load_error_engaged(), other.payload_) {}

    SROOK_CONSTEXPR expected_base(expected_base&& other)
        : payload_(other.payload_.load_engaged(), other.payload_.load_error_engaged(), srook::move(other.payload_)) {}

    expected_base& operator=(const expected_base& other)
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_copyable<stored_value_type>, is_nothrow_copyable<error_type>>::value))
    {
        if (other.payload_.is_engaged()) {
            if (is_engaged()) {
                get() = other.get();
            } else {
                construct(other.get()); // include destruction
            }
        } else if (other.payload_.is_error_engaged()) {
            if (is_error_engaged()) {
                get_error() = other.get_error();
            } else {
                construct_err(other.get_error()); // ditto
            }
        } else {
            reset();
        }

        return *this;
    }

    expected_base& operator=(expected_base&& other)
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_movable<stored_value_type>, is_nothrow_movable<error_type>>::value))
    {
        if (other.payload_.is_engaged()) {
            if (is_engaged()) {
                get() = srook::move(other.get());
            } else {
                construct(srook::move(other.get())); // include destruction
            }
        } else if (other.payload_.is_error_engaged()) {
            if (is_error_engaged()) {
                get_error() = srook::move(other.get_error());
            } else {
                construct_err(srook::move(other.get_error())); // ditto
            }
        } else {
            reset();
        }
        return *this;
    }
protected:
    SROOK_CONSTEXPR bool is_engaged() const SROOK_NOEXCEPT_TRUE
    {
        return payload_.load_engaged();
    }

    SROOK_CONSTEXPR bool is_error_engaged() const SROOK_NOEXCEPT_TRUE
    {
        return payload_.load_error_engaged();
    }

    SROOK_CONSTEXPR bool is_any_engaged() const SROOK_NOEXCEPT_TRUE
    {
        return payload_.any_engaged();
    }

    SROOK_CONSTEXPR const stored_value_type& get() const SROOK_NOEXCEPT_TRUE
    {
        assert(is_engaged());
        return payload_.load_payload();
    }

    SROOK_CONSTEXPR stored_value_type& get() SROOK_NOEXCEPT_TRUE
    {
        assert(is_engaged());
        return payload_.load_payload();
    }

    SROOK_CONSTEXPR const error_type& get_error() const SROOK_NOEXCEPT_TRUE
    {
        assert(is_error_engaged());
        return payload_.load_error();
    }

    SROOK_CONSTEXPR error_type& get_error() SROOK_NOEXCEPT_TRUE
    {
        assert(is_error_engaged());
        return payload_.load_error();
    }

    template <class... Args>
    void construct(Args&&... args)
    SROOK_NOEXCEPT((is_nothrow_constructible<stored_value_type, Args...>::value))
    {
        payload_.construct(srook::forward<Args>(args)...);
    }

    template <class... Args>
    void construct_err(Args&&... args)
    SROOK_NOEXCEPT((is_nothrow_constructible<error_type, Args...>::value))
    {
        payload_.construct_err(srook::forward<Args>(args)...);
    }

    void destruct()
    SROOK_NOEXCEPT(is_nothrow_destructible<stored_value_type>::value)
    {
        payload_.store_engaged(false);
        payload_.load_payload().~stored_value_type();
    }

    void destruct_err()
    SROOK_NOEXCEPT(is_nothrow_destructible<error_type>::value)
    {
        payload_.store_error_engaged(false);
        payload_.load_error().~error_type();
    }

    void reset() 
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_destructible<stored_value_type>, is_nothrow_destructible<error_type>>::value))
    {
        if (payload_.load_engaged()) {
            destruct();
        } else if (payload_.load_error_engaged()) {
            destruct_err();
        }
    }
private:
    payload_type payload_;
};


template <class T, class ErrType = std::exception_ptr, template <class, class, bool, bool, template <class, bool, bool> class> class Payload = detail::expected_payload>
class expected
    : private expected_base<T, ErrType, Payload>,
      private enable_copy_move<
        type_traits::detail::Land<is_constructible<T>, is_copy_assignable<ErrType>>::value,
        type_traits::detail::Land<is_copy_constructible<T>, is_copy_assignable<T>, is_copy_constructible<ErrType>, is_copy_assignable<ErrType>>::value,
        type_traits::detail::Land<is_move_constructible<T>, is_move_constructible<ErrType>>::value,
        type_traits::detail::Land<is_move_constructible<T>, is_move_assignable<T>, is_move_constructible<ErrType>, is_move_assignable<ErrType>>::value,
        expected<T, ErrType, Payload> 
    > {
public:
    typedef expected_base<T, ErrType, Payload> base_type;
    typedef SROOK_DEDUCED_TYPENAME remove_cv<T>::type value_type;
    typedef SROOK_DEDUCED_TYPENAME remove_cv<ErrType>::type error_type;
private:
    SROOK_ST_ASSERT((type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME remove_cv<T>::type, in_place_t>>::value));
    SROOK_ST_ASSERT((type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME remove_cv<T>::type, set_value_t>>::value));
    SROOK_ST_ASSERT((type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME remove_cv<T>::type, set_error_t>>::value));
    
    template <class... Ts>
    using stored_constructible = is_constructible<value_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>;

    template <class... Ts>
    using error_constructible = is_constructible<error_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>;

    template <class... Ts>
    using not_tags = 
        type_traits::detail::Land<
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_value_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_error_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<in_place_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>
         >;

    template <class T1, class T2, class UU>
    using converts_from_expected = 
        type_traits::detail::Lor<
            is_constructible<T1, const expected<T2, UU, Payload>&>,
            is_constructible<T1, expected<T2, UU, Payload>&>,
            is_constructible<T1, const expected<T2, UU, Payload>&>,
            is_constructible<T1, expected<T2, UU, Payload>&&>,
            is_convertible<const expected<T2, UU, Payload>&, T1>,
            is_convertible<expected<T2, UU, Payload>&, T1>,
            is_convertible<const expected<T2, UU, Payload>&, T1>,
            is_convertible<expected<T2, UU, Payload>&&, T1>
        >;

    template <class T1, class T2, class UU>
    using assign_from_expected =
        type_traits::detail::Lor<
            is_assignable<T1&, const expected<T2, UU, Payload>&>,
            is_assignable<T1&, expected<T2, UU, Payload>&>,
            is_assignable<T1&, const expected<T2, UU, Payload>&&>,
            is_assignable<T1&, expected<T2, UU, Payload>&&>
        >;

public:
    SROOK_CONSTEXPR expected() SROOK_DEFAULT

    template <
        class U = value_type, 
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<U>::type>>,
                not_tags<U>,
                stored_constructible<U>,
                type_traits::detail::Lnot<error_constructible<U>>,
                is_convertible<U&&, value_type>
            >::value
        )
    >
    SROOK_CONSTEXPR expected(U&& t) 
        : base_type(in_place, set_value, srook::forward<U>(t)) {}
    
    template <
        class U = value_type, 
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<U>::type>>,
                not_tags<U>,
                stored_constructible<U>,
                is_convertible<U&&, value_type>
            >::value
        )
    >
    SROOK_CONSTEXPR expected(set_value_t, U&& t) 
        : base_type(in_place, set_value, srook::forward<U>(t)) {}
    
    template <
        class U = error_type, 
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<U>::type>>,
                not_tags<U>,
                type_traits::detail::Lnot<stored_constructible<U>>,
                error_constructible<U>,
                is_convertible<U&, error_type>
            >::value
        )
    >
    SROOK_CONSTEXPR expected(U&& t) 
        : base_type(in_place, set_error, srook::forward<U>(t)) {}
    
    template <
        class U = error_type, 
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<U>::type>>,
                not_tags<U>,
                error_constructible<U>,
                is_convertible<U&&, error_type>
            >::value
        )
    >
    SROOK_CONSTEXPR expected(set_error_t, U&& t) 
        : base_type(in_place, set_error, srook::forward<U>(t)) {}

    template <
        class U,
        class Err,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<value_type, U> >,
                stored_constructible<const U&>,
                is_convertible<const U&, value_type>,
                type_traits::detail::Lnot<converts_from_expected<value_type, U, Err> >,
                type_traits::detail::Lnot<is_same<error_type, Err> >,
                error_constructible<const Err&>,
                is_convertible<const Err&, error_type>,
                type_traits::detail::Lnot<converts_from_expected<error_type, U, Err> >,
                not_tags<U>,
                not_tags<Err>
            >::value
        )
    >
    SROOK_CONSTEXPR expected(const expected<U, Err, Payload>& other) 
        : base_type(other) {}
    
    template <
        class U,
        class Err,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<value_type, U> >,
                stored_constructible<const U&>,
                type_traits::detail::Lnot<is_convertible<const U&, value_type> >,
                type_traits::detail::Lnot<converts_from_expected<value_type, U, Err> >,
                type_traits::detail::Lnot<is_same<error_type, Err> >,
                error_constructible<const Err&>,
                type_traits::detail::Lnot<is_convertible<const Err&, error_type> >,
                type_traits::detail::Lnot<converts_from_expected<error_type, U, Err> >,
                not_tags<U>,
                not_tags<Err>
            >::value
        )
    >
    explicit SROOK_CONSTEXPR expected(const expected<U, Err, Payload>& other)
        : base_type(other) {}
    
    template <
        class U,
        class Err,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<value_type, U> >,
                stored_constructible<U&&>,
                is_convertible<U&&, value_type>,
                type_traits::detail::Lnot<converts_from_expected<value_type, U, Err> >,
                type_traits::detail::Lnot<is_same<error_type, Err> >,
                error_constructible<Err&&>,
                is_convertible<Err&&, error_type>,
                type_traits::detail::Lnot<converts_from_expected<error_type, U, Err> >,
                not_tags<U>,
                not_tags<Err>
            >::value
       )
    >
    SROOK_CONSTEXPR expected(expected<U, Err, Payload>&& other)
        : base_type(srook::move(other)) {}

    template <
        class U,
        class Err,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<value_type, U> >,
                stored_constructible<U&&>,
                type_traits::detail::Lnot<is_convertible<U&&, value_type> >,
                type_traits::detail::Lnot<converts_from_expected<value_type, U, Err> >,
                type_traits::detail::Lnot<is_same<error_type, Err> >,
                error_constructible<Err&&>,
                type_traits::detail::Lnot<is_convertible<Err&&, error_type> >,
                type_traits::detail::Lnot<converts_from_expected<error_type, U, Err> >,
                not_tags<U>,
                not_tags<Err>
            >::value
        )
    >
    explicit SROOK_CONSTEXPR expected(expected<U, Err, Payload>&& other)
        : base_type(srook::move(other)) {}
    
    template <class... Args, SROOK_REQUIRES(stored_constructible<Args&&...>::value)>
    explicit SROOK_CONSTEXPR expected(in_place_t, set_value_t, Args&&... args)
        : base_type(in_place, set_value, srook::forward<Args>(args)...) {}

    template <class U, class... Args, SROOK_REQUIRES(stored_constructible<std::initializer_list<U>&, Args&&...>::value)>
    explicit SROOK_CONSTEXPR expected(in_place_t, set_value_t, std::initializer_list<U> li, Args&&... args)
        : base_type(in_place, set_value, li, srook::forward<Args>(args)...) {}

    template <class... Args, SROOK_REQUIRES(error_constructible<Args&&...>::value)>
    explicit SROOK_CONSTEXPR expected(in_place_t, set_error_t, Args&&... args)
        : base_type(in_place, set_error, srook::forward<Args>(args)...) {}

    template <class U, class... Args, SROOK_REQUIRES(error_constructible<std::initializer_list<U>&, Args&&...>::value)>
    explicit SROOK_CONSTEXPR expected(in_place_t, set_error_t, std::initializer_list<U>& li, Args&&... args)
        : base_type(in_place, set_error, li, srook::forward<Args>(args)...) {}

    SROOK_CONSTEXPR expected(const unexpected<error_type>& une)
        : base_type(in_place, set_error, une.value()) {}

    SROOK_CONSTEXPR expected(unexpected<error_type>&& une)
        : base_type(in_place, set_error, srook::move(une.value())) {}

    template <class U = T, class Err>
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
            type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<Err>::type> >,
            stored_constructible<U>,
            error_constructible<Err>,
            type_traits::detail::Lnot<
                type_traits::detail::Land<
                    is_scalar<value_type>, 
                    is_same<value_type, SROOK_DEDUCED_TYPENAME decay<U>::type>, 
                    is_same<error_type, SROOK_DEDUCED_TYPENAME decay<Err>::type>
                >
            >,
            is_assignable<value_type&, U>,
            is_assignable<error_type&, Err>
        >::value,
        expected&
    >::type
    operator=(const expected<U, Err, Payload>& other)
    {
        if (other.is_engaged()) {
            if (this->is_engaged()) {
                this->get() = other.get();
            } else {
                construct(other.get());
            }
        } else if (other.is_error_engaged()) {
            if (this->is_error_engaged()) {
                this->get_error() = other.get_error();
            } else {
                construct_err(other.get_error());
            }
        } else {
            reset();
        }
        return *this;
    }

    template <class U = T, class Err>
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
            type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<Err>::type> >,
            stored_constructible<U>,
            error_constructible<Err>,
            type_traits::detail::Lnot<
                type_traits::detail::Land<
                    is_scalar<value_type>, 
                    is_same<value_type, SROOK_DEDUCED_TYPENAME decay<U>::type>, 
                    is_same<error_type, SROOK_DEDUCED_TYPENAME decay<Err>::type>
                >
            >,
            is_assignable<value_type&, U>,
            is_assignable<error_type&, Err>
        >::value,
        expected&
    >::type
    operator=(expected<U, Err, Payload>&& other)
    {
        if (other.is_engaged()) {
            if (this->is_engaged()) {
                this->get() = srook::move(other.get());
            } else {
                construct(srook::move(other.get()));
            }
        } else if (other.is_error_engaged()) {
            if (this->is_error_engaged()) {
                this->get_error() = srook::move(other.get_error());
            } else {
                construct_err(srook::move(other.get_error()));
            }
        } else {
            reset();
        }
        return *this;
    }

    template <class... Args>
    SROOK_DEDUCED_TYPENAME enable_if<type_traits::detail::Land<stored_constructible<Args&&...>, not_tags<Args...>>::value>::type
    emplace(srook::exception::set_value_t, Args&&... args)
    SROOK_NOEXCEPT((
        type_traits::detail::Land<
            is_nothrow_destructible<value_type>, is_nothrow_destructible<error_type>, is_nothrow_constructible<value_type, Args&&...>
        >::value
    ))
    {
        reset();
        this->construct(srook::forward<Args>(args)...);
    }
    
    template <class... Args>
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            stored_constructible<Args&&...>, 
            type_traits::detail::Lnot<error_constructible<Args&&...>>,
            not_tags<Args...>
        >::value
    >::type
    emplace(Args&&... args)
    SROOK_NOEXCEPT((
        type_traits::detail::Land<
            is_nothrow_destructible<value_type>, is_nothrow_destructible<error_type>, is_nothrow_constructible<value_type, Args&&...>
        >::value
    ))
    {
        reset();
        this->construct(srook::forward<Args>(args)...);
    }
    
    template <class... Args>
    SROOK_DEDUCED_TYPENAME enable_if<type_traits::detail::Land<error_constructible<Args&&...>, not_tags<Args...>>::value>::type
    emplace(srook::exception::set_error_t, Args&&... args) 
    SROOK_NOEXCEPT((
        type_traits::detail::Land<
            is_nothrow_destructible<value_type>, is_nothrow_destructible<error_type>, is_nothrow_constructible<error_type>
        >::value
    ))
    {
        reset();
        this->construct_err(srook::forward<Args>(args)...);
    }
    
    template <class... Args>
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            error_constructible<Args&&...>, 
            type_traits::detail::Lnot<stored_constructible<Args&&...>>,
            not_tags<Args...>
        >::value
    >::type
    emplace(Args&&... args) 
    SROOK_NOEXCEPT((
        type_traits::detail::Land<
            is_nothrow_destructible<value_type>, is_nothrow_destructible<error_type>, is_nothrow_constructible<error_type>
        >::value
    ))
    {
        reset();
        this->construct_err(srook::forward<Args>(args)...);
    }

    void swap(expected& other)
    SROOK_MEMFN_NOEXCEPT((type_traits::detail::Land<is_nothrow_move_constructible<value_type>, is_nothrow_swappable<T> >::value))
    {
        using std::swap;

        if (this == srook::addressof(other) || (!any_valid() && !other.any_valid())) {
            return;
        } else if (other.is_engaged()) {
            if (this->is_engaged()) {
                swap(this->get(), other.get());
            } else if (this->is_error_engaged()) {
                error_type tmp{ srook::move(this->get_error()) };
                this->construct(srook::move(other.get()));
                other.construct_err(srook::move(tmp));
            } else {
                this->construct(srook::move(other.get()));
                other.destruct();
            }
        } else if (other.is_error_engaged()) {
            if (this->is_engaged()) {
                value_type tmp = srook::move(other.get());
                this->construct_err(other.get_error());
                other.construct(srook::move(tmp));
            } else if (this->is_error_engaged()) {
                swap(this->get_error(), other.get_error());
            } else {
                this->construct_err(srook::move(other.get_error()));
                other.destruct_err();
            }
        } else {
            if (this->is_engaged()) {
                other.construct(srook::move(this->get()));
                this->destruct();
            } else if (this->is_error_engaged()) {
                other.construct_err(srook::move(this->get_error()));
                this->destruct_err();
            }
        }
    }

    SROOK_CONSTEXPR const T* operator->() const { return srook::addressof(this->get()); }
    T* operator->() { return srook::addressof(this->get()); }
    SROOK_CONSTEXPR const T& operator*() const& { return this->get(); }
    SROOK_CONSTEXPR T& operator*() & { return this->get(); }
    SROOK_CONSTEXPR T&& operator*() && { return srook::move(this->get()); }
    SROOK_CONSTEXPR T&& operator*() const&& { return srook::move(this->get()); }
    SROOK_CONSTEXPR SROOK_EXPLICIT operator bool() const SROOK_NOEXCEPT_TRUE { return this->is_engaged(); }
    SROOK_CONSTEXPR bool has_value() const SROOK_NOEXCEPT_TRUE { return bool(*this); }
    SROOK_CONSTEXPR bool valid() const SROOK_NOEXCEPT_TRUE { return has_value(); }

    SROOK_CONSTEXPR const error_type& error() const&
    {
        return this->get_error();
    }

    SROOK_CONSTEXPR error_type& error() &
    {
        return this->get_error();
    }

    SROOK_CONSTEXPR error_type&& error() &&
    {
        return srook::move(this->get_error());
    }

    SROOK_CONSTEXPR error_type&& error() const&&
    {
        return srook::move(this->get_error());
    }

    SROOK_CONSTEXPR const value_type& value() const&
    {
        return this->is_engaged() ? this->get() 
            : this->is_error_engaged() ? (detail::throw_expected_error(this->get_error()), this->get()) 
            : (detail::throw_bad_expected_access(), this->get());
    }

    SROOK_CONSTEXPR value_type& value() &
    {
        return this->is_engaged() ? this->get() 
            : this->is_error_engaged() ? (detail::throw_expected_error(this->get_error()), this->get()) 
            : (detail::throw_bad_expected_access(), this->get());
    }

    SROOK_CONSTEXPR value_type&& value() &&
    {
        return this->is_engaged() ? srook::move(this->get()) 
            : this->is_error_engaged() ? (detail::throw_expected_error(this->get_error()), srook::move(this->get())) 
            : (detail::throw_bad_expected_access(), srook::move(this->get()));
    }
    
    SROOK_CONSTEXPR value_type&& value() const&&
    {
        return this->is_engaged() ? srook::move(this->get()) 
            : this->is_error_engaged() ? (detail::throw_expected_error(this->get_error()), srook::move(this->get())) 
            : (detail::throw_bad_expected_access(), srook::move(this->get()));
    }

    template <class U, SROOK_REQUIRES(is_convertible<SROOK_DEDUCED_TYPENAME decay<U>::type, value_type>::value)>
    SROOK_CONSTEXPR value_type value_or(U&& u) const& SROOK_NOEXCEPT_TRUE
    {
        SROOK_ST_ASSERT((is_move_constructible<value_type>::value));
        SROOK_ST_ASSERT((is_move_constructible<error_type>::value));

        return this->is_engaged() ? this->get() : srook::forward<U>(u);
    }

    template <class U, SROOK_REQUIRES(is_convertible<SROOK_DEDUCED_TYPENAME decay<U>::type, value_type>::value)>
    SROOK_CONSTEXPR value_type&& value_or(U&& u) && SROOK_NOEXCEPT_TRUE
    {
        SROOK_ST_ASSERT((is_move_constructible<value_type>::value));
        SROOK_ST_ASSERT((is_move_constructible<error_type>::value));

        return this->is_engaged() ? srook::move(this->get()) : srook::forward<U>(u);
    }

    void reset() 
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_destructible<value_type>, is_nothrow_destructible<error_type>>::value))
    {
        base_type::reset();
    }

    SROOK_CONSTEXPR bool any_valid() const SROOK_NOEXCEPT_TRUE
    {
        return this->is_any_engaged();
    }
    
    template <class F, SROOK_REQUIRES(is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type>::value)>
    friend SROOK_FORCE_INLINE expected
    operator>>=(const expected& this_, F&& f) SROOK_NOEXCEPT(declval<F>()(declval<value_type>()))
    {
        return this_ ? srook::invoke(srook::forward<F>(f), *this_) : this_;
    }

    template <class F, SROOK_REQUIRES(is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type>::value)>
    friend SROOK_FORCE_INLINE expected
    operator<<=(F&& f, const expected& this_) SROOK_NOEXCEPT(declval<F>()(declval<value_type()))
    {
        return this_ >>= f;
    }

    template <class F, SROOK_REQUIRES(is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type>::value)>
    friend SROOK_FORCE_INLINE expected
    operator>>(const expected& this_, F&& f) SROOK_NOEXCEPT(declval<F>()(declval<value_type()))
    {
        return this_ ? srook::invoke(srook::forward<F>(f)) : this_;
    }

    template <class F, SROOK_REQUIRES(is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type>::value)>
    SROOK_FORCE_INLINE expected map(F&& f) SROOK_NOEXCEPT(declval<F>()(declval<value_type>()))
    {
        return *this ? *this >>= srook::forward<F>(f) : *this;
    }
};


template <class T, template <class, class, bool, bool, template <class, bool, bool> class> class Payload>
class expected<T, T, Payload>
    : private expected_base<T, T, Payload>,
      private enable_copy_move<
        type_traits::detail::Land<is_constructible<T>, is_copy_assignable<T>>::value,
        type_traits::detail::Land<is_copy_constructible<T>, is_copy_assignable<T>>::value,
        is_move_constructible<T>::value,
        type_traits::detail::Land<is_move_constructible<T>, is_move_assignable<T>>::value,
        expected<T, T, Payload> 
    > {
public:
    typedef expected_base<T, T, Payload> base_type;
    typedef SROOK_DEDUCED_TYPENAME remove_cv<T>::type value_type;
    typedef SROOK_DEDUCED_TYPENAME remove_cv<T>::type error_type;
private:
    SROOK_ST_ASSERT((type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME remove_cv<T>::type, in_place_t>>::value));
    SROOK_ST_ASSERT((type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME remove_cv<T>::type, set_value_t>>::value));
    SROOK_ST_ASSERT((type_traits::detail::Lnot<is_same<SROOK_DEDUCED_TYPENAME remove_cv<T>::type, set_error_t>>::value));
    
    template <class... Ts>
    using stored_constructible = is_constructible<value_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>;

    template <class... Ts>
    using error_constructible = is_constructible<error_type, SROOK_DEDUCED_TYPENAME decay<Ts>::type...>;

    template <class... Ts>
    using not_tags = 
        type_traits::detail::Land<
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_value_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<set_error_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>,
            type_traits::detail::Land<type_traits::detail::Lnot<is_same<in_place_t, SROOK_DEDUCED_TYPENAME decay<Ts>::type>>...>
         >;

    template <class T1, class T2, class UU>
    using converts_from_expected = 
        type_traits::detail::Lor<
            is_constructible<T1, const expected<T2, UU, Payload>&>,
            is_constructible<T1, expected<T2, UU, Payload>&>,
            is_constructible<T1, const expected<T2, UU, Payload>&>,
            is_constructible<T1, expected<T2, UU, Payload>&&>,
            is_convertible<const expected<T2, UU, Payload>&, T1>,
            is_convertible<expected<T2, UU, Payload>&, T1>,
            is_convertible<const expected<T2, UU, Payload>&, T1>,
            is_convertible<expected<T2, UU, Payload>&&, T1>
        >;

    template <class T1, class T2, class UU>
    using assign_from_expected =
        type_traits::detail::Lor<
            is_assignable<T1&, const expected<T2, UU, Payload>&>,
            is_assignable<T1&, expected<T2, UU, Payload>&>,
            is_assignable<T1&, const expected<T2, UU, Payload>&&>,
            is_assignable<T1&, expected<T2, UU, Payload>&&>
        >;

public:
    SROOK_CONSTEXPR expected() SROOK_DEFAULT

    template <
        class U = value_type, 
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<U>::type>>,
                not_tags<U>,
                stored_constructible<U>,
                is_convertible<U&&, value_type>
            >::value
        )
    >
    SROOK_CONSTEXPR expected(set_value_t, U&& t) 
        : base_type(in_place, set_value, srook::forward<U>(t)) {}
    
    template <
        class U = error_type, 
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<U>::type>>,
                not_tags<U>,
                error_constructible<U>,
                is_convertible<U&&, error_type>
            >::value
        )
    >
    SROOK_CONSTEXPR expected(set_error_t, U&& t) 
        : base_type(in_place, set_error, srook::forward<U>(t)) {}

    template <
        class U,
        class Err,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<value_type, U> >,
                stored_constructible<const U&>,
                is_convertible<const U&, value_type>,
                type_traits::detail::Lnot<converts_from_expected<value_type, U, Err> >,
                type_traits::detail::Lnot<is_same<error_type, Err> >,
                error_constructible<const Err&>,
                is_convertible<const Err&, error_type>,
                type_traits::detail::Lnot<converts_from_expected<error_type, U, Err> >,
                not_tags<U>,
                not_tags<Err>
            >::value
        )
    >
    SROOK_CONSTEXPR expected(const expected<U, Err, Payload>& other) 
        : base_type(other) {}
    
    template <
        class U,
        class Err,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<value_type, U> >,
                stored_constructible<const U&>,
                type_traits::detail::Lnot<is_convertible<const U&, value_type> >,
                type_traits::detail::Lnot<converts_from_expected<value_type, U, Err> >,
                type_traits::detail::Lnot<is_same<error_type, Err> >,
                error_constructible<const Err&>,
                type_traits::detail::Lnot<is_convertible<const Err&, error_type> >,
                type_traits::detail::Lnot<converts_from_expected<error_type, U, Err> >,
                not_tags<U>,
                not_tags<Err>
            >::value
        )
    >
    explicit SROOK_CONSTEXPR expected(const expected<U, Err, Payload>& other)
        : base_type(other) {}
    
    template <
        class U,
        class Err,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<value_type, U> >,
                stored_constructible<U&&>,
                is_convertible<U&&, value_type>,
                type_traits::detail::Lnot<converts_from_expected<value_type, U, Err> >,
                type_traits::detail::Lnot<is_same<error_type, Err> >,
                error_constructible<Err&&>,
                is_convertible<Err&&, error_type>,
                type_traits::detail::Lnot<converts_from_expected<error_type, U, Err> >,
                not_tags<U>,
                not_tags<Err>
            >::value
       )
    >
    SROOK_CONSTEXPR expected(expected<U, Err, Payload>&& other)
        : base_type(srook::move(other)) {}

    template <
        class U,
        class Err,
        SROOK_REQUIRES(
            type_traits::detail::Land<
                type_traits::detail::Lnot<is_same<value_type, U> >,
                stored_constructible<U&&>,
                type_traits::detail::Lnot<is_convertible<U&&, value_type> >,
                type_traits::detail::Lnot<converts_from_expected<value_type, U, Err> >,
                type_traits::detail::Lnot<is_same<error_type, Err> >,
                error_constructible<Err&&>,
                type_traits::detail::Lnot<is_convertible<Err&&, error_type> >,
                type_traits::detail::Lnot<converts_from_expected<error_type, U, Err> >,
                not_tags<U>,
                not_tags<Err>
            >::value
        )
    >
    explicit SROOK_CONSTEXPR expected(expected<U, Err, Payload>&& other)
        : base_type(srook::move(other)) {}
    
    template <class... Args, SROOK_REQUIRES(stored_constructible<Args&&...>::value)>
    explicit SROOK_CONSTEXPR expected(in_place_t, set_value_t, Args&&... args)
        : base_type(in_place, set_value, srook::forward<Args>(args)...) {}

    template <class U, class... Args, SROOK_REQUIRES(stored_constructible<std::initializer_list<U>&, Args&&...>::value)>
    explicit SROOK_CONSTEXPR expected(in_place_t, set_value_t, std::initializer_list<U> li, Args&&... args)
        : base_type(in_place, set_value, li, srook::forward<Args>(args)...) {}

    template <class... Args, SROOK_REQUIRES(error_constructible<Args&&...>::value)>
    explicit SROOK_CONSTEXPR expected(in_place_t, set_error_t, Args&&... args)
        : base_type(in_place, set_error, srook::forward<Args>(args)...) {}

    template <class U, class... Args, SROOK_REQUIRES(error_constructible<std::initializer_list<U>&, Args&&...>::value)>
    explicit SROOK_CONSTEXPR expected(in_place_t, set_error_t, std::initializer_list<U>& li, Args&&... args)
        : base_type(in_place, set_error, li, srook::forward<Args>(args)...) {}
    
    SROOK_CONSTEXPR expected(const unexpected<error_type>& une)
        : base_type(in_place, set_error, une.value()) {}

    SROOK_CONSTEXPR expected(unexpected<error_type>&& une)
        : base_type(in_place, set_error, srook::move(une.value())) {}

    template <class U = T, class Err>
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
            type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<Err>::type> >,
            stored_constructible<U>,
            error_constructible<Err>,
            type_traits::detail::Lnot<
                type_traits::detail::Land<
                    is_scalar<value_type>, 
                    is_same<value_type, SROOK_DEDUCED_TYPENAME decay<U>::type>, 
                    is_same<error_type, SROOK_DEDUCED_TYPENAME decay<Err>::type>
                >
            >,
            is_assignable<value_type&, U>,
            is_assignable<error_type&, Err>
        >::value,
        expected&
    >::type
    operator=(const expected<U, Err, Payload>& other)
    {
        if (other.is_engaged()) {
            if (this->is_engaged()) {
                this->get() = other.get();
            } else {
                construct(other.get());
            }
        } else if (other.is_error_engaged()) {
            if (this->is_error_engaged()) {
                this->get_error() = other.get_error();
            } else {
                construct_err(other.get_error());
            }
        } else {
            reset();
        }
        return *this;
    }

    template <class U = T, class Err>
    SROOK_DEDUCED_TYPENAME enable_if<
        type_traits::detail::Land<
            type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<U>::type> >,
            type_traits::detail::Lnot<is_same<expected, SROOK_DEDUCED_TYPENAME decay<Err>::type> >,
            stored_constructible<U>,
            error_constructible<Err>,
            type_traits::detail::Lnot<
                type_traits::detail::Land<
                    is_scalar<value_type>, 
                    is_same<value_type, SROOK_DEDUCED_TYPENAME decay<U>::type>, 
                    is_same<error_type, SROOK_DEDUCED_TYPENAME decay<Err>::type>
                >
            >,
            is_assignable<value_type&, U>,
            is_assignable<error_type&, Err>
        >::value,
        expected&
    >::type
    operator=(expected<U, Err, Payload>&& other)
    {
        if (other.is_engaged()) {
            if (this->is_engaged()) {
                this->get() = srook::move(other.get());
            } else {
                construct(srook::move(other.get()));
            }
        } else if (other.is_error_engaged()) {
            if (this->is_error_engaged()) {
                this->get_error() = srook::move(other.get_error());
            } else {
                construct_err(srook::move(other.get_error()));
            }
        } else {
            reset();
        }
        return *this;
    }

    template <class... Args>
    SROOK_DEDUCED_TYPENAME enable_if<type_traits::detail::Land<stored_constructible<Args&&...>, not_tags<Args...>>::value>::type
    emplace(srook::exception::set_value_t, Args&&... args)
    SROOK_NOEXCEPT((
        type_traits::detail::Land<
            is_nothrow_destructible<value_type>, is_nothrow_destructible<error_type>, is_nothrow_constructible<value_type, Args&&...>
        >::value
    ))
    {
        reset();
        this->construct(srook::forward<Args>(args)...);
    }
    
    template <class... Args>
    SROOK_DEDUCED_TYPENAME enable_if<type_traits::detail::Land<error_constructible<Args&&...>, not_tags<Args...>>::value>::type
    emplace(srook::exception::set_error_t, Args&&... args) 
    SROOK_NOEXCEPT((
        type_traits::detail::Land<
            is_nothrow_destructible<value_type>, is_nothrow_destructible<error_type>, is_nothrow_constructible<error_type>
        >::value
    ))
    {
        reset();
        this->construct_err(srook::forward<Args>(args)...);
    }
    
    void swap(expected& other)
    SROOK_MEMFN_NOEXCEPT((type_traits::detail::Land<is_nothrow_move_constructible<value_type>, is_nothrow_swappable<T> >::value))
    {
        using std::swap;

        if (this == srook::addressof(other) || (!any_valid() && !other.any_valid())) {
            return;
        } else if (other.is_engaged()) {
            if (this->is_engaged()) {
                swap(this->get(), other.get());
            } else if (this->is_error_engaged()) {
                error_type tmp{ srook::move(this->get_error()) };
                this->construct(srook::move(other.get()));
                other.construct_err(srook::move(tmp));
            } else {
                this->construct(srook::move(other.get()));
                other.destruct();
            }
        } else if (other.is_error_engaged()) {
            if (this->is_engaged()) {
                value_type tmp = srook::move(other.get());
                construct_err(other.get_error());
                other.construct(srook::move(tmp));
            } else if (this->is_error_engaged()) {
                swap(this->get_error(), other.get_error());
            } else {
                construct_err(srook::move(other.get_error()));
                other.destruct_err();
            }
        } else {
            if (this->is_engaged()) {
                other.construct(srook::move(this->get()));
                this->destruct();
            } else if (this->is_error_engaged()) {
                other.construct_err(srook::move(this->get_error()));
                this->destruct_err();
            }
        }
    }

    SROOK_CONSTEXPR const T* operator->() const { return srook::addressof(this->get()); }
    T* operator->() { return srook::addressof(this->get()); }
    SROOK_CONSTEXPR const T& operator*() const& { return this->get(); }
    SROOK_CONSTEXPR T& operator*() & { return this->get(); }
    SROOK_CONSTEXPR T&& operator*() && { return srook::move(this->get()); }
    SROOK_CONSTEXPR T&& operator*() const&& { return srook::move(this->get()); }
    SROOK_CONSTEXPR SROOK_EXPLICIT operator bool() const SROOK_NOEXCEPT_TRUE { return this->is_engaged(); }
    SROOK_CONSTEXPR bool has_value() const SROOK_NOEXCEPT_TRUE { return bool(*this); }
    SROOK_CONSTEXPR bool valid() const SROOK_NOEXCEPT_TRUE { return has_value(); }

    SROOK_CONSTEXPR const error_type& error() const&
    {
        return this->get_error();
    }

    SROOK_CONSTEXPR error_type& error() &
    {
        return this->get_error();
    }

    SROOK_CONSTEXPR error_type&& error() &&
    {
        return srook::move(this->get_error());
    }

    SROOK_CONSTEXPR error_type&& error() const&&
    {
        return srook::move(this->get_error());
    }

    SROOK_CONSTEXPR const value_type& value() const&
    {
        return this->is_engaged() ? this->get() 
            : this->is_error_engaged() ? (detail::throw_expected_error(this->get_error()), this->get()) 
            : (detail::throw_bad_expected_access(), this->get());
    }

    SROOK_CONSTEXPR value_type& value() &
    {
        return this->is_engaged() ? this->get() 
            : this->is_error_engaged() ? (detail::throw_expected_error(this->get_error()), this->get()) 
            : (detail::throw_bad_expected_access(), this->get());
    }

    SROOK_CONSTEXPR value_type&& value() &&
    {
        return this->is_engaged() ? srook::move(this->get()) 
            : this->is_error_engaged() ? (detail::throw_expected_error(this->get_error()), srook::move(this->get())) 
            : (detail::throw_bad_expected_access(), srook::move(this->get()));
    }
    
    SROOK_CONSTEXPR value_type&& value() const&&
    {
        return this->is_engaged() ? srook::move(this->get()) 
            : this->is_error_engaged() ? (detail::throw_expected_error(this->get_error()), srook::move(this->get())) 
            : (detail::throw_bad_expected_access(), srook::move(this->get()));
    }
    
    template <class U, SROOK_REQUIRES(is_convertible<SROOK_DEDUCED_TYPENAME decay<U>::type, value_type>::value)>
    SROOK_CONSTEXPR value_type value_or(U&& u) const& SROOK_NOEXCEPT_TRUE
    {
        SROOK_ST_ASSERT((is_move_constructible<value_type>::value));
        SROOK_ST_ASSERT((is_move_constructible<error_type>::value));

        return this->is_engaged() ? this->get() : srook::forward<U>(u);
    }

    template <class U, SROOK_REQUIRES(is_convertible<SROOK_DEDUCED_TYPENAME decay<U>::type, value_type>::value)>
    SROOK_CONSTEXPR value_type&& value_or(U&& u) && SROOK_NOEXCEPT_TRUE
    {
        SROOK_ST_ASSERT((is_move_constructible<value_type>::value));
        SROOK_ST_ASSERT((is_move_constructible<error_type>::value));

        return this->is_engaged() ? srook::move(this->get()) : srook::forward<U>(u);
    }
    
    void reset() 
    SROOK_NOEXCEPT((type_traits::detail::Land<is_nothrow_destructible<value_type>, is_nothrow_destructible<error_type>>::value))
    {
        base_type::reset();
    }

    SROOK_CONSTEXPR bool any_valid() const SROOK_NOEXCEPT_TRUE
    {
        return this->is_any_engaged();
    }

    template <class F, SROOK_REQUIRES(is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type>::value)>
    friend SROOK_FORCE_INLINE expected
    operator>>=(const expected& this_, F&& f) SROOK_NOEXCEPT(declval<F>()(declval<value_type>()))
    {
        return this_ ? srook::invoke(srook::forward<F>(f), *this_) : this_;
    }

    template <class F, SROOK_REQUIRES(is_invocable<SROOK_DEDUCED_TYPENAME decay<F>::type, value_type>::value)>
    SROOK_FORCE_INLINE expected map(F&& f) SROOK_NOEXCEPT(declval<F>()(declval<value_type>()))
    {
        return *this ? *this >>= srook::forward<F>(f) : *this;
    }
};

template <class T>
SROOK_CONSTEXPR expected<SROOK_DEDUCED_TYPENAME decay<T>::type> make_expected(const T& v)
SROOK_NOEXCEPT((
    type_traits::detail::Land<
        is_nothrow_move_constructible<SROOK_DEDUCED_TYPENAME decay<T>::type>, 
        is_nothrow_copy_constructible<SROOK_DEDUCED_TYPENAME decay<T>::type>
    >::value
))
{
    return expected<SROOK_DEDUCED_TYPENAME decay<T>::type, std::exception_ptr>{ set_value, v };
}

template <class T, class E>
SROOK_CONSTEXPR expected<SROOK_DEDUCED_TYPENAME decay<T>::type, SROOK_DEDUCED_TYPENAME decay<E>::type> make_expected(const T& v)
SROOK_NOEXCEPT((
    type_traits::detail::Land<
        is_nothrow_move_constructible<SROOK_DEDUCED_TYPENAME decay<T>::type>,
        is_nothrow_copy_constructible<SROOK_DEDUCED_TYPENAME decay<T>::type>
    >::value
))
{
    return expected<SROOK_DEDUCED_TYPENAME decay<T>::type, SROOK_DEDUCED_TYPENAME decay<E>::type>{ set_value, v };
}

template <class T>
SROOK_CONSTEXPR expected<SROOK_DEDUCED_TYPENAME decay<T>::type> make_expected(T&& v)
SROOK_NOEXCEPT((
    type_traits::detail::Land<
        is_nothrow_move_constructible<SROOK_DEDUCED_TYPENAME decay<T>::type>, 
        is_nothrow_copy_constructible<SROOK_DEDUCED_TYPENAME decay<T>::type>
    >::value
))
{
    return expected<SROOK_DEDUCED_TYPENAME decay<T>::type, std::exception_ptr>{ set_value, srook::move(v) };
}

template <class T, class E>
SROOK_CONSTEXPR expected<SROOK_DEDUCED_TYPENAME decay<T>::type, SROOK_DEDUCED_TYPENAME decay<E>::type> make_expected(T&& v)
SROOK_NOEXCEPT((
    type_traits::detail::Land<
        is_nothrow_move_constructible<SROOK_DEDUCED_TYPENAME decay<T>::type>,
        is_nothrow_copy_constructible<SROOK_DEDUCED_TYPENAME decay<T>::type>
    >::value
))
{
    return expected<SROOK_DEDUCED_TYPENAME decay<T>::type, SROOK_DEDUCED_TYPENAME decay<E>::type>{ set_value, srook::move(v) };
}

SROOK_INLINE_NAMESPACE_END
} // namespace exception

using exception::expected;
using exception::bad_expected_access;
using exception::set_error;
using exception::set_error_t;
using exception::set_value;
using exception::set_value_t;
using exception::make_expected;

} // namespace srook

#endif
#endif
