// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ITERATOR_RANGE_ACCESS_BEGIN_END_HPP
#define INCLUDED_SROOK_ITERATOR_RANGE_ACCESS_BEGIN_END_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <iterator>
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
#include <initializer_list>
#include <valarray>

SROOK_NESTED_NAMESPACE(srook, iterator) {
SROOK_INLINE_NAMESPACE(v1)

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto begin(Container& c) -> SROOK_DECLTYPE(c.begin())
{
    return c.begin();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto begin(const Container& c) -> SROOK_DECLTYPE(c.begin())
{
    return c.begin();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto end(Container& c) -> SROOK_DECLTYPE(c.end())
{
    return c.end();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto end(const Container& c) -> SROOK_DECLTYPE(c.end())
{
    return c.end();
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR T* begin(T (&ar)[n])
{
    return ar;
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR T* end(T (&ar)[n])
{
    return ar + n;
}

template <class T> T* begin(std::valarray<T>&);
template <class T> const T* begin(const std::valarray<T>&);
template <class T> T* end(std::valarray<T>&);
template <class T> const T* end(const std::valarray<T>&);

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR auto cbegin(const Container& c) SROOK_NOEXCEPT(srook::begin(c))
-> SROOK_DECLTYPE(srook::iterator::begin(c))
{
    return srook::iterator::begin(c);
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR auto cend(const Container& c) SROOK_NOEXCEPT(srook::end(c))
-> SROOK_DECLTYPE(srook::iterator::end(c))
{
    return srook::iterator::end(c);
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto rbegin(Container& c) 
-> SROOK_DECLTYPE(c.rbegin())
{
    return c.rbegin();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto rbegin(const Container& c) 
-> SROOK_DECLTYPE(c.rbegin())
{
    return c.rbegin();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto rend(Container& c) 
-> SROOK_DECLTYPE(c.rend())
{
    return c.rend();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto rend(const Container& c) 
-> SROOK_DECLTYPE(c.rend())
{
    return c.rend();
}
        
template <class T, std::size_t n>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR std::reverse_iterator<T*> rbegin(T (&ar)[n])
{
    return std::reverse_iterator<T*>(ar + n);
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR std::reverse_iterator<T*> rend(T (&ar)[n])
{
    return std::reverse_iterator<T*>(ar);
}

template <class T>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR std::reverse_iterator<const T*> rbegin(std::initializer_list<T> li)
{
    return std::reverse_iterator<const T*>(li.end());
}

template <class T>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR std::reverse_iterator<const T*> rend(std::initializer_list<T> li)
{
    return std::reverse_iterator<const T*>(li.begin());
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto crbegin(const Container& c) 
-> SROOK_DECLTYPE(srook::iterator::rbegin(c))
{
    return srook::iterator::rbegin(c);
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto crend(const Container& c) 
-> SROOK_DECLTYPE(srook::iterator::rend(c))
{
    return srook::iterator::rend(c);
}


template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto size(const Container& c) SROOK_NOEXCEPT(c.size())
-> SROOK_DECLTYPE(c.size())
{
    return c.size();
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE SROOK_CONSTEXPR std::size_t size(const T (&)[n]) SROOK_NOEXCEPT_TRUE
{
    return n;
}

template <class Container>
SROOK_ATTRIBUTE_NODISCARD SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto empty(const Container& c) SROOK_NOEXCEPT(c.empty())
-> SROOK_DECLTYPE(c.empty())
{
    return c.empty();
}

template <class T, std::size_t n>
SROOK_ATTRIBUTE_NODISCARD SROOK_FORCE_INLINE SROOK_CONSTEXPR auto empty(const T (&)[n]) SROOK_NOEXCEPT_TRUE
{
    return false;
}

template <class T>
SROOK_ATTRIBUTE_NODISCARD SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR bool empty(std::initializer_list<T> li) SROOK_NOEXCEPT_TRUE
{
    return li.size() == 0;
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto data(Container& c) SROOK_NOEXCEPT(c.data())
-> SROOK_DECLTYPE(c.data())
{
    return c.data();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_CXX17_CONSTEXPR auto data(const Container& c) SROOK_NOEXCEPT(c.data())
-> SROOK_DECLTYPE(c.data())
{
    return c.data();
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE SROOK_CONSTEXPR T* data(T (&ar)[n]) SROOK_NOEXCEPT_TRUE
{
    return ar;
}

template <class T>
SROOK_FORCE_INLINE SROOK_CXX14_CONSTEXPR T* data(std::initializer_list<T> li) SROOK_NOEXCEPT_TRUE
{
    return li.begin();
}

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(iterator, srook)

#else

template <class T, std::size_t n>
SROOK_FORCE_INLINE T* begin(T (&ar)[n])
{
    return ar;
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE T* end(T (&ar)[n])
{
    return ar + n;
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE std::reverse_iterator<T*> rbegin(T (&ar)[n])
{
    return std::reverse_iterator<T*>(ar + n);
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE std::reverse_iterator<T*> rend(T (&ar)[n])
{
    return std::reverse_iterator<T*>(ar);
}

SROOK_NESTED_NAMESPACE(srook, iterator) {

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::iterator begin(Container& c)
{
    return c.begin();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::iterator end(Container& c)
{
    return c.end();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::const_iterator cbegin(const Container& c)
{
    return srook::iterator::begin(c);
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::const_iterator cend(const Container& c)
{
    return srook::iterator::end(c);
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::reverse_iterator rbegin(Container& c)
{
    return c.rbegin();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::reverse_iterator rend(Container& c)
{
    return c.rend();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::const_reverse_iterator crbegin(const Container& c)
{
    return srook::iterator::rbegin(c);
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::const_reverse_iterator crend(const Container& c)
{
    return srook::iterator::rend(c);
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::size_type size(Container& c) SROOK_NOEXCEPT_TRUE
{
    return c.size();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::size_type size(const Container& c) SROOK_NOEXCEPT_TRUE
{
    return c.size();
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE std::size_t size(const T (&)[n])
{
    return n;
}

template <class Container>
SROOK_FORCE_INLINE bool empty(Container& c) SROOK_NOEXCEPT_TRUE
{
    return c.empty();
}

template <class Container>
SROOK_FORCE_INLINE bool empty(const Container& c) SROOK_NOEXCEPT_TRUE
{
    return c.empty();
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE bool empty(const T (&)[n])
{
    return false;
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::value_type* data(Container& c)
{
    return c.data();
}

template <class Container>
SROOK_FORCE_INLINE SROOK_DEDUCED_TYPENAME Container::value_type* data(const Container& c)
{
    return c.data();
}

template <class T, std::size_t n>
SROOK_FORCE_INLINE T* data(T (&ar)[n])
{
    return ar;
}

} SROOK_NESTED_NAMESPACE_END(iterator, srook)
#endif

namespace srook {

using srook::iterator::begin;
using srook::iterator::end;
using srook::iterator::cbegin;
using srook::iterator::cend;
using srook::iterator::rbegin;
using srook::iterator::rend;
using srook::iterator::crbegin;
using srook::iterator::crend;
using srook::iterator::data;
using srook::iterator::size;
using srook::iterator::empty;

} // namespace srook

#endif
