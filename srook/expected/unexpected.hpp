// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_EXPECTED_UNEXPECTED_HPP
#define INCLUDED_SROOK_EXPECTED_UNEXPECTED_HPP

#include <srook/config.hpp>
#include <srook/type_traits.hpp>
#include <srook/utility.hpp>
#include <stdexcept>
#if SROOK_HAS_INCLUDE(<boost/exception_ptr.hpp>) && SROOK_CONFIG_ENABLE_USE_BOOST_EXCEPTION_PTR
#   include <boost/exception_ptr.hpp>
#   define SROOK_HAS_BOOST_EXCEPTION_PTR 1
#endif
#if 0 && SROOK_HAS_INCLUDE(<cmp>) // C++20 feature
#   include <cmp>
#endif

namespace srook {
namespace exception {
SROOK_INLINE_NAMESPACE(v1)

template <class ErrorT = std::exception_ptr>
class unexpected {
    typedef SROOK_DEDUCED_TYPENAME remove_cv<ErrorT>::type error_type;
    error_type er_;
public:
    unexpected() SROOK_EQ_DELETE

    template <SROOK_REQUIRES(is_copy_constructible<error_type>::value)>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR explicit unexpected(const error_type& er)
        : er_(er) {}
    template <SROOK_REQUIRES(is_move_constructible<error_type>::value)>
    SROOK_FORCE_INLINE SROOK_CONSTEXPR explicit unexpected(error_type&& er)
        : er_(srook::move(er)) {}

    SROOK_CONSTEXPR SROOK_FORCE_INLINE const error_type& value() const& { return er_; }
    SROOK_CONSTEXPR SROOK_FORCE_INLINE error_type& value() & { return er_; }
    SROOK_CONSTEXPR SROOK_FORCE_INLINE error_type&& value() && { return srook::move(er_); }

#if 0 // C++20 feature
    std::strong_ordering operator<=>(const unexpected& rhs) = default;
#endif
};

template <>
class unexpected<std::exception_ptr> {
    typedef std::exception_ptr error_type;
    error_type er_;
public:
    unexpected() SROOK_EQ_DELETE

    SROOK_FORCE_INLINE explicit unexpected(const error_type& e)
        : er_(e) {}
    SROOK_FORCE_INLINE explicit unexpected(error_type&& e)
        : er_(srook::move(e)) {}
    template <class E>
    SROOK_FORCE_INLINE explicit unexpected(E&& e)
        : er_(std::make_exception_ptr(srook::forward<E>(e))) {}
    SROOK_FORCE_INLINE const error_type& value() const { return er_; }

#if 0 // C++20 feature
    std::strong_equality operator<=>(const unexpected& rhs) = default;

    friend SROOK_CONSTEXPR bool operator<(const unexpected&, const unexpected&){ return false; }
    friend SROOK_CONSTEXPR bool operator>(const unexpected&, const unexpected&){ return false; }
    friend SROOK_CONSTEXPR bool operator<=(const unexpected& lhs, const unexpected& rhs) const SROOK_NOEXCEPT_TRUE { return lhs == rhs; }
    friend SROOK_CONSTEXPR bool operator>=(const unexpected& lhs, const unexpected& rhs) const SROOK_NOEXCEPT_TRUE { return lhs == rhs; }
#endif
};

#if SROOK_HAS_BOOST_EXCEPTION_PTR
template <>
class unexpected<boost::exception_ptr> {
    typedef boost::exception_ptr error_type;
    error_type er_;
public:
    unexpected() SROOK_EQ_DELETE

    SROOK_FORCE_INLINE explicit unexpected(const error_type& e)
        : er_(e) {}
    SROOK_FORCE_INLINE explicit unexpected(error_type&& e)
        : er_(srook::move(e)) {}
    template <class E>
    SROOK_FORCE_INLINE explicit unexpected(E&& e)
        : er_(boost::copy_exception(srook::forward<E>(e))) {}
    SROOK_FORCE_INLINE const error_type& value() const { return er_; }

#if 0 // C++20 feature
    std::strong_equality operator<=>(const unexpected& rhs) = default;
    
    friend SROOK_CONSTEXPR bool operator<(const unexpected&, const unexpected&){ return false; }
    friend SROOK_CONSTEXPR bool operator>(const unexpected&, const unexpected&){ return false; }
    friend SROOK_CONSTEXPR bool operator<=(const unexpected& lhs, const unexpected& rhs) const SROOK_NOEXCEPT_TRUE { return lhs == rhs; }
    friend SROOK_CONSTEXPR bool operator>=(const unexpected& lhs, const unexpected& rhs) const SROOK_NOEXCEPT_TRUE { return lhs == rhs; }
#endif
};
#endif

#if 1
template <class E, class F>
SROOK_CONSTEXPR const unexpected<E>& operator>>=(const unexpected<E>& lhs, F&&) { return lhs; }        
template <class E>
SROOK_CONSTEXPR bool operator==(const unexpected<E>& lhs, const unexpected<E>& rhs) { return lhs.value() == rhs.value(); }
template <class E>
SROOK_CONSTEXPR bool operator!=(const unexpected<E>& lhs, const unexpected<E>& rhs) { return !(lhs == rhs); }
template <class E>
SROOK_CONSTEXPR bool operator<(const unexpected<E>& lhs, const unexpected<E>& rhs) { return lhs.value() < rhs.value(); }
template <class E>
SROOK_CONSTEXPR bool operator>(const unexpected<E>& lhs, const unexpected<E>& rhs) { return (rhs < lhs); }
template <class E>
SROOK_CONSTEXPR bool operator<=(const unexpected<E>& lhs, const unexpected<E>& rhs) { return !(rhs < lhs); }
template <class E>
SROOK_CONSTEXPR bool operator>=(const unexpected<E>& lhs, const unexpected<E>& rhs) { return !(lhs < rhs); }
inline SROOK_CONSTEXPR bool operator<(const unexpected<std::exception_ptr>&, const unexpected<std::exception_ptr>&) { return false; }
inline SROOK_CONSTEXPR bool operator>(const unexpected<std::exception_ptr>&, const unexpected<std::exception_ptr>&) { return false; }
inline SROOK_CONSTEXPR bool operator<=(const unexpected<std::exception_ptr>& lhs, const unexpected<std::exception_ptr>& rhs) { return lhs == rhs; }
inline SROOK_CONSTEXPR bool operator>=(const unexpected<std::exception_ptr>& lhs, const unexpected<std::exception_ptr>& rhs) { return lhs == rhs; }

#if SROOK_HAS_BOOST_EXCEPTION_PTR
inline SROOK_CONSTEXPR bool operator<(const unexpected<boost::exception_ptr>&, const unexpected<boost::exception_ptr>&) { return false; }
inline SROOK_CONSTEXPR bool operator>(const unexpected<boost::exception_ptr>&, const unexpected<boost::exception_ptr>&) { return false; }
inline SROOK_CONSTEXPR bool operator<=(const unexpected<boost::exception_ptr>& lhs, const unexpected<boost::exception_ptr>& rhs) { return lhs == rhs; }
inline SROOK_CONSTEXPR bool operator>=(const unexpected<boost::exception_ptr>& lhs, const unexpected<boost::exception_ptr>& rhs) { return lhs == rhs; }
#endif

#endif

template <class E>
SROOK_FORCE_INLINE SROOK_CONSTEXPR unexpected<SROOK_DEDUCED_TYPENAME decay<E>::type> make_unexpected(E&& e)
{
    return unexpected<SROOK_DEDUCED_TYPENAME decay<E>::type>(srook::forward<E>(e));
}

SROOK_FORCE_INLINE unexpected<std::exception_ptr> make_unexpected_from_current_exception()
{
    return unexpected<std::exception_ptr>(std::current_exception());
}

template <class E>
struct is_unexpected : SROOK_FALSE_TYPE {};
template <class E>
struct is_unexpected<unexpected<E>> : SROOK_TRUE_TYPE {};

SROOK_INLINE_NAMESPACE_END
} // namespace exception

using exception::unexpected;
using exception::is_unexpected;
using exception::make_unexpected;
using exception::make_unexpected_from_current_exception;

} // namespace srook

#endif
