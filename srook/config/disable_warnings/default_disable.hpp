// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_DISABLE_WARNINGS_DEFAULT_DISABLES_HPP
#define INCLUDED_SROOK_CONFIG_DISABLE_WARNINGS_DEFAULT_DISABLES_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1400) 
#   pragma warning(disable:4996)
#endif

#if defined(__INTEL_COMPILER) || defined(__ICL)
#   pragma warning(disable:1786)
#endif

#endif
