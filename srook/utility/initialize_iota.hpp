// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_INIT_IOTA
#define INCLUDED_INIT_IOTA
#include <srook/config/cpp_predefined.hpp>
#if SROOK_HAS_INCLUDE(<boost/preprocessor/repetition/repeat_from_to.hpp>)
#   define INIT_IOTA_T(z,x,text) x,
#   define INIT_IOTA(x,y) BOOST_PP_REPEAT_FROM_TO(x,y,INIT_IOTA_T,_)
#   define IIOTA INIT_IOTA
#endif
#endif
