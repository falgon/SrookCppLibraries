// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_ALGORITHM_SEARCHING_DETAIL_CONFIG_HPP
#define INCLUDED_SROOK_ALGORITHM_SEARCHING_DETAIL_CONFIG_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/config.hpp>
#include <srook/cxx20/concepts/iterator/ForwardIterator.hpp>
#include <srook/iterator/range_iterator.hpp>

#ifdef BOOST_RANGE_BEGIN_HPP
#   ifndef SROOK_HAS_BOOST_RANGE_BEGIN_HPP
#       define SROOK_HAS_BOOST_RANGE_BEGIN_HPP 1
#   endif
#else
#   if !defined(SROOK_HAS_BOOST_RANGE_BEGIN_HPP) && SROOK_HAS_INCLUDE(<boost/range/begin.hpp>)
#       include <boost/range/begin.hpp>
#       define SROOK_HAS_BOOST_RANGE_BEGIN_HPP 1
#   else
#       define SROOK_HAS_BOOST_RANGE_BEGIN_HPP 0
#   endif
#endif

#ifdef BOOST_RANGE_END_HPP
#   ifndef SROOK_HAS_BOOST_RANGE_END_HPP
#       define SROOK_HAS_BOOST_RANGE_END_HPP 1
#   endif
#else
#   if !defined(SROOK_HAS_BOOST_RANGE_END_HPP) && SROOK_HAS_INCLUDE(<boost/range/end.hpp>)
#       include <boost/range/end.hpp>
#       define SROOK_HAS_BOOST_RANGE_END_HPP 1
#   else
#       define SROOK_HAS_BOOST_RANGE_END_HPP 0
#   endif
#endif

#endif
