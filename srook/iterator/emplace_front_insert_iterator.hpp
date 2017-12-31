// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_EMPLACE_FRONT_INSERT_ITERATOR
#define INCLUDED_EMPLACE_FRONT_INSERT_ITERATOR
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>
#include <srook/config/deprecated/cpp_lib_std_iterator.hpp>
#include <srook/config/feature/inline_namespace.hpp>

namespace srook {
inline namespace v1 {

template <class Container>
class emplace_front_insert_iterator : public SROOK_STD_ITERATOR(std::output_iterator_tag, void, void, void, void) {
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

    explicit constexpr emplace_front_insert_iterator(Container &x)
	: container(&x)
    {
    }

#if SROOK_CPLUSPLUS11_CONSTANT >= SROOK_CPLUSPLUS
    emplace_front_insert_iterator &
    operator=(typename Container::const_reference value)
    {
	container->emplace_front(value);
	return *this;
    }
#endif

#if SROOK_CPLUSPLUS11_CONSTANT <= SROOK_CPLUSPLUS
    emplace_front_insert_iterator &
    operator=(const typename Container::value_type &value)
    {
	container->emplace_front(value);
	return *this;
    }
    emplace_front_insert_iterator &
    operator=(const typename Container::value_type &&value)
    {
	container->emplace_front(std::move(value));
	return *this;
    }
#endif
    emplace_front_insert_iterator &
    operator*()
    {
	return *this;
    }
    emplace_front_insert_iterator &
    operator++()
    {
	return *this;
    }
    emplace_front_insert_iterator &
    operator++(int)
    {
	return *this;
    }
};

template <class Container>
constexpr emplace_front_insert_iterator<Container> emplace_front_inserter(Container &x)
{
    return emplace_front_insert_iterator<Container>(x);
}

} // namespace v1
} // namespace srook
#endif
#endif
