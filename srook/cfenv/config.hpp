// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CFENV_CONFIG_HPP
#define INCLUDED_SROOK_CFENV_CONFIG_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#ifdef __cplusplus
#   ifndef SROOK_NO_FENV_H
#       include <cfenv>
#   else
#       error This feature needs to cfenv
#   endif
#else
#   ifndef SROOK_NO_FENV_H
#       include <fenv.h>
#   else
#       error This feature needs to fenv.h
#   endif
#endif
#include <srook/config.hpp>

#endif
