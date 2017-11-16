// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_OPTIONAL_HPP
#define INCLUDED_SROOK_OPTIONAL_HPP
#include <srook/config/cpp_predefined.hpp>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <cassert>
#    include <initializer_list>
#    include <new>
#    include <srook/config/attribute.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/memory/addressof.hpp>
#    include <srook/type_traits.hpp>
#    include <srook/utility.hpp>
#    include <stdexcept>
#    include <type_traits>
#    if SROOK_HAS_INCLUDE(<optional>) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#        include <optional>
#        define SROOK_HAS_STD_OPTIONAL 1
#    endif
#    if __has_include(<boost/optional.hpp>)
#        include <boost/optional.hpp>
#        define SROOK_HAS_BOOST_OPTIONAL 1
#    endif
#    include <optional>

namespace srook {
namespace optionally {
SROOK_INLINE_NAMESPACE(v1)

template <class>
class optional;

struct nullopt_t {
    SROOK_STRONG_ENUM_BEGIN(Construct){
        Token
	};
    SROOK_STRONG_ENUM_EPILOG(Construct)
    explicit SROOK_CONSTEXPR nullopt_t(Construct) {}
};
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR
    nullopt_t nullopt{ nullopt_t::Construct::Token };

class bad_optional_access : public std::exception {
public:
    bad_optional_access() SROOK_DEFAULT

    virtual const char* what() const
    SROOK_NOEXCEPT_TRUE SROOK_OVERRIDE
    {
        return "bad optional access";
    }

    virtual ~bad_optional_access() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
};

template <class>
class optional;

namespace detail {

SROOK_FORCE_INLINE SROOK_NORETURN void throw_bad_optional_access() { SROOK_THROW bad_optional_access(); }

template <class T,
          bool = type_traits::detail::Land<std::is_trivially_copy_constructible<T>, std::is_trivially_move_constructible<T> >::value,
          bool = std::is_trivially_destructible<T>::value>
struct optional_payload {
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
    SROOK_CONSTEXPR optional_payload(bool, const optional_payload& other)
        : optional_payload(other) {}
    SROOK_CONSTEXPR optional_payload(bool, optional_payload&& other)
        : optional_payload(srook::move(other)) {}
    SROOK_CONSTEXPR optional_payload(const optional_payload& other)
    {
        if (other.engaged_) construct(other.payload_);
    }
    SROOK_CONSTEXPR optional_payload(optional_payload&& other)
    {
        if (other.engaged_) construct(srook::move(other.payload_));
    }

    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type Stored_type;
    struct Empty_byte {};
    union {
        Empty_byte empty_;
        Stored_type payload_;
    };
    bool engaged_ = false;

    ~optional_payload()
    {
        if (engaged_) payload_.~Stored_type();
    }

    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<Stored_type, Args...>::value))
    {
        ::new ((void*)addressof(payload_)) Stored_type(srook::forward<Args>(args)...);
        engaged_ = true;
    }
};

template <class T>
struct optional_payload<T, false, true> {
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
    SROOK_CONSTEXPR optional_payload(const optional_payload& other)
    {
        if (other.engaged_) construct(other.payload_);
    }
    SROOK_CONSTEXPR optional_payload(optional_payload&& other)
    {
        if (other.engaged) construct(srook::move(other.payload_));
    }

    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type Stored_type;
    struct Empty_byte {};
    union {
        Empty_byte empty_;
        Stored_type payload_;
    };
    bool engaged_ = false;

	// trivially destructible...

    template <class... Args>
    void construct(Args&&... args)
    SROOK_MEMFN_NOEXCEPT((is_nothrow_constructible<Stored_type, Args...>::value))
    {
        ::new ((void*)addressof(payload_)) Stored_type(srook::forward<Args>(args)...);
        engaged_ = true;
    }
};

template <class T>
class optional_base {
    typedef SROOK_DEDUCED_TYPENAME remove_const<T>::type Stored_type;

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
        : payload_(other.payload_.engaged_, other.payload_) {}
    SROOK_CONSTEXPR optional_base(optional_base&& other)
        SROOK_NOEXCEPT(is_nothrow_constructible<T>::value)
        : payload_(other.payload_.engaged_, srook::move(other.payload_)) {}
    optional_base& operator=(const optional_base& other)
    {
        if (payload_.engaged_ && other.payload_.engaged_) {
            get() = other.get();
        } else {
            if (other.payload_.engaged_) {
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
        if (payload_.engaged_ && other.payload_.engaged_) {
            get() = srook::move(other.get());
        } else {
            if (other.payload_.engaged_) {
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
        return payload_.engaged_;
    }
    SROOK_CONSTEXPR T& get() SROOK_NOEXCEPT_TRUE
    {
        assert(is_engaged());
        return payload_.payload_;
    }
    SROOK_CONSTEXPR const T& get() const SROOK_NOEXCEPT_TRUE
    {
        assert(is_engaged());
        return payload_.payload_;
    }
    template <class... Args>
    void construct(Args&&... args)
    SROOK_NOEXCEPT((is_nothrow_constructible<Stored_type, Args...>::value))
    {
        ::new (addressof(payload_.payload_)) Stored_type(srook::forward<Args>(args)...);
        payload_.engaged_ = true;
    }
    void destruct()
    SROOK_NOEXCEPT((is_nothrow_destructible<Stored_type>::value))
    {
        payload_.engaged_ = false;
        payload_.payload_.~Stored_type();
    }
    void reset()
    {
        if (payload_.engaged_) destruct();
    }

private:
    optional_payload<T> payload_;
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

template <class T>
class optional
    : private detail::optional_base<T>,
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
    typedef detail::optional_base<T> Base_type;

public:
    typedef T value_type;

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

#    define DEF_OPERATOR(X)                                   \
        optional& operator=(X::nullopt_t) SROOK_NOEXCEPT_TRUE \
        {                                                     \
            reset();                                          \
            return *this;                                     \
        }
    DEF_OPERATOR(optionally)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_OPERATOR(std)
#    endif
#    if SROOK_HAS_BOOST_OPTIONAL
    optional& operator=(boost::none_t) SROOK_NOEXCEPT_TRUE
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
        optional&>::type
    operator=(U&& u)
    {
        if (Base_type::is_engaged())
            Base_type::get() = srook::forward<U>(u);
        else
            construct(srook::forward<U>(u));
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
            optional&>::type                                                             \
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
            optional&>::type                                                             \
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
        construct(srook::forward<Args>(args)...);
        return Base_type::get();
    }

    template <class U, class... Args>
    SROOK_DEDUCED_TYPENAME enable_if<is_constructible<T, std::initializer_list<U>&, Args&&...>::value, T&>::type
    emplace(std::initializer_list<U> li, Args&&... args)
    {
        reset();
        construct(li, srook::forward<Args>(args)...);
        return Base_type::get();
    }

    void swap(optional& other)
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

    SROOK_CONSTEXPR const T* operator->() const { return addressof(Base_type::get()); }
    T* operator->() { return addressof(Base_type::get()); }
    SROOK_CONSTEXPR const T& operator*() const& { return Base_type::get(); }
    SROOK_CONSTEXPR T& operator*() & { return Base_type::get(); }
    SROOK_CONSTEXPR T&& operator*() && { return srook::move(Base_type::get()); }
    SROOK_CONSTEXPR T&& operator*() const&& { return srook::move(Base_type::get()); }
    SROOK_CONSTEXPR SROOK_EXPLICIT operator bool() const SROOK_NOEXCEPT_TRUE { return Base_type::is_engaged(); }
    SROOK_CONSTEXPR bool has_value() const SROOK_NOEXCEPT_TRUE { return Base_type::is_engaged(); }

    SROOK_CONSTEXPR const T& value() const&
    {
        return Base_type::is_engaged() ? Base_type::get() : (detail::throw_bad_optional_access(), Base_type::get());
    }
    SROOK_CONSTEXPR T& value() &
    {
        return Base_type::is_engaged() ? Base_type::get() : (detail::throw_bad_optional_access(), Base_type::get());
    }
    SROOK_CONSTEXPR T&& value() &&
    {
        return Base_type::is_engaged() ? srook::move(Base_type::get()) : (detail::throw_bad_optional_access(), srook::move(Base_type::get()));
    }
    SROOK_CONSTEXPR const T& value() const&&
    {
        return Base_type::is_engaged() ? srook::move(Base_type::get()) : (detail::throw_bad_optional_access(), srook::move(Base_type::get()));
    }
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

#    define DEF_OPERATORS(X, Y, NULLOP)                                                                          \
        template <class L, class R>                                                                              \
        friend SROOK_CONSTEXPR auto operator==(const X::optional<L>& lhs, const Y::optional<R>& rhs)             \
        -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() == declval<R>()))>                                \
        {                                                                                                        \
            return static_cast<bool>(lhs) == static_cast<bool>(rhs) && (!lhs || *lhs == *rhs);                   \
        }                                                                                                        \
        template <class L, class R>                                                                              \
        friend SROOK_CONSTEXPR auto operator!=(const X::optional<L>& lhs, const Y::optional<R>& rhs)             \
        ->detail::optional_relop<SROOK_DECLTYPE((declval<L>() != declval<R>()))>                                 \
        {                                                                                                        \
            return static_cast<bool>(lhs) != static_cast<bool>(rhs) || (static_cast<bool>(lhs) && *lhs != *rhs); \
        }                                                                                                        \
        template <class L, class R>                                                                              \
        friend SROOK_CONSTEXPR auto operator<(const X::optional<L>& lhs, const Y::optional<R>& rhs)              \
        -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() < declval<R>()))>                                 \
        {                                                                                                        \
            return static_cast<bool>(rhs) && (!lhs || *lhs < *rhs);                                              \
        }                                                                                                        \
        template <class L, class R>                                                                              \
        friend SROOK_CONSTEXPR auto operator>(const X::optional<L>& lhs, const Y::optional<R>& rhs)              \
        -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() > declval<R>()))>                                 \
        {                                                                                                        \
            return static_cast<bool>(lhs) && (!rhs || *lhs > *rhs);                                              \
        }                                                                                                        \
        template <class L, class R>                                                                              \
        friend SROOK_CONSTEXPR auto operator<=(const X::optional<L>& lhs, const Y::optional<R>& rhs)             \
        -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() <= declval<R>()))>                                \
        {                                                                                                        \
            return !lhs || (static_cast<bool>(rhs) && *lhs <= *rhs);                                             \
        }                                                                                                        \
        template <class L, class R>                                                                              \
        friend SROOK_CONSTEXPR auto operator>=(const X::optional<L>& lhs, const Y::optional<R>& rhs)             \
        -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() >= declval<R>()))>                                \
        {                                                                                                        \
            return !rhs || (static_cast<bool>(lhs) && *lhs >= *rhs);                                             \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator==(const X::optional<U>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE         \
        {                                                                                                        \
            return !lhs;                                                                                         \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator==(X::NULLOP, const Y::optional<U>& rhs) SROOK_NOEXCEPT_TRUE         \
        {                                                                                                        \
            return !rhs;                                                                                         \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator!=(const X::optional<T>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE         \
        {                                                                                                        \
            return static_cast<bool>(lhs);                                                                       \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator!=(X::NULLOP, const Y::optional<T>& rhs) SROOK_NOEXCEPT_TRUE         \
        {                                                                                                        \
            return static_cast<bool>(rhs);                                                                       \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator<(const X::optional<U>&, Y::NULLOP) SROOK_NOEXCEPT_TRUE              \
        {                                                                                                        \
            return false;                                                                                        \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator<(X::NULLOP, const Y::optional<U>& rhs) SROOK_NOEXCEPT_TRUE          \
        {                                                                                                        \
            return static_cast<bool>(rhs);                                                                       \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator>(const X::optional<U>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE          \
        {                                                                                                        \
            return static_cast<bool>(lhs);                                                                       \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator>(X::NULLOP, const Y::optional<U>&) SROOK_NOEXCEPT_TRUE              \
        {                                                                                                        \
            return false;                                                                                        \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator<=(const X::optional<U>& lhs, Y::NULLOP) SROOK_NOEXCEPT_TRUE         \
        {                                                                                                        \
            return !lhs;                                                                                         \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator<=(X::NULLOP, const Y::optional<U>&) SROOK_NOEXCEPT_TRUE             \
        {                                                                                                        \
            return true;                                                                                         \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator>=(const X::optional<U>&, Y::NULLOP) SROOK_NOEXCEPT_TRUE             \
        {                                                                                                        \
            return true;                                                                                         \
        }                                                                                                        \
        template <class U>                                                                                       \
        friend SROOK_CONSTEXPR bool operator>=(X::NULLOP, const Y::optional<U>& rhs) SROOK_NOEXCEPT_TRUE         \
        {                                                                                                        \
            return !rhs;                                                                                         \
        }
    DEF_OPERATORS(optionally, optionally, nullopt_t)
#    if SROOK_HAS_STD_OPTIONAL
    DEF_OPERATORS(optionally, std, nullopt_t)
    DEF_OPERATORS(std, optionally, nullopt_t)
#    endif
#    if SROOK_HAS_BOOST_OPTIONAL
#        undef DEF_OPERATORS
#        define DEF_OPERATORS(X, Y)                                                                                  \
            template <class L, class R>                                                                              \
            friend SROOK_CONSTEXPR auto operator==(const X::optional<L>& lhs, const Y::optional<R>& rhs)             \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() == declval<R>()))>                                \
            {                                                                                                        \
                return static_cast<bool>(lhs) == static_cast<bool>(rhs) && (!lhs || *lhs == *rhs);                   \
            }                                                                                                        \
            template <class L, class R>                                                                              \
            friend SROOK_CONSTEXPR auto operator!=(const X::optional<L>& lhs, const Y::optional<R>& rhs)             \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() != declval<R>()))>                                \
            {                                                                                                        \
                return static_cast<bool>(lhs) != static_cast<bool>(rhs) || (static_cast<bool>(lhs) && *lhs != *rhs); \
            }                                                                                                        \
            template <class L, class R>                                                                              \
            friend SROOK_CONSTEXPR auto operator<(const X::optional<L>& lhs, const Y::optional<R>& rhs)              \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() < declval<R>()))>                                 \
            {                                                                                                        \
                return static_cast<bool>(rhs) && (!lhs || *lhs < *rhs);                                              \
            }                                                                                                        \
            template <class L, class R>                                                                              \
            friend SROOK_CONSTEXPR auto operator>(const X::optional<L>& lhs, const Y::optional<R>& rhs)              \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() > declval<R>()))>                                 \
            {                                                                                                        \
                return static_cast<bool>(lhs) && (!rhs || *lhs > *rhs);                                              \
            }                                                                                                        \
            template <class L, class R>                                                                              \
            friend SROOK_CONSTEXPR auto operator<=(const X::optional<L>& lhs, const Y::optional<R>& rhs)             \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() <= declval<R>()))>                                \
            {                                                                                                        \
                return !lhs || (static_cast<bool>(rhs) && *lhs <= *rhs);                                             \
            }                                                                                                        \
            template <class L, class R>                                                                              \
            friend SROOK_CONSTEXPR auto operator>=(const X::optional<L>& lhs, const Y::optional<R>& rhs)             \
            -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() >= declval<R>()))>                                \
            {                                                                                                        \
                return !rhs || (static_cast<bool>(lhs) && *lhs >= *rhs);                                             \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator==(const X::optional<U>& lhs, boost::none_t) SROOK_NOEXCEPT_TRUE     \
            {                                                                                                        \
                return !lhs;                                                                                         \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator==(boost::none_t, const Y::optional<U>& rhs) SROOK_NOEXCEPT_TRUE     \
            {                                                                                                        \
                return !rhs;                                                                                         \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator!=(const X::optional<T>& lhs, boost::none_t) SROOK_NOEXCEPT_TRUE     \
            {                                                                                                        \
                return static_cast<bool>(lhs);                                                                       \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator!=(boost::none_t, const Y::optional<T>& rhs) SROOK_NOEXCEPT_TRUE     \
            {                                                                                                        \
                return static_cast<bool>(rhs);                                                                       \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator<(const X::optional<U>&, boost::none_t) SROOK_NOEXCEPT_TRUE          \
            {                                                                                                        \
                return false;                                                                                        \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator<(boost::none_t, const Y::optional<U>& rhs) SROOK_NOEXCEPT_TRUE      \
            {                                                                                                        \
                return static_cast<bool>(rhs);                                                                       \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator>(const X::optional<U>& lhs, boost::none_t) SROOK_NOEXCEPT_TRUE      \
            {                                                                                                        \
                return static_cast<bool>(lhs);                                                                       \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator>(boost::none_t, const Y::optional<U>&) SROOK_NOEXCEPT_TRUE          \
            {                                                                                                        \
                return false;                                                                                        \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator<=(const X::optional<U>& lhs, boost::none_t) SROOK_NOEXCEPT_TRUE     \
            {                                                                                                        \
                return !lhs;                                                                                         \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator<=(boost::none_t, const Y::optional<U>&) SROOK_NOEXCEPT_TRUE         \
            {                                                                                                        \
                return true;                                                                                         \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator>=(const X::optional<U>&, boost::none_t) SROOK_NOEXCEPT_TRUE         \
            {                                                                                                        \
                return true;                                                                                         \
            }                                                                                                        \
            template <class U>                                                                                       \
            friend SROOK_CONSTEXPR bool operator>=(boost::none_t, const Y::optional<U>& rhs) SROOK_NOEXCEPT_TRUE     \
            {                                                                                                        \
                return !rhs;                                                                                         \
            }
    DEF_OPERATORS(boost, optionally)
    DEF_OPERATORS(optionally, boost)
#    endif
#    undef DEF_OPERATORS

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator==(const optional<L>& lhs, const R& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() == declval<R>()))>
    {
        return lhs && *lhs == rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator==(const L& lhs, const optional<R>& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() == declval<R>()))>
    {
        return rhs && lhs == *rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator!=(const optional<L>& lhs, const R& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() != declval<R>()))>
    {
        return !lhs || *lhs != rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator!=(const L& lhs, const optional<R>& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() != declval<R>()))>
    {
        return !rhs || lhs != *rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator<(const optional<L>& lhs, const R& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() < declval<R>()))>
    {
        return !lhs || *lhs < rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator<(const L& lhs, const optional<R>& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() < declval<R>()))>
    {
        return rhs && lhs < *rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator>(const optional<L>& lhs, const R& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() > declval<R>()))>
    {
        return lhs && *lhs > rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator>(const L& lhs, const optional<R>& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() > declval<R>()))>
    {
        return !rhs || lhs > *rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator<=(const optional<L>& lhs, const R& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() <= declval<R>()))>
    {
        return !lhs || *lhs <= rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator<=(const L& lhs, const optional<R>& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() <= declval<R>()))>
    {
        return rhs && lhs <= *rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator>=(const optional<L>& lhs, const R& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() >= declval<R>()))>
    {
        return lhs && *lhs >= rhs;
    }

    template <class L, class R>
    friend SROOK_CONSTEXPR auto operator>=(const L& lhs, const optional<R>& rhs)
    -> detail::optional_relop<SROOK_DECLTYPE((declval<L>() >= declval<R>()))>
    {
        return !rhs || lhs >= *rhs;
    }
};

#    define DEF_SWAP(X, Y)                                                                                                      \
        template <class T>                                                                                                      \
        SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME                                                                               \
        enable_if<type_traits::detail::Land<is_move_constructible<T>, is_swappable<T> >::value>::type                           \
        swap(X::optional<T>& lhs, Y::optional<T>& rhs)                                                                          \
        SROOK_NOEXCEPT(lhs.swap(rhs))                                                                                           \
        {                                                                                                                       \
            lhs.swap(rhs);                                                                                                      \
        }                                                                                                                       \
        template <class T>                                                                                                      \
        SROOK_DEDUCED_TYPENAME                                                                                                  \
        enable_if<                                                                                                              \
            type_traits::detail::Lnot<type_traits::detail::Land<is_move_constructible<T>, is_swappable<T> > >::value>::type     \
        swap(X::optional<T>&, Y::optional<T>&) SROOK_EQ_DELETE
DEF_SWAP(optionally, optionally)
#    if SROOK_HAS_STD_OPTIONAL
DEF_SWAP(optionally, std)
DEF_SWAP(std, optionally)
#    endif
#    undef DEF_SWAP

template <class T>
SROOK_CONSTEXPR optional<SROOK_DEDUCED_TYPENAME decay<T>::type> make_optional(T&& t)
{
    return optional<SROOK_DEDUCED_TYPENAME decay<T>::type>(srook::forward<T>(t));
}

template <class T, class... Args>
SROOK_CONSTEXPR optional<T>
make_optional(Args&&... args)
{
    return optional<T>(in_place, srook::forward<Args>(args)...);
}

template <class T, class U, class... Args>
SROOK_CONSTEXPR optional<T>
make_optional(std::initializer_list<U> li, Args&&... args)
{
    return optional<T>(in_place, li, srook::forward<Args>(args)...);
}

// TASK: specialize hash

//#undef SROOK_HAS_STD_OPTIONAL
//#undef SROOK_HAS_BOOST_OPTIONAL
SROOK_INLINE_NAMESPACE_END
} // namespace optionally

using optionally::make_optional;
using optionally::nullopt;
using optionally::nullopt_t;
using optionally::optional;
using optionally::swap;

} // namespace srook
#    endif
#endif
