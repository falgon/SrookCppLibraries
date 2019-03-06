// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_NUMERIC_ALGORITHM_HPP
#define INCLUDED_SROOK_NUMERIC_ALGORITHM_HPP

#ifdef _MSC_VER
#   if _MSC_VER > 1000
#       pragma once
#   endif
#endif

#include <srook/numeric/algorithm/accumulate.hpp>
#include <srook/numeric/algorithm/inner_product.hpp>
#include <srook/numeric/algorithm/iota.hpp>
#include <srook/numeric/algorithm/correlation_coefficient.hpp>
#include <srook/math/geometry/algorithm/line/straight/least_squares.hpp>

SROOK_NESTED_NAMESPACE(srook, numeric, algorithm) {

using srook::math::geometry::algorithm::line::straight::least_squares;

} SROOK_NESTED_NAMESPACE_END(algorithm, numeric, srook)

#endif
