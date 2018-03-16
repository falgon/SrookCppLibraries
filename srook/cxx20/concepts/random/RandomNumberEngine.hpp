#ifndef INCLUDED_SROOK_CXX20_CONCEPT_RANDOM_RANDOM_NUMBER_ENGINE_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_RANDOM_RANDOM_NUMBER_ENGINE_HPP
#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/cxx20/concepts/random/UniformRandomBitGenerator.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/is_unsigned.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/utility/declval.hpp>
#include <ostream>
#include <istream>
#include <random> // for std::seed_seq

#if SROOK_HAS_CONCEPTS

SROOK_NESTED_NAMESPACE(srook, concepts) {
SROOK_INLINE_NAMESPACE(v1)

template <class E>
SROOK_CONCEPT RandomNumberEngine = srook::concepts::UniformRandomBitGenerator<E> &&
requires (E e, E& v, const E x, const E y) {
    E();
    E(x);
    E(declval<SROOK_DEDUCED_TYPENAME E::result_type>());
    E(declval<std::seed_seq>());
    { e.seed() } -> void;
    { e.seed(declval<SROOK_DEDUCED_TYPENAME E::result_type>()) } -> void;
    { e.seed(declval<std::seed_seq>()) } -> void;
    { e() } -> SROOK_DEDUCED_TYPENAME E::result_type;
    { e.discard(declval<unsigned long long>()) } -> void;
    { x == y } -> bool;
    { x != y } -> bool;
    { declval<std::ostream&>() << x } -> SROOK_DECLTYPE(declval<std::ostream&>())&;
    { declval<std::istream&>() >> v } -> SROOK_DECLTYPE(declval<std::istream&>())&;
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(concepts, srook)

#endif
#endif
