#ifndef INCLUDED_SROOK_ARRAY_VIEW_TEST_HPP
#define INCLUDED_SROOK_ARRAY_VIEW_TEST_HPP

#include <srook/cxx17/mpl/array_view.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/conjunction.hpp>
#include <srook/type_traits/add_const.hpp>
#include <srook/type_traits/is_default_constructible.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <type_traits>

#define ARRAY_VIEW_TEST int main(){}
static constexpr int test_data[] = { 2, 3, 4, 5, 6 };
using test_type1 = srook::array_view<test_data, sizeof(test_data) / sizeof(*test_data)>; // set element size
using test_type2 = srook::array_view<test_data>; // no set element size

#endif
