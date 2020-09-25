// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_NUMERIC_FIXED_POINT_FIXED_POINT_HPP
#define INCLUDED_SROOK_NUMERIC_FIXED_POINT_FIXED_POINT_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/numeric/fixed_point/detail/config.hpp>
#include <srook/math/constants/algorithm/isnan.hpp>
#include <srook/math/constants/algorithm/isinf.hpp>
#include <srook/functional/op.hpp>
#include <srook/algorithm/max.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/bit/algorithm/nlz.hpp>
#include <srook/tmpl/vt/compare/lt.hpp>
#include <ostream>
#include <stdexcept>
#ifdef SROOK_FUNC_NAME
#   include <string>
#   define SROOK_FIXED_POINT_THROW_OVERFLOW(x) SROOK_THROW std::overflow_error(std::string("srook::numeric_limits::fixed_point::") + SROOK_FUNC_NAME + ": " + #x)
#   define SROOK_FIXED_POINT_THROW_UNDERFLOW(x) SROOK_THROW std::underflow_error(std::string("srook::numeric_limits::fixed_point::") + SROOK_FUNC_NAME + ": " + #x)
#else
#   define SROOK_FIXED_POINT_THROW_OVERFLOW SROOK_THROW std::overflow_error("srook::numeric_limits::fixed_point: " #x)
#   define SROOK_FIXED_POINT_THROW_UNDERFLOW SROOK_THROW std::underflow_error("srook::numeric_limits::fixed_point: " #x)
#endif

SROOK_NESTED_NAMESPACE(srook, numeric) {
SROOK_INLINE_NAMESPACE(v1)

template <std::size_t I, std::size_t F>
class fixed_point {
public:
    struct fixed_point_tag {}; // composed only
    typedef detail::fixed_point_traits<I + F> traits_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::size_type size_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::value_type value_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::next_fixed_point::value_type next_value_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::unsigned_type unsigned_value_type;

    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST size_type fractional_bits = F;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST size_type integer_bits = I;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST size_type total_bits = I + F;
    static SROOK_INLINE_VARIABLE const value_type fractional_mask = ~((~value_type(0)) << fractional_bits);
    static SROOK_INLINE_VARIABLE const value_type integer_mask = ~fractional_mask;
    static SROOK_INLINE_VARIABLE SROOK_CONSTEXPR_OR_CONST value_type one = value_type(1) << fractional_bits;

    SROOK_CONSTEXPR fixed_point() SROOK_DEFAULT
    SROOK_CONSTEXPR fixed_point(const fixed_point&) SROOK_DEFAULT

    template <typename ValueType, SROOK_REQUIRES(type_traits::detail::Land<type_traits::detail::Lnot<is_same<ValueType, fixed_point>>, is_integral<ValueType>>::value)>
    fixed_point(ValueType n) SROOK_NOEXCEPT(false) 
        : data_(assert_integer(srook::move(n), SROOK_DEDUCED_TYPENAME compare<ValueType>::type())) {}

    template <typename ValueType, SROOK_REQUIRES(type_traits::detail::Land<type_traits::detail::Lnot<is_same<ValueType, fixed_point>>, is_floating_point<ValueType>>::value)>
    fixed_point(ValueType n) SROOK_NOEXCEPT(false)
        : data_(assert_floating(srook::move(n))) {}

    static SROOK_CONSTEXPR fixed_point from_value(value_type n) SROOK_NOEXCEPT(is_nothrow_constructible<value_type>::value) 
    { 
        return fixed_point(srook::move(n), noscale()); 
    }

#if 0 && SROOK_HAS_INCLUDE(<compare>)
    SROOK_CONSTEXPR std::strong_ordering operator<=>(const fixed_point& other) const SROOK_NOEXCEPT_TRUE
    {
        return data_ <=> other.data_;
    }
#else
    SROOK_CONSTEXPR bool operator==(const fixed_point& other) const SROOK_NOEXCEPT_TRUE { return data_ == other.data_; }
    SROOK_CONSTEXPR bool operator!=(const fixed_point& other) const SROOK_NOEXCEPT_TRUE { return !(*this == other); }
    SROOK_CONSTEXPR bool operator<(const fixed_point& other) const SROOK_NOEXCEPT_TRUE { return data_ < other.data_; }
    SROOK_CONSTEXPR bool operator<=(const fixed_point& other) const SROOK_NOEXCEPT_TRUE { return *this == other || *this < other; }
    SROOK_CONSTEXPR bool operator>(const fixed_point& other) const SROOK_NOEXCEPT_TRUE { return !(*this <= other); }
    SROOK_CONSTEXPR bool operator>=(const fixed_point& other) const SROOK_NOEXCEPT_TRUE { return *this > other || *this == other; }
#endif
    SROOK_CONSTEXPR bool operator!() const SROOK_NOEXCEPT_TRUE 
    { 
        return !data_; 
    }
    
    SROOK_CXX14_CONSTEXPR fixed_point operator~() const SROOK_NOEXCEPT_TRUE
    {
        fixed_point t(*this);
        t.data_ = static_cast<value_type>(~t.data_);
        return t;
    }

    SROOK_CXX14_CONSTEXPR fixed_point operator-() const SROOK_NOEXCEPT_TRUE
    {
        fixed_point t(*this);
        t.data_ = static_cast<value_type>(-t.data_);
        return t;
    }

    SROOK_CONSTEXPR fixed_point operator+() const SROOK_NOEXCEPT_TRUE 
    {
        return *this; 
    }

    SROOK_FORCE_INLINE fixed_point& operator++() SROOK_NOEXCEPT_TRUE
    {
        data_ = static_cast<value_type>(data_ + one);
        return *this;
    }

    SROOK_FORCE_INLINE fixed_point& increment()
    {
        data_ = numeric_limits<value_type>::max() >= data_ + one ? static_cast<value_type>(data_ + one) : SROOK_FIXED_POINT_THROW_OVERFLOW(overflow);
        return *this;
    }

    SROOK_FORCE_INLINE fixed_point& operator--() SROOK_NOEXCEPT_TRUE
    {
        data_ = static_cast<value_type>(data_ - one);
        return *this;
    }

    SROOK_FORCE_INLINE fixed_point& decrement()
    {
        data_ = numeric_limits<value_type>::min() <= data_ - one ? static_cast<value_type>(data_ - one) : SROOK_FIXED_POINT_THROW_UNDERFLOW(underflow);
        return *this;
    }

    SROOK_FORCE_INLINE fixed_point operator++(int) SROOK_NOEXCEPT_TRUE
    {
        fixed_point t(*this);
        ++*this;
        return t;
    }

    SROOK_FORCE_INLINE fixed_point post_increment()
    {
        fixed_point t(*this);
        increment();
        return t;
    }

    SROOK_FORCE_INLINE fixed_point operator--(int) SROOK_NOEXCEPT_TRUE
    {
        fixed_point t(*this);
        --*this;
        return t;
    }

    SROOK_FORCE_INLINE fixed_point post_decrement()
    {
        fixed_point t(*this);
        decrement();
        return t;
    }

#define SROOK_DEF_INPLACE_OPERATORS(OPERATOR)\
    SROOK_FORCE_INLINE fixed_point& operator OPERATOR##=(const fixed_point& other) SROOK_NOEXCEPT_TRUE\
    {\
        data_ = static_cast<value_type>(data_ OPERATOR other.data_);\
        return *this;\
    }

    SROOK_DEF_INPLACE_OPERATORS(+)
    SROOK_DEF_INPLACE_OPERATORS(-)
    SROOK_DEF_INPLACE_OPERATORS(|)
    SROOK_DEF_INPLACE_OPERATORS(^)
    SROOK_DEF_INPLACE_OPERATORS(&)

    SROOK_FORCE_INLINE fixed_point& operator*=(const fixed_point& other) SROOK_NOEXCEPT_TRUE
    {
        return multiply(other);
    }

    SROOK_FORCE_INLINE fixed_point& operator/=(const fixed_point& other) SROOK_NOEXCEPT_TRUE
    {
        return divide(other);
    }

    SROOK_FORCE_INLINE fixed_point& operator>>=(const fixed_point& other) SROOK_NOEXCEPT_TRUE
    {
        data_ >>= static_cast<int>(other);
        return *this;
    }

    SROOK_FORCE_INLINE fixed_point& operator<<=(const fixed_point& other) SROOK_NOEXCEPT_TRUE
    {
        data_ <<= static_cast<int>(other);
        return *this;
    }
#undef SROOK_DEF_INPLACE_OPERATORS

    SROOK_FORCE_INLINE fixed_point& iadd(const fixed_point& other)
    {
        data_ = numeric_limits<value_type>::max() >= data_ + other.data_ ? static_cast<value_type>(data_ + other.data_) : SROOK_FIXED_POINT_THROW_OVERFLOW(overflow);
        return *this;
    }
    
    SROOK_FORCE_INLINE fixed_point& isub(const fixed_point& other)
    {
        data_ = numeric_limits<value_type>::min() <= data_ - other.data_ ? static_cast<value_type>(data_ - other.data_) : SROOK_FIXED_POINT_THROW_UNDERFLOW(underflow);
        return *this;
    }
    
    SROOK_FORCE_INLINE fixed_point& imul(const fixed_point& other)
    {
        (numeric_limits<value_type>::max() >= (other.data_ * data_)) ? multiply(other) : SROOK_FIXED_POINT_THROW_OVERFLOW(overflow);
        return *this;
    }

    SROOK_FORCE_INLINE fixed_point& idiv(const fixed_point& other)
    {
        return divide(other);
    }

    template <typename T, SROOK_REQUIRES(is_integral<T>::value)>
    SROOK_EXPLICIT SROOK_CONSTEXPR operator T() const 
    { 
        return (data_ & integer_mask) >> fractional_bits; 
    }

    template <typename T, SROOK_REQUIRES(is_floating_point<T>::value)>
    SROOK_EXPLICIT SROOK_CONSTEXPR operator T() const
    {
        return static_cast<T>(data_) / one;
    }

    SROOK_CXX14_CONSTEXPR void swap(fixed_point& other) SROOK_NOEXCEPT_TRUE
    {
        using std::swap;
        swap(data_, other.data_);
    }
private:
    struct noscale {};
    
    fixed_point(value_type n, const noscale&) : data_(srook::move(n)) {}
    
    template <class T>
    struct compare 
        : conditional<is_signed<T>::value, std::greater<size_type>, std::greater_equal<size_type>> {};
    
    template <typename ValueType, class Compare, SROOK_REQUIRES(is_integral<ValueType>::value)>
    SROOK_CONSTEXPR value_type assert_integer(ValueType x, Compare comp)
    {
        return comp(integer_bits, numeric_limits<ValueType>::digits - srook::bit::algorithm::nlz(x)) ? static_cast<value_type>(x << fractional_bits) : SROOK_FIXED_POINT_THROW_OVERFLOW(overflow);
    }

    template <typename ValueType, SROOK_REQUIRES(is_floating_point<ValueType>::value)>
    SROOK_CONSTEXPR value_type assert_floating(ValueType x)
    {
        return 
            !srook::math::isnan(x) ?
                !srook::math::isinf(x) ? 
                    (numeric_limits<value_type>::max() >= x * one ? static_cast<value_type>(x * one) : SROOK_FIXED_POINT_THROW_OVERFLOW(overflow))
                : SROOK_FIXED_POINT_THROW_OVERFLOW(Inf has been detected)
            : SROOK_FIXED_POINT_THROW_OVERFLOW(NaN has been detected);
    }
    
    template <class This, SROOK_REQUIRES(type_traits::detail::Land<is_same<This, fixed_point>, bool_constant<traits_type::next_fixed_point::is_specialized>>::value)>
    SROOK_FORCE_INLINE fixed_point& multiply(const This& other)
    {
        return *this = 
            from_value(
                static_cast<value_type>(
                    next_value_type(static_cast<next_value_type>((static_cast<next_value_type>(data_) * static_cast<next_value_type>(other.data_)) >> fractional_bits))
                )
            );
    }

    template <class This, SROOK_REQUIRES(type_traits::detail::Land<is_same<This, fixed_point>, bool_constant<!traits_type::next_fixed_point::is_specialized>>::value)>
    SROOK_FORCE_INLINE fixed_point&
    multiply(const This& other)
    {
        const value_type 
            ahi = (data_ & integer_mask) >> fractional_bits, 
            bhi = (other.data_ & integer_mask) >> fractional_bits,
            alo = (data_ & fractional_mask),
            blo = (other.data_ & fractional_mask);
        const value_type
            x1 = ahi * bhi,
            x2 = ahi * blo,
            x3 = alo * bhi,
            x4 = alo * blo;
        return *this = from_value((x1 << fractional_bits) + (x3 + x2) + (x4 >> fractional_bits));
    }

    // Ref: http://www.artist-embedded.org/docs/Events/2009/EmbeddedControl/SLIDES/FixPoint.pdf
    template <class This, SROOK_REQUIRES(type_traits::detail::Land<is_same<This, fixed_point>, bool_constant<traits_type::next_fixed_point::is_specialized>>::value)>
    SROOK_FORCE_INLINE fixed_point& divide(const This& other)
    {
        return *this = from_value(static_cast<value_type>((static_cast<next_value_type>(data_) << fractional_bits) / other.data_));
    }

    //TODO: for bool_constant<!traits_type::next_fixed_point::is_specialized> implementation

    friend SROOK_FORCE_INLINE std::ostream& operator<<(std::ostream& os, const fixed_point& this_)
    {
        return os << static_cast<double>(this_);
    }

// operator with over difference integer part
#define SROOK_DEF_DIFF_INTEGER_OPERATION(OPERATOR)\
    template <std::size_t I1>\
    friend SROOK_FORCE_INLINE SROOK_CONSTEXPR fixed_point<srook::algorithm::max(I, I1), F> operator OPERATOR(const fixed_point& lhs, const fixed_point<I1, F>& rhs)\
    {\
        typedef fixed_point<srook::algorithm::max(I, I1), F> return_type;\
        return return_type::from_value(lhs.data_ OPERATOR rhs.data_);\
    }
    SROOK_DEF_DIFF_INTEGER_OPERATION(+)
    SROOK_DEF_DIFF_INTEGER_OPERATION(-)
    SROOK_DEF_DIFF_INTEGER_OPERATION(*)
    SROOK_DEF_DIFF_INTEGER_OPERATION(/)
#undef SROOK_DEF_DIFF_INTEGER_OPERATION
private:
    value_type data_;
};

// compare operator with fundamental types
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator==(const fixed_point<I, F>& f, Arithmetic x) SROOK_NOEXCEPT_TRUE { return static_cast<Arithmetic>(f) == x; }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator==(Arithmetic x, const fixed_point<I, F>& f) SROOK_NOEXCEPT_TRUE { return f == x; }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator!=(const fixed_point<I, F>& f, Arithmetic x) SROOK_NOEXCEPT_TRUE { return !(f == x); }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator!=(Arithmetic x, const fixed_point<I, F>& f) SROOK_NOEXCEPT_TRUE { return f != x; }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator<(const fixed_point<I, F>& f, Arithmetic x) SROOK_NOEXCEPT_TRUE { return static_cast<Arithmetic>(f) < x; }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator<(Arithmetic x, const fixed_point<I, F>& f) SROOK_NOEXCEPT_TRUE { return !(f < x) && x != f; }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator>(const fixed_point<I, F>& f, Arithmetic x) SROOK_NOEXCEPT_TRUE { return x < f; }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator>(Arithmetic x, const fixed_point<I, F>& f) SROOK_NOEXCEPT_TRUE { return f < x; }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator<=(Arithmetic x, const fixed_point<I, F>& f) SROOK_NOEXCEPT_TRUE { return x < f || x == f; }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator<=(const fixed_point<I, F>& f, Arithmetic x) SROOK_NOEXCEPT_TRUE { return f < x || x == f; }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator>=(Arithmetic x, const fixed_point<I, F>& f) SROOK_NOEXCEPT_TRUE { return x > f || x == f; }
template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR bool operator>=(const fixed_point<I, F>& f, Arithmetic x) SROOK_NOEXCEPT_TRUE { return f > x || x == f; }

// arithmetic operator with fundamental types
namespace detail {

template <std::size_t I, std::size_t F, class Arithmetic, class Operator, SROOK_REQUIRES(srook::tmpl::vt::lt<SROOK_DEDUCED_TYPENAME fixed_point<I, F>::value_type, Arithmetic>::type::value)>
SROOK_CONSTEXPR fixed_point<I, F> operation(const fixed_point<I, F>& f, Arithmetic x, Operator op) SROOK_NOEXCEPT_TRUE
{
    return op(f, fixed_point<I, F>(x));
}

template <std::size_t I, std::size_t F, class Arithmetic, class Operator, SROOK_REQUIRES(srook::tmpl::vt::lt<SROOK_DEDUCED_TYPENAME fixed_point<I, F>::value_type, Arithmetic>::type::value)>
SROOK_CONSTEXPR fixed_point<I, F> operation(Arithmetic x, const fixed_point<I, F>& f, Operator op) SROOK_NOEXCEPT_TRUE
{
    return op(fixed_point<I, F>(x), f);
}

template <std::size_t I, std::size_t F, class Arithmetic, class Operator, 
    SROOK_REQUIRES(type_traits::detail::Lnot<SROOK_DEDUCED_TYPENAME srook::tmpl::vt::lt<SROOK_DEDUCED_TYPENAME fixed_point<I, F>::value_type, Arithmetic>::type>::value)>
SROOK_CONSTEXPR Arithmetic operation(const fixed_point<I, F>& f, Arithmetic x, Operator op) SROOK_NOEXCEPT_TRUE
{
    return op(static_cast<Arithmetic>(f), x);
}

template <std::size_t I, std::size_t F, class Arithmetic, class Operator, 
    SROOK_REQUIRES(type_traits::detail::Lnot<SROOK_DEDUCED_TYPENAME srook::tmpl::vt::lt<SROOK_DEDUCED_TYPENAME fixed_point<I, F>::value_type, Arithmetic>::type>::value)>
SROOK_CONSTEXPR Arithmetic operation(Arithmetic x, const fixed_point<I, F>& f, Operator op) SROOK_NOEXCEPT_TRUE
{
    return op(x, static_cast<Arithmetic>(f));
}

} // namespace detail

template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR auto operator+(const fixed_point<I, F>& f, Arithmetic x) SROOK_NOEXCEPT_TRUE
-> SROOK_DECLTYPE(detail::operation(f, x, srook::functional::deduction_plus()))
{
    return detail::operation(f, x, srook::functional::deduction_plus());
}

template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR auto operator+(Arithmetic x, const fixed_point<I, F>& f) SROOK_NOEXCEPT_TRUE
-> SROOK_DECLTYPE(f + x)
{
    return f + x;
}

template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR auto operator*(const fixed_point<I, F>& f, Arithmetic x) SROOK_NOEXCEPT_TRUE
-> SROOK_DECLTYPE(detail::operation(f, x, srook::functional::deduction_multiplies()))
{
    return detail::operation(f, x, srook::functional::deduction_multiplies());
}

template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR auto operator*(Arithmetic x, const fixed_point<I, F>& f) SROOK_NOEXCEPT_TRUE
-> SROOK_DECLTYPE(f * x)
{
    return f * x;
}

template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR auto operator-(const fixed_point<I, F>& f, Arithmetic x) SROOK_NOEXCEPT_TRUE
-> SROOK_DECLTYPE(detail::operation(f, x, srook::functional::deduction_minus()))
{
    return detail::operation(f, x, srook::functional::deduction_minus());
}

template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR auto operator-(Arithmetic x, const fixed_point<I, F>& f) SROOK_NOEXCEPT_TRUE
-> SROOK_DECLTYPE(detail::operation(x, f, srook::functional::deduction_minus()))
{
    return detail::operation(x, f, srook::functional::deduction_minus());
}

template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR auto operator/(const fixed_point<I, F>& f, Arithmetic x) SROOK_NOEXCEPT_TRUE
-> SROOK_DECLTYPE(detail::operation(f, x, srook::functional::deduction_divides()))
{
    return detail::operation(f, x, srook::functional::deduction_divides());
}

template <std::size_t I, std::size_t F, class Arithmetic, SROOK_REQUIRES(is_arithmetic<Arithmetic>::value)>
SROOK_CONSTEXPR auto operator/(Arithmetic x, const fixed_point<I, F>& f) SROOK_NOEXCEPT_TRUE
-> SROOK_DECLTYPE(detail::operation(x, f, srook::functional::deduction_divides()))
{
    return detail::operation(x, f, srook::functional::deduction_divides());
}


SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(numeric, srook)

namespace srook {

template <std::size_t I, std::size_t F>
class numeric_limits<srook::numeric::fixed_point<I, F>> : numeric_limits<SROOK_DEDUCED_TYPENAME srook::numeric::fixed_point<I, F>::value_type> {
private:
    typedef SROOK_DEDUCED_TYPENAME srook::numeric::fixed_point<I, F>::traits_type traits_type;
public:
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR_OR_CONST srook::numeric::fixed_point<I, F> max() SROOK_NOEXCEPT_TRUE
    {
        return srook::numeric::fixed_point<I, F>::from_value(numeric_limits<SROOK_DEDUCED_TYPENAME traits_type::value_type>::max());
    }
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR_OR_CONST srook::numeric::fixed_point<I, F> min() SROOK_NOEXCEPT_TRUE
    {
        return srook::numeric::fixed_point<I, F>::from_value(numeric_limits<SROOK_DEDUCED_TYPENAME traits_type::value_type>::min());
    }
};

} // namespace srook

namespace std {

template <std::size_t I, std::size_t F>
class numeric_limits<srook::numeric::fixed_point<I, F>> : numeric_limits<SROOK_DEDUCED_TYPENAME srook::numeric::fixed_point<I, F>::value_type> {
private:
    typedef SROOK_DEDUCED_TYPENAME srook::numeric::fixed_point<I, F>::traits_type traits_type;
public:
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR_OR_CONST srook::numeric::fixed_point<I, F> max() SROOK_NOEXCEPT_TRUE
    {
        return srook::numeric::fixed_point<I, F>::from_value(numeric_limits<SROOK_DEDUCED_TYPENAME traits_type::value_type>::max());
    }
    SROOK_FORCE_INLINE static SROOK_CONSTEXPR_OR_CONST srook::numeric::fixed_point<I, F> min() SROOK_NOEXCEPT_TRUE
    {
        return srook::numeric::fixed_point<I, F>::from_value(numeric_limits<SROOK_DEDUCED_TYPENAME traits_type::value_type>::min());
    }
};

} // namespace std

#undef SROOK_FIXED_POINT_THROW_OVERFLOW
#endif
