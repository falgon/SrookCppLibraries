// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_FEATURE_DEDUCED_TYPENAME_HPP
#define INCLUDED_SROOK_CONFIG_FEATURE_DEDUCED_TYPENAME_HPP

#if (defined(_MSC_VER) && (_MSC_VER <= 1300)) || (defined(__BORLANDC__) && (__BORLANDC__ <= 0x551))
#    define SROOK_DEDUCED_TYPENAME
#else
#    define SROOK_DEDUCED_TYPENAME typename
#endif

#endif
