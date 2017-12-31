// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
// This file defines the all aliases for polymorphic memory resources.
#ifndef INCLUDED_SROOK_MEMORY_RESOURCE_PMRLIB_HPP
#define INCLUDED_SROOK_MEMORY_RESOURCE_PMRLIB_HPP

#include <srook/config.hpp>
#if SROOK_CPP_ALIAS_TEMPLATES && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#include <srook/memory_resource/polymorphic_allocator.hpp>
#ifdef SROOK_CONFIG_PMR_ALL_INCLUDE
#   include <string>
#   include <deque>
#   include <forward_list>
#   include <list>
#   include <vector>
#   include <map>
#   include <set>
#   include <unordered_map>
#   include <unordered_set>
#   include <regex>
#   if SROOK_HAS_INCLUDE(<boost/container/pmr/flat_map.hpp>)
#       include <boost/container/pmr/flat_map.hpp>
#   endif
#   if SROOK_HAS_INCLUDE(<boost/container/pmr/flat_set.hpp>)
#       include <boost/container/pmr/flat_set.hpp>
#   endif
#   if SROOK_HAS_INCLUDE(<boost/container/pmr/slist.hpp>)
#       include <boost/container/pmr/slist.hpp>
#   endif
#   if SROOK_HAS_INCLUDE(<boost/container/pmr/small_vector.hpp>)
#       include <boost/container/pmr/small_vector.hpp>
#   endif
#   if SROOK_HAS_INCLUDE(<boost/container/pmr/stable_vector.hpp>)
#       include <boost/container/pmr/stable_vector.hpp>
#   endif
#else
#   ifdef SROOK_CONFIG_PMR_STD_BASIC_STRING_INCLUDE
#       include <string>
#   endif
#   ifdef SROOK_CONFIG_PMR_STD_DEQUE_INCLUDE
#       include <deque>
#   endif
#   ifdef SROOK_CONFIG_PMR_STD_FORWARD_LIST_INCLUDE
#       include <forward_list>
#   endif
#   ifdef SROOK_CONFIG_PMR_STD_LIST_INCLUDE
#       include <list>
#   endif
#   ifdef SROOK_CONFIG_PMR_STD_VECTOR_INCLUDE
#       include <vector>
#   endif
#   ifdef SROOK_CONFIG_PMR_STD_MAP_INCLUDE
#       include <mep>
#   endif
#   ifdef SROOK_CONFIG_PMR_STD_SET_INCLUDE
#       include <set>
#   endif
#   ifdef SROOK_CONFIG_PMR_STD_UNORDERED_MAP_INCLUDE
#       include <unordered_map>
#   endif
#   ifdef SROOK_CONFIG_PMR_STD_UNORDERED_SET_INCLUDE
#       include <unordered_set>
#   endif
#   ifdef SROOK_CONFIG_PMR_STD_REGEX_INCLUDE
#       include <regex>
#   endif
#   if SROOK_CONFIG_PMR_BOOST_FLAT_MAP_INCLUDE && SROOK_HAS_INCLUDE(<boost/container/pmr/flat_map.hpp>)
#       include <boost/container/pmr/flat_map.hpp>
#   endif
#   if SROOK_CONFIG_PMR_BOOST_FLAT_SET_INCLUDE && SROOK_HAS_INCLUDE(<boost/container/pmr/flat_set.hpp>)
#       include <boost/container/pmr/flat_set.hpp>
#   endif
#   if SROOK_CONFIG_PMR_BOOST_SLIST_INCLUDE && SROOK_HAS_INCLUDE(<boost/container/pmr/slist.hpp>)
#       include <boost/container/pmr/slist.hpp>
#   endif
#   if SROOK_CONFIG_PMR_BOOST_SMALL_VECTOR && SROOK_HAS_INCLUDE(<boost/container/pmr/small_vector.hpp>)
#       include <boost/container/pmr/small_vector.hpp>
#   endif
#   if SROOK_CONFIG_PMR_BOOST_STABLE_VECTOR && SROOK_HAS_INCLUDE(<boost/container/pmr/stable_vector.hpp>)
#       include <boost/container/pmr/stable_vector.hpp>
#   endif

#endif

namespace srook {
namespace pmr {

#if SROOK_CONFIG_PMR_ALL_INCLUDE || SROOK_CONFIG_PMR_STD_BASIC_STRING_INCLUDE
// basic_string
template <class charT, class traits = std::char_traits<charT>>
using basic_string = std::basic_string<charT, traits, polymorphic_allocator<charT>>;

typedef basic_string<char> string;
typedef basic_string<char16_t> u16string;
typedef basic_string<char32_t> u32string;
typedef basic_string<wchar_t> wstring;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || SROOK_CONFIG_PMR_STD_DEQUE_INCLUDE
// deque
template <class T>
using deque = std::deque<T, polymorphic_allocator<T>>;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || SROOK_CONFIG_PMR_STD_FORWARD_LIST_INCLUDE
// forward_list
template <class T>
using forward_list = std::forward_list<T, polymorphic_allocator<T>>;
#endif


#if SROOK_CONFIG_PMR_ALL_INCLUDE || SROOK_CONFIG_PMR_STD_LIST_INCLUDE
// list
template <class T>
using list = std::list<T, polymorphic_allocator<T>>;
#endif


#if SROOK_CONFIG_PMR_ALL_INCLUDE || SROOK_CONFIG_PMR_STD_VECTOR_INCLUDE
// vector
template <class T>
using vector = std::vector<T, polymorphic_allocator<T>>;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || SROOK_CONFIG_PMR_STD_MAP_INCLUDE
// map
template <class Key, class T, class Compare = std::less<Key>>
using map = std::map<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T>>>;

// multimap
template <class Key, class T, class Compare = std::less<Key>>
using multimap = std::multimap<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T>>>;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || SROOK_CONFIG_PMR_STD_SET_INCLUDE
// set
template <class Key, class Compare = std::less<Key>>
using set = std::set<Key, Compare, polymorphic_allocator<Key>>;

// multiset
template <class Key, class Compare = std::less<Key>>
using multiset = std::multiset<Key, Compare, polymorphic_allocator<Key>>;
#endif


#if SROOK_CONFIG_PMR_ALL_INCLUDE || SROOK_CONFIG_PMR_STD_UNORDERED_MAP_INCLUDE
// unordered_map
template <class Key, class T, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
using unordered_map = std::unordered_map<Key, T, Hash, Pred, polymorphic_allocator<std::pair<const Key, T>>>;

// unordered_multimap
template <class Key, class T, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
using unordered_multimap = std::unordered_multimap<Key, T, Hash, Pred, polymorphic_allocator<std::pair<const Key, T>>>;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || SROOK_CONFIG_PMR_STD_UNORDERED_SET_INCLUDE
// unordered_set
template <class Key, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
using unordered_set = std::unordered_set<Key, Hash, Pred, polymorphic_allocator<Key>>;

// unordered_multiset
template <class Key, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
using unordered_multiset = std::unordered_multiset<Key, Hash, Pred, polymorphic_allocator<Key>>;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || SROOK_CONFIG_PMR_STD_REGEX_INCLUDE
// regex::match_results
template <class BidirectionalIterator>
using match_results = std::match_results<BidirectionalIterator, polymorphic_allocator<std::sub_match<BidirectionalIterator>>>;

typedef match_results<const char*> cmatch;
typedef match_results<const wchar_t*> wcmatch;
typedef match_results<std::string::const_iterator> smatch;
typedef match_results<std::wstring::const_iterator> wsmatch;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || (SROOK_CONFIG_PMR_BOOST_FLAT_MAP_INCLUDE && SROOK_HAS_INCLUDE(<boost/container/pmr/flat_map.hpp>))
// boost::flat_map
template <class Key, class T, class Compare = std::less<Key>>
using flat_map = boost::container::flat_map<Key, T, Compare, polymorphic_allocator<std::pair<Key, T>>>;

// boost::flat_multimap
template <class Key, class T, class Compare = std::less<Key>>
using flat_multimap = boost::container::flat_multimap<Key, T, Compare, polymorphic_allocator<std::pair<Key, T>>>;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || (SROOK_CONFIG_PMR_BOOST_FLAT_SET_INCLUDE && SROOK_HAS_INCLUDE(<boost/container/pmr/flat_set.hpp>))
// boost::flat_set
template <class Key, class Compare = std::less<Key>>
using flat_set = boost::container::flat_set<Key, Compare, polymorphic_allocator<Key>>;

// boost::flat_multiset
template <class Key, class Compare = std::less<Key>>
using flat_multiset = boost::container::flat_multiset<Key, Compare, polymorphic_allocator<Key>>;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || (SROOK_CONFIG_PMR_BOOST_SLIST_INCLUDE && SROOK_HAS_INCLUDE(<boost/container/pmr/slist.hpp>))
// boost::slist
template <class T>
using slist = boost::container::slist<T, polymorphic_allocator<T>>;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || (SROOK_CONFIG_PMR_BOOST_SMALL_VECTOR && SROOK_HAS_INCLUDE(<boost/container/pmr/small_vector.hpp>))
// boost::small_vector
template <class T, std::size_t N>
using small_vector = boost::container::small_vector<T, N, polymorphic_allocator<T>>;
#endif

#if SROOK_CONFIG_PMR_ALL_INCLUDE || (SROOK_CONFIG_PMR_BOOST_STABLE_VECTOR && SROOK_HAS_INCLUDE(<boost/container/pmr/stable_vector.hpp>))
// boost::stable_vector
template <class T>
using stable_vector = boost::container::stable_vector<T, polymorphic_allocator<T>>;
#endif

} // namespace pmr
} // namespace srook

#endif
#endif
