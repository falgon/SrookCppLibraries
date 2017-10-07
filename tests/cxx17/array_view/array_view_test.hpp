#ifndef INCLUDED_SROOK_ARRAY_VIEW_TEST_HPP
#define INCLUDED_SROOK_ARRAY_VIEW_TEST_HPP

#include <srook/cxx17/mpl/array_view.hpp>
#include <srook/type_traits/integral_constant.hpp>
#include <srook/type_traits/is_same.hpp>
#include <srook/type_traits/conjunction.hpp>
#include <srook/type_traits/add_const.hpp>
#include <srook/type_traits/is_default_constructible.hpp>
#include <srook/type_traits/detail/logical.hpp>
#include <cassert>
#include <type_traits>

#define ARRAY_VIEW_TEST int main(){}
static SROOK_CONSTEXPR int test_data1[] = { 2, 3, 4, 5, 6 };
using test_type1 = srook::meta::array_view<test_data1, sizeof(test_data1) / sizeof(*test_data1)>; // set element size
using test_type2 = srook::meta::array_view<test_data1>; // no set element size

static SROOK_CONSTEXPR const char test_data2[] = "foo";
using test_type3 = srook::meta::array_view<test_data2, sizeof(test_data2) / sizeof(*test_data2)>;
using test_type4 = srook::meta::array_view<test_data2>;

#endif
