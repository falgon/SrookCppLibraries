// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_DEFINES_MAP_HPP
#define INCLUDED_SROOK_TMPL_VT_DEFINES_MAP_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/type_traits/true_false_type.hpp>
#include <srook/type_traits/detail/sfinae_types.hpp>
#include <utility>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt, defines) {
SROOK_INLINE_NAMESPACE(v1)

namespace detail {

template <class T>
class map_has_type {
    template <class U>
    static type_traits::detail::sfinae_types::one test(SROOK_DEDUCED_TYPENAME U::key_type*, 
            SROOK_DEDUCED_TYPENAME U::value_type*,
            SROOK_DEDUCED_TYPENAME U::mapped_type*);
    template <class>
    static type_traits::detail::sfinae_types::two test(...);
public:
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR_OR_CONST bool value = 
        sizeof(test<T>(SROOK_NULLPTR, SROOK_NULLPTR, SROOK_NULLPTR)) == sizeof(SROOK_TRUE_TYPE);
};

#define DEF_TYPE(TYPEN)\
    template <class T>\
    struct def_##TYPEN {\
        typedef T TYPEN;\
    }

DEF_TYPE(key_type);
DEF_TYPE(mapped_type);

#undef DEF_TYPE

} // namespace detail

template <class T>
struct is_map : detail::map_has_type<T> {};

template <class K, class V>
struct is_map<std::pair<K, V>> : SROOK_TRUE_TYPE {};

template <class K, class V>
struct is_map<std::tuple<K, V>> : SROOK_TRUE_TYPE {};

template <class K, class V>
struct is_map<packer<K, V>> : SROOK_TRUE_TYPE {};

#if SROOK_CPP_VARIABLE_TEMPLATES
template <class T>
SROOK_INLINE_VARIABLE SROOK_CONSTEXPR bool is_map_v = is_map<T>::value;
#endif

template <class T>
struct map_types 
    : detail::def_key_type<SROOK_DEDUCED_TYPENAME T::key_type>, 
    detail::def_mapped_type<SROOK_DEDUCED_TYPENAME T::mapped_type> {
    SROOK_STATIC_ASSERT(is_map<T>::value, "Given type is not map");
};

template <class K, class V>
struct map_types<std::pair<K, V>>
    : detail::def_key_type<K>, detail::def_mapped_type<V> {};

template <class K, class V>
struct map_types<std::tuple<K, V>>
    : detail::def_key_type<K>, detail::def_mapped_type<V> {};

template <class K, class V>
struct map_types<packer<K, V>> 
    : detail::def_key_type<K>, detail::def_mapped_type<V> {};

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(defines, vt, tmpl, srook)

#endif
