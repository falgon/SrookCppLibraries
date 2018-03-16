#ifndef INCLUDED_SROOK_CXX20_CONCEPT_RANDOM_RANDOMNUMBERENGINEADAPTOR_HPP
#define INCLUDED_SROOK_CXX20_CONCEPT_RANDOM_RANDOMNUMBERENGINEADAPTOR_HPP
#include <srook/config/feature/nested_namespace.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/cxx20/concepts/CopyConstructible.hpp>
#include <srook/cxx20/concepts/CopyAssignable.hpp>
#include <srook/cxx20/concepts/EqualityComparable.hpp>
#include <srook/type_traits/is_integral.hpp>
#include <srook/type_traits/is_unsigned.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <srook/type_traits/is_arithmetic.hpp>
#include <srook/utility/declval.hpp>
#include <random> // for the type satisfying RandomNumberEngine, std::seed_seq

#if SROOK_HAS_CONCEPTS

SROOK_NESTED_NAMESPACE(srook, concepts) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

typedef std::minstd_rand0 randomnumber_engine_type;

} // namespace detail

template <class A>
SROOK_CONCEPT RandomNumberEngineAdaptor = srook::concepts::EqualityComparable<A> &&
requires (A a) {
    A();
    A(declval<SROOK_DEDUCED_TYPENAME A::result_type>());
    A(declval<std::seed_seq>());
    a.seed();
    a.seed(declval<SROOK_DEDUCED_TYPENAME A::result_type>());
    a.seed(declval<std::seed_seq>());
};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(concepts, srook)

#endif
#endif
