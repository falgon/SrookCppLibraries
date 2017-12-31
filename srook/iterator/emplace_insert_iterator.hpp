// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_EMPLACE_INSERT_ITERATOR
#define INCLUDED_EMPLACE_INSERT_ITERATOR
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/deprecated/cpp_lib_std_iterator.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace iterator {
SROOK_INLINE_NAMESPACE(v1)

template <class Container>
class emplace_insert_iterator : public SROOK_STD_ITERATOR(std::output_iterator_tag, void, void, void, void) {
protected:
    Container *container;
    typename Container::iterator iter;

public:
#if SROOK_STD_ITERATOR_DEPRECATED
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;
#endif
    typedef Container container_type;

    explicit constexpr emplace_insert_iterator(Container &x, typename Container::iterator i)
	: container(&x), iter(i)
    {
    }

#if SROOK_CPLUSPLUS11_CONSTANT >= SROOK_CPLUSPLUS
    emplace_insert_iterator &operator=(typename Container::const_reference value)
    {
	iter = container->emplace(iter, value);
	++iter;
	return *this;
    }
#endif
#if SROOK_CPLUSPLUS11_CONSTANT <= SROOK_CPLUSPLUS
    emplace_insert_iterator &
    operator=(const typename Container::value_type &value)
    {
	iter = container->emplace(iter, value);
	++iter;
	return *this;
    }
    emplace_insert_iterator &
    operator=(const typename Container::value_type &&value)
    {
	iter = container->emplace(iter, std::move(value));
	++iter;
	return *this;
    }
#endif
    emplace_insert_iterator &
    operator*()
    {
	return *this;
    }
    emplace_insert_iterator &
    operator++()
    {
	return *this;
    }
    emplace_insert_iterator &
    operator++(int)
    {
	return *this;
    }
};

template <class Container, class Iterator>
inline emplace_insert_iterator<Container>
emplace_inserter(Container &x, Iterator i)
{
    return emplace_insert_iterator<Container>(x, typename Container::iterator(i));
}

SROOK_INLINE_NAMESPACE_END
} // namespace iterator

using iterator::emplace_inserter;
using iterator::emplace_insert_iterator;

} // namespace srook
#endif
