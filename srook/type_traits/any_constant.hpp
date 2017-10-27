#ifndef INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_TYPE_TRAITS_ANY_CONSTANT_HPP
#define INCLUDED_SROOK_MPL_CONSTANT_SEQUENCE_TYPE_TRAITS_ANY_CONSTANT_HPP
#include <cstdint>
#include <srook/config/cpp_predefined/feature_testing.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/config/inline_variable.hpp>
#include <srook/config/noexcept_detection.hpp>
#include <srook/functional/deduction_divides.hpp>
#include <srook/functional/deduction_minus.hpp>
#include <srook/functional/deduction_modulus.hpp>
#include <srook/functional/deduction_multiplies.hpp>
#include <srook/functional/deduction_negate.hpp>
#include <srook/functional/deduction_plus.hpp>
#include <srook/mpl/constant_sequence/math/detail/convert_type.hpp>
#include <srook/type_traits/is_constexpr_function.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/utility/void_t.hpp>
#include <type_traits>

namespace srook {
namespace type_traits {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

template <typename ConvertType>
struct convert_type {
    explicit constexpr convert_type() = default;

    using value_type = ConvertType;

    template <class U>
    SROOK_FORCE_INLINE constexpr value_type operator()(U&& v) const SROOK_NOEXCEPT_TRUE
    {
        static_assert(std::is_convertible<value_type, typename std::decay<U>::type>::value, "These types are not able to convert");
        return static_cast<value_type>(v);
    }
};

template <typename, long long, class>
struct any_constant;
template <class, class, class>
struct any_constant_compute;

template <typename T, long long Value, class Callable = convert_type<T> >
struct any_constant {
private:
    static_assert(std::is_trivially_default_constructible<Callable>::value, "Callable must have constexpr default constructor");

public:
    typedef T value_type;
    typedef any_constant type;
    static constexpr value_type value = T(Callable()(Value));
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }

    template <class Rhs>
    struct Plus {
        typedef any_constant_compute<deduction_plus, type, Rhs> inner_type;
    };
    template <class Rhs>
    struct Minus {
        typedef any_constant_compute<deduction_minus, type, Rhs> inner_type;
    };
    template <class Rhs>
    struct Multiplies {
        typedef any_constant_compute<deduction_multiplies, type, Rhs> inner_type;
    };
    template <class Rhs>
    struct Divides {
        typedef any_constant_compute<deduction_divides, type, Rhs> inner_type;
    };
    template <class Rhs>
    struct Modulus {
        typedef any_constant_compute<deduction_modulus, type, Rhs> inner_type;
    };
    template <class Rhs>
    struct Negate {
        typedef any_constant_compute<deduction_modulus, type, Rhs> inner_type;
    };

#if SROOK_CPP_ALIAS_TEMPLATES
    template <class Rhs>
    using Plus_t = typename Plus<Rhs>::inner_type;
    template <class Rhs>
    using Minus_t = typename Minus<Rhs>::inner_type;
    template <class Rhs>
    using Multiplies_t = typename Multiplies<Rhs>::inner_type;
    template <class Rhs>
    using Divides_t = typename Divides<Rhs>::inner_type;
    template <class Rhs>
    using Modulus_t = typename Modulus<Rhs>::inner_type;
    template <class Rhs>
    using Negate_t = typename Negate<Rhs>::inner_type;
#endif
};

template <class Op, typename L, long long Value1, class Callable1, typename R, long long Value2, class Callable2>
struct any_constant_compute<Op, any_constant<L, Value1, Callable1>, any_constant<R, Value2, Callable2> > {
private:
    static_assert(
        std::is_trivially_default_constructible<Op>::value and
            std::is_trivially_default_constructible<Callable1>::value and
                std::is_trivially_default_constructible<Callable2>::value,
        "");

public:
    typedef Op apply_type;
    typedef decltype(apply_type()(Callable1()(Value1), Callable2()(Value2))) value_type;
    static constexpr value_type value = apply_type()(Callable1()(Value1), Callable2()(Value2));
};

template <class Op, class Inner_Op, class Inner_typeL, class Inner_typeR, class R, long long Value1, class Callable1>
struct any_constant_compute<Op, any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR>, any_constant<R, Value1, Callable1> > {
    typedef decltype(Op()(any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR>::value, Callable1()(Value1))) value_type;
    static constexpr value_type value = Op()(any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR>::value, Callable1()(Value1));
};

template <class Op, class Inner_Op, class Inner_typeL, class Inner_typeR, class L, long long Value1, class Callable1>
struct any_constant_compute<Op, any_constant<L, Value1, Callable1>, any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR> > {
    typedef decltype(Op()(Callable1()(Value1), any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR>::value)) value_type;
    static constexpr value_type value = Op()(Callable1()(Value1), any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR>::value);
};

template <class Op, class LInner_Op, class LInner_typeL, class LInner_typeR, class RInner_Op, class RInner_typeL, class RInner_typeR>
struct any_constant_compute<Op, any_constant_compute<LInner_Op, LInner_typeL, LInner_typeR>, any_constant_compute<RInner_Op, RInner_typeL, RInner_typeR> > {
    typedef decltype(Op()(any_constant_compute<LInner_Op, LInner_typeL, LInner_typeR>::value, any_constant_compute<RInner_Op, RInner_typeL, RInner_typeR>::value)) value_type;
    static constexpr value_type value = Op()(any_constant_compute<LInner_Op, LInner_typeL, LInner_typeR>::value, any_constant_compute<RInner_Op, RInner_typeL, RInner_typeR>::value);
};

template <typename OutputType, typename T, T value, class Operator>
struct Operator_value {
private:
    static_assert(std::is_convertible<T, OutputType>::value, "must be convertible");

public:
    typedef OutputType value_type;
    explicit constexpr Operator_value() = default;

    template <class U>
    SROOK_FORCE_INLINE constexpr value_type operator()(U&& v) const SROOK_NOEXCEPT_TRUE
    {
        typedef typename std::common_type<typename std::decay<U>::type, OutputType>::type common_type;
        return static_cast<value_type>(Operator()(static_cast<common_type>(v), static_cast<common_type>(value)));
    }
};

// for good error message...
template <class, class = typename voider<>::type>
struct has_value : SROOK_FALSE_TYPE {
};
template <class T>
struct has_value<T, typename voider<decltype(T::value)>::type> : SROOK_TRUE_TYPE {
};

template <typename OutputType, class AnyConstantType, class Op>
struct Operator {
private:
    static_assert(has_value<AnyConstantType>::value, "must have static constexpr value data");
    static_assert(std::is_convertible<typename AnyConstantType::value_type, OutputType>::value, "must be convertible");

public:
    typedef OutputType value_type;
    typedef value_type type;
    explicit constexpr Operator() = default;
    static constexpr typename AnyConstantType::value_type value = AnyConstantType::value;

    template <class U>
    SROOK_FORCE_INLINE constexpr OutputType operator()(U&& v) const SROOK_NOEXCEPT_TRUE
    {
        typedef typename std::common_type<typename std::decay<U>::type, OutputType>::type common_type;
        return static_cast<value_type>(Op()(static_cast<common_type>(v), static_cast<common_type>(value)));
    }
};

template <typename L, typename R, long long Value1, long long Value2, class Callable1, class Callable2, class Op>
struct Operator<any_constant<L, Value1, Callable1>, any_constant<R, Value2, Callable2>, Op> {
    explicit constexpr Operator() = default;
    typedef decltype(Op()(Callable1()(Value1), Callable2()(Value2))) value_type;
    typedef any_constant_compute<Op, any_constant<L, Value1, Callable1>, any_constant<R, Value1, Callable2> > type;
    static constexpr value_type value = type::value;
};

template <class Inner_Op, class Inner_typeL, class Inner_typeR, class R, long long Value1, class Callable, class Op>
struct Operator<any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR>, any_constant<R, Value1, Callable>, Op> {
    explicit constexpr Operator() = default;
    typedef decltype(Op()(any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR>::value, Callable()(Value1))) value_type;
    typedef any_constant_compute<Op, any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR>, any_constant<R, Value1, Callable> > type;
    static constexpr value_type value = type::value;
};

template <class Inner_Op, class Inner_typeL, class Inner_typeR, class L, long long Value1, class Callable, class Op>
struct Operator<any_constant<L, Value1, Callable>, any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR>, Op> {
    explicit constexpr Operator() = default;
    typedef decltype(Op()(Callable()(Value1), any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR>::value)) value_type;
    typedef any_constant_compute<Op, any_constant<L, Value1, Callable>, any_constant_compute<Inner_Op, Inner_typeL, Inner_typeR> > type;
    static constexpr value_type value = type::value;
};

template <class LInner_Op, class LInner_typeL, class LInner_typeR, class RInner_Op, class RInner_typeL, class RInner_typeR, class Op>
struct Operator<any_constant_compute<LInner_Op, LInner_typeL, LInner_typeR>, any_constant_compute<RInner_Op, RInner_typeL, RInner_typeR>, Op> {
    explicit constexpr Operator() = default;
    typedef decltype(Op()(any_constant_compute<LInner_Op, LInner_typeL, LInner_typeR>::value, any_constant_compute<RInner_Op, RInner_typeL, RInner_typeR>::value)) value_type;
    typedef any_constant_compute<Op, any_constant_compute<LInner_Op, LInner_typeL, LInner_typeR>, any_constant_compute<RInner_Op, RInner_typeL, RInner_typeR> > type;
    static constexpr value_type value = type::value;
};

template <typename OutputType, typename T, T value>
struct Plus_value : Operator_value<OutputType, T, value, deduction_plus> {
};
template <typename OutputType, typename T, T value>
struct Minus_value : Operator_value<OutputType, T, value, deduction_minus> {
};
template <typename OutputType, typename T, T value>
struct Multiplies_value : Operator_value<OutputType, T, value, deduction_multiplies> {
};
template <typename OutputType, typename T, T value>
struct Divides_value : Operator_value<OutputType, T, value, deduction_divides> {
};
template <typename OutputType, typename T, T value>
struct Modulus_value : Operator_value<OutputType, T, value, deduction_modulus> {
};
template <typename OutputType, typename T, T value>
struct Negate_value : Operator_value<OutputType, T, value, deduction_negate> {
};

template <typename OutputType, class AnyConstantType>
struct Plus : Operator<OutputType, AnyConstantType, deduction_plus> {
};
template <typename OutputType, class AnyConstantType>
struct Minus : Operator<OutputType, AnyConstantType, deduction_minus> {
};
template <typename OutputType, class AnyConstantType>
struct Multiplies : Operator<OutputType, AnyConstantType, deduction_multiplies> {
};
template <typename OutputType, class AnyConstantType>
struct Divides : Operator<OutputType, AnyConstantType, deduction_divides> {
};
template <typename OutputType, class AnyConstantType>
struct Modulus : Operator<OutputType, AnyConstantType, deduction_modulus> {
};
template <typename OutputType, class AnyConstantType>
struct Negate : Operator<OutputType, AnyConstantType, deduction_negate> {
};

} // namespace detail

using detail::any_constant;

SROOK_INLINE_NAMESPACE_END
} // namespace type_traits

namespace realvalue_compute {

using type_traits::detail::convert_type;
using type_traits::detail::Divides;
using type_traits::detail::Divides_value;
using type_traits::detail::Minus;
using type_traits::detail::Minus_value;
using type_traits::detail::Multiplies;
using type_traits::detail::Multiplies_value;
using type_traits::detail::Plus;
using type_traits::detail::Plus_value;

#if SROOK_CPP_ALIAS_TEMPLATES

template <typename OutputType, class AnyConstantType>
using Plus_t = typename Plus<OutputType, AnyConstantType>::type;
template <typename OutputType, class AnyConstantType>
using Minus_t = typename Minus<OutputType, AnyConstantType>::type;
template <typename OutputType, class AnyConstantType>
using Multiplies_t = typename Multiplies<OutputType, AnyConstantType>::type;
template <typename OutputType, class AnyConstantType>
using Divides_t = typename Divides<OutputType, AnyConstantType>::type;

#endif

} // namespace realvalue_compute

using type_traits::detail::any_constant;

#if SROOK_CPP_VARIABLE_TEMPLATES

template <typename T, long long Value, class Callable>
SROOK_INLINE_VARIABLE constexpr T any_constant_v = any_constant<T, Value, Callable>();

#endif

} // namespace srook

#endif
