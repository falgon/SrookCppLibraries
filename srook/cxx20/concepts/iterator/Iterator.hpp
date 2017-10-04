#ifndef INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_ITERATOR_HPP
#define INCLUDED_SROOK_CXX20_CONCEPTS_ITERATOR_ITERATOR_HPP
#include <srook/cxx20/concepts/workaround/workaround.hpp>
#include <srook/config/feature/inline_namespace.hpp>
#include <srook/type_traits/is_copy_constructible.hpp>
#include <srook/type_traits/is_destructible.hpp>
#include <srook/type_traits/is_copy_assignable.hpp>
#include <srook/type_traits/is_swappable.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/conditional.hpp>
#include <srook/type_traits/is_lvalue_reference.hpp>
#include <iterator>

namespace srook {
namespace concepts {
SROOK_INLINE_NAMESPACE(v1)

template <class Iter>
SROOK_CONCEPT Iterator = requires (Iter iter) {
	typename std::iterator_traits<Iter>::value_type;
	typename std::iterator_traits<Iter>::difference_type;
	typename std::iterator_traits<Iter>::reference;
	typename std::iterator_traits<Iter>::pointer;
	typename std::iterator_traits<Iter>::iterator_category;
	{ iter } -> Iter;
	*iter;
	{ ++iter } -> Iter&;
} && is_copy_constructible<Iter>::value
&& is_destructible<Iter>::value
&& is_copy_assignable<Iter>::value
&& conditional<is_lvalue_reference<Iter>::value, is_swappable<Iter>, SROOK_TRUE_TYPE>::type::value;

SROOK_INLINE_NAMESPACE_END

} // namespace concepts
} // namespace srook

#endif
