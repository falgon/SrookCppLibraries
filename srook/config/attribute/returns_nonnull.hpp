// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_ATTRIBUTE_RETURNS_NONNULL_HPP
#define INCLUDED_SROOK_CONFIG_ATTRIBUTE_RETURNS_NONNULL_HPP

#if defined(__GNUC__) || defined(__clang__)
#	define SROOK_ATTRIBUTE_RETURNS_NONNULL __attribute__((returns_nonnull))
#else
#	define SROOK_ATTRIBUTE_RETURNS_NONNULL
#endif

#endif
