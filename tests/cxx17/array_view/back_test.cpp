#include "array_view_test.hpp"
ARRAY_VIEW_TEST
using namespace srook;

constexpr void test1()
{
	static_assert(
			test_type1::back() == 6 &&
			test_type1::back_v == 6 &&
			test_type1{}.instance_back() == 6
	);
}
