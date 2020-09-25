// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_LIBRARIES_TYPE_TRAITS_INDEX_SEQUENCE_HPP
#define INCLUDED_SROOK_CONFIG_LIBRARIES_TYPE_TRAITS_INDEX_SEQUENCE_HPP

#include <srook/config/cpp_predefined.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
#    include <utility>
#    define SROOK_INDEX_SEQUENCE std::index_sequence
#    define SROOK_MAKE_INDEX_SEQUENCE(x) std::make_index_sequence<x>
#else
#    include <srook/utility/index_sequence.hpp>
#    define SROOK_INDEX_SEQUENCE srook::index_sequence
#    define SROOK_MAKE_INDEX_SEQUENCE(x) typename srook::make_index_sequence_type<x>::type
#endif

#endif
