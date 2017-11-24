// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_PREPROCESSOR_CONTROL_IIF_HPP
#define INCLUDED_SROOK_PREPROCESSOR_CONTROL_IIF_HPP

#ifndef _MSC_VER
#   define SROOK_PP_IIF(bit, t, f) SROOK_PP_IIF_I(bit, t, f)
#else
#   define SROOK_PP_IIF(bit, t, f) SROOK_PP_IIF_OO((bit, t, f))
#   define SROOK_PP_IIF_OO(par) SROOK_OO_IIF_I ## par
#endif
#ifndef _MSC_VER
#   define SROOK_PP_IIF_I(bit, t, f) SROOK_PP_IIF_ ## bit(t, f)
#else
#   define SROOK_PP_IIF_I(bit, t, f) SROOK_PP_IIF_II(SROOK_PP_IIF_ ## bit(t, f))
#   define SROOK_PP_IIF_II(id) id
#endif

#define SROOK_PP_IIF_0(t, f) f
#define SROOK_PP_IIF_1(t, f) t

#endif
