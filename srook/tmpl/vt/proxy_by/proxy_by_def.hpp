// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_TMPL_VT_PROXY_BY_PROXY_BY_DEF_HPP
#define INCLUDED_SROOK_TMPL_VT_PROXY_BY_PROXY_BY_DEF_HPP

#include <srook/tmpl/vt/detail/config.hpp>
#include <srook/preprocessor/concat.hpp>

#define SROOK_TMPL_VT_PROXY_BY_DEF(XXX_TYPE)\
    template <template <class...> class F> \
    struct SROOK_PP_CONCAT(proxy_by_, XXX_TYPE) { \
        template <class... Ts> \
        struct generate : \
            type_constant<SROOK_DEDUCED_TYPENAME F<Ts...>:: XXX_TYPE> {}; \
    }

#endif
