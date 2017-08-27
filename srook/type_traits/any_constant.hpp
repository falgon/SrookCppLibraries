#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_TYPE_TRAITS_ANY_CONSTANT_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_TYPE_TRAITS_ANY_CONSTANT_HPP
#include <cstdint>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/inline_variable.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/functional/deduction_divides.hpp>
#include <srook/functional/deduction_minus.hpp>
#include <srook/functional/deduction_multiplies.hpp>
#include <srook/functional/deduction_plus.hpp>
#include <srook/type_traits/is_constexpr_function.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/void_t.hpp>
#include <type_traits>

namespace srook {
namespace type_traits {
inline namespace v1 {
namespace detail {

template <typename ConvertType>
struct convert_type {
    explicit constexpr convert_type() = default;

    using value_type = ConvertType;

    template <class U>
    SROOK_FORCE_INLINE constexpr value_type operator()(U &&v) const SROOK_NOEXCEPT_TRUE
    {
	static_assert(std::is_convertible<value_type, typename std::decay<U>::type>::value, "These types are not able to convert");
	return static_cast<value_type>(v);
    }
};

template <typename T, long long Value, class Callable = convert_type<T>>
struct any_constant {
private:
    static_assert(std::is_trivially_default_constructible<Callable>::value, "Callable must have constexpr default constructor");

public:
    typedef T value_type;
    typedef any_constant type;
    static constexpr value_type value = T(Callable()(Value));
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

template <typename OutputType, typename T, T value, class Operator>
struct Operator_value {
private:
    static_assert(std::is_convertible<T, OutputType>::value, "must be convertible");

public:
    typedef OutputType value_type;
    explicit constexpr Operator_value() = default;

    template <class U>
    SROOK_FORCE_INLINE constexpr value_type operator()(U &&v) const SROOK_NOEXCEPT_TRUE
    {
	typedef typename std::common_type<typename std::decay<U>::type, OutputType>::type common_type;
	return static_cast<value_type>(Operator()(static_cast<common_type>(v), static_cast<common_type>(value)));
    }
};

// for good error message...
template <class, class = typename voider<>::type> struct has_value : SROOK_FALSE_TYPE {};
template <class T> struct has_value<T, typename voider<decltype(T::value)>::type> : SROOK_TRUE_TYPE {};

template <typename OutputType, class AnyConstantType, class Op>
struct Operator {
private:
    static_assert(has_value<AnyConstantType>::value, "must have static constexpr value data");
    static_assert(std::is_convertible<typename AnyConstantType::value_type, OutputType>::value, "must be convertible");

public:
    typedef OutputType value_type;
    explicit constexpr Operator() = default;
    static constexpr typename AnyConstantType::value_type value = AnyConstantType::value;

    template <class U>
    SROOK_FORCE_INLINE constexpr OutputType operator()(U &&v) const SROOK_NOEXCEPT_TRUE
    {
	typedef typename std::common_type<typename std::decay<U>::type, OutputType>::type common_type;
	return static_cast<value_type>(Op()(static_cast<common_type>(v), static_cast<common_type>(value)));
    }
};

template <typename OutputType, typename T, T value>
struct Plus_value : Operator_value<OutputType, T, value, deduction_plus> {};
template <typename OutputType, typename T, T value>
struct Minus_value : Operator_value<OutputType, T, value, deduction_minus> {};
template <typename OutputType, typename T, T value>
struct Multiplies_value : Operator_value<OutputType, T, value, deduction_multiplies> {};
template <typename OutputType, typename T, T value>
struct Divides_value : Operator_value<OutputType, T, value, deduction_divides> {};

template <typename OutputType, class AnyConstantType>
struct Plus : Operator<OutputType, AnyConstantType, deduction_plus> {};
template <typename OutputType, class AnyConstantType>
struct Minus : Operator<OutputType, AnyConstantType, deduction_minus> {};
template <typename OutputType, class AnyConstantType>
struct Multiplies : Operator<OutputType, AnyConstantType, deduction_multiplies> {};
template <typename OutputType, class AnyConstantType>
struct Divides : Operator<OutputType, AnyConstantType, deduction_divides> {};

} // namespace detail

using detail::any_constant;
using detail::convert_type;
using detail::Plus_value;
using detail::Minus_value;
using detail::Multiplies_value;
using detail::Divides_value;
using detail::Plus;
using detail::Minus;
using detail::Multiplies;
using detail::Divides;

} // namespace v1
} // namespace type_traits

using type_traits::detail::any_constant;

#if SROOK_CPP_VARIABLE_TEMPLATES

template <typename T, long long Value, class Callable>
SROOK_INLINE_VARIABLE constexpr T any_constant_v = any_constant<T, Value, Callable>();

#endif

} // namespace srook

#endif
