// Copyright (C) 2017 roki
#ifndef INCLUDED_EMPLACE_BACK_INSERT_ITERATOR
#define INCLUDED_EMPLACE_BACK_INSERT_ITERATOR
#include <srook/config/deprecated/cpp_lib_std_iterator.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
namespace iterator {
SROOK_INLINE_NAMESPACE(v1)

template <class Container>
class emplace_back_insert_iterator : public SROOK_STD_ITERATOR(std::output_iterator_tag, void, void, void, void) {
protected:
    Container *container;

public:
#if SROOK_STD_ITERATOR_DEPRECATED
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;
#endif
    typedef Container container_type;

    explicit constexpr emplace_back_insert_iterator(Container &x)
	: container(&x)
    {
    }

#if SROOK_CPLUSPLUS11_CONSTANT >= SROOK_CPLUSPLUS
    emplace_back_insert_iterator &operator=(typename Container::const_reference value)
    {
	container->emplace_back(value);
	return *this;
    }
#endif
#if SROOK_CPLUSPLUS11_CONSTANT <= SROOK_CPLUSPLUS
    emplace_back_insert_iterator &operator=(const typename Container::value_type &value)
    {
	container->emplace_back(value);
	return *this;
    }
    emplace_back_insert_iterator &operator=(const typename Container::value_type &&value)
    {
	container->emplace_back(std::move(value));
	return *this;
    }
#endif
    emplace_back_insert_iterator &operator*()
    {
	return *this;
    }
    emplace_back_insert_iterator &operator++() { return *this; }
    emplace_back_insert_iterator &operator++(int) { return *this; }
};

template <class Container>
constexpr emplace_back_insert_iterator<Container> emplace_back_inserter(Container &container)
{
    return emplace_back_insert_iterator<Container>(container);
}

SROOK_INLINE_NAMESPACE_END
} // namespace iterator

using iterator::emplace_back_inserter;
using iterator::emplace_back_insert_iterator;

} // namespace srook
#endif
