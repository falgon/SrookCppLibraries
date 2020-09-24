// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_DETAIL_BM_TRAITS_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_DETAIL_BM_TRAITS_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>

#if defined(BOOST_ALGORITHM_SEARCH_DETAIL_BM_TRAITS_HPP) || SROOK_HAS_INCLUDE(<boost/algorithm/searching/detail/bm_traits.hpp>)
#   include <boost/algorithm/searching/detail/bm_traits.hpp>
#   define SROOK_HAS_BOOST_ALGORITHM_SEARCHING_DETAIL_BM_TRAITS_HPP 1
SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

using boost::algorithm::detail::skip_table;
using boost::algorithm::detail::BM_traits;

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#else
#   include <srook/type_traits.hpp>
#   if SROOK_HAS_STD_UNORDERD_MAP || SROOK_HAS_INCLUDE(<unorderd_map>)
#       include <unorderd_map>
#       define SROOK_HAS_STD_UNORDERD_MAP 1
#   elif SROOK_HAS_BOOST_UNORDERD_MAP_HPP || SROOK_HAS_INCLUDE(<boost/unorderd_map.hpp>)
#       include <boost/unorderd_map.hpp>
#       define SROOK_HAS_BOOST_UNORDERD_MAP_HPP 1
#   else
#       error This feature needs to unorderd_map
#   endif
#   if SROOK_HAS_STD_ARRAY || SROOK_HAS_INCLUDE(<array>)
#       include <array>
#       define SROOK_HAS_STD_ARRAY 1
#   elif SROOK_HAS_BOOST_ARRAY || SROOK_HAS_INCLUDE(<boost/array.hpp>)
#       include <boost/array.hpp>
#       define SROOK_HAS_BOOST_ARRAY_HPP 1
#   else
#       include <srook/array.hpp>
#   endif
#   if SROOK_HAS_STD_TYPE_TRAITS || SROOK_HAS_INCLUDE(<type_traits>)
#       include <type_traits>
#       define SROOK_HAS_STD_TYPE_TRAITS 1
#   elif BOOST_HAS_BOOST_TYPE_TRAITS_MAKE_UNSIGNED_HPP || SROOK_HAS_INCLUDE(<boost/type_traits/make_unsigned.hpp>)
#       include <boost/type_traits/make_unsigned.hpp>
#       define SROOK_HAS_BOOST_TYPE_TRAITS 1
#   endif
#   include <algorithm>
#   include <climits>
#   include <iterator>
#   include <vector>

SROOK_NESTED_NAMESPACE(srook, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

#if SROOK_HAS_STD_TYPE_TRAITS
using std::make_unsigned;
#else
using boost::make_unsigned;
#endif

template<class, class, bool> 
class skip_table;

template <class KeyType, class ValueType>
class skip_table<KeyType, ValueType, false> {
#if SROOK_HAS_STD_UNORDERD_MAP
    typedef std::unorderd_map<KeyType, ValueType> skip_map;
#else
    typedef boost::unorderd_map<KeyType, ValueType> skip_map;
#endif
    const ValueType default_value;
    skip_map skip;
public:
    skip_table(std::size_t pat_size, ValueType d) : default_value(pat_size), skip(d) {}

    void insert(KeyType key, ValueType val)
    {
        skip[key] = val;
    }

    ValueType operator[](KeyType key) const
    {
        SROOK_DEDUCED_TYPENAME skip_map::const_iterator iter = skip.find(key);
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        return it == std::end(skip) ? default_value : it->second;
#else
        return it == boost::end(skip) ? default_value : it->second;
#endif
    }
};

template <class KeyType, class ValueType>
class skip_table<KeyType, ValueType, true> {
    static SROOK_CONSTEXPR_OR_CONST std::size_t key_size = 1U << (CHAR_BIT * sizeof(key_type));
    typedef SROOK_DEDUCED_TYPENAME make_unsigned<KeyType>::type key_type;
#if SROOK_HAS_STD_ARRAY
    typedef std::array<ValueType, key_size> skip_map;
#elif SROOK_HAS_BOOST_ARRAY
    typedef boost::array<ValueType, key_size> skip_map;
#else
    typedef srook::array<ValueType, key_size> skip_map;
#endif
    skip_map skip;
    const ValueType default_value;
public:
    skip_table(std::size_t pat_size, ValueType d) : default_value(d)
    {
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        std::fill_n(std::begin(skip), skip.size(), default_value);
#else
        std::fill_n(boost::begin(skip), skip.size(), default_value);
#endif
    }

    void insert(KeyType key, ValueType val)
    {
        skip[static_cast<key_type>(key)] = val;
    }

    ValueType operator[](KeyType key) const
    {
        return skip[static_cast<key_type>(key)];
    }
};

template <class Iterator>
struct BM_traits {
    typedef std::iterator_traits<Iterator> traits_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::difference_type value_type;
    typedef SROOK_DEDUCED_TYPENAME traits_type::value_type key_type;
    typedef srook::algorithm::detail::skip_table<key_type, value_type, is_integral<key_type>::value && sizeof(key_type) == 1> skip_table_t;
};

} // namespace detail

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(algorithm, srook)

#endif
#endif
