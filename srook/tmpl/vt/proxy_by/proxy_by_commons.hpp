// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_PROXY_BY_PROXY_BY_COMMONDS_HPP
#define INCLUDED_SROOK_TMPL_VT_PROXY_BY_PROXY_BY_COMMONDS_HPP

#include <srook/tmpl/vt/proxy_by/proxy_by_def.hpp>

SROOK_NESTED_NAMESPACE(srook, tmpl, vt) {
SROOK_INLINE_NAMESPACE(v1)

// from containers
SROOK_TMPL_VT_PROXY_BY_DEF(traits_type);
SROOK_TMPL_VT_PROXY_BY_DEF(const_reference);
SROOK_TMPL_VT_PROXY_BY_DEF(iterator);
SROOK_TMPL_VT_PROXY_BY_DEF(const_iterator);
SROOK_TMPL_VT_PROXY_BY_DEF(reverse_iterator);
SROOK_TMPL_VT_PROXY_BY_DEF(const_reverse_iterator);
SROOK_TMPL_VT_PROXY_BY_DEF(char_type);

// from pair
SROOK_TMPL_VT_PROXY_BY_DEF(first_type);
SROOK_TMPL_VT_PROXY_BY_DEF(second_type);

// from char_traits
SROOK_TMPL_VT_PROXY_BY_DEF(int_type);
SROOK_TMPL_VT_PROXY_BY_DEF(off_type);
SROOK_TMPL_VT_PROXY_BY_DEF(pos_type);
SROOK_TMPL_VT_PROXY_BY_DEF(state_type);

// from regex_traits
SROOK_TMPL_VT_PROXY_BY_DEF(string_type);
SROOK_TMPL_VT_PROXY_BY_DEF(locale_type);
SROOK_TMPL_VT_PROXY_BY_DEF(char_class_type);

// from iterator_traits
SROOK_TMPL_VT_PROXY_BY_DEF(difference_type);
SROOK_TMPL_VT_PROXY_BY_DEF(value_type);
SROOK_TMPL_VT_PROXY_BY_DEF(pointer);
SROOK_TMPL_VT_PROXY_BY_DEF(reference);
SROOK_TMPL_VT_PROXY_BY_DEF(iterator_category);

// from pointer_traits
SROOK_TMPL_VT_PROXY_BY_DEF(element);

// from allocator_traits
SROOK_TMPL_VT_PROXY_BY_DEF(allocator_type);
SROOK_TMPL_VT_PROXY_BY_DEF(const_pointer);
SROOK_TMPL_VT_PROXY_BY_DEF(void_pointer);
SROOK_TMPL_VT_PROXY_BY_DEF(const_void_pointer);
SROOK_TMPL_VT_PROXY_BY_DEF(size_type);
SROOK_TMPL_VT_PROXY_BY_DEF(propagate_on_container_copy_assignment);
SROOK_TMPL_VT_PROXY_BY_DEF(propagate_on_container_move_assignment);
SROOK_TMPL_VT_PROXY_BY_DEF(propagate_on_container_swap);

SROOK_INLINE_NAMESPACE_END
} SROOK_NESTED_NAMESPACE_END(vt, tmpl, srook)

#endif
