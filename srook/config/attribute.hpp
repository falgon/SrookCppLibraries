// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_HPP
#ifdef __GNUC__
#define SROOK_attribute_UNUSED [[gnu::unused]]
#else
#define SROOK_attribute_UNUSED [[maybe_unused]]
#endif
#endif
