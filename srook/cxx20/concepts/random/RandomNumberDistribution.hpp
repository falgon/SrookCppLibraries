#ifndef INCLUDED_SROOK_CXX20_CONCEPT_RANDOM_RANDOMNUMBERDISTRIBUTION_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_RANDOM_RANDOMNUMBERDISTRIBUTION_HPP
#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/cxx20/concepts/CopyConstructible.hpp>
#include <srook/cxx20/concepts/CopyAssignable.hpp>
#include <srook/cxx20/concepts/EqualityComparable.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/utility/declval.hpp>
#include <random> // for the type satisfying UniformRandomBitGenerator

#if SROOK_HAS_CONCEPTS

SROOK_NESTED_NAMESPACE(srook, concepts) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

typedef std::minstd_rand0 uniform_randombit_generator_type;

} // namespace detail

template <class D>
SROOK_CONCEPT RandomNumberDistribution = 
srook::concepts::CopyConstructible<D> && 
srook::concepts::CopyAssignable<D> &&
is_arithmetic<SROOK_DEDUCED_TYPENAME D::result_type>::value &&
srook::concepts::CopyConstructible<SROOK_DEDUCED_TYPENAME D::param_type> &&
srook::concepts::CopyAssignable<SROOK_DEDUCED_TYPENAME D::param_type> &&
srook::concepts::EqualityComparable<SROOK_DEDUCED_TYPENAME D::param_type> &&
is_same<SROOK_DEDUCED_TYPENAME D::param_type::distribution_type, D>::value &&
requires (D d, D x, D y, const D cx, const D cy) {
    D();
    D(declval<SROOK_DEDUCED_TYPENAME D::param_type>());
    { d.reset() } -> void;
    { x.param() } -> SROOK_DEDUCED_TYPENAME D::param_type;
    { cx.param() } -> SROOK_DEDUCED_TYPENAME D::param_type;
    { d.param(declval<SROOK_DEDUCED_TYPENAME D::param_type>()) } -> void;
    { d(declval<detail::uniform_randombit_generator_type>()) } -> SROOK_DEDUCED_TYPENAME D::result_type;
    { d(declval<detail::uniform_randombit_generator_type>(), declval<SROOK_DEDUCED_TYPENAME D::param_type>()) } -> SROOK_DEDUCED_TYPENAME D::result_type;
    { x.min() } -> SROOK_DEDUCED_TYPENAME D::result_type;
    { cx.min() } -> SROOK_DEDUCED_TYPENAME D::result_type;
    { x.max() } -> SROOK_DEDUCED_TYPENAME D::result_type;
    { cx.max() } -> SROOK_DEDUCED_TYPENAME D::result_type;
    { x == y } -> bool;
    { x == cy } -> bool;
    { cx == y } -> bool;
    { cx == cy } -> bool;
    { x != y } -> bool;
    { x != cy } -> bool;
    { cx != y } -> bool;
    { cx != cy } -> bool;
    { declval<std::ostream&>() << x } -> std::ostream&;
    { declval<std::ostream&>() << cx } -> std::ostream&;
    { declval<std::istream&>() >> d } -> std::istream&;
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(concepts, srook)

#endif
#endif
